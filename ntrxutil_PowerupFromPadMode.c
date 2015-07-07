/**
 * @file ntrxutil_PowerupFromPadMode.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for powerdown mode
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

#include "..\Application\delay.h"

extern PhyPIB phyPIB;

/**************************************************************************/
void NTRXPowerupFromPadMode(void)
/**************************************************************************/
{
  ntrxShadowReg[NA_EnableBbCrystal_O] |= (1 << NA_EnableBbCrystal_B);
  NTRXSPIWriteByte(NA_EnableBbCrystal_O, ntrxShadowReg[NA_EnableBbCrystal_O]);

  delay_nms(5);   /* 5 ms */

  NTRXSPIWriteByte(NA_ResetBbClockGate_O, 0);

  ntrxShadowReg[NA_EnableBbClock_O] |= (1 << NA_EnableBbClock_B);
  NTRXSPIWriteByte(NA_EnableBbCrystal_O, ntrxShadowReg[NA_EnableBbCrystal_O]);
}

