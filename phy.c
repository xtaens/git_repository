/**
 * @file phy.c
 * @date 2007-Dez-4
 * @author S.Radtke
 * @c (C) 2007 Nanotron Technologies
 * @brief Functions for data transmission and reception.
 *
 * @note BuildNumber = "8350"
 *
 * @note This module contains all functions to operate the nanoLOC chip.
 */
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "phy.h"
#include "ntrxutil.h"
#include "nnspi.h"
#include "hwclock.h"
#include "ntrxranging.h"

#include "..\Application\delay.h"

#define DEVKIT201_CHANGE 1

/**
 * @def SendCfgUp
 * @brief Callback function of upper layer.
 *
 * This function is called when the physical layer wants to send configuration
 * data to the next upper layer. This define is used to be able to add
 * another layer.
 *
 */
#define SendCfgUp (*phySendMsgUp)

void NTRXInterrupt(void);

//extern RangingPIB rangingPIB;

extern void APLCallback(MsgT *msg);
callbackfn_t phySendMsgUp = &APLCallback;

/****************************************************************************
 *  Local stuff
 ****************************************************************************/
MsgT upMsg;                       /**< message struct for all received data. */
int16_t rcwd = 0;                 /**< retransmission counter for dynamic recalibration. */
uint32_t tiRecal;                 /**< timestamp of last calibration. */
uint32_t tiPhyRxTimeout;          /**< timestamp of last rx. */
bool_t tiPhyRxTimeout_once;       /**< report only once time */
volatile uint8_t txIrq;           /**< tx interrupt status register. */
volatile uint8_t rxIrq;           /**< rx interrupt status register. */
uint8_t lastArqCount;             /**< number of retransmissions of last transmitted message. */
MsgT *txSendMsg = NULL;           /**< pointer to store last transmitted message. */
bool_t  trxPollMode = TRUE;       /**< flag for irq polling. */
uint8_t buffSwapped = FALSE;      /**< swap buffer state for accessing the right memory block */
AddrT brdcAddr = PHY_BRDC_ADDR;   /**< broadcast address */
uint8_t last_frameType;           /**< last frameType */
uint8_t rxFrameType;

/** @brief structure for all layer configuration settings  */
PhyPIB phyPIB;

/**
 * @brief Initializing of module global variables.
 *
 * This function initializes all module global variables located in the
 * physical layers parameter information base (phyPIB). The nanoLOC chip
 * has to be already initialized and in ready (idle) mode. The receiver is started
 * and interrupts for CRC2 and Tx End and Rx End are enabled.
 *
 */
/****************************************************************************/
void PHYInit(void)
/****************************************************************************/
{
  phyPIB.currentChannel = PHY_CHANNEL_MIN;
  phyPIB.CAMode         = PHY_CCA_MODE_DEFAULT;
  phyPIB.titxstart      = 0;
  phyPIB.rxState        = PHY_TRX_OFF;
  phyPIB.rxOn           = FALSE;
  phyPIB.txPower        = RfTxOutputPower_DEFAULT;
  phyPIB.pwrDownMode    = 2;
  txSendMsg             = NULL;
  phyPIB.recalInterval  = CONFIG_NTRX_RECAL_DELAY;
  phyPIB.phyRxTimeout   = CONFIG_NTRX_PHY_RX_TIMEOUT;
  tiPhyRxTimeout        = hwclock() + phyPIB.phyRxTimeout;
  tiPhyRxTimeout_once   = FALSE;
  phyPIB.arqMax         = CONFIG_MAX_ARQ;
  phyPIB.testmode       = 0;
  phyPIB.fec            = FALSE;
  phyPIB.frameType      = last_frameType = PHY_FRAME_TYPE_DATA;
  phyPIB.ant            = 0;
  trxPollMode           = TRUE;
  buffSwapped           = FALSE;
  /*
    * Clear and reset all interrupt flags of the nanoLOC chip
    */
  ntrxShadowReg[NA_TxIntsReset_O] = 0x3f;
  ntrxShadowReg[NA_RxIntsReset_O] = 0x7f;
  /*
   * enable tx and rx interrupts
   */
  ntrxShadowReg[NA_RxIrqEnable_O] |= ((1 << NA_RxIrqEnable_B) | (1 << NA_TxIrqEnable_B));

  /*
     * enable CRC checks on received messages. This will cause corrupt frames to be droped
     * silently by the nanoLOC chip. The receiver is restarted automatically.
     */
  if ((ntrxShadowReg[NA_RxCrc2Mode_O] & (1 << NA_RxCrc2Mode_B)) !=  0)
  {
    ntrxShadowReg[NA_RxIntsEn_O] = (0x01 << NA_RxEnd_B);
  }
  else
  {
    ntrxShadowReg[NA_RxIntsEn_O] = ((0x01 << NA_RxEnd_B) | (0x01 << NA_RxOverflow_B));
  }
  ntrxShadowReg[NA_TxIntsEn_O] = (1 << NA_TxEnd_B);

  NTRXSPIWrite(NA_RxIrqEnable_O, ntrxShadowReg + 0x0f, 6);//地址0x0F，值0x03 3F 7F 00 04 04
  /*
   * initialize layer global variables
   */
  txIrqStatus = 0;
  rxIrqStatus = 0;
  txIrq = 0;
  rxIrq = 0;
  ntrxShadowReg[NA_TxIntsReset_O] = 0;
  ntrxShadowReg[NA_RxIntsReset_O] = 0;

  /*
   * start the receiver of the TRX chip
   */
  if (phyPIB.rxState == PHY_RX_ON)//不执行
  {
    NTRXRXEnable(TRUE);
  }

  ntrxState    = TxIDLE;

  NTRXRangingInit();
  #ifdef CONFIG_NTRX_IRQ
    NTRXIrqEnable( TRUE );
  #endif
}

/**
 * @brief This function send packets out.
 * @param *msg this is the message pointer
 *
 * This function is called ever on sending packets (e.g. PDSap).
 *
 */
