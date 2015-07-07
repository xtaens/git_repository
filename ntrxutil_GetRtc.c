/**
 * @file ntrxutil_GetRtc.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for reading the RTC from nanoLOC
 *
 * @note BuildNumber = "8350"
 *
 * @note This file contains the source code for the implementation of the
 *    NTRX helper functions
 */
#include "config.h"
#include "ntrxtypes.h"
#include "portation.h"
#include "ntrxutil.h"
#include "nnspi.h"
#include "hwclock.h"
#include "phy.h"

#include "..\Application\delay.h"

extern PhyPIB phyPIB;

/**
 * @brief read out the real time clock of the transceiver.
 * @param force == TRUE lets the function read the RTC anyway
 * @returns the time in 1/32768 seconds (ca. 30 us)
 *
 * This function reads out the real time clock of the transceiver
 *
 */

 //不调用这个函数，2015-04-01
/**************************************************************************/
uint32_t NTRXGetRtc(bool_t force)
/**************************************************************************/
{
  /*FIXME disabled for debugging!*/
  static uint32_t currentRTC;         /**< stores the last RTC value*/
  static uint32_t currentHwclock = 0xFFFFFFFF;  /**< stores the hwclock value when RTC was read*/
  uint32_t now = hwclock();

  /*
  Avoid redundant access to RTC to save time.
  force == TRUE lets the function read the RTC anyway.
  */
  if ((now != currentHwclock) || (force))
  {
    uint8_t rtc[5];
    uint8_t reg;
    bool_t lastRxState = ((phyPIB.rxOn >0) ? TRUE:FALSE);

    /*disable receiver*/
    NTRXRXEnable(FALSE);

    /*read current RTC*/
    ENTER_TASK;
    reg = (uint8_t)(ntrxShadowReg[NA_RtcCmdRd_O] | (1 << NA_RtcCmdRd_B));
    NTRXSPIWriteByte(NA_RtcCmdRd_O, reg);
    //delay_nus(130);

    //2015-04-01
    delay_nus(10);
    NTRXSPIRead(NA_RamRtcReg_O + 1, rtc, 4);
    reg = 0;
    NTRXSPIWriteByte(NA_RtcCmdRd_O, reg);

    /*update current RTC and hwclock entries*/
    currentRTC = (
                   (((uint32_t)rtc[0])   <<  0)
                   | (((uint32_t)rtc[1]) <<  8)
                   | (((uint32_t)rtc[2]) << 16)
                   | (((uint32_t)rtc[3]) << 24)
                 );
    /*FIXME what can we do with the most significant byte?!*/
    //currentRTC = (currentRTC >> 7) | (rtc[5] << 1);
    currentHwclock = now;
    LEAVE_TASK;

    /*restore receiver state */
    NTRXRXEnable(lastRxState);
  }
  return currentRTC;
}

