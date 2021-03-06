/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * msp430x12x2 devices.
 *
 * Copyright 1996-2012 IAR Systems AB.
 *
 *
 *
 ********************************************************************/

#ifndef __IO430X12X2
#define __IO430X12X2

#ifdef  __IAR_SYSTEMS_ICC__

#include "intrinsics.h"
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430x12x2.h file for use with ICC430/A430 only
#endif


#ifdef __IAR_SYSTEMS_ICC__
#pragma language=save
#pragma language=extended


#ifdef __cplusplus
#define __READ    /* not supported */
#else
#define __READ    const
#endif


/*-------------------------------------------------------------------------
 *   Standard Bits
 *-------------------------------------------------------------------------*/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

/*-------------------------------------------------------------------------
 *   Status register bits
 *-------------------------------------------------------------------------*/

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)


#define LPM0      __bis_SR_register(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */



/*-------------------------------------------------------------------------
 *   Special Function
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char IE1;   /* Interrupt Enable 1 */

  struct
  {
    unsigned char WDTIE           : 1; /*  */
    unsigned char OFIE            : 1; /*  */
    unsigned char                : 2;
    unsigned char NMIIE           : 1; /*  */
    unsigned char ACCVIE          : 1; /*  */
  }IE1_bit;
} @0x0000;


enum {
  WDTIE           = 0x0001,
  OFIE            = 0x0002,
  NMIIE           = 0x0010,
  ACCVIE          = 0x0020
};


__no_init volatile union
{
  unsigned char IFG1;   /* Interrupt Flag 1 */

  struct
  {
    unsigned char WDTIFG          : 1; /*  */
    unsigned char OFIFG           : 1; /*  */
    unsigned char                : 2;
    unsigned char NMIIFG          : 1; /*  */
  }IFG1_bit;
} @0x0002;


enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  NMIIFG          = 0x0010
};


__no_init volatile union
{
  unsigned char IE2;   /* Interrupt Enable 2 */

  struct
  {
    unsigned char URXIE0          : 1; /*  */
    unsigned char UTXIE0          : 1; /*  */
  }IE2_bit;
} @0x0001;


enum {
  URXIE0          = 0x0001,
  UTXIE0          = 0x0002
};


__no_init volatile union
{
  unsigned char IFG2;   /* Interrupt Flag 2 */

  struct
  {
    unsigned char URXIFG0         : 1; /*  */
    unsigned char UTXIFG0         : 1; /*  */
  }IFG2_bit;
} @0x0003;


enum {
  URXIFG0         = 0x0001,
  UTXIFG0         = 0x0002
};


__no_init volatile union
{
  unsigned char ME2;   /* Module Enable 2 */

  struct
  {
    unsigned char URXE0           : 1; /*  */
    unsigned char UTXE0           : 1; /*  */
  }ME2_bit;
} @ 0x0005;


enum {
  URXE0           = 0x0001,
  UTXE0           = 0x0002
};



#define U0IE                IE2       /* UART0 Interrupt Enable Register */
#define U0IFG               IFG2      /* UART0 Interrupt Flag Register */
#define U0ME                ME2       /* UART0 Module Enable Register */
#define USPIE0              (0x01)

/*-------------------------------------------------------------------------
 *   Watchdog Timer
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short WDTCTL;   /* Watchdog Timer Control */

  struct
  {
    unsigned short WDTIS0          : 1; /*  */
    unsigned short WDTIS1          : 1; /*  */
    unsigned short WDTSSEL         : 1; /*  */
    unsigned short WDTCNTCL        : 1; /*  */
    unsigned short WDTTMSEL        : 1; /*  */
    unsigned short WDTNMI          : 1; /*  */
    unsigned short WDTNMIES        : 1; /*  */
    unsigned short WDTHOLD         : 1; /*  */
  }WDTCTL_bit;
} @ 0x0120;


enum {
  WDTIS0          = 0x0001,
  WDTIS1          = 0x0002,
  WDTSSEL         = 0x0004,
  WDTCNTCL        = 0x0008,
  WDTTMSEL        = 0x0010,
  WDTNMI          = 0x0020,
  WDTNMIES        = 0x0040,
  WDTHOLD         = 0x0080
};



#define __MSP430_HAS_WDT__            /* Definition to show that Module is available */

#define WDTPW               (0x5A00u)
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)                 /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)          /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1)          /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)   /* 1.9ms   " */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL)                          /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)                   /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)                   /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)            /* 1.9ms   " */

