/**
 * @file ntrxutil_SetTestChirpMode.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting the test chirp mode
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

/**
 * @brief Testmode for chip measurement.
 *
 * This function enables or disables the chip test mode. In this mode
 * a continuous chirp is transmitted. This requires to swich off the receiver.
 * Note: This function should be interrupted periodically and the transmitter
 * recalibrated. Otherwise the frequency might be out of range.
 */
/**************************************************************************/
void NTRXSetTestChirpMode(bool_t value)
/**************************************************************************/
{
  NTRXRXEnable(FALSE);

  if (value == TRUE)
  {
    ntrxShadowReg[NA_CsqUseRam_O] |= 0x80;
    NTRXSPIWriteByte(NA_CsqUseRam_O, ntrxShadowReg[NA_CsqUseRam_O]);

    ntrxShadowReg[NA_CsqUsePhaseShift_O] |= (1 << NA_CsqUsePhaseShift_B);
    NTRXSPIWriteByte(NA_CsqUsePhaseShift_O, ntrxShadowReg[NA_CsqUsePhaseShift_O]);

    ntrxShadowReg[NA_EnableLO_O] |= ((1 << NA_EnableLO_B) | (1 << NA_EnableLOdiv10_B) | (1 << NA_EnableCsqClock_B));
    NTRXSPIWriteByte(NA_EnableLO_O, ntrxShadowReg[NA_EnableLO_O]);

    ntrxShadowReg[NA_EnableTx_O] |= (1 << NA_EnableTx_B);
    NTRXSPIWriteByte(NA_EnableTx_O, ntrxShadowReg[NA_EnableTx_O]);

    ntrxShadowReg[NA_EnableExtPA_O] |= 0x20;
    NTRXSPIWriteByte(NA_EnableExtPA_O, ntrxShadowReg[NA_EnableExtPA_O]);
  }
  else
  {
    ntrxShadowReg[NA_EnableExtPA_O] &= (uint8_t)(~(0x20));
    NTRXSPIWriteByte(NA_EnableExtPA_O, ntrxShadowReg[NA_EnableExtPA_O]);

    ntrxShadowReg[NA_EnableTx_O] &= (uint8_t)(~(1 << NA_EnableTx_B));
    NTRXSPIWriteByte(NA_EnableTx_O, ntrxShadowReg[NA_EnableTx_O]);

    ntrxShadowReg[NA_EnableCsqClock_O] &= (uint8_t)(~(1 << NA_EnableCsqClock_B));
    ntrxShadowReg[NA_EnableLOdiv10_O] &= (uint8_t)(~(1 << NA_EnableLOdiv10_B));
    ntrxShadowReg[NA_EnableLO_O] &= (uint8_t)(~(1 << NA_EnableLO_B));
    NTRXSPIWriteByte(NA_EnableLO_O, ntrxShadowReg[NA_EnableLO_O]);

    ntrxShadowReg[NA_CsqUsePhaseShift_O] &= (uint8_t)(~(1 << NA_CsqUsePhaseShift_B));
    NTRXSPIWriteByte(NA_CsqUsePhaseShift_O, ntrxShadowReg[NA_CsqUsePhaseShift_O]);

    ntrxShadowReg[NA_CsqUseRam_O] &= (uint8_t)(~(0x80));
    NTRXSPIWriteByte(NA_CsqUseRam_O, ntrxShadowReg[NA_CsqUseRam_O]);
  }
}
