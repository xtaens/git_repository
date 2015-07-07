/**
 * @file avrport.h
 * @date 2010-Jun-14
 * @author S. Rohdemann
 * @c (C) 2010 Nanotron Technologies
 * @brief support for AVR.
 *
 * @note BuildNumber = "8350"
 *
 * @note This file contains the type- / data- and function definitions
 *    for the skeleton portation
 *
 */
#ifndef _PORTATION_H
#define _PORTATION_H

#include "config.h"
#include "ntrxtypes.h"
#include "hwclock.h"
#include <stdio.h>

#ifdef CONFIG_FIXED_POINT
  #define TWEAK                            ( 1 * 10000 / 2997924 )
  #define RANGING_FECon_22MHZ_4000NS       0
  #define RANGING_FECoff_22MHZ_4000NS      0
  #define RANGING_FECon_80MHZ_1000NS       ( 1225566 + TWEAK )
  #define RANGING_FECoff_80MHZ_1000NS      ( 9250524 + TWEAK )
  #define RANGING_FECon_80MHZ_4000NS       ( 4456487 + TWEAK )
  #define RANGING_FECoff_80MHZ_4000NS      ( 3255870 + TWEAK )
  #define RANGING_FECon_22MHZ_4000NS_ROM   0
  #define RANGING_FECoff_22MHZ_4000NS_ROM  0
#else
  #define TWEAK                            ( 1.0 / 299.792458 )
  #define RANGING_FECon_22MHZ_4000NS       0.0
  #define RANGING_FECoff_22MHZ_4000NS      0.0
  #define RANGING_FECon_80MHZ_1000NS       ( 122.55664361 + TWEAK )
  #define RANGING_FECoff_80MHZ_1000NS      ( 92.505235904 + TWEAK )
  #define RANGING_FECon_80MHZ_4000NS       ( 445.648702415 + TWEAK )
  #define RANGING_FECoff_80MHZ_4000NS      ( 325.587060636 + TWEAK )
  #define RANGING_FECon_22MHZ_4000NS_ROM   0.0
  #define RANGING_FECoff_22MHZ_4000NS_ROM  0.0
#endif

#define RANGING_TIMEOUT_22MHZ_4000NS       0
#define RANGING_TIMEOUT_80MHZ_1000NS       RANGING_TIMEOUT_7MS
#define RANGING_TIMEOUT_80MHZ_4000NS       RANGING_TIMEOUT_13MS
#define RANGING_TIMEOUT_22MHZ_4000NS_ROM   0


#endif