/*-------------------------------------------------------------------------
 *   Port 1/2
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned __READ char P1IN;   /* Port 1 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P1IN_bit;
} @0x0020;


enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};


__no_init volatile union
{
  unsigned char P1OUT;   /* Port 1 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1OUT_bit;
} @0x0021;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1DIR;   /* Port 1 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1DIR_bit;
} @0x0022;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IFG;   /* Port 1 Interrupt Flag */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IFG_bit;
} @0x0023;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IES;   /* Port 1 Interrupt Edge Select */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IES_bit;
} @0x0024;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IE;   /* Port 1 Interrupt Enable */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IE_bit;
} @0x0025;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1SEL;   /* Port 1 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1SEL_bit;
} @0x0026;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned __READ char P2IN;   /* Port 2 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P2IN_bit;
} @0x0028;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2OUT;   /* Port 2 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2OUT_bit;
} @0x0029;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2DIR;   /* Port 2 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2DIR_bit;
} @0x002A;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IFG;   /* Port 2 Interrupt Flag */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IFG_bit;
} @0x002B;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IES;   /* Port 2 Interrupt Edge Select */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IES_bit;
} @0x002C;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IE;   /* Port 2 Interrupt Enable */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IE_bit;
} @0x002D;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2SEL;   /* Port 2 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2SEL_bit;
} @ 0x002E;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};
*/



#define __MSP430_HAS_PORT1__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port 3
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned __READ char P3IN;   /* Port 3 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P3IN_bit;
} @0x0018;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3OUT;   /* Port 3 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3OUT_bit;
} @0x0019;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3DIR;   /* Port 3 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3DIR_bit;
} @0x001A;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3SEL;   /* Port 3 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3SEL_bit;
} @ 0x001B;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};
*/



#define __MSP430_HAS_PORT3__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   USART 0  UART/SPI Mode
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char U0CTL;   /* USART 0 Control */

  struct
  {
    unsigned char SWRST           : 1; /* USART Software Reset */
    unsigned char MM              : 1; /* Master Mode off/on */
    unsigned char SYNC            : 1; /* UART / SPI mode */
    unsigned char LISTEN          : 1; /* Listen mode */
    unsigned char CHAR            : 1; /* Data 0:7-bits / 1:8-bits */
    unsigned char SPB             : 1; /* Stop Bits 0:one / 1: two */
    unsigned char PEV             : 1; /* Parity 0:odd / 1:even */
    unsigned char PENA            : 1; /* Parity enable */
  }U0CTL_bit;
} @0x0070;


enum {
  SWRST           = 0x0001,
  MM              = 0x0002,
  SYNC            = 0x0004,
  LISTEN          = 0x0008,
  CHAR            = 0x0010,
  SPB             = 0x0020,
  PEV             = 0x0040,
  PENA            = 0x0080
};


__no_init volatile union
{
  unsigned char U0TCTL;   /* USART 0 Transmit Control */

  struct
  {
    unsigned char TXEPT           : 1; /* TX Buffer empty */
    unsigned char STC             : 1; /* SPI: STC enable 0:on / 1:off */
    unsigned char TXWAKE          : 1; /* TX Wake up mode */
    unsigned char URXSE           : 1; /* Receive Start edge select */
    unsigned char SSEL0           : 1; /* Clock Source Select 0 */
    unsigned char SSEL1           : 1; /* Clock Source Select 1 */
    unsigned char CKPL            : 1; /* Clock Polarity */
    unsigned char CKPH            : 1; /* SPI: Clock Phase */
  }U0TCTL_bit;
} @0x0071;


enum {
  TXEPT           = 0x0001,
  STC             = 0x0002,
  TXWAKE          = 0x0004,
  URXSE           = 0x0008,
  SSEL0           = 0x0010,
  SSEL1           = 0x0020,
  CKPL            = 0x0040,
  CKPH            = 0x0080
};


__no_init volatile union
{
  unsigned char U0RCTL;   /* USART 0 Receive Control */

  struct
  {
    unsigned char RXERR           : 1; /* RX Error Error */
    unsigned char RXWAKE          : 1; /* RX Wake up detect */
    unsigned char URXWIE          : 1; /* RX Wake up interrupt enable */
    unsigned char URXEIE          : 1; /* RX Error interrupt enable */
    unsigned char BRK             : 1; /* Break detected */
    unsigned char OE              : 1; /* Overrun Error */
    unsigned char PE              : 1; /* Parity Error */
    unsigned char FE              : 1; /* Frame Error */
  }U0RCTL_bit;
} @0x0072;