/****************************************************************************/
void NTRXSendPacket(MsgT *msg)
/****************************************************************************/
{
  uint8_t txLen[2];

  /* if ntrx is in sleep mode, dont use ntrx */
  if (phyPIB.pwrDown == TRUE)
  {
    return;
  }

# ifdef CONFIG_NTRX_AUTO_RECALIB
  if (phyPIB.recalInterval != 0)
  {
    if (tiRecal < hwclock())
    {
      /* INFO: If the TRX sends a packet, calibration failes!
        * In this case rcwd is not reset, but tiRecal is.
        */
      /* normal operation mode */
      if (phyPIB.testmode == 0)
      {
        if (NTRXAllCalibration())
        {
          tiRecal = hwclock() + phyPIB.recalInterval;
          rcwd = 0;
        }
      }
    }
  }
# endif /* CONFIG_NTRX_AUTO_RECALIB */

  /* only messages with payload > 0 allowed, PDSap allready cover this! */
  if (msg->len == 0)
  {
    return;
  }

  /* check which buffer is free to transmit data */
  if (buffSwapped == TRUE)
  {
    /* write user data to transmit buffer in ntrx chip */
    NTRXSetIndexReg(2);
    NTRXSPIWrite((uint8_t)(NA_RamTxBuffer_O & 0xff), msg->data, (uint8_t)(msg->len & 0xff));
  }
  else
  {
    /* write user data to transmit buffer in ntrx chip */
    NTRXSetIndexReg(3);
    NTRXSPIWrite((uint8_t)(NA_RamTxBuffer_O & 0xff), msg->data, (uint8_t)(msg->len & 0xff));
  }

  NTRXSetIndexReg(0);
  NTRXSPIWrite(NA_RamTxDstAddr_O, msg->addr, 6);

  if (memcmp(brdcAddr, msg->addr, 6) == 0)
  {
    msg->prim = PHY_FRAME_TYPE_BRDC;
  }

  switch (msg->prim)
  {
    case PD_TIMEB_REQUEST:
      /*special treatment for frame type TimeB*/
      last_frameType = phyPIB.frameType; /* backup of the frame type */
      phyPIB.frameType = PHY_FRAME_TYPE_TIMEB;
      ntrxShadowReg[NA_TxPacketType_O] &= (uint8_t)(~(0x0F));
      ntrxShadowReg[NA_TxPacketType_O] |= phyPIB.frameType;
      NTRXSPIWriteByte(NA_TxPacketType_O , ntrxShadowReg[NA_TxPacketType_O]);

      /*enable RTC auto mode temporarily in order to transmit current RTC to remotes*/
      NTRXSPIWriteByte(NA_RtcTimeBAutoMode_O, (uint8_t)(ntrxShadowReg[NA_RtcTimeBAutoMode_O] | (1 << NA_RtcTimeBAutoMode_B)));

      PHY_DEBUG("frame type : TIMEB\r\n");

      ntrxShadowReg[NA_TxArq_O] &= (uint8_t)(~(1 << NA_TxArq_B));
      NTRXSPIWriteByte(NA_TxArq_O, ntrxShadowReg[NA_TxArq_O]);
      break;

    case PHY_FRAME_TYPE_BRDC:
      /*special treatment for frame type broadcast*/
      last_frameType = phyPIB.frameType; /* backup of the frame type */
      phyPIB.frameType = PHY_FRAME_TYPE_BRDC;
      ntrxShadowReg[NA_TxPacketType_O] &= (uint8_t)(~(0x0F));
      ntrxShadowReg[NA_TxPacketType_O] |= phyPIB.frameType;
      NTRXSPIWriteByte(NA_TxPacketType_O , ntrxShadowReg[NA_TxPacketType_O]);

      PHY_DEBUG("frame type : BRDC\r\n");

      ntrxShadowReg[NA_TxArq_O] &= (uint8_t)(~(1 << NA_TxArq_B));
      NTRXSPIWriteByte(NA_TxArq_O, ntrxShadowReg[NA_TxArq_O]);
      break;

    default:
      break;
  }


  /* TODO DEBUG REMOVE */
  PHY_DEBUG("send : ");
  {
    uint8_t o;
    for (o = 0; o < msg->len; o++)
    {
      PHY_DEBUG("0x%X ", (uint16_t) msg->data[o]);
    }
    PHY_DEBUG("\r\n");
  }


  /* TODO DEBUG REMOVE */
  PHY_DEBUG("dest MAC : ");
  {
    uint8_t a;
    for (a = 0; a < sizeof(AddrT); a++)
    {
      PHY_DEBUG("0x%X ", (uint16_t) msg->addr[a]);
    }
    PHY_DEBUG("\r\n");
  }


  /* packet length max. CONFIG_MAX_PACKET_SIZE byte */
  txLen[0] = (uint8_t)((msg->len > CONFIG_MAX_PACKET_SIZE) ? CONFIG_MAX_PACKET_SIZE : msg->len);
  /* headerbits for identify data or rangingpackets (xxx- ----) */
  txLen[1] = (uint8_t)((msg->attribute << 5) & 0xE0);

  NTRXSPIWrite(NA_RamTxLength_O, txLen, 2);
  ntrxState = TxSEND;

  /* reset bit 1,2 */
  ntrxShadowReg[NA_TxPhCarrSenseMode_O] &= (uint8_t)(~(0x03 << NA_TxPhCarrSenseMode_LSB));

  /* set bit 1,2 with CAMode */
  ntrxShadowReg[NA_TxPhCarrSenseMode_O] |= (uint8_t)(phyPIB.CAMode << NA_TxPhCarrSenseMode_LSB);

  /* write to nanoLOC */
  NTRXSPIWriteByte(NA_TxPhCarrSenseMode_O, ntrxShadowReg[NA_TxPhCarrSenseMode_O]);

  if (phyPIB.CAMode != PHY_CCA_OFF)
  {
    PHY_DEBUG("CSMA enabled\r\n");
    phyPIB.titxstart = hwclock();
  }

  /* mark buffers as valid and start transmission */
  NTRXSPIWriteByte(NA_TxBufferCmd_O, (1 << NA_TxCmdStart_B) | (0x03 << NA_TxBufferCmd_LSB));
  //TRIGGER_LED_TX();

  txSendMsg = msg;

  do
  {
    PHYPoll();
  }
  while (ntrxState != TxIDLE);
}

/**
 * @brief This function processes all data request.
 * @param *msg this is the message pointer
 *
 * This function represents the service access point for data requests and
 * ranging requests. When the primitive is set to @em PD_DATA_REQUEST all
 * necessary actions are taken to copy the payload to the nanoLOC chip
 * and set the MAC header parameter in the corresponding registers.
 * When all this is done the transmission will be initiated.
 * In case of a transmission in progress, @em PDSap will reject the message
 * and indicate a failure with the status @em PHY_BUSY_TX.
 *
 */
