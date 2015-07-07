/**
 * @file ntrxutil_RxEnable.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for starting the receiver
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
#include <stdio.h>

extern PhyPIB phyPIB;

/**************************************************************************/
void NTRXRXEnable(bool_t enable)
/**************************************************************************/
{
  /*
  * start the receiver of the TRX chip
  */
  if (enable == TRUE && phyPIB.rxOn == FALSE)
  {
    NTRXSPIWriteByte(NA_RxIntsReset_O, 0x7F);//地址0x11，值0x7F
    rxIrqStatus = 0;
    //地址0x56，值0x0E
    NTRXSPIWriteByte(NA_RxCmdStart_O, (uint8_t)(ntrxShadowReg[NA_RxCmdStart_O]
                     | (1 << NA_RxCmdStart_B)
                     | (1 << NA_RxBufferCmd_LSB)
                     | (1 << NA_RxBufferCmd_MSB)));

    phyPIB.rxOn = TRUE;

    PHY_DEBUG("RX enable\r\n");
  }
  else if (enable == FALSE && phyPIB.rxOn == TRUE)
  {
    NTRXSPIWriteByte(NA_RxCmdStop_O, (uint8_t)(ntrxShadowReg[NA_RxCmdStop_O]
                     | (1 << NA_RxCmdStop_B)
                     | (1 << NA_RxBufferCmd_LSB)
                     | (1 << NA_RxBufferCmd_MSB)));//地址0x56，值0x0D

    NTRXSPIWriteByte(NA_RxIntsReset_O, 0x7F);//地址0x11，值0x7F
    phyPIB.rxOn = FALSE;
    rxIrqStatus = 0;

    PHY_DEBUG("RX disable\r\n");
  }
}


