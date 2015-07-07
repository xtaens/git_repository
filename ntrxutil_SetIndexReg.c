/**
 * @file ntrxutil_SetIndexReg.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for register setting
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
extern uint8_t  ntrxShadowReg[SHADOWREGCOUNT];  /**< shadow register for the nanoLOC chip. Needed for write-only register */

/**
 * @brief set the index register.
 * @param page address index
 *
 * This function sets the index registers for the transceiver chip.
 * The chip address space is deviced into 4 sections a 1kbyte.
 *
 */
/**************************************************************************/
void NTRXSetIndexReg(uint8_t page)
/**************************************************************************/
{
  if (page != ntrxShadowReg[NA_RamIndex_O])
  {
    ntrxShadowReg[NA_RamIndex_O] = page;
    NTRXSPIWriteByte(NA_RamIndex_O, page);//地址0x0E，值0x30 //地址0x0E，值0x31 //地址0x0E，值0x32 //地址0x0E，值0x20 //地址0x0E，值0x21
  }
}