/****************************************************************************/
void PDSap(MsgT *msg)
/****************************************************************************/
{

  /* if ntrx is in sleep mode, dont use ntrx */
  if (phyPIB.pwrDown == TRUE)
  {
    return;
  }

  /*
   * check the message length. If the message length is bigger than
   * the allowed buffer size the packet will be rejected.
   */
  if (msg->len > CONFIG_MAX_PACKET_SIZE)
  {
    PHY_DEBUG("packet size > %d\r\n", CONFIG_MAX_PACKET_SIZE);
    msg->prim = PD_DATA_CONFIRM;
    msg->status = PHY_INVALID_PARAMETER;
    msg->pdu = msg->data;
    SendMsgUp(msg);
    return;
  }

  switch (msg->prim)
  {
    case PD_TIMEB_REQUEST :
    case PD_DATA_REQUEST :
      /* transmitter still busy */
      if (txSendMsg != NULL)
      {
        PHY_DEBUG("busy tx\r\n");
        msg->prim = PD_DATA_CONFIRM;
        msg->status = PHY_BUSY_TX;
        msg->pdu = msg->data;
        SendMsgUp(msg);
        return;
      }

      if (msg->len == 0)
      {
        PHY_DEBUG("packet length <= 0\r\n");
        msg->prim = PD_DATA_CONFIRM;
        msg->status = PHY_INVALID_PARAMETER;
        msg->pdu = msg->data;
        SendMsgUp(msg);
        return;
      }

      msg->attribute = MSG_TYPE_DATA;
      NTRXSendPacket(msg);
      break;

    case PD_RANGING_REQUEST :

      NTRXRangingRequest(msg);

      break;

    default:
      break;
  }
}

/**
 * @brief Helper function to switch off test modes.
 *
 * This function switches off a previously enabled test mode.
 * Note: Only one test mode at a time can be enabled.
 */
/****************************************************************************/
void TestmodeOff(void)
/****************************************************************************/
{
  switch (phyPIB.testmode)
  {
    case PHY_CONTINUOUS_MODE:
      NTRXSetTestChirpMode(FALSE);
      break;

    case PHY_CARRIER_MODE:
      NTRXSetTestCarrierMode(FALSE);
      break;

    default:
      break;
  }
}

/**
 * @brief Physical layer management entety
 * @param *msg this is the the message struct
 *
 * This function represents the service access point to configure the
 * physical layer. All configuration parameters are stored in the physical layer
 * parameter information base @em phyPIB. This function hides all necessarey steps
 * to enable or disable certain features. With this function it is possible to set values but
 * also to query the following settings:
 *
 * @ref PHY_CURRENT_CHANNEL : the channel is a transmission mode defined in PHY_TRX_MODE
 * @ref PHY_TRX_MODE : a set of three parameters bandwidth, symbol duration and symbol rate
 * @ref PHY_LOG_CHANNEL : is a predefined group of chip settings
 * @ref PHY_TX_POWER : output power setting [ 0 - 63 ]
 * @ref PHY_ARQ : hardware acknowledgement
 * @ref PHY_FEC : forward error correction
 * @ref PHY_MAC_ADDRESS1 : 1st MAC address for address matching
 * @ref PHY_MAC_ADDRESS2 : 2nd MAC address for address matching
 * @ref PHY_TX_ADDR_SELECT : select the MAC address as sender address
 * @ref PHY_ADDR_MATCHING : address matching or promiscuous mode
 * @ref PHY_PWR_DOWN_MODE : set operational mode
 * @ref PHY_RECALIBRATION : recalibration interval
 * @ref PHY_FRAME_TYPE : set frame types that will be handled by the nanoLOC chip
 */
