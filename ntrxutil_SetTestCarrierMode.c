/**
 * @file ntrxutil_SetTestCarrierMode.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting the test carrier mode
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
 * @brief Carriermode for chip measurement.
 *
 *
 *
 * This function enables or disables the unmodulated carrier signal test mode by
 * sending a continuous carrier. This requires to swich off the receiver.
 * Note: This function should be periodically interrupted and the transmitter
 * recalibrated. Otherwise the frequency might be out of range.
 */
/**************************************************************************/
void NTRXSetTestCarrierMode(bool_t value)
/**************************************************************************/
{
  static uint8_t fdma;

  NTRXRXEnable(FALSE);

  if (value == TRUE)
  {
    fdma = ntrxShadowReg[NA_FdmaEnable_O];
    ntrxShadowReg[NA_FdmaEnable_O] &= (uint8_t)(~(1 << NA_FdmaEnable_B));
    NTRXSPIWriteByte(NA_FdmaEnable_O, ntrxShadowReg[NA_FdmaEnable_O]);

    ntrxShadowReg[NA_EnableLO_O] |= ((1 << NA_EnableLO_B) | (1 << NA_EnableLOdiv10_B));
    NTRXSPIWriteByte(NA_EnableLO_O, ntrxShadowReg[NA_EnableLO_O]);

    ntrxShadowReg[NA_CsqSetValue_O] = 0x1F;
    NTRXSPIWriteByte(NA_CsqSetValue_O, ntrxShadowReg[NA_CsqSetValue_O]);

    ntrxShadowReg[NA_CsqSetValue_O] |= (1 << 6);
    NTRXSPIWriteByte(NA_CsqSetValue_O, ntrxShadowReg[NA_CsqSetValue_O]);

    ntrxShadowReg[NA_CsqSetValue_O] = 0x3F;
    NTRXSPIWriteByte(NA_CsqSetValue_O, ntrxShadowReg[NA_CsqSetValue_O]);

    ntrxShadowReg[NA_CsqSetValue_O] |= (1 << 7);
    NTRXSPIWriteByte(NA_CsqSetValue_O, ntrxShadowReg[NA_CsqSetValue_O]);

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

    ntrxShadowReg[NA_EnableLO_O] &= (uint8_t)(~((1 << NA_EnableLO_B)
                                    | (1 << NA_EnableLOdiv10_B)
                                    | (1 << NA_EnableCsqClock_B)));
    NTRXSPIWriteByte(NA_EnableLO_O, ntrxShadowReg[NA_EnableLO_O]);

    ntrxShadowReg[NA_FdmaEnable_O] = fdma;
    NTRXSPIWriteByte(NA_FdmaEnable_O, ntrxShadowReg[NA_FdmaEnable_O]);
  }
}