enum {
  RXERR           = 0x0001,
  RXWAKE          = 0x0002,
  URXWIE          = 0x0004,
  URXEIE          = 0x0008,
  BRK             = 0x0010,
  OE              = 0x0020,
  PE              = 0x0040,
  FE              = 0x0080
};


  /* USART 0 Modulation Control */
__no_init volatile unsigned char U0MCTL @ 0x0073;



  /* USART 0 Baud Rate 0 */
__no_init volatile unsigned char U0BR0 @ 0x0074;



  /* USART 0 Baud Rate 1 */
__no_init volatile unsigned char U0BR1 @ 0x0075;



  /* USART 0 Receive Buffer */
__no_init volatile unsigned __READ char U0RXBUF @ 0x0076;



  /* USART 0 Transmit Buffer */
__no_init volatile unsigned char U0TXBUF @ 0x0077;


#define __MSP430_HAS_UART0__          /* Definition to show that Module is available */

#define UCTL0               U0CTL     /* USART 0 Control */
#define UTCTL0              U0TCTL    /* USART 0 Transmit Control */
#define URCTL0              U0RCTL    /* USART 0 Receive Control */
#define UMCTL0              U0MCTL    /* USART 0 Modulation Control */
#define UBR00               U0BR0     /* USART 0 Baud Rate 0 */
#define UBR10               U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF0              U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF0              U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL0_              U0CTL_    /* USART 0 Control */
#define UTCTL0_             U0TCTL_   /* USART 0 Transmit Control */
#define URCTL0_             U0RCTL_   /* USART 0 Receive Control */
#define UMCTL0_             U0MCTL_   /* USART 0 Modulation Control */
#define UBR00_              U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR10_              U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF0_             U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF0_             U0TXBUF_  /* USART 0 Transmit Buffer */
#define UCTL_0              U0CTL     /* USART 0 Control */
#define UTCTL_0             U0TCTL    /* USART 0 Transmit Control */
#define URCTL_0             U0RCTL    /* USART 0 Receive Control */
#define UMCTL_0             U0MCTL    /* USART 0 Modulation Control */
#define UBR0_0              U0BR0     /* USART 0 Baud Rate 0 */
#define UBR1_0              U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF_0             U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF_0             U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL_0_             U0CTL_    /* USART 0 Control */
#define UTCTL_0_            U0TCTL_   /* USART 0 Transmit Control */
#define URCTL_0_            U0RCTL_   /* USART 0 Receive Control */
#define UMCTL_0_            U0MCTL_   /* USART 0 Modulation Control */
#define UBR0_0_             U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR1_0_             U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF_0_            U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF_0_            U0TXBUF_  /* USART 0 Transmit Buffer */

/*-------------------------------------------------------------------------
 *   Timer A3
 *-------------------------------------------------------------------------*/



  /* Timer A Interrupt Vector Word */
__no_init volatile unsigned __READ short TAIV @ 0x012E;



__no_init volatile union
{
  unsigned short TACTL;   /* Timer A Control */

  struct
  {
    unsigned short TAIFG           : 1; /* Timer A counter interrupt flag */
    unsigned short TAIE            : 1; /* Timer A counter interrupt enable */
    unsigned short TACLR           : 1; /* Timer A counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TASSEL0         : 1; /* Timer A clock source select 0 */
    unsigned short TASSEL1         : 1; /* Timer A clock source select 1 */
  }TACTL_bit;
} @0x0160;


enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200
};