/****************************************************************************/
void PLMESap(MsgT *msg)
/****************************************************************************/
{
  uint8_t bw = 0, sd = 0, br = 0, cf = 0, tuned = 0;

  /* if ntrx is in sleep mode, dont use ntrx */
  if (phyPIB.pwrDown == TRUE)
  {
    return;
  }

  switch (msg->prim)
  {
    case PLME_GET_REQUEST:
      msg->prim = PLME_GET_CONFIRM;
      msg->status = PHY_SUCCESS;
      switch (msg->attribute)
      {
        case PHY_CURRENT_CHANNEL:
          msg->value = phyPIB.currentChannel;
          break;

        case PHY_TRX_MODE:
          msg->value = phyPIB.trxMode;
          break;

        case PHY_LOG_CHANNEL:
          msg->value = phyPIB.logChannel;
          break;

        case PHY_TX_POWER:
          msg->value = phyPIB.txPower;
          break;

        case PHY_ARQ:
          msg->value = phyPIB.arqMode;
          break;

        case PHY_ARQ_MAX:
          msg->value = phyPIB.arqMax;
          break;

        case PHY_FEC:
          msg->value = phyPIB.fec;
          break;

        case PHY_MAC_ADDRESS1:
          memcpy(msg->data, phyPIB.macAddr0, 6);
          break;

        case PHY_MAC_ADDRESS2:
          memcpy(msg->data, phyPIB.macAddr0, 6);
          break;

        case PHY_TX_ADDR_SELECT:
          msg->value = phyPIB.txAddrSel;
          break;

        case PHY_ADDR_MATCHING:
          msg->value = phyPIB.addrMatch;
          break;

        case PHY_PWR_DOWN_MODE:
          msg->value = phyPIB.pwrDownMode;
          break;

        case PHY_RECALIBRATION:
          msg->value = (uint16_t)(phyPIB.lastRecalibration / 1000);
          break;

        case PHY_RECAL_INTERVAL:
          msg->value = (uint16_t)(phyPIB.recalInterval / 1000);
          break;

        case PHY_FRAME_TYPE:
          msg->value = phyPIB.frameType;
          break;

        case PHY_TESTMODE:
          msg->value = phyPIB.testmode;
          break;

        case PHY_RX_STATE:
          msg->value = phyPIB.rxState;
          break;

        case PHY_RSSI:
          msg->value = NTRXGetRssi();
          break;

        default:
          msg->status = PHY_UNSUPPORTED_ATTRIBUTE;
          break;
      }
      msg->pdu = msg->data;
      SendCfgUp(msg);
      break;

    case PLME_SET_REQUEST:
      msg->prim = PLME_SET_CONFIRM;
      msg->status = PHY_SUCCESS;
      switch (msg->attribute)
      {
        case PHY_CCA_MODE:
          if (msg->value > 3)
          {
            msg->status = PHY_INVALID_PARAMETER;
            phyPIB.CAMode = PHY_CCA_OFF;
          }
          else
          {
            phyPIB.CAMode = (uint8_t)(msg->value);
          }
          break;
        case PHY_CURRENT_CHANNEL:
          if (msg->value > 16)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {
            phyPIB.currentChannel = (uint8_t)(msg->value);
            switch (phyPIB.currentChannel)
            {
              case 0:
                bw = NA_80MHz;
                sd = NA_1us;
                br = NA_1M_S;
                break;
              default:
                bw = NA_22MHz;
                sd = NA_4us;
                br = NA_250k_S;
                break;
            }
            NTRXSetChannel(phyPIB.currentChannel);
            NTRXSetupTrxMode(bw, sd, br);
          }
          break;

        case PHY_LOG_CHANNEL:
          if (msg->value > CONFIG_MAX_LOG_CHANNEL - 1)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {
            phyPIB.logChannel = (uint8_t)(msg->value);
            switch (phyPIB.logChannel)
            {
              case 1:
                bw = NA_22MHz;
                sd = NA_4us;
                br = NA_250k_S;
                cf = 1;
                ntrxShadowReg[NA_UseFec_O] &= (uint8_t)(~(1 << NA_UseFec_B));
                break;

              case 2:
                bw = NA_22MHz;
                sd = NA_4us;
                br = NA_250k_S;
                cf = 7;
                ntrxShadowReg[NA_UseFec_O] &= (uint8_t)(~(1 << NA_UseFec_B));
                break;

              case 3:
                bw = NA_22MHz;
                sd = NA_4us;
                br = NA_250k_S;
                cf = 13;
                ntrxShadowReg[NA_UseFec_O] &= (uint8_t)(~(1 << NA_UseFec_B));
                break;

              default:
                bw = NA_80MHz;
                sd = NA_1us;
                br = NA_1M_S;
                cf = 0;
                ntrxShadowReg[NA_UseFec_O] &= (uint8_t)(~(1 << NA_UseFec_B));
                break;
            }
            NTRXSPIWriteByte(NA_UseFec_O, ntrxShadowReg[NA_UseFec_O]);
            NTRXSetChannel(cf);
            NTRXSetupTrxMode(bw, sd, br);
          }
          break;

        case PHY_TRX_MODE:
          phyPIB.trxMode = (uint8_t)(msg->value);
          switch (msg->value)
          {
#                                   ifdef CONFIG_NTRX_80MHZ_1000NS
            case 21:
              bw = NA_80MHz;
              sd = NA_1us;
              br = NA_1M_S;
              break;
#                                   ifdef DEVKIT201_CHANGE
            case 23:
              bw = NA_80MHz;
              sd = NA_1us;
              br = NA_1M_S;
              tuned = 1;
              break;
#                                   endif /* DEVKIT201_CHANGE */
#                                   endif /* CONFIG_NTRX_80MHZ_1000NS */

#                                   ifdef CONFIG_NTRX_80MHZ_4000NS
            case 41:
              bw = NA_80MHz;
              sd = NA_4us;
              br = NA_250k_S;
              break;
#                                   endif /* CONFIG_NTRX_80MHZ_4000NS */

#                                   ifdef CONFIG_NTRX_22MHZ_4000NS
            case 71:
              bw = NA_22MHz;
              sd = NA_4us;
              br = NA_250k_S;
              break;
#                                   endif /* CONFIG_NTRX_22MHZ_4000NS */

            default:
              PHY_DEBUG("Valid modes: 10-43 (80Mhz) 50-84 (22Mhz) 90-93 (22HR)\r\n");
              msg->status = PHY_INVALID_PARAMETER;
              msg->pdu = msg->data;
              SendCfgUp(msg);
              return;
          }
#                                 ifdef DEVKIT201_CHANGE
          if (bw == NA_80MHz)
          {
            if (tuned == 0)
            {
              NTRXSetChannel(17);
            }
            else
            {
              NTRXSetChannel(0);
            }
          }
#                                 endif
          NTRXSetupTrxMode(bw, sd, br);

          switch (bw)
          {
            case NA_80MHz:
              PHY_DEBUG("New Mode 80 Mhz ");
              break;
            case NA_22MHz:
              PHY_DEBUG("New Mode 22 Mhz ");
              break;
            default:
              PHY_DEBUG("Unknown mode ??? ");
              break;
          }
          switch (sd)
          {
            case NA_1us:
              PHY_DEBUG("1 us, ");
              break;
            case NA_4us:
              PHY_DEBUG("4 us, ");
              break;
            default:
              break;
          }
          switch (br)
          {
            case NA_250k_S:
              PHY_DEBUG("250 kSym\r\n");
              break;
            case NA_1M_S:
              PHY_DEBUG("1 MSym\r\n");
              break;
            default:
              break;
          }
          break;

        case PHY_TX_POWER:
          if (msg->value > 63)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {
            phyPIB.txPower = (uint8_t)((msg->value) & 0x3f);
            ntrxShadowReg[NA_TxOutputPower0_O] &= (uint8_t)(~(0x3f << NA_TxOutputPower0_LSB));
            ntrxShadowReg[NA_TxOutputPower0_O] |= (uint8_t)(phyPIB.txPower << NA_TxOutputPower0_LSB);
            if (phyPIB.txPower != 0x3f)
            {
              /* This way no table for the transmission output power is necessary */
              ntrxShadowReg[NA_TxOutputPower0_O] &= (uint8_t)(~(1 << NA_TxOutputPower0_LSB));
            }
            NTRXSPIWriteByte(NA_TxOutputPower0_O, ntrxShadowReg[NA_TxOutputPower0_O]);

            ntrxShadowReg[NA_TxOutputPower1_O] &= (uint8_t)(~(0x3f << NA_TxOutputPower1_LSB));
            ntrxShadowReg[NA_TxOutputPower1_O] |= (uint8_t)((phyPIB.txPower << NA_TxOutputPower1_LSB));
            if (phyPIB.txPower != 0x3f)
            {
              /* This way no table for the transmission output power is necessary */
              ntrxShadowReg[NA_TxOutputPower1_O] &= (uint8_t)(~(1 << NA_TxOutputPower1_LSB));
            }
            NTRXSPIWriteByte(NA_TxOutputPower1_O, ntrxShadowReg[NA_TxOutputPower1_O]);
          }
          break;

        case PHY_ARQ:
          NTRXRXEnable(FALSE);
          if (msg->value == 0)
          {
            ntrxShadowReg[NA_TxArq_O] &= (uint8_t)(~(1 << NA_TxArq_B));
            ntrxShadowReg[NA_RxArqMode_O] &= (uint8_t)(~((0x03 << NA_RxArqMode_LSB)
                                             | (1 << NA_RxCrc2Mode_B)));
          }
          else
          {
            ntrxShadowReg[NA_TxArq_O] |= (1 << NA_TxArq_B);
            ntrxShadowReg[NA_RxArqMode_O] |= ((NA_RxArqModeCrc2_VC_C << NA_RxArqMode_LSB)
                                              | (NA_RxCrc2ModeTrigOn_BC_C << NA_RxCrc2Mode_B));
          }
          NTRXSPIWriteByte(NA_TxArq_O, ntrxShadowReg[NA_TxArq_O]);
          NTRXSPIWriteByte(NA_RxArqMode_O, ntrxShadowReg[NA_RxArqMode_O]);
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;

        case PHY_ARQ_MAX:
          if (msg->value > 14)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {
            NTRXRXEnable(FALSE);
            phyPIB.arqMax = (uint8_t)(msg->value);
            if (phyPIB.arqMax == 0)
            {
              ntrxShadowReg[NA_TxArqMax_O] &= (uint8_t)(~(0x0f << NA_TxArqMax_LSB));
            }
            else
            {
              ntrxShadowReg[NA_TxArqMax_O] &= (uint8_t)(~(0x0f << NA_TxArqMax_LSB));
              ntrxShadowReg[NA_TxArqMax_O] |= ((uint8_t)(msg->value << NA_TxArqMax_LSB));
            }
            NTRXSPIWriteByte(NA_TxArqMax_O, ntrxShadowReg[NA_TxArqMax_O]);
            if (phyPIB.rxState == PHY_RX_ON)
            {
              NTRXRXEnable(TRUE);
            }
          }
          break;

        case PHY_FEC:
          NTRXRXEnable(FALSE);
          if (msg->value == TRUE)
          {
            ntrxShadowReg[NA_UseFec_O] |= (1 << NA_UseFec_B);//不执行
          }
          else
          {
            ntrxShadowReg[NA_UseFec_O] &= (uint8_t)(~(1 << NA_UseFec_B));
          }
          NTRXSPIWriteByte(NA_UseFec_O, ntrxShadowReg[NA_UseFec_O]);//地址0x49，值0x00

          phyPIB.fec = (uint8_t)(msg->value);
          modeSet.fec = (uint8_t)(msg->value);

          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);//不执行
          }
          break;

        case PHY_MAC_ADDRESS1:
          NTRXRXEnable(FALSE);
          memcpy(phyPIB.macAddr0, msg->data, 6);
          NTRXSetIndexReg(0);
          NTRXSPIWrite(NA_RamStaAddr0_O, msg->data , 6);//地址0x80，值卡号+xxx
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;

        case PHY_MAC_ADDRESS2:
          NTRXRXEnable(FALSE);
          memcpy(phyPIB.macAddr1, msg->data, 6);
          NTRXSetIndexReg(0);
          NTRXSPIWrite(NA_RamStaAddr1_O, msg->data, 6);
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;

        case PHY_TX_ADDR_SELECT:
          NTRXRXEnable(FALSE);
          phyPIB.txAddrSel = (uint8_t)(msg->value);
          if (msg->value == 0)
          {
            ntrxShadowReg[NA_TxAddrSlct_O] &= (uint8_t)(~(1 << NA_TxAddrSlct_B));
          }
          else
          {
            ntrxShadowReg[NA_TxAddrSlct_O] |= (1 << NA_TxAddrSlct_B);
          }
          NTRXSPIWriteByte(NA_TxAddrSlct_O, ntrxShadowReg[NA_TxAddrSlct_O]);
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;

        case PHY_ADDR_MATCHING:
          NTRXRXEnable(FALSE);
          phyPIB.addrMatch = (uint8_t)(msg->value);
          if (msg->value == 0)
          {
            /* promiscuous mode */
            ntrxShadowReg[NA_RxAddrMode_O] &= (uint8_t)(~(1 << NA_RxAddrMode_B));
          }
          else
          {
            ntrxShadowReg[NA_RxAddrMode_O] |= (1 << NA_RxAddrMode_B);
          }
          NTRXSPIWriteByte(NA_RxAddrMode_O, ntrxShadowReg[NA_RxAddrMode_O]);
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;

        case PHY_RECALIBRATION:
          if (NTRXAllCalibration())
          {
            phyPIB.lastRecalibration = hwclock();
            tiRecal = hwclock() + phyPIB.recalInterval;
            rcwd = 0;
          }
          else
          {
            msg->status = PHY_BUSY_RX;
          }
          break;

        case PHY_RECAL_INTERVAL:        /* delay time for recalibration */
          phyPIB.recalInterval = msg->value * 1000;
          break;

        case PHY_RTC:
          /*no TimeB pending and no incoming/outgoing traffic?*/
          // if ((port->rtcCommit) && (port->ntrxState == TxIDLE))
          /*TODO
          - Monitor TimeB reception state,
          - Do not read RTC while non-auto TimeB packet reception pending.
          */
          if (ntrxState == TxIDLE)
          {
            /*disable receiver*/
            //bool_t lastRxState = phyPIB.rxOn;
            bool_t lastRxState = ((phyPIB.rxOn >0) ? TRUE:FALSE);

            NTRXRXEnable(FALSE);

            NTRXSPIWriteByte(NA_RtcCmdRd_O, (uint8_t)(ntrxShadowReg[NA_RtcCmdRd_O] | (1 << NA_RtcCmdRd_B)));
            //delay_nus(70);

            //2015-04-01
            delay_nus(30);
            NTRXSPIRead(NA_RamRtcReg_O, msg->data, 6);
            msg->len = 6;

            /*restore receiver state */
            NTRXRXEnable(lastRxState);
          }
          else
          {
            /*RTC read failed*/
            PHY_DEBUG("PHY error: PHY busy, cannot read RTC right now!\r\n");
            PHY_DEBUG("ntrxState = %i\r\n", ntrxState);
            memset(msg->data, 0, 6);
            msg->len = 0;
            msg->status = PHY_BUSY;
          }
          break;

        case PHY_PWR_DOWN_MODE:
          if (msg->value > 1)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {

            PHY_DEBUG("PowerDown : %ld\r\n", *(uint32_t *)(msg->data));
            trxPollMode = (bool_t)((phyPIB.recalInterval == 0) ? FALSE : TRUE);
            phyPIB.pwrDownMode = (uint8_t)(msg->value);
            NTRXPowerdownMode((uint8_t)(msg->value), *(uint32_t *)(msg->data));
            phyPIB.pwrDown = TRUE;
          }
          break;
        case PHY_POWERDOWN_PAD_MODE:
          if (msg->value == 0)
          {
            NTRXPowerupFromPadMode();
            trxPollMode = TRUE;
            phyPIB.pwrUp = FALSE;
            phyPIB.pwrDown = FALSE;
            if (phyPIB.rxState == PHY_RX_ON)
            {
              NTRXRXEnable(TRUE);
            }
          }
          else
          {
            // do not poll nanoLOC while in sleep mode
            NTRXPowerdownModeDIO(1, (uint8_t)(msg->value - 1));
            trxPollMode = FALSE;
            phyPIB.pwrDown = TRUE;
          }
          break;

        case PHY_FRAME_TYPE:
          phyPIB.frameType = (uint8_t)(msg->value & 0x0F);
          ntrxShadowReg[NA_TxPacketType_O] &= (uint8_t)(~(0x0F));
          ntrxShadowReg[NA_TxPacketType_O] |= phyPIB.frameType;
          NTRXSPIWriteByte(NA_TxPacketType_O , ntrxShadowReg[NA_TxPacketType_O]);
          last_frameType = phyPIB.frameType; /* set both even to prevent resetting the frametype after sending a packet */
          break;

        case PHY_TESTMODE:
          if (msg->value > 2)
          {
            msg->status = PHY_INVALID_PARAMETER;
          }
          else
          {
            switch (msg->value)
            {
              case 1:
                TestmodeOff();
                NTRXSetTestChirpMode(TRUE);
                /* this blocks the transmission path of the PDSap */
                txSendMsg = &upMsg;
                break;

              case 2:
                TestmodeOff();
                NTRXSetTestCarrierMode(TRUE);
                /* this blocks the transmission path of the PDSap */
                txSendMsg = &upMsg;
                break;

              default:/* this enables the transmission path of the PDSap */
                TestmodeOff();
                txSendMsg = NULL;
            }

            phyPIB.testmode = (uint8_t)(msg->value);

          }
          break;

        case PHY_RX_CMD:
          switch (msg->value)
          {
            case PHY_TRX_OFF:
            case PHY_RX_ON:
              phyPIB.rxState = (uint8_t)(msg->value);
              /*stop the receiver and clear the buffers */
              NTRXRXEnable(FALSE);

              /* clear interrupts */
              NTRXSPIWriteByte(NA_RxIntsReset_O, 0x7F);//地址0x11，值0x7F
              rxIrq = 0;
#                                             ifdef CONFIG_NTRX_SNIFFER
              upMsg.count = 0;
#                                             endif
              if (msg->value == PHY_RX_ON)
              {
                NTRXRXEnable(TRUE);
              }

              break;

            default:
              msg->status = PHY_INVALID_PARAMETER;
              break;
          }
          break;

        case PHY_RX_STATE:
          switch (msg->value)
          {
            case PHY_RX_ON:
            case PHY_TRX_OFF:
              phyPIB.rxState = (uint8_t)(msg->value);
              break;

            default:
              msg->status = PHY_INVALID_PARAMETER;
              break;
          }
          break;

        case PHY_SYNCWORD:

          NTRXRXEnable(FALSE);
          memcpy(phyPIB.syncword, (uint8_t *)(msg->data), 8);
          NTRXSetSyncWord(phyPIB.syncword);
          if (phyPIB.rxState == PHY_RX_ON)
          {
            NTRXRXEnable(TRUE);
          }
          break;
        case PHY_RTC_AUTOMODE:
          ntrxShadowReg[NA_RtcTimeBAutoMode_O] &= (uint8_t) ~(1 << NA_RtcTimeBAutoMode_B);

          if (msg->value == TRUE)
          {
            ntrxShadowReg[NA_RtcTimeBAutoMode_O] |= (uint8_t)(1 << NA_RtcTimeBAutoMode_B);
          }

          NTRXSPIWriteByte(NA_RtcTimeBAutoMode_O, ntrxShadowReg[NA_RtcTimeBAutoMode_O]);
          break;

        default:
          msg->status = PHY_UNSUPPORTED_ATTRIBUTE;
          break;
      }
      msg->pdu = msg->data;
      //SendCfgUp (msg);
      break;

    default:
      break;
  }
  /* ieee config stuff */
}

