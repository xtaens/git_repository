/**
 * @file ntrxutil_SetChannel.c
 * @date 2009-Nov-2
 * @author S.Radtke
 * @c (C) 2009 Nanotron Technologies
 * @brief Functions for setting the Channel of ISM band
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

uint8_t loTarVal[6][2] = {{0x59, 0x68},     /* current value */
  {0x59, 0x68},       /* Channel 0: 2.44175 GHz, center of the band,
                                    shall be used for 80 MHz mode */
#ifdef COUNTRY_CODE_1
  /* USA */
  {0x66, 0x62},     /* Channel 0: 2.412 GHz non overlapping chanel no. ( USA ) */
  {0x66, 0x67},     /* Channel 5: 2.437 GHz non overlapping chanel no. ( USA ) */
  {0x66, 0x6c}      /* Channel 10: 2.462 GHz non overlapping chanel no. ( USA ) */
#else
  /* COUNTRY_CODE_2 */
  /* EUROPE */
  {0x66, 0x62},     /* Channel 0: 2.412 GHz non overlapping chanel no. ( Europe ) */
  {0x66, 0x68},     /* Channel 6: 2.442 GHz non overlapping chanel no. ( Europe ) */
  {0x66, 0x6e},     /* Channel 12: 2.472 GHz non overlapping chanel no. ( Europe ) */
  {0xcd, 0x70}      /* Channel 13: 2.484 GHz overlapping chanel no. 13 */
#endif
};


uint8_t loTarValTx[2] = {0x59, 0x68};     /* current value */
uint8_t loTarValRx[2] = {0x6f, 0x68};     /* current value */

#if (CONFIG_DEFAULT_MODE == CONFIG_DEFAULT_TRX_80MHZ_1000NS)
uint8_t loTarValRx_418kHz[] = {0x6f, 0x68};
#else
uint8_t loTarValRx_418kHz[] = {0x5c, 0x68};
#endif

/**
 * @brief set the logical channel.
 * @param value the logical channel id
 *
 * This function sets the logical channel for transmission and reception
 *
 */
/**************************************************************************/
void NTRXSetChannel(uint8_t value)
/**************************************************************************/
{
  /*
   * first check for a valid parameter. If the parameter is out of range
   * do nothing.
   */
  if (value > NTRX_MAX_CHANNEL_ID)
  {
    return;
  }

  /*
   * in the first slot of the loTarVal array the currently used channel
   * (center frequency) is stored. The other 4 are used to hold the
   * predefined channels. When a new channel is selected, the value
   * is copied form the list to the first slot. For fdma only the first
   * channel is stored. The other 14 channels are calculated with the
   * first channel as the basis.
   */
  switch (value)
  {
    case 0:
      loTarValTx[0] = loTarVal[1][0];
      loTarValTx[1] = loTarVal[1][1];
      loTarValRx[0] = loTarValRx_418kHz[0];
      loTarValRx[1] = loTarValRx_418kHz[1];
      break;
    case 13:
      loTarValTx[0] = loTarVal[5][0];
      loTarValTx[1] = loTarVal[5][1];
      loTarValRx[0] = loTarVal[5][0];
      loTarValRx[1] = loTarVal[5][1];
      break;
    default:
#       ifdef COUNTRY_CODE_1
      loTarValTx[0] = loTarVal[2][0];
      loTarValTx[1] = (uint8_t)(loTarVal[2][1] + (5 * (value - 1)));
      loTarValRx[0] = loTarVal[2][0];
      loTarValRx[1] = (uint8_t)(loTarVal[2][1] + (5 * (value - 1)));
#       else
      loTarValTx[0] = loTarVal[2][0];
      loTarValTx[1] = (uint8_t)(loTarVal[2][1] + (6 * (value - 1)));
      loTarValRx[0] = loTarVal[2][0];
      loTarValRx[1] = (uint8_t)(loTarVal[2][1] + (6 * (value - 1)));
#       endif
      break;
  }
}
