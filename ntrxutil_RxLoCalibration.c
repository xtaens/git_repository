/**
 * @file ntrxutil_RxLoCalibration.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for calibrating the oscillators
 *
 * @note BuildNumber = "8350"
 *
 * @note This file contains the source code for the implementation of the
 *    NTRX helper functions
 */
#include "config.h"
#include "ntrxtypes.h"
#include "ntrxutil.h"
#include "nnspi.h"
#include "hwclock.h"
#include "phy.h"

extern PhyPIB phyPIB;
extern uint8_t loTarValRx[2];
extern uint8_t tx_caps[3], rx_caps[3]; /**< used for fake calibration */
/**
 * @brief calibrates the local ocsillator.
 *
 * This function callibrates the local oscillator of the receiver part.
 * It is not called directly but from within the NTRXAllCalibration
 * function.
 *
 */
/**************************************************************************/
void NTRXRxLoCalibration(void)
/**************************************************************************/
{
  uint8_t data[3];

  NTRXRXEnable(FALSE);
  //地址0x42，值0x17
  NTRXSPIWriteByte(NA_EnableLO_O, (uint8_t)(ntrxShadowReg[NA_EnableLO_O] | (1 << NA_EnableLO_B) | (1 << NA_EnableLOdiv10_B)));

#if 0
  delay_nms(4);   /* ms (only neede if FDMA is enabled (22MHz) */
#endif
  //地址0x1C，值0x99
  NTRXSPIWriteByte(NA_UseLoRxCaps_O, (uint8_t)(ntrxShadowReg[NA_UseLoRxCaps_O] | (1 << NA_UseLoRxCaps_B)));

  data[0] = 0x03;
  NTRXSPIWriteByte(NA_LoIntsReset_O, data[0]);//地址0x12，值0x03
  NTRXSPIWrite(NA_LoTargetValue_O, loTarValRx, 2);//地址0x1D，值0x5C 68

  do
  {
    NTRXSPIReadByte(NA_LoIntsRawStat_O, &data[0]);//地址0x12，值0x
  }
  while ((data[0] & (1 << NA_LoTuningReady_B)) != (1 << NA_LoTuningReady_B));

  /* Read out caps values if needed */
  //NTRXSPIRead (0x16, data, 3);
  NTRXSPIRead(0x16, rx_caps, 3);//地址0x16，值0xBF 00 20,该值随机变化

  NTRXSPIWriteByte(NA_UseLoRxCaps_O, ntrxShadowReg[NA_UseLoRxCaps_O]);//地址0x1C，值0x19
  NTRXSPIWriteByte(NA_EnableLO_O, ntrxShadowReg[NA_EnableLO_O]);//地址0x42，值0x14

  /*
   * start receiver if it was started before calibration
   */
  if (phyPIB.rxState == PHY_RX_ON)
  {
    NTRXRXEnable(TRUE);
  }
}