/**
 * @brief Callback function for received messages
 *
 * This function reads out the payload of a received message and
 * calls the upper layer/application
 *
 */
/****************************************************************************/
void PDCallback(void)
/****************************************************************************/
{
  uint8_t       status;
  uint8_t       reg[2];
  uint8_t header_bits;

  /* on packet reception the rx is switched off automaticly from hardware */
  phyPIB.rxOn = FALSE;

  /*
   * read the crc2 status register
   */
  NTRXSPIReadByte(NA_RxCrc2Stat_O, &status);
  rxIrq = 0;

  /* check if data is valid */
  if ((status & (1 << NA_RxCrc2Stat_B)) != 0)
  {
    NTRXSetIndexReg(0);
    /* read source address */
    NTRXSPIRead(NA_RamRxSrcAddr_O, upMsg.addr, 6);
    /* read length plus additionl bits */
    NTRXSPIRead(NA_RamRxLength_O, reg, 2);

    header_bits = (uint8_t)(reg[1] >> 5);

    /* read destination address */
#ifdef CONFIG_NTRX_SNIFFER
    NTRXSPIRead(NA_RamRxDstAddr_O, upMsg.rxAddr, 6);
    upMsg.count++;
    upMsg.extBits = header_bits;
    upMsg.frameType = (status & 0x0f);
#endif
    rxFrameType = (uint8_t)(status & 0x0f);

    upMsg.len = reg[0];
    if (upMsg.len > CONFIG_MAX_PACKET_SIZE)
    {
      /* restart receiver */
      if (phyPIB.rxState == PHY_RX_ON)
      {
        NTRXRXEnable(TRUE);
      }
    }
    else
    {

      if (buffSwapped == TRUE)
      {
        buffSwapped = FALSE;
        /* SWAP BUFFER for receive*/
        ntrxShadowReg[NA_SwapBbBuffers_O] &= (uint8_t)(~(1 << NA_SwapBbBuffers_B));
        NTRXSPIWriteByte(NA_SwapBbBuffers_O, ntrxShadowReg[NA_SwapBbBuffers_O]);

        NTRXSetIndexReg(3);
      }
      else
      {
        buffSwapped = TRUE;
        /* SWAP BUFFER for receive*/
        ntrxShadowReg[NA_SwapBbBuffers_O] |= (1 << NA_SwapBbBuffers_B);
        NTRXSPIWriteByte(NA_SwapBbBuffers_O, ntrxShadowReg[NA_SwapBbBuffers_O]);

        NTRXSetIndexReg(2);
      }

      tiPhyRxTimeout_once = FALSE;
      tiPhyRxTimeout = hwclock() + phyPIB.phyRxTimeout;

      /*
       * restart receiver and than read rx buffer. This is ok because we use
       * buffer swapping.
       */
      if (phyPIB.rxState == PHY_RX_ON)
      {
        NTRXRXEnable(TRUE);
      }

      NTRXSPIRead((uint8_t)(NA_RamRxBuffer_O & 0xFF), upMsg.data, upMsg.len);
      NTRXSetIndexReg(0);
#ifdef    CONFIG_NTRX_SNIFFER
      upMsg.value = 0xff;
      upMsg.prim = PD_DATA_INDICATION;
      upMsg.pdu = upMsg.data;
      SendMsgUp(&upMsg);
#else

#if PDCallback_DEBUG > 0
      PHY_DEBUG("PDCallback (%d) : ", (uint16_t) header_bits);
      {
        uint8_t o;
        for (o = 0; o < upMsg.len; o++)
        {
          PHY_DEBUG("0x%X ", (uint16_t) upMsg.data[o]);
        }
      }
      PHY_DEBUG("\r\n");
#endif
      /*
       * if address matching off, ignore rangingstates
       * this path is used for normal data reception
       * ranging is handled in the else path
       */
      if (((ntrxShadowReg[NA_RxAddrMode_O] & (1 << NA_RxAddrMode_B)) == 0) || (header_bits != MSG_TYPE_RANGING))
      {
        switch (rxFrameType)
        {
          case PHY_FRAME_TYPE_TIMEB:
            /*read out received TimeB value*/
            NTRXSPIRead(NA_RamRtcRx_O, upMsg.rxTimeB, 6);
            upMsg.prim = PD_TIMEB_INDICATION;
            break;

          case PHY_FRAME_TYPE_BRDC:
            upMsg.prim = PD_BRDC_INDICATION;
            break;

          default:
            upMsg.prim = PD_DATA_INDICATION;
            break;
        }

        upMsg.value = 0xff;
        upMsg.pdu = upMsg.data;
        SendMsgUp(&upMsg);
      }
      else
      {
        NTRXRangingRX(&upMsg);
      }
#endif /* CONFIG_NTRX_SNIFFER */
    }
  }
  else
  {
    /* restart receiver */
    if (phyPIB.rxState == PHY_RX_ON)
    {
      NTRXRXEnable(TRUE);
    }
  }
}

