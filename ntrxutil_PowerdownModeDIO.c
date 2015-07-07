/**
 * @file ntrxutil_PowerdownModeDIO.c
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
#include "nnspi.h"
#include "hwclock.h"
#include "phy.h"

extern PhyPIB phyPIB;

/**************************************************************************/
void NTRXPowerdownModeDIO(uint8_t mode , uint8_t dio)
/**************************************************************************/
{
  /*Stop receiver*/
  NTRXRXEnable(FALSE);

  // enable DIGIO for wake-up alarm, start the alarm function,
  // rising edge causes the alarm, configure as an input pin
  ntrxShadowReg[NA_DioDirection_O] = (1 << NA_DioOutValueAlarmEnable_B)
                                     | (1 << NA_DioAlarmStart_B)
                                     | (1 << NA_DioAlarmPolarity_B);
  NTRXSPIWriteByte(NA_DioDirection_O, ntrxShadowReg[NA_DioDirection_O]);

  // apply settings to DIGIO port
  ntrxShadowReg[NA_DioPortWe_O] = (uint8_t)(1 << dio);
  NTRXSPIWriteByte(NA_DioPortWe_O, ntrxShadowReg[NA_DioPortWe_O]);
  ntrxShadowReg[NA_DioPortWe_O] = 0;
  NTRXSPIWriteByte(NA_DioPortWe_O, ntrxShadowReg[NA_DioPortWe_O]);  // clear the write enable register

  // alarm source for powering up is DIGIO, power down mode as selected with parameter mode,
  // power up time is set (ticks)
  // 1 tick = 1/4096s ~= 244us
  // reg. 0x06 is R/W
  ntrxShadowReg[NA_EnableWakeUpDio_O] = (uint8_t)((1 << NA_EnableWakeUpDio_B)
                                        | (NA_PowerUpTime1Ticks_C << NA_PowerUpTime_LSB)
                                        | ((mode & 0x01) << NA_PowerDownMode_B));  // register value is rewritten completely
  NTRXSPIWriteByte(NA_EnableWakeUpDio_O, ntrxShadowReg[NA_EnableWakeUpDio_O]);

  // turn off BB clock
  ntrxShadowReg[NA_EnableBbClock_O] &= (uint8_t)(~(1 << NA_EnableBbClock_B));
  NTRXSPIWriteByte(NA_EnableBbClock_O, ntrxShadowReg[NA_EnableBbClock_O]);
  ntrxShadowReg[NA_ResetBbClockGate_O] = (1 << NA_ResetBbClockGate_B) | (1 << NA_ResetBbRadioCtrl_B);
  NTRXSPIWriteByte(NA_ResetBbClockGate_O, ntrxShadowReg[NA_ResetBbClockGate_O]);
  ntrxShadowReg[NA_EnableBbCrystal_O] &= (uint8_t)(~(1 << NA_EnableBbCrystal_B));
  NTRXSPIWriteByte(NA_EnableBbCrystal_O, ntrxShadowReg[NA_EnableBbCrystal_O]);

  // go to power down mode
  ntrxShadowReg[NA_PowerDown_O] = (1 << NA_ResetBbRadioCtrl_B)
                                  | (1 << NA_ResetBbClockGate_B)
                                  | (1 << NA_PowerDown_B);
  NTRXSPIWriteByte(NA_PowerDown_O, ntrxShadowReg[NA_PowerDown_O]);
}

