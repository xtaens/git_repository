/**
 * @file ntrxutil_PowerdownMode.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting powerdownmode
 *
 * @note BuildNumber = "8350"
 *
 * @note This file contains the source code for the implementation of the
 *    NTRX helper functions
 */
#include "config.h"
#include "ntrxtypes.h"
#include "ntrxutil.h"
#include "ntrxiqpar.h"
#include "nnspi.h"
#include "hwclock.h"
#include "phy.h"

extern PhyPIB phyPIB;



/**
 * @brief read out the real time clock of the transceiver.
 * @param mode 0 is full and 1 is for pad mode
 * @param seconds wake up time from now
 *
 * This function starts the alarm clock if the parameter seconds is
 * greater than 0 and brings the transceiver into the requested powerdown mode.
 * There are two powerdown modes supported: powerdown mode full and
 * powerdown mode pad. The second mode can be used to supervise the dig-IO
 * pins of the nanoLOC chip.
 *
 */
/**************************************************************************/
void NTRXPowerdownMode(uint8_t mode, uint32_t ms)
/**************************************************************************/
{
  uint8_t   value, valNull = 0;
  uint8_t   i;
  uint8_t   wakeupTime8;
  uint32_t wakeupTime32;

  /*Stop receiver*/
  NTRXRXEnable(FALSE);
#if 0
  NTRXSPIWriteByte(NA_RxCmdStop_O, ntrxShadowReg[NA_RxCmdStop_O] | (1 << NA_RxCmdStop_B));
#endif

  if (ms > 0)
  {
    ms = (uint32_t)(ms / (float) 7.8125);   /* 7.8125ms steps */
    /* Round errors leads to always to short measurements.
     * add +1 to be sure not to sleep shorter than expected */
    ms += 1;

    wakeupTime32 = ms + NTRXGetRtc(TRUE);

    /*write down wake up time*/
    for (i = NA_WakeUpTimeWe_LSB; i <= NA_WakeUpTimeWe_MSB; i++)
    {

      /*convert 32bit integer wakeup time -> RTC value*/
      wakeupTime8 = (uint8_t)(wakeupTime32 & 0xFF);
      wakeupTime32 >>= 8;

      /*write one of the 3 bytes into the RtcWakeUpTime Register*/
      NTRXSPIWriteByte(NA_WakeUpTimeByte_O, wakeupTime8);

      /*generate Strobe to store value in the right place*/
      value = (uint8_t)(1 << i);
      NTRXSPIWriteByte(NA_WakeUpTimeWe_O, value);
      NTRXSPIWriteByte(NA_WakeUpTimeWe_O, valNull);
    }
  }

  value = (0x00 | (1 << NA_ResetBbClockGate_B));
  NTRXSPIWriteByte(NA_PowerDown_O, value);
  value = 0;
  NTRXSPIWriteByte(0x8, value);
  /*set wakeup parameter*/
  if (ms > 0)
  {
    value = (uint8_t)((0x00
                       | (1 << NA_EnableWakeUpRtc_B)
                       | (1 << NA_PowerUpTime_LSB)
                       | ((0x01 & mode) << NA_PowerDownMode_B)));
  }
  else
  {
    value = (uint8_t)(((0x01 & mode) << NA_PowerDownMode_B));
  }
  NTRXSPIWriteByte(NA_EnableWakeUpRtc_O, value);

  value = (0x00
           | (1 << NA_PowerDown_B)
           | (1 << NA_ResetBbClockGate_B));
  NTRXSPIWriteByte(NA_PowerDown_O, value);
  phyPIB.pwrUp = TRUE;
  phyPIB.pwrDown = TRUE;
}