/**
 * @brief polls the nanoLOC chip for incomming messages
 *
 * This function is the main part of the the physical layer. It processes
 * all interrupt flags and supervises the periodic recalibration.
 *
 */
/***************************************************************************/
void PHYPoll(void)
/***************************************************************************/
{
  uint8_t arqCount;
  MsgT *tMsg;

  /* if ntrx is in sleep mode, dont use ntrx */
  if (phyPIB.pwrDown == TRUE)
  {
    return;
  }

  if ((phyPIB.CAMode != PHY_CCA_OFF) && (ntrxState == TxSEND) && (hwclock() > phyPIB.titxstart + TO_CSMA))
  {
    PHY_DEBUG("CSMA Timeout\r\n");

    /* cancel transmission */
    NTRXSPIWriteByte(NA_TxBufferCmd_O, (1 << NA_TxCmdStop_B));

    /* disable csma/cca */
    ntrxShadowReg[NA_TxPhCarrSenseMode_O] &= (uint8_t)(~(0x03 << NA_TxPhCarrSenseMode_LSB));
    NTRXSPIWriteByte(NA_TxPhCarrSenseMode_O, ntrxShadowReg[NA_TxPhCarrSenseMode_O]);

    /* mark buffers as valid and start transmission again */
    NTRXSPIWriteByte(NA_TxBufferCmd_O, (1 << NA_TxCmdStart_B) | (0x03 << NA_TxBufferCmd_LSB));
  }

  #ifdef CONFIG_NTRX_IRQ
    ENTER_TASK;
    nnIrq = 0;
    LEAVE_TASK;
  #endif

  if (tiPhyRxTimeout < hwclock() && tiPhyRxTimeout_once == FALSE)
  {
    tiPhyRxTimeout_once = TRUE;

    upMsg.prim = PD_STATUS_INDICATION;
    upMsg.attribute = PHY_RX_TIMEOUT;
    upMsg.pdu = upMsg.data;
    SendMsgUp(&upMsg);
  }

  #ifndef CONFIG_NTRX_IRQ
    if (trxPollMode == TRUE)
    {
      NTRXInterrupt ();
    }
  #endif

  if (ntrxState == TxWAIT)
  {
    /*
    * get number of transmissions needed to last message
    * This information is used to determine if the last
    * transmission was successfull or failed.
    */
    NTRXSPIReadByte(NA_TxArqCnt_O, &arqCount);
    arqCount &= 0x0F;

    if (arqCount > phyPIB.arqMax)
    {
      #ifdef CONFIG_NTRX_AUTO_RECALIB
      if ((++rcwd > 3) && (phyPIB.recalInterval != 0))
      {
        /* INFO: If the TRX sends a packet, calibration failes!
        * In this case rcwd is not reset, but tiRecal is.
        */
        /* normal operation mode */
        if (phyPIB.testmode == 0)
        {
          if (NTRXAllCalibration())
          {
            tiRecal = hwclock() + phyPIB.recalInterval;
            rcwd = 0;
            //TRIGGER_LED_CAL();
          }
        }
        else
        {
          /*
          * in case of an enabled testmode recalibration is a bit trickier.
          * We first have to disable the testmode, recalibrate and then
          * enable the testmode again.
          */

          if (phyPIB.testmode == 1)
          {
            NTRXSetTestChirpMode(FALSE);
            NTRXAllCalibration();
            //TRIGGER_LED_CAL();
            NTRXSetTestChirpMode(TRUE);
          }
          else
          {
            NTRXSetTestCarrierMode(FALSE);
            NTRXAllCalibration();
            //TRIGGER_LED_CAL();
            NTRXSetTestCarrierMode(TRUE);
          }
        }
      }
      #endif

      //TRIGGER_LED_ERR();
      txSendMsg->status = PHY_NO_ACK;
    }
    else
    {
      txSendMsg->status = PHY_SUCCESS;
    }

    txIrq &= (uint8_t)(~(0x01 << NA_TxEnd_B));
    ntrxState = TxIDLE;
    txSendMsg->value = arqCount;

    if (phyPIB.frameType != last_frameType)
    {
      phyPIB.frameType = last_frameType;
      ntrxShadowReg[NA_TxPacketType_O] &= (uint8_t)(~(0x0F));
      ntrxShadowReg[NA_TxPacketType_O] |= phyPIB.frameType;
      NTRXSPIWriteByte(NA_TxPacketType_O , ntrxShadowReg[NA_TxPacketType_O]);

      PHY_DEBUG("frame type restore\r\n");

      ntrxShadowReg[NA_TxArq_O] |= (1 << NA_TxArq_B);
      NTRXSPIWriteByte(NA_TxArq_O, ntrxShadowReg[NA_TxArq_O]);
    }

    switch (txSendMsg->prim)
    {
      case PD_TIMEB_REQUEST:
        txSendMsg->prim = PD_TIMEB_CONFIRM;

        /*set auto mode to the state which was set before sending the timeb packet */
        NTRXSPIWriteByte(NA_RtcTimeBAutoMode_O, ntrxShadowReg[NA_RtcTimeBAutoMode_O]);

        tMsg = txSendMsg;
        txSendMsg = NULL;
        tMsg->pdu = tMsg->data;
        SendMsgUp(tMsg);
        break;
      case PD_RANGING_REQUEST:
        NTRXRangingACK();

        break;
      default:
        txSendMsg->prim = PD_DATA_CONFIRM;

        tMsg = txSendMsg;
        txSendMsg = NULL;
        tMsg->pdu = tMsg->data;
        SendMsgUp(tMsg);
        break;
    }
  }

  /* check if nanoLOC TRX chip has received valid data */
  if (ntrxState == TxIDLE)
  {
    if ((rxIrq & (0x01 << NA_RxEnd_B)) != 0)
    {
      /*FIXME how to find out if the ACK was properly sent?!*/
      //#define NTRX_DEBUG_ACK_DELAY (1)

#ifdef NTRX_DEBUG_ACK_DELAY
  #ifdef CONFIG_DEFAULT_TRX_80MHZ_4000NS
    delay_nus(300);//修改这个延时没有用，这里根本不进来，2015-04-01
  #endif
#else /*NTRX_DEBUG_ACK_DELAY*/
      uint8_t val;

      /* Wait until hwack is fully transmitted.
       * Depends on symbolduration and is always less
       * than 300us.
       *
       * NOTE: This is an workaround to make sure,
       * that the receptionprocess is completed. This
       * is necessary to prevent the possible destruction
       * of the corresponding hwack (e.g. through powering down
       * to early).
       *
       * NOTE: Use DebugMacFsm register only in this
       * circumstance!
       */
      /* Bcast noAck 80/4 */
      if ((modeSet.sd == NA_4us)
          && (modeSet.bw == NA_80MHz)
          && (rxFrameType == NA_TypeCodeData_VC_C)
          && ((ntrxShadowReg[NA_TxArq_O] & (uint8_t)(1 << NA_TxArq_B)) != 0))
      {
        do
        {
          NTRXSPIReadByte(NA_DebugMacFsm_O, &val);
        }
        while (((val & 0xF0) >> NA_DebugMacFsm_LSB) != NA_DebugMacFsmIdle_VC_C);
      }
#endif /*NTRX_DEBUG_ACK_DELAY*/
      PDCallback();//非常重要的一个函数，里面调用了测距等函数，2014-11-20

      //P2OUT ^=BIT6;
    }
  }

  #ifdef CONFIG_NTRX_AUTO_RECALIB
  if (phyPIB.recalInterval != 0)
  {
    if ((rcwd > 3) || (tiRecal < hwclock()))
    {
      /* INFO: If the TRX sends a packet, calibration failes!
       * In this case rcwd is not reset, but tiRecal is. */
      if (phyPIB.testmode == 0)
      {
        if (NTRXAllCalibration())
        {
          tiRecal = hwclock() + phyPIB.recalInterval;
          rcwd = 0;
          //TRIGGER_LED_CAL();
        }
      }
      else
      {
        /*
          * in case of an enabled testmode recalibration is a bit trickier.
          * We first have to disable the testmode, recalibrate and then
          * enable the testmode again.
          */
        if (phyPIB.testmode == 1)
        {
          NTRXSetTestChirpMode(FALSE);
          NTRXAllCalibration();
          //TRIGGER_LED_CAL();
          NTRXSetTestChirpMode(TRUE);
        }
        else
        {
          NTRXSetTestCarrierMode(FALSE);
          NTRXAllCalibration();
          //TRIGGER_LED_CAL();
          NTRXSetTestCarrierMode(TRUE);
        }
      }
    }
  }
  #endif /* CONFIG_NTRX_AUTO_RECALIB */
}