__no_init volatile union
{
  unsigned short TACCTL0;   /* Timer A Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL0_bit;
} @0x0162;


enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000
};


__no_init volatile union
{
  unsigned short TACCTL1;   /* Timer A Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL1_bit;
} @0x0164;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TACCTL2;   /* Timer A Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL2_bit;
} @0x0166;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer A Counter Register */
__no_init volatile unsigned short TAR @ 0x0170;



  /* Timer A Capture/Compare 0 */
__no_init volatile unsigned short TACCR0 @ 0x0172;



  /* Timer A Capture/Compare 1 */
__no_init volatile unsigned short TACCR1 @ 0x0174;



  /* Timer A Capture/Compare 2 */
__no_init volatile unsigned short TACCR2 @ 0x0176;


#define __MSP430_HAS_TA3__            /* Definition to show that Module is available */
/* Alternate register names */
#define CCTL0               TACCTL0   /* Timer A Capture/Compare Control 0 */
#define CCTL1               TACCTL1   /* Timer A Capture/Compare Control 1 */
#define CCTL2               TACCTL2   /* Timer A Capture/Compare Control 2 */
#define CCR0                TACCR0    /* Timer A Capture/Compare 0 */
#define CCR1                TACCR1    /* Timer A Capture/Compare 1 */
#define CCR2                TACCR2    /* Timer A Capture/Compare 2 */
#define CCTL0_              TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define CCTL1_              TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define CCTL2_              TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define CCR0_               TACCR0_   /* Timer A Capture/Compare 0 */
#define CCR1_               TACCR1_   /* Timer A Capture/Compare 1 */
#define CCR2_               TACCR2_   /* Timer A Capture/Compare 2 */
/* Alternate register names - 5xx style */
#define TA0IV               TAIV      /* Timer A Interrupt Vector Word */
#define TA0CTL              TACTL     /* Timer A Control */
#define TA0CCTL0            TACCTL0   /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1            TACCTL1   /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2            TACCTL2   /* Timer A Capture/Compare Control 2 */
#define TA0R                TAR       /* Timer A Counter Register */
#define TA0CCR0             TACCR0    /* Timer A Capture/Compare 0 */
#define TA0CCR1             TACCR1    /* Timer A Capture/Compare 1 */
#define TA0CCR2             TACCR2    /* Timer A Capture/Compare 2 */
#define TA0IV_              TAIV_     /* Timer A Interrupt Vector Word */
#define TA0CTL_             TACTL_    /* Timer A Control */
#define TA0CCTL0_           TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_           TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2_           TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define TA0R_               TAR_      /* Timer A Counter Register */
#define TA0CCR0_            TACCR0_   /* Timer A Capture/Compare 0 */
#define TA0CCR1_            TACCR1_   /* Timer A Capture/Compare 1 */
#define TA0CCR2_            TACCR2_   /* Timer A Capture/Compare 2 */
#define TIMER0_A1_VECTOR    TIMERA1_VECTOR /* Int. Vector: Timer A CC1-2, TA */
#define TIMER0_A0_VECTOR    TIMERA0_VECTOR /* Int. Vector: Timer A CC0 */

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */
/* TA3IV Definitions */
#define TAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define TAIV_TACCR1         (0x0002u)    /* TACCR1_CCIFG */
#define TAIV_TACCR2         (0x0004u)    /* TACCR2_CCIFG */
#define TAIV_6              (0x0006u)    /* Reserved */
#define TAIV_8              (0x0008u)    /* Reserved */
#define TAIV_TAIFG          (0x000Au)    /* TAIFG */

/*-------------------------------------------------------------------------
 *   System Clock
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char DCOCTL;   /* DCO Clock Frequency Control */

  struct
  {
    unsigned char MOD0            : 1; /* Modulation Bit 0 */
    unsigned char MOD1            : 1; /* Modulation Bit 1 */
    unsigned char MOD2            : 1; /* Modulation Bit 2 */
    unsigned char MOD3            : 1; /* Modulation Bit 3 */
    unsigned char MOD4            : 1; /* Modulation Bit 4 */
    unsigned char DCO0            : 1; /* DCO Select Bit 0 */
    unsigned char DCO1            : 1; /* DCO Select Bit 1 */
    unsigned char DCO2            : 1; /* DCO Select Bit 2 */
  }DCOCTL_bit;
} @0x0056;


enum {
  MOD0            = 0x0001,
  MOD1            = 0x0002,
  MOD2            = 0x0004,
  MOD3            = 0x0008,
  MOD4            = 0x0010,
  DCO0            = 0x0020,
  DCO1            = 0x0040,
  DCO2            = 0x0080
};


__no_init volatile union
{
  unsigned char BCSCTL1;   /* Basic Clock System Control 1 */

  struct
  {
    unsigned char RSEL0           : 1; /* Range Select Bit 0 */
    unsigned char RSEL1           : 1; /* Range Select Bit 1 */
    unsigned char RSEL2           : 1; /* Range Select Bit 2 */
    unsigned char XT5V            : 1; /* XT5V should always be reset */
    unsigned char DIVA0           : 1; /* ACLK Divider 0 */
    unsigned char DIVA1           : 1; /* ACLK Divider 1 */
    unsigned char XTS             : 1; /* LFXTCLK 0:Low Freq. / 1: High Freq. */
    unsigned char XT2OFF          : 1; /* Enable XT2CLK */
  }BCSCTL1_bit;
} @0x0057;


enum {
  RSEL0           = 0x0001,
  RSEL1           = 0x0002,
  RSEL2           = 0x0004,
  XT5V            = 0x0008,
  DIVA0           = 0x0010,
  DIVA1           = 0x0020,
  XTS             = 0x0040,
  XT2OFF          = 0x0080
};


