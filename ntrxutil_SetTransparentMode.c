/**
 * @file ntrxutil_SetTransparentMode.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting the transparent mode
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
#if 0
/**************************************************************************/
void NTRXSetTransparentMode(bool_t on)
/**************************************************************************/
{
  uint8_t len[2];

  if (on == TRUE)
  {
    len[0] = 0x80;
    len[1] = 0;
    NTRXSPIWrite(NA_RxTransBytes_O, len, 2);

    // NTRXSetRegister( NA_TxRxMode, TRUE );
    ntrxShadowReg[NA_TxRxMode_O] |= (1 << NA_TxRxMode_B);
    NTRXSPIWriteByte(NA_TxRxMode_O, ntrxShadowReg[NA_TxRxMode_O]);

    // NTRXSetRegister( NA_TxRxBbBufferMode0, TRUE );
    ntrxShadowReg[NA_TxRxBbBufferMode0_O] |= (1 << NA_TxRxBbBufferMode0_B);
    NTRXSPIWriteByte(NA_TxRxBbBufferMode0_O, ntrxShadowReg[NA_TxRxBbBufferMode0_O]);

    NTRXSetRegister(NA_TxScrambEn, FALSE);
    NTRXSetRegister(NA_TxScrambInit, 0);
    NTRXSetRegister(NA_TxArq, FALSE);
    NTRXSetRegister(NA_TxArqMax, 0);
    NTRXSetRegister(NA_RxArqMode, NA_RxArqModeNone_VC_C);
    NTRXSetRegister(NA_RxCrc2Mode, FALSE);
  }
  else
  {
    NTRXSetRegister(NA_TxRxMode, FALSE);
    NTRXSetRegister(NA_TxScrambEn, TRUE);
    NTRXSetRegister(NA_TxScrambInit, 0x7f);
    NTRXSetRegister(NA_TxArq, TRUE);
    NTRXSetRegister(NA_TxArqMax, CONFIG_MAX_ARQ);

    NTRXSetRegister(NA_RxArqMode, NA_RxArqModeCrc2_VC_C);
    NTRXSetRegister(NA_RxCrc2Mode, TRUE);
  }
}
#endif