/**
 * @brief interrupt service routine for the nanoLOC chip
 *
 * This function is an interrupt service routine of the nanochip.
 * It updates the TX and RX status flags.
 *
 */
/**************************************************************************/
void NTRXInterrupt(void)
/**************************************************************************/
{
  /* if ntrx is in sleep mode, dont use ntrx */
  if (phyPIB.pwrDown == TRUE)
  {
    return;
  }

  /* we have received an interrupt and neede to find out what caused it */
  NTRXSPIRead(NA_TxIntsRawStat_O, ntrxIrqStatus, 2);

  /* check if it was the transmitter */
  if (txIrqStatus != 0)
  {
    /* clear interrupts */
    NTRXSPIWriteByte(NA_TxIntsReset_O, txIrqStatus);
    txIrq |= (uint8_t)(txIrqStatus & (0x01 << NA_TxEnd_B));
    if ((txIrq & (0x01 << NA_TxEnd_B)) != 0)
    {
      ntrxState = TxWAIT;

      #ifdef CONFIG_NTRX_IRQ
        nnIrq = 1;
      #endif
    }
  }
  /* check if it was the receiver */
  if (rxIrqStatus != 0)
  {
    /* clear interrupts */
    NTRXSPIWriteByte(NA_RxIntsReset_O, rxIrqStatus);
    rxIrq |= (uint8_t)(rxIrqStatus & (0x01 << NA_RxEnd_B));

    #ifdef CONFIG_NTRX_IRQ
      nnIrq = 1;
    #endif
  }
  //BASEBAND
  NTRXSPIRead(NA_BbTimerIrqStatus_O, &ntrxBBStatus, 1);
  /* check if it was the basebandtimer */
  if ((ntrxBBStatus & 0x40) != 0)
  {
    NTRXStopBbTimer();
    NTRXRangingInterrupt();
    ntrxBBStatus = 0;
  }
}