__no_init volatile union
{
  unsigned char BCSCTL2;   /* Basic Clock System Control 2 */

  struct
  {
    unsigned char DCOR            : 1; /* Enable External Resistor : 1 */
    unsigned char DIVS0           : 1; /* SMCLK Divider 0 */
    unsigned char DIVS1           : 1; /* SMCLK Divider 1 */
    unsigned char SELS            : 1; /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
    unsigned char DIVM0           : 1; /* MCLK Divider 0 */
    unsigned char DIVM1           : 1; /* MCLK Divider 1 */
    unsigned char SELM0           : 1; /* MCLK Source Select 0 */
    unsigned char SELM1           : 1; /* MCLK Source Select 1 */
  }BCSCTL2_bit;
} @ 0x0058;


enum {
  DCOR            = 0x0001,
  DIVS0           = 0x0002,
  DIVS1           = 0x0004,
  SELS            = 0x0008,
  DIVM0           = 0x0010,
  DIVM1           = 0x0020,
  SELM0           = 0x0040,
  SELM1           = 0x0080
};



#define __MSP430_HAS_BASIC_CLOCK__    /* Definition to show that Module is available */

#define DIVA_0              (0x00)   /* ACLK Divider 0: /1 */
#define DIVA_1              (0x10)   /* ACLK Divider 1: /2 */
#define DIVA_2              (0x20)   /* ACLK Divider 2: /4 */
#define DIVA_3              (0x30)   /* ACLK Divider 3: /8 */

#define DIVS_0              (0x00)   /* SMCLK Divider 0: /1 */
#define DIVS_1              (0x02)   /* SMCLK Divider 1: /2 */
#define DIVS_2              (0x04)   /* SMCLK Divider 2: /4 */
#define DIVS_3              (0x06)   /* SMCLK Divider 3: /8 */

#define DIVM_0              (0x00)   /* MCLK Divider 0: /1 */
#define DIVM_1              (0x10)   /* MCLK Divider 1: /2 */
#define DIVM_2              (0x20)   /* MCLK Divider 2: /4 */
#define DIVM_3              (0x30)   /* MCLK Divider 3: /8 */

#define SELM_0              (0x00)   /* MCLK Source Select 0: DCOCLK */
#define SELM_1              (0x40)   /* MCLK Source Select 1: DCOCLK */
#define SELM_2              (0x80)   /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3              (0xC0)   /* MCLK Source Select 3: LFXTCLK */

/*-------------------------------------------------------------------------
 *   Flash
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short FCTL1;   /* FLASH Control 1 */

  struct
  {
    unsigned short                : 1;
    unsigned short ERASE           : 1; /* Enable bit for Flash segment erase */
    unsigned short MERAS           : 1; /* Enable bit for Flash mass erase */
    unsigned short                : 3;
    unsigned short WRT             : 1; /* Enable bit for Flash write */
    unsigned short BLKWRT          : 1; /* Enable bit for Flash segment write */
  }FCTL1_bit;
} @0x0128;


enum {
  ERASE           = 0x0002,
  MERAS           = 0x0004,
  WRT             = 0x0040,
  BLKWRT          = 0x0080
};


__no_init volatile union
{
  unsigned short FCTL2;   /* FLASH Control 2 */

  struct
  {
    unsigned short FN0             : 1; /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to: */
    unsigned short FN1             : 1; /* 32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1 */
    unsigned short FN2             : 1; /*  */
    unsigned short FN3             : 1; /*  */
    unsigned short FN4             : 1; /*  */
    unsigned short FN5             : 1; /*  */
    unsigned short FSSEL0          : 1; /* Flash clock select 0 */        /* to distinguish from USART SSELx */
    unsigned short FSSEL1          : 1; /* Flash clock select 1 */
  }FCTL2_bit;
} @0x012A;


enum {
  FN0             = 0x0001,
  FN1             = 0x0002,
  FN2             = 0x0004,
  FN3             = 0x0008,
  FN4             = 0x0010,
  FN5             = 0x0020,
  FSSEL0          = 0x0040,
  FSSEL1          = 0x0080
};


__no_init volatile union
{
  unsigned short FCTL3;   /* FLASH Control 3 */

  struct
  {
    unsigned short BUSY            : 1; /* Flash busy: 1 */
    unsigned short KEYV            : 1; /* Flash Key violation flag */
    unsigned short ACCVIFG         : 1; /* Flash Access violation flag */
    unsigned short WAIT            : 1; /* Wait flag for segment write */
    unsigned short LOCK            : 1; /* Lock bit: 1 - Flash is locked (read only) */
    unsigned short EMEX            : 1; /* Flash Emergency Exit */
  }FCTL3_bit;
} @ 0x012C;


