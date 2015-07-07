/**
 * @file ntrxutil_SetRamIndex.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting registers
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
 * @brief set the index register.
 * @param page address index
 *
 * This function sets the index registers for the transceiver chip
 * The chip address space is deviced into 4 sections a 1kbyte.
 *
 */
/**************************************************************************/
void NTRXSetRamIndex(uint8_t page)
/**************************************************************************/
{
  page &= 0x03;
  if (page != (ntrxShadowReg[NA_RamIndex_O] & 0x03))
  {
    ntrxShadowReg[NA_RamIndex_O] &= 0xf0;
    ntrxShadowReg[NA_RamIndex_O] |= page;
    page = ntrxShadowReg[NA_RamIndex_O];
    NTRXSPIWriteByte(NA_RamIndex_O, page);
  }
}