/**************************************************************************/
/**
 * @brief Configuration of callback functions.
 * @param cbMsg Callback function pointer for the (protocol) message interface.
 * If not set the PHY will call the function @ref APLCallback by default.
 */
void PHYRegisterCallback(callbackfn_t cbMsg)
{
  if (cbMsg == NULL)
  {
    phySendMsgUp = &APLCallback;
  }
  else
  {
    phySendMsgUp = cbMsg;
  }
}

/**************************************************************************/
/**
 * @brief Returns status of PHY and RANGING.
 * @return TRUE if phy and ranging in status IDLE.
 * Used to check the status of the driver before going power down.
 */
bool_t PHYIsIDLE(void)
{
  if ((ntrxState == TxIDLE) && (NTRXRangingIsIDLE()))
  {
    return TRUE;
  }

  return FALSE;
}

#ifdef CONFIG_NTRX_AUTO_RECALIB
/**************************************************************************/
void PHYAutoCalibration(void)
/**************************************************************************/
{
  if (phyPIB.recalInterval != 0)
  {
    if (tiRecal < hwclock())
    {
      /* INFO: If the TRX sends a packet, calibration failes!
       * In this case rcwd is not reset, but tiRecal is. */
      if (phyPIB.testmode == 0)
      {
        if (NTRXAllCalibration())
        {
          tiRecal = hwclock() + phyPIB.recalInterval;
          rcwd = 0;
          //TRIGGER_LED_CAL();
        }
      }
      else
      {
        /*
          * in case of an enabled testmode recalibration is a bit trickier.
          * We first have to disable the testmode, recalibrate and then
          * enable the testmode again.
          */
        if (phyPIB.testmode == 1)
        {
          NTRXSetTestChirpMode(FALSE);
          NTRXAllCalibration();
          //TRIGGER_LED_CAL();
          NTRXSetTestChirpMode(TRUE);
        }
        else
        {
          NTRXSetTestCarrierMode(FALSE);
          NTRXAllCalibration();
          //TRIGGER_LED_CAL();
          NTRXSetTestCarrierMode(TRUE);
        }
      }
    }
  }
}
#endif /* CONFIG_NTRX_AUTO_RECALIB */