enum {
  BUSY            = 0x0001,
  KEYV            = 0x0002,
  ACCVIFG         = 0x0004,
  WAIT            = 0x0008,
  LOCK            = 0x0010,
  EMEX            = 0x0020
};



#define __MSP430_HAS_FLASH__          /* Definition to show that Module is available */

#define FRKEY               (0x9600u)  /* Flash key returned by read */
#define FWKEY               (0xA500u)  /* Flash key for write */
#define FXKEY               (0x3300u)  /* for use with XOR instruction */
#define SEGWRT              (0x0080u)  /* old definition */ /* Enable bit for Flash segment write */

#define FSSEL_0             (0x0000u)  /* Flash clock select: 0 - ACLK */
#define FSSEL_1             (0x0040u)  /* Flash clock select: 1 - MCLK */
#define FSSEL_2             (0x0080u)  /* Flash clock select: 2 - SMCLK */
#define FSSEL_3             (0x00C0u)  /* Flash clock select: 3 - SMCLK */

/*-------------------------------------------------------------------------
 *   ADC10
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char ADC10DTC0;   /* ADC10 Data Transfer Control 0 */

  struct
  {
    unsigned char ADC10FETCH      : 1; /* This bit should normally be reset */
    unsigned char ADC10B1         : 1; /* ADC10 block one */
    unsigned char ADC10CT         : 1; /* ADC10 continuous transfer */
    unsigned char ADC10TB         : 1; /* ADC10 two-block mode */
  }ADC10DTC0_bit;
} @0x0048;


enum {
  ADC10FETCH      = 0x0001,
  ADC10B1         = 0x0002,
  ADC10CT         = 0x0004,
  ADC10TB         = 0x0008
};


  /* ADC10 Data Transfer Control 1 */
__no_init volatile unsigned char ADC10DTC1 @ 0x0049;



__no_init volatile union
{
  unsigned char ADC10AE;   /* ADC10 Analog Enable */

  struct
  {
    unsigned char ADC10AE0        : 1; /* ADC10 External Input Enable 0 */
    unsigned char ADC10AE1        : 1; /* ADC10 External Input Enable 1 */
    unsigned char ADC10AE2        : 1; /* ADC10 External Input Enable 2 */
    unsigned char ADC10AE3        : 1; /* ADC10 External Input Enable 3 */
    unsigned char ADC10AE4        : 1; /* ADC10 External Input Enable 4 */
    unsigned char ADC10AE5        : 1; /* ADC10 External Input Enable 5 */
    unsigned char ADC10AE6        : 1; /* ADC10 External Input Enable 6 */
    unsigned char ADC10AE7        : 1; /* ADC10 External Input Enable 7 */
  }ADC10AE_bit;
} @0x004A;


enum {
  ADC10AE0        = 0x0001,
  ADC10AE1        = 0x0002,
  ADC10AE2        = 0x0004,
  ADC10AE3        = 0x0008,
  ADC10AE4        = 0x0010,
  ADC10AE5        = 0x0020,
  ADC10AE6        = 0x0040,
  ADC10AE7        = 0x0080
};


__no_init volatile union
{
  unsigned short ADC10CTL0;   /* ADC10 Control 0 */

  struct
  {
    unsigned short ADC10SC         : 1; /* ADC10 Start Conversion */
    unsigned short ENC             : 1; /* ADC10 Enable Conversion */
    unsigned short ADC10IFG        : 1; /* ADC10 Interrupt Flag */
    unsigned short ADC10IE         : 1; /* ADC10 Interrupt Enalbe */
    unsigned short ADC10ON         : 1; /* ADC10 On/Enable */
    unsigned short REFON           : 1; /* ADC10 Reference on */
    unsigned short REF2_5V         : 1; /*  */
    unsigned short MSC             : 1; /* ADC10 Multiple SampleConversion */
    unsigned short REFBURST        : 1; /* ADC10 Reference Burst Mode */
    unsigned short REFOUT          : 1; /* ADC10 Enalbe output of Ref. */
    unsigned short ADC10SR         : 1; /* ADC10 Sampling Rate 0:200ksps / 1:50ksps */
    unsigned short ADC10SHT0       : 1; /* ADC10 Sample Hold Select Bit: 0 */
    unsigned short ADC10SHT1       : 1; /* ADC10 Sample Hold Select Bit: 1 */
    unsigned short SREF0           : 1; /* ADC10 Reference Select Bit: 0 */
    unsigned short SREF1           : 1; /* ADC10 Reference Select Bit: 1 */
    unsigned short SREF2           : 1; /* ADC10 Reference Select Bit: 2 */
  }ADC10CTL0_bit;
} @0x01B0;


enum {
  ADC10SC         = 0x0001,
  ENC             = 0x0002,
  ADC10IFG        = 0x0004,
  ADC10IE         = 0x0008,
  ADC10ON         = 0x0010,
  REFON           = 0x0020,
  REF2_5V         = 0x0040,
  MSC             = 0x0080,
  REFBURST        = 0x0100,
  REFOUT          = 0x0200,
  ADC10SR         = 0x0400,
  ADC10SHT0       = 0x0800,
  ADC10SHT1       = 0x1000,
  SREF0           = 0x2000,
  SREF1           = 0x4000,
  SREF2           = 0x8000
};


__no_init volatile union
{
  unsigned short ADC10CTL1;   /* ADC10 Control 1 */

  struct
  {
    unsigned short ADC10BUSY       : 1; /* ADC10 BUSY */
    unsigned short CONSEQ0         : 1; /* ADC10 Conversion Sequence Select 0 */
    unsigned short CONSEQ1         : 1; /* ADC10 Conversion Sequence Select 1 */
    unsigned short ADC10SSEL0      : 1; /* ADC10 Clock Source Select Bit: 0 */
    unsigned short ADC10SSEL1      : 1; /* ADC10 Clock Source Select Bit: 1 */
    unsigned short ADC10DIV0       : 1; /* ADC10 Clock Divider Select Bit: 0 */
    unsigned short ADC10DIV1       : 1; /* ADC10 Clock Divider Select Bit: 1 */
    unsigned short ADC10DIV2       : 1; /* ADC10 Clock Divider Select Bit: 2 */
    unsigned short ISSH            : 1; /* ADC10 Invert Sample Hold Signal */
    unsigned short ADC10DF         : 1; /* ADC10 Data Format 0:binary 1:2's complement */
    unsigned short SHS0            : 1; /* ADC10 Sample/Hold Source Bit: 0 */
    unsigned short SHS1            : 1; /* ADC10 Sample/Hold Source Bit: 1 */
    unsigned short INCH0           : 1; /* ADC10 Input Channel Select Bit: 0 */
    unsigned short INCH1           : 1; /* ADC10 Input Channel Select Bit: 1 */
    unsigned short INCH2           : 1; /* ADC10 Input Channel Select Bit: 2 */
    unsigned short INCH3           : 1; /* ADC10 Input Channel Select Bit: 3 */
  }ADC10CTL1_bit;
} @0x01B2;


enum {
  ADC10BUSY       = 0x0001,
  CONSEQ0         = 0x0002,
  CONSEQ1         = 0x0004,
  ADC10SSEL0      = 0x0008,
  ADC10SSEL1      = 0x0010,
  ADC10DIV0       = 0x0020,
  ADC10DIV1       = 0x0040,
  ADC10DIV2       = 0x0080,
  ISSH            = 0x0100,
  ADC10DF         = 0x0200,
  SHS0            = 0x0400,
  SHS1            = 0x0800,
  INCH0           = 0x1000,
  INCH1           = 0x2000,
  INCH2           = 0x4000,
  INCH3           = 0x8000
};


  /* ADC10 Memory */
__no_init volatile unsigned short ADC10MEM @ 0x01B4;



  /* ADC10 Data Transfer Start Address */
__no_init volatile unsigned short ADC10SA @ 0x01BC;


#define __MSP430_HAS_ADC10__            /* Definition to show that Module is available */
#define ADC10SHT_0          (0*0x800u)   /* 4 x ADC10CLKs */
#define ADC10SHT_1          (1*0x800u)   /* 8 x ADC10CLKs */
#define ADC10SHT_2          (2*0x800u)   /* 16 x ADC10CLKs */
#define ADC10SHT_3          (3*0x800u)   /* 64 x ADC10CLKs */

#define SREF_0              (0*0x2000u)  /* VR+ = AVCC and VR- = AVSS */
#define SREF_1              (1*0x2000u)  /* VR+ = VREF+ and VR- = AVSS */
#define SREF_2              (2*0x2000u)  /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_3              (3*0x2000u)  /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_4              (4*0x2000u)  /* VR+ = AVCC and VR- = VREF-/VEREF- */
#define SREF_5              (5*0x2000u)  /* VR+ = VREF+ and VR- = VREF-/VEREF- */
#define SREF_6              (6*0x2000u)  /* VR+ = VEREF+ and VR- = VREF-/VEREF- */
#define SREF_7              (7*0x2000u)  /* VR+ = VEREF+ and VR- = VREF-/VEREF- */

#define CONSEQ_0            (0*2u)       /* Single channel single conversion */
#define CONSEQ_1            (1*2u)       /* Sequence of channels */
#define CONSEQ_2            (2*2u)       /* Repeat single channel */
#define CONSEQ_3            (3*2u)       /* Repeat sequence of channels */

#define ADC10SSEL_0         (0*8u)       /* ADC10OSC */
#define ADC10SSEL_1         (1*8u)       /* ACLK */
#define ADC10SSEL_2         (2*8u)       /* MCLK */
#define ADC10SSEL_3         (3*8u)       /* SMCLK */

#define ADC10DIV_0          (0*0x20u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV_1          (1*0x20u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV_2          (2*0x20u)    /* ADC10 Clock Divider Select 2 */
#define ADC10DIV_3          (3*0x20u)    /* ADC10 Clock Divider Select 3 */
#define ADC10DIV_4          (4*0x20u)    /* ADC10 Clock Divider Select 4 */
#define ADC10DIV_5          (5*0x20u)    /* ADC10 Clock Divider Select 5 */
#define ADC10DIV_6          (6*0x20u)    /* ADC10 Clock Divider Select 6 */
#define ADC10DIV_7          (7*0x20u)    /* ADC10 Clock Divider Select 7 */

#define SHS_0               (0*0x400u)   /* ADC10SC */
#define SHS_1               (1*0x400u)   /* TA3 OUT1 */
#define SHS_2               (2*0x400u)   /* TA3 OUT0 */
#define SHS_3               (3*0x400u)   /* TA3 OUT2 */

#define INCH_0              (0*0x1000u)  /* Selects Channel 0 */
#define INCH_1              (1*0x1000u)  /* Selects Channel 1 */
#define INCH_2              (2*0x1000u)  /* Selects Channel 2 */
#define INCH_3              (3*0x1000u)  /* Selects Channel 3 */
#define INCH_4              (4*0x1000u)  /* Selects Channel 4 */
#define INCH_5              (5*0x1000u)  /* Selects Channel 5 */
#define INCH_6              (6*0x1000u)  /* Selects Channel 6 */
#define INCH_7              (7*0x1000u)  /* Selects Channel 7 */
#define INCH_8              (8*0x1000u)  /* Selects Channel 8 */
#define INCH_9              (9*0x1000u)  /* Selects Channel 9 */
#define INCH_10             (10*0x1000u) /* Selects Channel 10 */
#define INCH_11             (11*0x1000u) /* Selects Channel 11 */
#define INCH_12             (12*0x1000u) /* Selects Channel 12 */
#define INCH_13             (13*0x1000u) /* Selects Channel 13 */
#define INCH_14             (14*0x1000u) /* Selects Channel 14 */
#define INCH_15             (15*0x1000u) /* Selects Channel 15 */
#define ADC10DISABLE        (0x000)     /* ADC10DTC1 */




#pragma language=restore
#endif  /* __IAR_SYSTEMS_ICC__  */


/************************************************************
* Timer A interrupt vector value
************************************************************/

/* Compability definitions */

#define TAIV_CCIFG1         TAIV_TACCR1       /* Capture/compare 1 */
#define TAIV_CCIFG2         TAIV_TACCR2       /* Capture/compare 2 */
#define TAIV_CCIFG3         TAIV_6            /* Capture/compare 3 */
#define TAIV_CCIFG4         TAIV_8            /* Capture/compare 4 */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define PORT1_VECTOR        (2 * 2u)  /* 0xFFE4 Port 1 */
#define PORT2_VECTOR        (3 * 2u)  /* 0xFFE6 Port 2 */
#define ADC10_VECTOR        (5 * 2u)  /* 0xFFEA ADC10 */
#define USART0TX_VECTOR     (6 * 2u)  /* 0xFFEC USART 0 Transmit */
#define USART0RX_VECTOR     (7 * 2u)  /* 0xFFEE USART 0 Receive */
#define TIMERA1_VECTOR      (8 * 2u)  /* 0xFFF0 Timer A CC1-2, TA */
#define TIMERA0_VECTOR      (9 * 2u)  /* 0xFFF2 Timer A CC0 */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */
#define UART0TX_VECTOR      USART0TX_VECTOR
#define UART0RX_VECTOR      USART0RX_VECTOR


#endif /* __IO430xxxx */
