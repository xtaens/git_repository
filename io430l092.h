/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * msp430l092 devices.
 *
 * Copyright 2010-2012 IAR Systems AB.
 *
 *
 *
 ********************************************************************/

#ifndef __IO430C091
#define __IO430C091

#ifdef  __IAR_SYSTEMS_ICC__

#include "intrinsics.h"
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430l092.h file for use with ICC430/A430 only
#endif

#if __REGISTER_MODEL__ == __REGISTER_MODEL_REG20__
#define __ACCESS_20BIT_REG__  void __data20 * volatile
#else
#define __ACCESS_20BIT_REG__  volatile unsigned short  /* only short access from C is allowed in small memory model */
#endif


#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430XV2 CPU */


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
 *   Analog Pool
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short APCNF;   /* A-POOL Configuration Register */

  struct
  {
    unsigned short TA0EN           : 1; /* A-POOL TimerA0 trigger enable */
    unsigned short TA1EN           : 1; /* A-POOL TimerA1 trigger enable */
    unsigned short DFSET0          : 1; /* A-POOL Deglitch Filter Bit: 0 */
    unsigned short DFSET1          : 1; /* A-POOL Deglitch Filter Bit: 1 */
    unsigned short LCMP            : 1; /* A-POOL Latch comparator */
    unsigned short CMPON           : 1; /* A-POOL Comparator enable */
    unsigned short DBON            : 1; /* A-POOL DAC buffer enable signal */
    unsigned short CONVON          : 1; /* A-POOL Enable for converter’s resistor ladder */
    unsigned short CLKSEL0         : 1; /* A-POOL Conversion clock select Bit: 0 */
    unsigned short CLKSEL1         : 1; /* A-POOL Conversion clock select Bit: 1 */
    unsigned short EOCBU           : 1; /* A-POOL Enable bit for loading conversion buffer */
    unsigned short ATBU            : 1; /* A-POOL Automatic update of conversion register */
    unsigned short A3PSEL          : 1; /* A-POOL Analog input A3 access Bit */
    unsigned short APREFON         : 1; /* A-POOL Internal voltage reference enable */
    unsigned short VREFEN          : 1; /* A-POOL Reference voltage pin enable */
  } APCNF_bit;

  struct
  {
    unsigned char APCNF_L;
    unsigned char APCNF_H;
  };
} @0x01A0;

enum {
  TA0EN           = 0x0001,
  TA1EN           = 0x0002,
  DFSET0          = 0x0004,
  DFSET1          = 0x0008,
  LCMP            = 0x0010,
  CMPON           = 0x0020,
  DBON            = 0x0040,
  CONVON          = 0x0080,
  CLKSEL0         = 0x0100,
  CLKSEL1         = 0x0200,
  EOCBU           = 0x0400,
  ATBU            = 0x0800,
  A3PSEL          = 0x1000,
  APREFON         = 0x2000,
  VREFEN          = 0x4000
};

__no_init volatile union
{
  unsigned short APCTL;   /* A-POOL Control Register 1 */

  struct
  {
    unsigned short ODEN            : 1; /* A-POOL Output driver enable */
    unsigned short OSWP            : 1; /* A-POOL Output swap */
    unsigned short OSEL            : 1; /* A-POOL Output buffer select */
    unsigned short SLOPE           : 1; /* A-POOL Slope select of converter */
    unsigned short APNSEL0         : 1; /* A-POOL Neg. Channel Input Select 0 */
    unsigned short APNSEL1         : 1; /* A-POOL Neg. Channel Input Select 1 */
    unsigned short APNSEL2         : 1; /* A-POOL Neg. Channel Input Select 2 */
    unsigned short APNSEL3         : 1; /* A-POOL Neg. Channel Input Select 3 */
    unsigned short RUNSTOP         : 1; /* A-POOL Converter’s Run/Stop bit */
    unsigned short SBSTP           : 1; /* A-POOL Saturation based conversion stop enable */
    unsigned short CBSTP           : 1; /* A-POOL Comparator based conversion stop enable */
    unsigned short TBSTP           : 1; /* A-POOL Timer based conversion stop enable for TimerA0 */
    unsigned short APPSEL0         : 1; /* A-POOL Pos. Channel Input Select 0 */
    unsigned short APPSEL1         : 1; /* A-POOL Pos. Channel Input Select 1 */
    unsigned short APPSEL2         : 1; /* A-POOL Pos. Channel Input Select 2 */
    unsigned short APPSEL3         : 1; /* A-POOL Pos. Channel Input Select 3 */
  } APCTL_bit;

  struct
  {
    unsigned char APCTL_L;
    unsigned char APCTL_H;
  };
} @0x01A2;

enum {
  ODEN            = 0x0001,
  OSWP            = 0x0002,
  OSEL            = 0x0004,
  SLOPE           = 0x0008,
  APNSEL0         = 0x0010,
  APNSEL1         = 0x0020,
  APNSEL2         = 0x0040,
  APNSEL3         = 0x0080,
  RUNSTOP         = 0x0100,
  SBSTP           = 0x0200,
  CBSTP           = 0x0400,
  TBSTP           = 0x0800,
  APPSEL0         = 0x1000,
  APPSEL1         = 0x2000,
  APPSEL2         = 0x4000,
  APPSEL3         = 0x8000
};

__no_init volatile union
{
  unsigned short APOMR;   /* A-POOL Operation Mode Register 2 */

  struct
  {
    unsigned short CLKDIV0         : 1; /* A-POOL Prescaler Control Bit: 0 */
    unsigned short CLKDIV1         : 1; /* A-POOL Prescaler Control Bit: 1 */
    unsigned short CLKDIV2         : 1; /* A-POOL Prescaler Control Bit: 2 */
    unsigned short SAREN           : 1; /* A-POOL SAR conversion enable */
    unsigned short                : 4;
    unsigned short CTEN            : 1; /* A-POOL Continuous time mode of comparator */
    unsigned short AZCMP           : 1; /* A-POOL Clocked zero compensated long term comparison */
    unsigned short AZSWREQ         : 1; /* A-POOL SW request for Auto Zero Phase */
    unsigned short SVMINH          : 1; /* A-POOL Suppress the generation of an SVM interrupt event. */
  } APOMR_bit;

  struct
  {
    unsigned char APOMR_L;
    unsigned char APOMR_H;
  };
} @0x01A4;

enum {
  CLKDIV0         = 0x0001,
  CLKDIV1         = 0x0002,
  CLKDIV2         = 0x0004,
  SAREN           = 0x0008,
  CTEN            = 0x0100,
  AZCMP           = 0x0200,
  AZSWREQ         = 0x0400,
  SVMINH          = 0x0800
};

__no_init volatile union
{
  unsigned short APVDIV;   /* A-POOL Voltage Divider Register 3 */

  struct
  {
    unsigned short A0DIV           : 1; /* A-POOL Analog channel #0 voltage divider control */
    unsigned short A1DIV           : 1; /* A-POOL Analog channel #1 voltage divider control */
    unsigned short A2DIV0          : 1; /* A-POOL Analog channel #2 voltage divider control Bit : 0 */
    unsigned short A2DIV1          : 1; /* A-POOL Analog channel #2 voltage divider control Bit : 1 */
    unsigned short A3DIV0          : 1; /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
    unsigned short A3DIV1          : 1; /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
    unsigned short TMPSEN          : 1; /* A-POOL Temperature sensor enable */
    unsigned short VCCDIVEN        : 1; /* A-POOL VCC voltage divider enable */
    unsigned short                : 2;
    unsigned short CLKTRIM0        : 1; /* A-POOL Clock trimming Bit : 0 */
    unsigned short CLKTRIM1        : 1; /* A-POOL Clock trimming Bit : 1 */
  } APVDIV_bit;

  struct
  {
    unsigned char APVDIV_L;
    unsigned char APVDIV_H;
  };
} @0x01A6;

enum {
  A0DIV           = 0x0001,
  A1DIV           = 0x0002,
  A2DIV0          = 0x0004,
  A2DIV1          = 0x0008,
  A3DIV0          = 0x0010,
  A3DIV1          = 0x0020,
  TMPSEN          = 0x0040,
  VCCDIVEN        = 0x0080,
  CLKTRIM0        = 0x0400,
  CLKTRIM1        = 0x0800
};

__no_init volatile union
{
  unsigned short APTRIM;   /* A-POOL trimming register */

  struct
  {
    unsigned short REFTSEL         : 1; /* A-POOL Register bank used for the reference trimming */
    unsigned short                : 11;
    unsigned short REFTRIM0        : 1; /* A-POOL Reference trimming bit: 0 */
    unsigned short REFTRIM1        : 1; /* A-POOL Reference trimming bit: 1 */
    unsigned short REFTRIM2        : 1; /* A-POOL Reference trimming bit: 2 */
    unsigned short REFTRIM3        : 1; /* A-POOL Reference trimming bit: 3 */
  } APTRIM_bit;

  struct
  {
    unsigned char APTRIM_L;
    unsigned char APTRIM_H;
  };
} @0x01A8;

enum {
  REFTSEL         = 0x0001,
  REFTRIM0        = 0x1000,
  REFTRIM1        = 0x2000,
  REFTRIM2        = 0x4000,
  REFTRIM3        = 0x8000
};

__no_init volatile union
{
  unsigned short APINT;   /* A-POOL Integer Conversion Register */
  struct
  {
    unsigned char APINT_L;
    unsigned char APINT_H;
  };
} @0x01B0;

__no_init volatile union
{
  unsigned short APINTB;   /* A-POOL Integer Conversion Buffer Register */
  struct
  {
    unsigned char APINTB_L;
    unsigned char APINTB_H;
  };
} @0x01B2;

__no_init volatile union
{
  unsigned short APFRACT;   /* A-POOL Fractional Conversion Register */
  struct
  {
    unsigned char APFRACT_L;
    unsigned char APFRACT_H;
  };
} @0x01B4;

__no_init volatile union
{
  unsigned short APFRACTB;   /* A-POOL Fractional Conversion Buffer Register */
  struct
  {
    unsigned char APFRACTB_L;
    unsigned char APFRACTB_H;
  };
} @0x01B6;

__no_init volatile union
{
  unsigned short APIFG;   /* A-POOL Interrupt Flag Register */

  struct
  {
    unsigned short EOCIFG          : 1; /* A-POOL End of conversion interrupt flag */
    unsigned short CFIFG           : 1; /* A-POOL Comparator falling edge interrupt flag */
    unsigned short CRIFG           : 1; /* A-POOL Comparator rising edge interrupt flag */
    unsigned short REFOKIFG        : 1; /* A-POOL Reference voltage ready interrupt flag */
  } APIFG_bit;

  struct
  {
    unsigned char APIFG_L;
    unsigned char APIFG_H;
  };
} @0x01BA;

enum {
  EOCIFG          = 0x0001,
  CFIFG           = 0x0002,
  CRIFG           = 0x0004,
  REFOKIFG        = 0x0008
};

__no_init volatile union
{
  unsigned short APIE;   /* A-POOL Interrupt Enable Register */

  struct
  {
    unsigned short EOCIE           : 1; /* A-POOL End of conversion interrupt enable */
    unsigned short CFIE            : 1; /* A-POOL Comparator falling edge interrupt enable */
    unsigned short CRIE            : 1; /* A-POOL Comparator rising edge interrupt enable */
    unsigned short REFIKIE         : 1; /* A-POOL Reference voltage ready interrupt enable */
  } APIE_bit;

  struct
  {
    unsigned char APIE_L;
    unsigned char APIE_H;
  };
} @0x01BC;

enum {
  EOCIE           = 0x0001,
  CFIE            = 0x0002,
  CRIE            = 0x0004,
  REFIKIE         = 0x0008
};

__no_init volatile union
{
  unsigned __READ short APIV;   /* A-POOL Interrupt Vector Word */
  struct
  {
    unsigned __READ char APIV_L;
    unsigned __READ char APIV_H;
  };
} @0x01BE;

#define __MSP430_HAS_APOOL__           /* Definition to show that Module is available */
/* APCNF Control Bits */
#define TA0EN_L             (0x0001u)  /* A-POOL TimerA0 trigger enable */
#define TA1EN_L             (0x0002u)  /* A-POOL TimerA1 trigger enable */
#define DFSET0_L            (0x0004u)  /* A-POOL Deglitch Filter Bit: 0 */
#define DFSET1_L            (0x0008u)  /* A-POOL Deglitch Filter Bit: 1 */
#define LCMP_L              (0x0010u)  /* A-POOL Latch comparator */
#define CMPON_L             (0x0020u)  /* A-POOL Comparator enable */
#define DBON_L              (0x0040u)  /* A-POOL DAC buffer enable signal */
#define CONVON_L            (0x0080u)  /* A-POOL Enable for converter’s resistor ladder */
/* APCNF Control Bits */
#define CLKSEL0_H           (0x0001u)  /* A-POOL Conversion clock select Bit: 0 */
#define CLKSEL1_H           (0x0002u)  /* A-POOL Conversion clock select Bit: 1 */
#define EOCBU_H             (0x0004u)  /* A-POOL Enable bit for loading conversion buffer */
#define ATBU_H              (0x0008u)  /* A-POOL Automatic update of conversion register */
#define A3PSEL_H            (0x0010u)  /* A-POOL Analog input A3 access Bit */
#define APREFON_H           (0x0020u)  /* A-POOL Internal voltage reference enable */
#define VREFEN_H            (0x0040u)  /* A-POOL Reference voltage pin enable */

#define DFSET_0              (0x0000u)  /* A-POOL Deglitch Filter select: 0 */
#define DFSET_1              (0x0004u)  /* A-POOL Deglitch Filter select: 1 */
#define DFSET_2              (0x0008u)  /* A-POOL Deglitch Filter select: 2 */
#define DFSET_3              (0x000Cu)  /* A-POOL Deglitch Filter select: 3 */

#define CLKSEL_0             (0x0000u)  /* A-POOL Conversion clock select: 0 */
#define CLKSEL_1             (0x0100u)  /* A-POOL Conversion clock select: 1 */
#define CLKSEL_2             (0x0200u)  /* A-POOL Conversion clock select: 2 */
#define CLKSEL_VLOCLK        (0x0000u)  /* A-POOL Conversion clock select: VLOCLK */
#define CLKSEL_MCLK          (0x0100u)  /* A-POOL Conversion clock select: MCLK */
#define CLKSEL_SMCLK         (0x0200u)  /* A-POOL Conversion clock select: SMCLK */
/* APCTL Control Bits */
#define ODEN_L              (0x0001u)  /* A-POOL Output driver enable */
#define OSWP_L              (0x0002u)  /* A-POOL Output swap */
#define OSEL_L              (0x0004u)  /* A-POOL Output buffer select */
#define SLOPE_L             (0x0008u)  /* A-POOL Slope select of converter */
#define APNSEL0_L           (0x0010u)  /* A-POOL Neg. Channel Input Select 0 */
#define APNSEL1_L           (0x0020u)  /* A-POOL Neg. Channel Input Select 1 */
#define APNSEL2_L           (0x0040u)  /* A-POOL Neg. Channel Input Select 2 */
#define APNSEL3_L           (0x0080u)  /* A-POOL Neg. Channel Input Select 3 */
/* APCTL Control Bits */
#define RUNSTOP_H           (0x0001u)  /* A-POOL Converter’s Run/Stop bit */
#define SBSTP_H             (0x0002u)  /* A-POOL Saturation based conversion stop enable */
#define CBSTP_H             (0x0004u)  /* A-POOL Comparator based conversion stop enable */
#define TBSTP_H             (0x0008u)  /* A-POOL Timer based conversion stop enable for TimerA0 */
#define APPSEL0_H           (0x0010u)  /* A-POOL Pos. Channel Input Select 0 */
#define APPSEL1_H           (0x0020u)  /* A-POOL Pos. Channel Input Select 1 */
#define APPSEL2_H           (0x0040u)  /* A-POOL Pos. Channel Input Select 2 */
#define APPSEL3_H           (0x0080u)  /* A-POOL Pos. Channel Input Select 3 */

#define APNSEL_0             (0x0000u)  /* A-POOL V- terminal Input Select: Channel 0 */
#define APNSEL_1             (0x0010u)  /* A-POOL V- terminal Input Select: Channel 1 */
#define APNSEL_2             (0x0020u)  /* A-POOL V- terminal Input Select: Channel 2 */
#define APNSEL_3             (0x0030u)  /* A-POOL V- terminal Input Select: Channel 3 */
#define APNSEL_4             (0x0040u)  /* A-POOL V- terminal Input Select: Channel 4 */
#define APNSEL_5             (0x0050u)  /* A-POOL V- terminal Input Select: Channel 5 */
#define APNSEL_6             (0x0060u)  /* A-POOL V- terminal Input Select: Channel 6 */
#define APNSEL_7             (0x0070u)  /* A-POOL V- terminal Input Select: Channel 7 */

#define APPSEL_0             (0x0000u)  /* A-POOL V+ Terminal Input Select: Channel 0 */
#define APPSEL_1             (0x1000u)  /* A-POOL V+ Terminal Input Select: Channel 1 */
#define APPSEL_2             (0x2000u)  /* A-POOL V+ Terminal Input Select: Channel 2 */
#define APPSEL_3             (0x3000u)  /* A-POOL V+ Terminal Input Select: Channel 3 */
#define APPSEL_4             (0x4000u)  /* A-POOL V+ Terminal Input Select: Channel 4 */
#define APPSEL_5             (0x5000u)  /* A-POOL V+ Terminal Input Select: Channel 5 */
#define APPSEL_6             (0x6000u)  /* A-POOL V+ Terminal Input Select: Channel 6 */
#define APPSEL_7             (0x7000u)  /* A-POOL V+ Terminal Input Select: Channel 7 */
#define APPSEL_8             (0x8000u)  /* A-POOL V+ Terminal Input Select: Channel 8 */
/* APVDIV Control Bits */
#define A0DIV_L             (0x0001u)  /* A-POOL Analog channel #0 voltage divider control */
#define A1DIV_L             (0x0002u)  /* A-POOL Analog channel #1 voltage divider control */
#define A2DIV0_L            (0x0004u)  /* A-POOL Analog channel #2 voltage divider control Bit : 0 */
#define A2DIV1_L            (0x0008u)  /* A-POOL Analog channel #2 voltage divider control Bit : 1 */
#define A3DIV0_L            (0x0010u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define A3DIV1_L            (0x0020u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define TMPSEN_L            (0x0040u)  /* A-POOL Temperature sensor enable */
#define VCCDIVEN_L          (0x0080u)  /* A-POOL VCC voltage divider enable */
#define CLKTRIM0_H          (0x0004u)  /* A-POOL Clock trimming Bit : 0 */
#define CLKTRIM1_H          (0x0008u)  /* A-POOL Clock trimming Bit : 1 */

#define A2DIV_0              (0x0000u)  /* A-POOL Analog channel #2 voltage divider control: 0 */
#define A2DIV_1              (0x0004u)  /* A-POOL Analog channel #2 voltage divider control: 1 */
#define A2DIV_2              (0x0008u)  /* A-POOL Analog channel #2 voltage divider control: 2 */
#define A2DIV_3              (0x000Cu)  /* A-POOL Analog channel #2 voltage divider control: 3 */

#define A3DIV_0              (0x0000u)  /* A-POOL Analog channel #3 voltage divider control: 0 */
#define A3DIV_1              (0x0010u)  /* A-POOL Analog channel #3 voltage divider control: 1 */
#define A3DIV_2              (0x0020u)  /* A-POOL Analog channel #3 voltage divider control: 2 */
#define A3DIV_3              (0x0030u)  /* A-POOL Analog channel #3 voltage divider control: 3 */

#define CLKTRIM_0            (0x0000u)  /* A-POOL Clock trimming: 0 */
#define CLKTRIM_1            (0x0400u)  /* A-POOL Clock trimming: 1 */
#define CLKTRIM_2            (0x0800u)  /* A-POOL Clock trimming: 2 */
#define CLKTRIM_3            (0x0C00u)  /* A-POOL Clock trimming: 3 */

#define REFTRIM_0            (0x0000u)  /* A-POOL Reference trimming: 0 */
#define REFTRIM_1            (0x1000u)  /* A-POOL Reference trimming: 1 */
#define REFTRIM_2            (0x2000u)  /* A-POOL Reference trimming: 2 */
#define REFTRIM_3            (0x3000u)  /* A-POOL Reference trimming: 3 */
#define REFTRIM_4            (0x4000u)  /* A-POOL Reference trimming: 4 */
#define REFTRIM_5            (0x5000u)  /* A-POOL Reference trimming: 5 */
#define REFTRIM_6            (0x6000u)  /* A-POOL Reference trimming: 6 */
#define REFTRIM_7            (0x7000u)  /* A-POOL Reference trimming: 7 */
/* APTRIM Control Bits */
#define REFTSEL_L           (0x0001u)  /* A-POOL Register bank used for the reference trimming */
/* APTRIM Control Bits */
#define REFTRIM0_H          (0x0010u)  /* A-POOL Reference trimming bit: 0 */
#define REFTRIM1_H          (0x0020u)  /* A-POOL Reference trimming bit: 1 */
#define REFTRIM2_H          (0x0040u)  /* A-POOL Reference trimming bit: 2 */
#define REFTRIM3_H          (0x0080u)  /* A-POOL Reference trimming bit: 3 */
/* APOMR Control Bits */
#define CLKDIV0_L           (0x0001u)  /* A-POOL Prescaler Control Bit: 0 */
#define CLKDIV1_L           (0x0002u)  /* A-POOL Prescaler Control Bit: 1 */
#define CLKDIV2_L           (0x0004u)  /* A-POOL Prescaler Control Bit: 2 */
#define SAREN_L             (0x0008u)  /* A-POOL SAR conversion enable */
/* APOMR Control Bits */
#define CTEN_H              (0x0001u)  /* A-POOL Continuous time mode of comparator */
#define AZCMP_H             (0x0002u)  /* A-POOL Clocked zero compensated long term comparison */
#define AZSWREQ_H           (0x0004u)  /* A-POOL SW request for Auto Zero Phase */
#define SVMINH_H            (0x0008u)  /* A-POOL Suppress the generation of an SVM interrupt event. */

#define CLKDIV_0             (0x0000u)  /* A-POOL Prescaler Control 0 : /1 */
#define CLKDIV_1             (0x0001u)  /* A-POOL Prescaler Control 1 : /2 */
#define CLKDIV_2             (0x0002u)  /* A-POOL Prescaler Control 2 : /4 */
#define CLKDIV_3             (0x0003u)  /* A-POOL Prescaler Control 3 : /8 */
#define CLKDIV_4             (0x0004u)  /* A-POOL Prescaler Control 4 : /16 */
#define CLKDIV_5             (0x0005u)  /* A-POOL Prescaler Control 5 : /32 */
#define CLKDIV__1            (0x0000u)  /* A-POOL Prescaler Control 0 : /1 */
#define CLKDIV__2            (0x0001u)  /* A-POOL Prescaler Control 1 : /2 */
#define CLKDIV__4            (0x0002u)  /* A-POOL Prescaler Control 2 : /4 */
#define CLKDIV__8            (0x0003u)  /* A-POOL Prescaler Control 3 : /8 */
#define CLKDIV__16           (0x0004u)  /* A-POOL Prescaler Control 4 : /16 */
#define CLKDIV__32           (0x0005u)  /* A-POOL Prescaler Control 5 : /32 */
/* APIFG Control Bits */
#define EOCIFG_L            (0x0001u)  /* A-POOL End of conversion interrupt flag */
#define CFIFG_L             (0x0002u)  /* A-POOL Comparator falling edge interrupt flag */
#define CRIFG_L             (0x0004u)  /* A-POOL Comparator rising edge interrupt flag */
#define REFOKIFG_L          (0x0008u)  /* A-POOL Reference voltage ready interrupt flag */
/* APIFG Control Bits */
#define EOCIE_L             (0x0001u)  /* A-POOL End of conversion interrupt enable */
#define CFIE_L              (0x0002u)  /* A-POOL Comparator falling edge interrupt enable */
#define CRIE_L              (0x0004u)  /* A-POOL Comparator rising edge interrupt enable */
#define REFIKIE_L           (0x0008u)  /* A-POOL Reference voltage ready interrupt enable */
/* APIV Definitions */
#define APIV_NONE           (0x0000u)    /* No Interrupt pending */
#define APIV_EOCIF          (0x0002u)    /* EOCIFG */
#define APIV_CFIFG          (0x0004u)    /* CFIFG */
#define APIV_CRIFG          (0x0006u)    /* CRIFG */

/*-------------------------------------------------------------------------
 *   CCS  Compact System Clock
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short CCSCTL0;   /* CCS Control Register 0 */
  struct
  {
    unsigned char CCSCTL0_L;
    unsigned char CCSCTL0_H;
  };
} @0x0160;

__no_init volatile union
{
  unsigned short CCSCTL1;   /* CCS Control Register 1 */

  struct
  {
    unsigned short DIVCLK          : 1; /* Clock division for CLKIN / X-OSC */
  } CCSCTL1_bit;

  struct
  {
    unsigned char CCSCTL1_L;
    unsigned char CCSCTL1_H;
  };
} @0x0162;

enum {
  DIVCLK          = 0x0001
};

__no_init volatile union
{
  unsigned short CCSCTL2;   /* CCS Control Register 2 */

  struct
  {
    unsigned short FSEL0           : 1; /* Frequency trimming of the HF-OSC Bit: 0 */
    unsigned short FSEL1           : 1; /* Frequency trimming of the HF-OSC Bit: 1 */
    unsigned short FSEL2           : 1; /* Frequency trimming of the HF-OSC Bit: 2 */
    unsigned short FSEL3           : 1; /* Frequency trimming of the HF-OSC Bit: 3 */
    unsigned short FSEL4           : 1; /* Frequency trimming of the HF-OSC Bit: 4 */
    unsigned short FSEL5           : 1; /* Frequency trimming of the HF-OSC Bit: 5 */
    unsigned short FSEL6           : 1; /* Frequency trimming of the HF-OSC Bit: 6 */
  } CCSCTL2_bit;

  struct
  {
    unsigned char CCSCTL2_L;
    unsigned char CCSCTL2_H;
  };
} @0x0164;

enum {
  FSEL0           = 0x0001,
  FSEL1           = 0x0002,
  FSEL2           = 0x0004,
  FSEL3           = 0x0008,
  FSEL4           = 0x0010,
  FSEL5           = 0x0020,
  FSEL6           = 0x0040
};

__no_init volatile union
{
  unsigned short CCSCTL4;   /* CCS Control Register 4 */

  struct
  {
    unsigned short SELM0           : 1; /* MCLK Source Select Bit: 0 */
    unsigned short SELM1           : 1; /* MCLK Source Select Bit: 1 */
    unsigned short                : 2;
    unsigned short SELS0           : 1; /* SMCLK Source Select Bit: 0 */
    unsigned short SELS1           : 1; /* SMCLK Source Select Bit: 1 */
    unsigned short                : 2;
    unsigned short SELA0           : 1; /* ACLK Source Select Bit: 0 */
    unsigned short SELA1           : 1; /* ACLK Source Select Bit: 1 */
  } CCSCTL4_bit;

  struct
  {
    unsigned char CCSCTL4_L;
    unsigned char CCSCTL4_H;
  };
} @0x0168;

enum {
  SELM0           = 0x0001,
  SELM1           = 0x0002,
  SELS0           = 0x0010,
  SELS1           = 0x0020,
  SELA0           = 0x0100,
  SELA1           = 0x0200
};

__no_init volatile union
{
  unsigned short CCSCTL5;   /* CCS Control Register 5 */

  struct
  {
    unsigned short DIVM0           : 1; /* MCLK Divider Bit: 0 */
    unsigned short DIVM1           : 1; /* MCLK Divider Bit: 1 */
    unsigned short DIVM2           : 1; /* MCLK Divider Bit: 2 */
    unsigned short                : 1;
    unsigned short DIVS0           : 1; /* SMCLK Divider Bit: 0 */
    unsigned short DIVS1           : 1; /* SMCLK Divider Bit: 1 */
    unsigned short DIVS2           : 1; /* SMCLK Divider Bit: 2 */
    unsigned short                : 1;
    unsigned short DIVA0           : 1; /* ACLK Divider Bit: 0 */
    unsigned short DIVA1           : 1; /* ACLK Divider Bit: 1 */
    unsigned short DIVA2           : 1; /* ACLK Divider Bit: 2 */
  } CCSCTL5_bit;

  struct
  {
    unsigned char CCSCTL5_L;
    unsigned char CCSCTL5_H;
  };
} @0x016A;

enum {
  DIVM0           = 0x0001,
  DIVM1           = 0x0002,
  DIVM2           = 0x0004,
  DIVS0           = 0x0010,
  DIVS1           = 0x0020,
  DIVS2           = 0x0040,
  DIVA0           = 0x0100,
  DIVA1           = 0x0200,
  DIVA2           = 0x0400
};

__no_init volatile union
{
  unsigned short CCSCTL6;   /* CCS Control Register 6 */

  struct
  {
    unsigned short XTOFF           : 1; /* Disable XT oscillator */
  } CCSCTL6_bit;

  struct
  {
    unsigned char CCSCTL6_L;
    unsigned char CCSCTL6_H;
  };
} @0x016C;

enum {
  XTOFF           = 0x0001
};

__no_init volatile union
{
  unsigned short CCSCTL7;   /* CCS Control Register 7 */

  struct
  {
    unsigned short XOFFG           : 1; /* X-tal Oscillator Fault Flag */
    unsigned short HFOFFG          : 1; /* High Frequency Oscillator Fault Flag */
  } CCSCTL7_bit;

  struct
  {
    unsigned char CCSCTL7_L;
    unsigned char CCSCTL7_H;
  };
} @0x016E;

enum {
  XOFFG           = 0x0001,
  HFOFFG          = 0x0002
};

__no_init volatile union
{
  unsigned short CCSCTL8;   /* CCS Control Register 8 */

  struct
  {
    unsigned short ACLKREQEN       : 1; /* ACLK Clock Request Enable */
    unsigned short MCLKREQEN       : 1; /* MCLK Clock Request Enable */
    unsigned short SMCLKREQEN      : 1; /* SMCLK Clock Request Enable */
  } CCSCTL8_bit;

  struct
  {
    unsigned char CCSCTL8_L;
    unsigned char CCSCTL8_H;
  };
} @0x0170;

enum {
  ACLKREQEN       = 0x0001,
  MCLKREQEN       = 0x0002,
  SMCLKREQEN      = 0x0004
};



#define __MSP430_HAS_CCS__            /* Definition to show that Module is available */
/* CCSCTL0 Control Bits */
#define CCSKEY               (0xA500u)    /* CCS Password */
/* CCSCTL1 Control Bits */
#define DIVCLK_L            (0x0001u)    /* Clock division for CLKIN / X-OSC */
/* CCSCTL2 Control Bits */
#define FSEL0_L             (0x0001u)    /* Frequency trimming of the HF-OSC Bit: 0 */
#define FSEL1_L             (0x0002u)    /* Frequency trimming of the HF-OSC Bit: 1 */
#define FSEL2_L             (0x0004u)    /* Frequency trimming of the HF-OSC Bit: 2 */
#define FSEL3_L             (0x0008u)    /* Frequency trimming of the HF-OSC Bit: 3 */
#define FSEL4_L             (0x0010u)    /* Frequency trimming of the HF-OSC Bit: 4 */
#define FSEL5_L             (0x0020u)    /* Frequency trimming of the HF-OSC Bit: 5 */
#define FSEL6_L             (0x0040u)    /* Frequency trimming of the HF-OSC Bit: 6 */
/* CCSCTL4 Control Bits */
#define SELM0_L             (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELS0_L             (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELA0_H             (0x0001u)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002u)   /* ACLK Source Select Bit: 1 */

#define SELM_0              (0x0000u)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001u)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002u)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003u)   /* MCLK Source Select 3 */
#define SELM__HFCLK         (0x0000u)   /* MCLK Source Select HFCLK */
#define SELM__LFCLK         (0x0001u)   /* MCLK Source Select LFCLK */
#define SELM__CLKIN         (0x0002u)   /* MCLK Source Select CLKIN */

#define SELS_0              (0x0000u)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010u)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020u)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030u)   /* SMCLK Source Select 3 */
#define SELS__HFCLK         (0x0000u)   /* SMCLK Source Select HFCLK */
#define SELS__LFCLK         (0x0010u)   /* SMCLK Source Select LFCLK */
#define SELS__CLKIN         (0x0020u)   /* SMCLK Source Select CLKIN */

#define SELA_0              (0x0000u)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100u)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200u)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300u)   /* ACLK Source Select 3 */
#define SELA__HFCLK         (0x0000u)   /* ACLK Source Select HFCLK */
#define SELA__LFCLK         (0x0100u)   /* ACLK Source Select LFCLK */
#define SELA__CLKIN         (0x0200u)   /* ACLK Source Select CLKIN */
/* CCSCTL5 Control Bits */
#define DIVM0_L             (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1_L             (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2_L             (0x0004u)   /* MCLK Divider Bit: 2 */
#define DIVS0_L             (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1_L             (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2_L             (0x0040u)   /* SMCLK Divider Bit: 2 */
#define DIVA0_H             (0x0001u)   /* ACLK Divider Bit: 0 */
#define DIVA1_H             (0x0002u)   /* ACLK Divider Bit: 1 */
#define DIVA2_H             (0x0004u)   /* ACLK Divider Bit: 2 */

#define DIVM_0              (0x0000u)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001u)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002u)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003u)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004u)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005u)    /* MCLK Source Divider 5 */
#define DIVM__1             (0x0000u)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001u)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002u)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003u)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004u)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005u)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000u)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010u)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020u)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030u)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040u)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050u)    /* SMCLK Source Divider 5 */
#define DIVS__1             (0x0000u)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010u)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020u)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030u)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040u)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050u)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000u)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100u)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200u)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300u)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400u)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500u)    /* ACLK Source Divider 5 */
#define DIVA__1             (0x0000u)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100u)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200u)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300u)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400u)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500u)    /* ACLK Source Divider f(ACLK)/32 */
/* CCSCTL6 Control Bits */
#define XTOFF_L             (0x0001u)    /* Disable XT oscillator */
/* CCSCTL7 Control Bits */
#define XOFFG_L             (0x0001u)    /* X-tal Oscillator Fault Flag */
#define HFOFFG_L            (0x0002u)    /* High Frequency Oscillator Fault Flag */
/* CCSCTL8 Control Bits */
#define ACLKREQEN_L         (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004u)    /* SMCLK Clock Request Enable */

/*-------------------------------------------------------------------------
 *   Port A
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PAIN;   /* Port A Input */

  struct
  {
    unsigned __READ short PAIN0           : 1; /*  */
    unsigned __READ short PAIN1           : 1; /*  */
    unsigned __READ short PAIN2           : 1; /*  */
    unsigned __READ short PAIN3           : 1; /*  */
    unsigned __READ short PAIN4           : 1; /*  */
    unsigned __READ short PAIN5           : 1; /*  */
    unsigned __READ short PAIN6           : 1; /*  */
    unsigned __READ short PAIN7           : 1; /*  */
    unsigned __READ short PAIN8           : 1; /*  */
    unsigned __READ short PAIN9           : 1; /*  */
    unsigned __READ short PAIN10          : 1; /*  */
    unsigned __READ short PAIN11          : 1; /*  */
    unsigned __READ short PAIN12          : 1; /*  */
    unsigned __READ short PAIN13          : 1; /*  */
    unsigned __READ short PAIN14          : 1; /*  */
    unsigned __READ short PAIN15          : 1; /*  */
  } PAIN_bit;

  struct
  {
    unsigned __READ char PAIN_L;
    unsigned __READ char PAIN_H;
  };
  struct
  {
    unsigned char P1IN;   /* Port 1 Input */
    unsigned char P2IN;   /* Port 2 Input */
  };
  struct
  {
    struct
    {
      unsigned char P1IN0           : 1; /*  */
      unsigned char P1IN1           : 1; /*  */
      unsigned char P1IN2           : 1; /*  */
      unsigned char P1IN3           : 1; /*  */
      unsigned char P1IN4           : 1; /*  */
      unsigned char P1IN5           : 1; /*  */
      unsigned char P1IN6           : 1; /*  */
      unsigned char P1IN7           : 1; /*  */
    } P1IN_bit;

    struct
    {
      unsigned char P2IN0           : 1; /*  */
      unsigned char P2IN1           : 1; /*  */
      unsigned char P2IN2           : 1; /*  */
      unsigned char P2IN3           : 1; /*  */
      unsigned char P2IN4           : 1; /*  */
      unsigned char P2IN5           : 1; /*  */
      unsigned char P2IN6           : 1; /*  */
      unsigned char P2IN7           : 1; /*  */
    } P2IN_bit;
  }; 
} @0x0200;

enum {
  PAIN0           = 0x0001,
  PAIN1           = 0x0002,
  PAIN2           = 0x0004,
  PAIN3           = 0x0008,
  PAIN4           = 0x0010,
  PAIN5           = 0x0020,
  PAIN6           = 0x0040,
  PAIN7           = 0x0080,
  PAIN8           = 0x0100,
  PAIN9           = 0x0200,
  PAIN10          = 0x0400,
  PAIN11          = 0x0800,
  PAIN12          = 0x1000,
  PAIN13          = 0x2000,
  PAIN14          = 0x4000,
  PAIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PAOUT;   /* Port A Output */

  struct
  {
    unsigned short PAOUT0          : 1; /*  */
    unsigned short PAOUT1          : 1; /*  */
    unsigned short PAOUT2          : 1; /*  */
    unsigned short PAOUT3          : 1; /*  */
    unsigned short PAOUT4          : 1; /*  */
    unsigned short PAOUT5          : 1; /*  */
    unsigned short PAOUT6          : 1; /*  */
    unsigned short PAOUT7          : 1; /*  */
    unsigned short PAOUT8          : 1; /*  */
    unsigned short PAOUT9          : 1; /*  */
    unsigned short PAOUT10         : 1; /*  */
    unsigned short PAOUT11         : 1; /*  */
    unsigned short PAOUT12         : 1; /*  */
    unsigned short PAOUT13         : 1; /*  */
    unsigned short PAOUT14         : 1; /*  */
    unsigned short PAOUT15         : 1; /*  */
  } PAOUT_bit;

  struct
  {
    unsigned char PAOUT_L;
    unsigned char PAOUT_H;
  };
  struct
  {
    unsigned char P1OUT;   /* Port 1 Output */
    unsigned char P2OUT;   /* Port 2 Output */
  };
  struct
  {
    struct
    {
      unsigned char P1OUT0          : 1; /*  */
      unsigned char P1OUT1          : 1; /*  */
      unsigned char P1OUT2          : 1; /*  */
      unsigned char P1OUT3          : 1; /*  */
      unsigned char P1OUT4          : 1; /*  */
      unsigned char P1OUT5          : 1; /*  */
      unsigned char P1OUT6          : 1; /*  */
      unsigned char P1OUT7          : 1; /*  */
    } P1OUT_bit;

    struct
    {
      unsigned char P2OUT0          : 1; /*  */
      unsigned char P2OUT1          : 1; /*  */
      unsigned char P2OUT2          : 1; /*  */
      unsigned char P2OUT3          : 1; /*  */
      unsigned char P2OUT4          : 1; /*  */
      unsigned char P2OUT5          : 1; /*  */
      unsigned char P2OUT6          : 1; /*  */
      unsigned char P2OUT7          : 1; /*  */
    } P2OUT_bit;
  }; 
} @0x0202;

enum {
  PAOUT0          = 0x0001,
  PAOUT1          = 0x0002,
  PAOUT2          = 0x0004,
  PAOUT3          = 0x0008,
  PAOUT4          = 0x0010,
  PAOUT5          = 0x0020,
  PAOUT6          = 0x0040,
  PAOUT7          = 0x0080,
  PAOUT8          = 0x0100,
  PAOUT9          = 0x0200,
  PAOUT10         = 0x0400,
  PAOUT11         = 0x0800,
  PAOUT12         = 0x1000,
  PAOUT13         = 0x2000,
  PAOUT14         = 0x4000,
  PAOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PADIR;   /* Port A Direction */

  struct
  {
    unsigned short PADIR0          : 1; /*  */
    unsigned short PADIR1          : 1; /*  */
    unsigned short PADIR2          : 1; /*  */
    unsigned short PADIR3          : 1; /*  */
    unsigned short PADIR4          : 1; /*  */
    unsigned short PADIR5          : 1; /*  */
    unsigned short PADIR6          : 1; /*  */
    unsigned short PADIR7          : 1; /*  */
    unsigned short PADIR8          : 1; /*  */
    unsigned short PADIR9          : 1; /*  */
    unsigned short PADIR10         : 1; /*  */
    unsigned short PADIR11         : 1; /*  */
    unsigned short PADIR12         : 1; /*  */
    unsigned short PADIR13         : 1; /*  */
    unsigned short PADIR14         : 1; /*  */
    unsigned short PADIR15         : 1; /*  */
  } PADIR_bit;

  struct
  {
    unsigned char PADIR_L;
    unsigned char PADIR_H;
  };
  struct
  {
    unsigned char P1DIR;   /* Port 1 Direction */
    unsigned char P2DIR;   /* Port 2 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P1DIR0          : 1; /*  */
      unsigned char P1DIR1          : 1; /*  */
      unsigned char P1DIR2          : 1; /*  */
      unsigned char P1DIR3          : 1; /*  */
      unsigned char P1DIR4          : 1; /*  */
      unsigned char P1DIR5          : 1; /*  */
      unsigned char P1DIR6          : 1; /*  */
      unsigned char P1DIR7          : 1; /*  */
    } P1DIR_bit;

    struct
    {
      unsigned char P2DIR0          : 1; /*  */
      unsigned char P2DIR1          : 1; /*  */
      unsigned char P2DIR2          : 1; /*  */
      unsigned char P2DIR3          : 1; /*  */
      unsigned char P2DIR4          : 1; /*  */
      unsigned char P2DIR5          : 1; /*  */
      unsigned char P2DIR6          : 1; /*  */
      unsigned char P2DIR7          : 1; /*  */
    } P2DIR_bit;
  }; 
} @0x0204;

enum {
  PADIR0          = 0x0001,
  PADIR1          = 0x0002,
  PADIR2          = 0x0004,
  PADIR3          = 0x0008,
  PADIR4          = 0x0010,
  PADIR5          = 0x0020,
  PADIR6          = 0x0040,
  PADIR7          = 0x0080,
  PADIR8          = 0x0100,
  PADIR9          = 0x0200,
  PADIR10         = 0x0400,
  PADIR11         = 0x0800,
  PADIR12         = 0x1000,
  PADIR13         = 0x2000,
  PADIR14         = 0x4000,
  PADIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PAREN;   /* Port A Resistor Enable */

  struct
  {
    unsigned short PAREN0          : 1; /*  */
    unsigned short PAREN1          : 1; /*  */
    unsigned short PAREN2          : 1; /*  */
    unsigned short PAREN3          : 1; /*  */
    unsigned short PAREN4          : 1; /*  */
    unsigned short PAREN5          : 1; /*  */
    unsigned short PAREN6          : 1; /*  */
    unsigned short PAREN7          : 1; /*  */
    unsigned short PAREN8          : 1; /*  */
    unsigned short PAREN9          : 1; /*  */
    unsigned short PAREN10         : 1; /*  */
    unsigned short PAREN11         : 1; /*  */
    unsigned short PAREN12         : 1; /*  */
    unsigned short PAREN13         : 1; /*  */
    unsigned short PAREN14         : 1; /*  */
    unsigned short PAREN15         : 1; /*  */
  } PAREN_bit;

  struct
  {
    unsigned char PAREN_L;
    unsigned char PAREN_H;
  };
  struct
  {
    unsigned char P1REN;   /* Port 1 Resistor Enable */
    unsigned char P2REN;   /* Port 2 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P1REN0          : 1; /*  */
      unsigned char P1REN1          : 1; /*  */
      unsigned char P1REN2          : 1; /*  */
      unsigned char P1REN3          : 1; /*  */
      unsigned char P1REN4          : 1; /*  */
      unsigned char P1REN5          : 1; /*  */
      unsigned char P1REN6          : 1; /*  */
      unsigned char P1REN7          : 1; /*  */
    } P1REN_bit;

    struct
    {
      unsigned char P2REN0          : 1; /*  */
      unsigned char P2REN1          : 1; /*  */
      unsigned char P2REN2          : 1; /*  */
      unsigned char P2REN3          : 1; /*  */
      unsigned char P2REN4          : 1; /*  */
      unsigned char P2REN5          : 1; /*  */
      unsigned char P2REN6          : 1; /*  */
      unsigned char P2REN7          : 1; /*  */
    } P2REN_bit;
  }; 
} @0x0206;

enum {
  PAREN0          = 0x0001,
  PAREN1          = 0x0002,
  PAREN2          = 0x0004,
  PAREN3          = 0x0008,
  PAREN4          = 0x0010,
  PAREN5          = 0x0020,
  PAREN6          = 0x0040,
  PAREN7          = 0x0080,
  PAREN8          = 0x0100,
  PAREN9          = 0x0200,
  PAREN10         = 0x0400,
  PAREN11         = 0x0800,
  PAREN12         = 0x1000,
  PAREN13         = 0x2000,
  PAREN14         = 0x4000,
  PAREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PADS;   /* Port A Resistor Drive Strenght */

  struct
  {
    unsigned short PADS0           : 1; /*  */
    unsigned short PADS1           : 1; /*  */
    unsigned short PADS2           : 1; /*  */
    unsigned short PADS3           : 1; /*  */
    unsigned short PADS4           : 1; /*  */
    unsigned short PADS5           : 1; /*  */
    unsigned short PADS6           : 1; /*  */
    unsigned short PADS7           : 1; /*  */
    unsigned short PADS8           : 1; /*  */
    unsigned short PADS9           : 1; /*  */
    unsigned short PADS10          : 1; /*  */
    unsigned short PADS11          : 1; /*  */
    unsigned short PADS12          : 1; /*  */
    unsigned short PADS13          : 1; /*  */
    unsigned short PADS14          : 1; /*  */
    unsigned short PADS15          : 1; /*  */
  } PADS_bit;

  struct
  {
    unsigned char PADS_L;
    unsigned char PADS_H;
  };
  struct
  {
    unsigned char P1DS;   /* Port 1 Resistor Drive Strenght */
    unsigned char P2DS;   /* Port 2 Resistor Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P1DS0           : 1; /*  */
      unsigned char P1DS1           : 1; /*  */
      unsigned char P1DS2           : 1; /*  */
      unsigned char P1DS3           : 1; /*  */
      unsigned char P1DS4           : 1; /*  */
      unsigned char P1DS5           : 1; /*  */
      unsigned char P1DS6           : 1; /*  */
      unsigned char P1DS7           : 1; /*  */
    } P1DS_bit;

    struct
    {
      unsigned char P2DS0           : 1; /*  */
      unsigned char P2DS1           : 1; /*  */
      unsigned char P2DS2           : 1; /*  */
      unsigned char P2DS3           : 1; /*  */
      unsigned char P2DS4           : 1; /*  */
      unsigned char P2DS5           : 1; /*  */
      unsigned char P2DS6           : 1; /*  */
      unsigned char P2DS7           : 1; /*  */
    } P2DS_bit;
  }; 
} @0x0208;

enum {
  PADS0           = 0x0001,
  PADS1           = 0x0002,
  PADS2           = 0x0004,
  PADS3           = 0x0008,
  PADS4           = 0x0010,
  PADS5           = 0x0020,
  PADS6           = 0x0040,
  PADS7           = 0x0080,
  PADS8           = 0x0100,
  PADS9           = 0x0200,
  PADS10          = 0x0400,
  PADS11          = 0x0800,
  PADS12          = 0x1000,
  PADS13          = 0x2000,
  PADS14          = 0x4000,
  PADS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PASEL0;   /* Port A Selection 0 */

  struct
  {
    unsigned short PASEL0_0        : 1; /*  */
    unsigned short PASEL0_1        : 1; /*  */
    unsigned short PASEL0_2        : 1; /*  */
    unsigned short PASEL0_3        : 1; /*  */
    unsigned short PASEL0_4        : 1; /*  */
    unsigned short PASEL0_5        : 1; /*  */
    unsigned short PASEL0_6        : 1; /*  */
    unsigned short PASEL0_7        : 1; /*  */
    unsigned short PASEL0_8        : 1; /*  */
    unsigned short PASEL0_9        : 1; /*  */
    unsigned short PASEL0_10       : 1; /*  */
    unsigned short PASEL0_11       : 1; /*  */
    unsigned short PASEL0_12       : 1; /*  */
    unsigned short PASEL0_13       : 1; /*  */
    unsigned short PASEL0_14       : 1; /*  */
    unsigned short PASEL0_15       : 1; /*  */
  } PASEL0_bit;

  struct
  {
    unsigned char PASEL0_L;
    unsigned char PASEL0_H;
  };
  struct
  {
    unsigned char P1SEL0;   /* Port 1 Selection 0 */
    unsigned char P2SEL0;   /* Port 2 Selection 0 */
  };
  struct
  {
    struct
    {
      unsigned char P1SEL0_0        : 1; /*  */
      unsigned char P1SEL0_1        : 1; /*  */
      unsigned char P1SEL0_2        : 1; /*  */
      unsigned char P1SEL0_3        : 1; /*  */
      unsigned char P1SEL0_4        : 1; /*  */
      unsigned char P1SEL0_5        : 1; /*  */
      unsigned char P1SEL0_6        : 1; /*  */
      unsigned char P1SEL0_7        : 1; /*  */
    } P1SEL0_bit;

    struct
    {
      unsigned char P2SEL0_0        : 1; /*  */
      unsigned char P2SEL0_1        : 1; /*  */
      unsigned char P2SEL0_2        : 1; /*  */
      unsigned char P2SEL0_3        : 1; /*  */
      unsigned char P2SEL0_4        : 1; /*  */
      unsigned char P2SEL0_5        : 1; /*  */
      unsigned char P2SEL0_6        : 1; /*  */
      unsigned char P2SEL0_7        : 1; /*  */
    } P2SEL0_bit;
  }; 
} @0x020A;

enum {
  PASEL0_0        = 0x0001,
  PASEL0_1        = 0x0002,
  PASEL0_2        = 0x0004,
  PASEL0_3        = 0x0008,
  PASEL0_4        = 0x0010,
  PASEL0_5        = 0x0020,
  PASEL0_6        = 0x0040,
  PASEL0_7        = 0x0080,
  PASEL0_8        = 0x0100,
  PASEL0_9        = 0x0200,
  PASEL0_10       = 0x0400,
  PASEL0_11       = 0x0800,
  PASEL0_12       = 0x1000,
  PASEL0_13       = 0x2000,
  PASEL0_14       = 0x4000,
  PASEL0_15       = 0x8000
};

__no_init volatile union
{
  unsigned short PASEL1;   /* Port A Selection 1 */

  struct
  {
    unsigned short PASEL1_0        : 1; /*  */
    unsigned short PASEL1_1        : 1; /*  */
    unsigned short PASEL1_2        : 1; /*  */
    unsigned short PASEL1_3        : 1; /*  */
    unsigned short PASEL1_4        : 1; /*  */
    unsigned short PASEL1_5        : 1; /*  */
    unsigned short PASEL1_6        : 1; /*  */
    unsigned short PASEL1_7        : 1; /*  */
    unsigned short PASEL1_8        : 1; /*  */
    unsigned short PASEL1_9        : 1; /*  */
    unsigned short PASEL1_10       : 1; /*  */
    unsigned short PASEL1_11       : 1; /*  */
    unsigned short PASEL1_12       : 1; /*  */
    unsigned short PASEL1_13       : 1; /*  */
    unsigned short PASEL1_14       : 1; /*  */
    unsigned short PASEL1_15       : 1; /*  */
  } PASEL1_bit;

  struct
  {
    unsigned char PASEL1_L;
    unsigned char PASEL1_H;
  };
  struct
  {
    unsigned char P1SEL1;   /* Port 1 Selection 1 */
    unsigned char P2SEL1;   /* Port 2 Selection 1 */
  };
  struct
  {
    struct
    {
      unsigned char P1SEL1_0        : 1; /*  */
      unsigned char P1SEL1_1        : 1; /*  */
      unsigned char P1SEL1_2        : 1; /*  */
      unsigned char P1SEL1_3        : 1; /*  */
      unsigned char P1SEL1_4        : 1; /*  */
      unsigned char P1SEL1_5        : 1; /*  */
      unsigned char P1SEL1_6        : 1; /*  */
      unsigned char P1SEL1_7        : 1; /*  */
    } P1SEL1_bit;

    struct
    {
      unsigned char P2SEL1_0        : 1; /*  */
      unsigned char P2SEL1_1        : 1; /*  */
      unsigned char P2SEL1_2        : 1; /*  */
      unsigned char P2SEL1_3        : 1; /*  */
      unsigned char P2SEL1_4        : 1; /*  */
      unsigned char P2SEL1_5        : 1; /*  */
      unsigned char P2SEL1_6        : 1; /*  */
      unsigned char P2SEL1_7        : 1; /*  */
    } P2SEL1_bit;
  }; 
} @0x020C;

enum {
  PASEL1_0        = 0x0001,
  PASEL1_1        = 0x0002,
  PASEL1_2        = 0x0004,
  PASEL1_3        = 0x0008,
  PASEL1_4        = 0x0010,
  PASEL1_5        = 0x0020,
  PASEL1_6        = 0x0040,
  PASEL1_7        = 0x0080,
  PASEL1_8        = 0x0100,
  PASEL1_9        = 0x0200,
  PASEL1_10       = 0x0400,
  PASEL1_11       = 0x0800,
  PASEL1_12       = 0x1000,
  PASEL1_13       = 0x2000,
  PASEL1_14       = 0x4000,
  PASEL1_15       = 0x8000
};

__no_init volatile union
{
  unsigned short PAIES;   /* Port A Interrupt Edge Select */

  struct
  {
    unsigned short PAIES0          : 1; /*  */
    unsigned short PAIES1          : 1; /*  */
    unsigned short PAIES2          : 1; /*  */
    unsigned short PAIES3          : 1; /*  */
    unsigned short PAIES4          : 1; /*  */
    unsigned short PAIES5          : 1; /*  */
    unsigned short PAIES6          : 1; /*  */
    unsigned short PAIES7          : 1; /*  */
    unsigned short PAIES8          : 1; /*  */
    unsigned short PAIES9          : 1; /*  */
    unsigned short PAIES10         : 1; /*  */
    unsigned short PAIES11         : 1; /*  */
    unsigned short PAIES12         : 1; /*  */
    unsigned short PAIES13         : 1; /*  */
    unsigned short PAIES14         : 1; /*  */
    unsigned short PAIES15         : 1; /*  */
  } PAIES_bit;

  struct
  {
    unsigned char PAIES_L;
    unsigned char PAIES_H;
  };
  struct
  {
    unsigned char P1IES;   /* Port 1 Interrupt Edge Select */
    unsigned char P2IES;   /* Port 2 Interrupt Edge Select */
  };
  struct
  {
    struct
    {
      unsigned char P1IES0          : 1; /*  */
      unsigned char P1IES1          : 1; /*  */
      unsigned char P1IES2          : 1; /*  */
      unsigned char P1IES3          : 1; /*  */
      unsigned char P1IES4          : 1; /*  */
      unsigned char P1IES5          : 1; /*  */
      unsigned char P1IES6          : 1; /*  */
      unsigned char P1IES7          : 1; /*  */
    } P1IES_bit;

    struct
    {
      unsigned char P2IES0          : 1; /*  */
      unsigned char P2IES1          : 1; /*  */
      unsigned char P2IES2          : 1; /*  */
      unsigned char P2IES3          : 1; /*  */
      unsigned char P2IES4          : 1; /*  */
      unsigned char P2IES5          : 1; /*  */
      unsigned char P2IES6          : 1; /*  */
      unsigned char P2IES7          : 1; /*  */
    } P2IES_bit;
  }; 
} @0x0218;

enum {
  PAIES0          = 0x0001,
  PAIES1          = 0x0002,
  PAIES2          = 0x0004,
  PAIES3          = 0x0008,
  PAIES4          = 0x0010,
  PAIES5          = 0x0020,
  PAIES6          = 0x0040,
  PAIES7          = 0x0080,
  PAIES8          = 0x0100,
  PAIES9          = 0x0200,
  PAIES10         = 0x0400,
  PAIES11         = 0x0800,
  PAIES12         = 0x1000,
  PAIES13         = 0x2000,
  PAIES14         = 0x4000,
  PAIES15         = 0x8000
};

__no_init volatile union
{
  unsigned short PAIE;   /* Port A Interrupt Enable */

  struct
  {
    unsigned short PAIE0           : 1; /*  */
    unsigned short PAIE1           : 1; /*  */
    unsigned short PAIE2           : 1; /*  */
    unsigned short PAIE3           : 1; /*  */
    unsigned short PAIE4           : 1; /*  */
    unsigned short PAIE5           : 1; /*  */
    unsigned short PAIE6           : 1; /*  */
    unsigned short PAIE7           : 1; /*  */
    unsigned short PAIE8           : 1; /*  */
    unsigned short PAIE9           : 1; /*  */
    unsigned short PAIE10          : 1; /*  */
    unsigned short PAIE11          : 1; /*  */
    unsigned short PAIE12          : 1; /*  */
    unsigned short PAIE13          : 1; /*  */
    unsigned short PAIE14          : 1; /*  */
    unsigned short PAIE15          : 1; /*  */
  } PAIE_bit;

  struct
  {
    unsigned char PAIE_L;
    unsigned char PAIE_H;
  };
  struct
  {
    unsigned char P1IE;   /* Port 1 Interrupt Enable */
    unsigned char P2IE;   /* Port 2 Interrupt Enable */
  };
  struct
  {
    struct
    {
      unsigned char P1IE0           : 1; /*  */
      unsigned char P1IE1           : 1; /*  */
      unsigned char P1IE2           : 1; /*  */
      unsigned char P1IE3           : 1; /*  */
      unsigned char P1IE4           : 1; /*  */
      unsigned char P1IE5           : 1; /*  */
      unsigned char P1IE6           : 1; /*  */
      unsigned char P1IE7           : 1; /*  */
    } P1IE_bit;

    struct
    {
      unsigned char P2IE0           : 1; /*  */
      unsigned char P2IE1           : 1; /*  */
      unsigned char P2IE2           : 1; /*  */
      unsigned char P2IE3           : 1; /*  */
      unsigned char P2IE4           : 1; /*  */
      unsigned char P2IE5           : 1; /*  */
      unsigned char P2IE6           : 1; /*  */
      unsigned char P2IE7           : 1; /*  */
    } P2IE_bit;
  }; 
} @0x021A;

enum {
  PAIE0           = 0x0001,
  PAIE1           = 0x0002,
  PAIE2           = 0x0004,
  PAIE3           = 0x0008,
  PAIE4           = 0x0010,
  PAIE5           = 0x0020,
  PAIE6           = 0x0040,
  PAIE7           = 0x0080,
  PAIE8           = 0x0100,
  PAIE9           = 0x0200,
  PAIE10          = 0x0400,
  PAIE11          = 0x0800,
  PAIE12          = 0x1000,
  PAIE13          = 0x2000,
  PAIE14          = 0x4000,
  PAIE15          = 0x8000
};

__no_init volatile union
{
  unsigned short PAIFG;   /* Port A Interrupt Flag */

  struct
  {
    unsigned short PAIFG0          : 1; /*  */
    unsigned short PAIFG1          : 1; /*  */
    unsigned short PAIFG2          : 1; /*  */
    unsigned short PAIFG3          : 1; /*  */
    unsigned short PAIFG4          : 1; /*  */
    unsigned short PAIFG5          : 1; /*  */
    unsigned short PAIFG6          : 1; /*  */
    unsigned short PAIFG7          : 1; /*  */
    unsigned short PAIFG8          : 1; /*  */
    unsigned short PAIFG9          : 1; /*  */
    unsigned short PAIFG10         : 1; /*  */
    unsigned short PAIFG11         : 1; /*  */
    unsigned short PAIFG12         : 1; /*  */
    unsigned short PAIFG13         : 1; /*  */
    unsigned short PAIFG14         : 1; /*  */
    unsigned short PAIFG15         : 1; /*  */
  } PAIFG_bit;

  struct
  {
    unsigned char PAIFG_L;
    unsigned char PAIFG_H;
  };
  struct
  {
    unsigned char P1IFG;   /* Port 1 Interrupt Flag */
    unsigned char P2IFG;   /* Port 2 Interrupt Flag */
  };
  struct
  {
    struct
    {
      unsigned char P1IFG0          : 1; /*  */
      unsigned char P1IFG1          : 1; /*  */
      unsigned char P1IFG2          : 1; /*  */
      unsigned char P1IFG3          : 1; /*  */
      unsigned char P1IFG4          : 1; /*  */
      unsigned char P1IFG5          : 1; /*  */
      unsigned char P1IFG6          : 1; /*  */
      unsigned char P1IFG7          : 1; /*  */
    } P1IFG_bit;

    struct
    {
      unsigned char P2IFG0          : 1; /*  */
      unsigned char P2IFG1          : 1; /*  */
      unsigned char P2IFG2          : 1; /*  */
      unsigned char P2IFG3          : 1; /*  */
      unsigned char P2IFG4          : 1; /*  */
      unsigned char P2IFG5          : 1; /*  */
      unsigned char P2IFG6          : 1; /*  */
      unsigned char P2IFG7          : 1; /*  */
    } P2IFG_bit;
  }; 
} @0x021C;

enum {
  PAIFG0          = 0x0001,
  PAIFG1          = 0x0002,
  PAIFG2          = 0x0004,
  PAIFG3          = 0x0008,
  PAIFG4          = 0x0010,
  PAIFG5          = 0x0020,
  PAIFG6          = 0x0040,
  PAIFG7          = 0x0080,
  PAIFG8          = 0x0100,
  PAIFG9          = 0x0200,
  PAIFG10         = 0x0400,
  PAIFG11         = 0x0800,
  PAIFG12         = 0x1000,
  PAIFG13         = 0x2000,
  PAIFG14         = 0x4000,
  PAIFG15         = 0x8000
};



#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define P1IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P1IV_P1IFG0          (0x0002u)    /* P1IV P1IFG.0 */
#define P1IV_P1IFG1          (0x0004u)    /* P1IV P1IFG.1 */
#define P1IV_P1IFG2          (0x0006u)    /* P1IV P1IFG.2 */
#define P1IV_P1IFG3          (0x0008u)    /* P1IV P1IFG.3 */
#define P1IV_P1IFG4          (0x000Au)    /* P1IV P1IFG.4 */
#define P1IV_P1IFG5          (0x000Cu)    /* P1IV P1IFG.5 */
#define P1IV_P1IFG6          (0x000Eu)    /* P1IV P1IFG.6 */
#define P1IV_P1IFG7          (0x0010u)    /* P1IV P1IFG.7 */
#define P2IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P2IV_P2IFG0          (0x0002u)    /* P2IV P2IFG.0 */
#define P2IV_P2IFG1          (0x0004u)    /* P2IV P2IFG.1 */
#define P2IV_P2IFG2          (0x0006u)    /* P2IV P2IFG.2 */
#define P2IV_P2IFG3          (0x0008u)    /* P2IV P2IFG.3 */
#define P2IV_P2IFG4          (0x000Au)    /* P2IV P2IFG.4 */
#define P2IV_P2IFG5          (0x000Cu)    /* P2IV P2IFG.5 */
#define P2IV_P2IFG6          (0x000Eu)    /* P2IV P2IFG.6 */
#define P2IV_P2IFG7          (0x0010u)    /* P2IV P2IFG.7 */

/*-------------------------------------------------------------------------
 *   Port 1/2
 *-------------------------------------------------------------------------*/


enum {
  P1IN0           = 0x0001,
  P1IN1           = 0x0002,
  P1IN2           = 0x0004,
  P1IN3           = 0x0008,
  P1IN4           = 0x0010,
  P1IN5           = 0x0020,
  P1IN6           = 0x0040,
  P1IN7           = 0x0080
};

enum {
  P1OUT0          = 0x0001,
  P1OUT1          = 0x0002,
  P1OUT2          = 0x0004,
  P1OUT3          = 0x0008,
  P1OUT4          = 0x0010,
  P1OUT5          = 0x0020,
  P1OUT6          = 0x0040,
  P1OUT7          = 0x0080
};

enum {
  P1DIR0          = 0x0001,
  P1DIR1          = 0x0002,
  P1DIR2          = 0x0004,
  P1DIR3          = 0x0008,
  P1DIR4          = 0x0010,
  P1DIR5          = 0x0020,
  P1DIR6          = 0x0040,
  P1DIR7          = 0x0080
};

enum {
  P1REN0          = 0x0001,
  P1REN1          = 0x0002,
  P1REN2          = 0x0004,
  P1REN3          = 0x0008,
  P1REN4          = 0x0010,
  P1REN5          = 0x0020,
  P1REN6          = 0x0040,
  P1REN7          = 0x0080
};

enum {
  P1DS0           = 0x0001,
  P1DS1           = 0x0002,
  P1DS2           = 0x0004,
  P1DS3           = 0x0008,
  P1DS4           = 0x0010,
  P1DS5           = 0x0020,
  P1DS6           = 0x0040,
  P1DS7           = 0x0080
};

enum {
  P1SEL0_0        = 0x0001,
  P1SEL0_1        = 0x0002,
  P1SEL0_2        = 0x0004,
  P1SEL0_3        = 0x0008,
  P1SEL0_4        = 0x0010,
  P1SEL0_5        = 0x0020,
  P1SEL0_6        = 0x0040,
  P1SEL0_7        = 0x0080
};

enum {
  P1SEL1_0        = 0x0001,
  P1SEL1_1        = 0x0002,
  P1SEL1_2        = 0x0004,
  P1SEL1_3        = 0x0008,
  P1SEL1_4        = 0x0010,
  P1SEL1_5        = 0x0020,
  P1SEL1_6        = 0x0040,
  P1SEL1_7        = 0x0080
};


  /* Port 1 Interrupt Vector Word */
__no_init volatile unsigned short P1IV @ 0x020E;


enum {
  P1IES0          = 0x0001,
  P1IES1          = 0x0002,
  P1IES2          = 0x0004,
  P1IES3          = 0x0008,
  P1IES4          = 0x0010,
  P1IES5          = 0x0020,
  P1IES6          = 0x0040,
  P1IES7          = 0x0080
};

enum {
  P1IE0           = 0x0001,
  P1IE1           = 0x0002,
  P1IE2           = 0x0004,
  P1IE3           = 0x0008,
  P1IE4           = 0x0010,
  P1IE5           = 0x0020,
  P1IE6           = 0x0040,
  P1IE7           = 0x0080
};

enum {
  P1IFG0          = 0x0001,
  P1IFG1          = 0x0002,
  P1IFG2          = 0x0004,
  P1IFG3          = 0x0008,
  P1IFG4          = 0x0010,
  P1IFG5          = 0x0020,
  P1IFG6          = 0x0040,
  P1IFG7          = 0x0080
};

enum {
  P2IN0           = 0x0001,
  P2IN1           = 0x0002,
  P2IN2           = 0x0004,
  P2IN3           = 0x0008,
  P2IN4           = 0x0010,
  P2IN5           = 0x0020,
  P2IN6           = 0x0040,
  P2IN7           = 0x0080
};

enum {
  P2OUT0          = 0x0001,
  P2OUT1          = 0x0002,
  P2OUT2          = 0x0004,
  P2OUT3          = 0x0008,
  P2OUT4          = 0x0010,
  P2OUT5          = 0x0020,
  P2OUT6          = 0x0040,
  P2OUT7          = 0x0080
};

enum {
  P2DIR0          = 0x0001,
  P2DIR1          = 0x0002,
  P2DIR2          = 0x0004,
  P2DIR3          = 0x0008,
  P2DIR4          = 0x0010,
  P2DIR5          = 0x0020,
  P2DIR6          = 0x0040,
  P2DIR7          = 0x0080
};

enum {
  P2REN0          = 0x0001,
  P2REN1          = 0x0002,
  P2REN2          = 0x0004,
  P2REN3          = 0x0008,
  P2REN4          = 0x0010,
  P2REN5          = 0x0020,
  P2REN6          = 0x0040,
  P2REN7          = 0x0080
};

enum {
  P2DS0           = 0x0001,
  P2DS1           = 0x0002,
  P2DS2           = 0x0004,
  P2DS3           = 0x0008,
  P2DS4           = 0x0010,
  P2DS5           = 0x0020,
  P2DS6           = 0x0040,
  P2DS7           = 0x0080
};

enum {
  P2SEL0_0        = 0x0001,
  P2SEL0_1        = 0x0002,
  P2SEL0_2        = 0x0004,
  P2SEL0_3        = 0x0008,
  P2SEL0_4        = 0x0010,
  P2SEL0_5        = 0x0020,
  P2SEL0_6        = 0x0040,
  P2SEL0_7        = 0x0080
};

enum {
  P2SEL1_0        = 0x0001,
  P2SEL1_1        = 0x0002,
  P2SEL1_2        = 0x0004,
  P2SEL1_3        = 0x0008,
  P2SEL1_4        = 0x0010,
  P2SEL1_5        = 0x0020,
  P2SEL1_6        = 0x0040,
  P2SEL1_7        = 0x0080
};


  /* Port 2 Interrupt Vector Word */
__no_init volatile unsigned short P2IV @ 0x021E;


enum {
  P2IES0          = 0x0001,
  P2IES1          = 0x0002,
  P2IES2          = 0x0004,
  P2IES3          = 0x0008,
  P2IES4          = 0x0010,
  P2IES5          = 0x0020,
  P2IES6          = 0x0040,
  P2IES7          = 0x0080
};

enum {
  P2IE0           = 0x0001,
  P2IE1           = 0x0002,
  P2IE2           = 0x0004,
  P2IE3           = 0x0008,
  P2IE4           = 0x0010,
  P2IE5           = 0x0020,
  P2IE6           = 0x0040,
  P2IE7           = 0x0080
};

enum {
  P2IFG0          = 0x0001,
  P2IFG1          = 0x0002,
  P2IFG2          = 0x0004,
  P2IFG3          = 0x0008,
  P2IFG4          = 0x0010,
  P2IFG5          = 0x0020,
  P2IFG6          = 0x0040,
  P2IFG7          = 0x0080
};



/*-------------------------------------------------------------------------
 *   SFR  Special Function Registers
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SFRIE1;   /* Interrupt Enable 1 */

  struct
  {
    unsigned short WDTIE           : 1; /* WDT Interrupt Enable */
    unsigned short OFIE            : 1; /* Osc Fault Enable */
    unsigned short                : 1;
    unsigned short VMAIE           : 1; /* Vacant Memory Interrupt Enable */
    unsigned short NMIIE           : 1; /* NMI Interrupt Enable */
    unsigned short                : 1;
    unsigned short JMBINIE         : 1; /* JTAG Mail Box input Interrupt Enable */
    unsigned short JMBOUTIE        : 1; /* JTAG Mail Box output Interrupt Enable */
    unsigned short SVMIE           : 1; /* SVM Interrupt Enable */
  } SFRIE1_bit;

  struct
  {
    unsigned char SFRIE1_L;
    unsigned char SFRIE1_H;
  };
} @0x0100;

enum {
  WDTIE           = 0x0001,
  OFIE            = 0x0002,
  VMAIE           = 0x0008,
  NMIIE           = 0x0010,
  JMBINIE         = 0x0040,
  JMBOUTIE        = 0x0080,
  SVMIE           = 0x0100
};

__no_init volatile union
{
  unsigned short SFRIFG1;   /* Interrupt Flag 1 */

  struct
  {
    unsigned short WDTIFG          : 1; /* WDT Interrupt Flag */
    unsigned short OFIFG           : 1; /* Osc Fault Flag */
    unsigned short                : 1;
    unsigned short VMAIFG          : 1; /* Vacant Memory Interrupt Flag */
    unsigned short NMIIFG          : 1; /* NMI Interrupt Flag */
    unsigned short                : 1;
    unsigned short JMBINIFG        : 1; /* JTAG Mail Box input Interrupt Flag */
    unsigned short JMBOUTIFG       : 1; /* JTAG Mail Box output Interrupt Flag */
    unsigned short SVMIFG          : 1; /* SVM Interrupt Flag */
  } SFRIFG1_bit;

  struct
  {
    unsigned char SFRIFG1_L;
    unsigned char SFRIFG1_H;
  };
} @0x0102;

enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  VMAIFG          = 0x0008,
  NMIIFG          = 0x0010,
  JMBINIFG        = 0x0040,
  JMBOUTIFG       = 0x0080,
  SVMIFG          = 0x0100
};

__no_init volatile union
{
  unsigned short SFRRPCR;   /* RESET Pin Control Register */

  struct
  {
    unsigned short SYSNMI          : 1; /* NMI select */
    unsigned short SYSNMIIES       : 1; /* NMI edge select */
    unsigned short SYSRSTUP        : 1; /* RESET Pin pull down/up select */
    unsigned short SYSRSTRE        : 1; /* RESET Pin Resistor enable */
  } SFRRPCR_bit;

  struct
  {
    unsigned char SFRRPCR_L;
    unsigned char SFRRPCR_H;
  };
} @0x0104;

enum {
  SYSNMI          = 0x0001,
  SYSNMIIES       = 0x0002,
  SYSRSTUP        = 0x0004,
  SYSRSTRE        = 0x0008
};



#define __MSP430_HAS_SFR__            /* Definition to show that Module is available */

#define WDTIE_L             (0x0001u)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002u)  /* Osc Fault Enable */
#define VMAIE_L             (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010u)  /* NMI Interrupt Enable */
#define JMBINIE_L           (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080u)  /* JTAG Mail Box output Interrupt Enable */
#define SVMIE_H             (0x0001u)  /* SVM Interrupt Enable */

#define WDTIFG_L            (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG_L             (0x0002u)  /* Osc Fault Flag */
#define VMAIFG_L            (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG_L            (0x0010u)  /* NMI Interrupt Flag */
#define JMBINIFG_L          (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L         (0x0080u)  /* JTAG Mail Box output Interrupt Flag */
#define SVMIFG_H            (0x0001u)  /* SVM Interrupt Flag */

#define SYSNMI_L            (0x0001u)  /* NMI select */
#define SYSNMIIES_L         (0x0002u)  /* NMI edge select */
#define SYSRSTUP_L          (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE_L          (0x0008u)  /* RESET Pin Resistor enable */

/*-------------------------------------------------------------------------
 *   CSYS  Compact System Module
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SYSCTL;   /* System control */

  struct
  {
    unsigned short SYSRIVECT       : 1; /* SYS - RAM based interrupt vectors */
    unsigned short                : 1;
    unsigned short SYSPMMPE        : 1; /* SYS - PMM access protect */
    unsigned short                : 1;
    unsigned short SYSBSLIND       : 1; /* SYS - TCK/RST indication detected */
    unsigned short SYSJTAGPIN      : 1; /* SYS - Dedicated JTAG pins enabled */
  } SYSCTL_bit;

  struct
  {
    unsigned char SYSCTL_L;
    unsigned char SYSCTL_H;
  };
} @0x0180;

enum {
  SYSRIVECT       = 0x0001,
  SYSPMMPE        = 0x0004,
  SYSBSLIND       = 0x0010,
  SYSJTAGPIN      = 0x0020
};

__no_init volatile union
{
  unsigned short SYSBSLC;   /* Boot strap configuration area */

  struct
  {
    unsigned short SYSBSLSIZE0     : 1; /* SYS - BSL Protection Size 0 */
    unsigned short SYSBSLSIZE1     : 1; /* SYS - BSL Protection Size 1 */
    unsigned short SYSBSLR         : 1; /* SYS - RAM assigned to BSL */
    unsigned short                : 11;
    unsigned short SYSBSLOFF       : 1; /* SYS - BSL Memeory disabled */
    unsigned short SYSBSLPE        : 1; /* SYS - BSL Memory protection enabled */
  } SYSBSLC_bit;

  struct
  {
    unsigned char SYSBSLC_L;
    unsigned char SYSBSLC_H;
  };
} @0x0182;

enum {
  SYSBSLSIZE0     = 0x0001,
  SYSBSLSIZE1     = 0x0002,
  SYSBSLR         = 0x0004,
  SYSBSLOFF       = 0x4000,
  SYSBSLPE        = 0x8000
};

__no_init volatile union
{
  unsigned short SYSJMBC;   /* JTAG mailbox control */

  struct
  {
    unsigned short JMBIN0FG        : 1; /* SYS - Incoming JTAG Mailbox 0 Flag */
    unsigned short JMBIN1FG        : 1; /* SYS - Incoming JTAG Mailbox 1 Flag */
    unsigned short JMBOUT0FG       : 1; /* SYS - Outgoing JTAG Mailbox 0 Flag */
    unsigned short JMBOUT1FG       : 1; /* SYS - Outgoing JTAG Mailbox 1 Flag */
    unsigned short JMBMODE         : 1; /* SYS - JMB 16/32 Bit Mode */
    unsigned short                : 1;
    unsigned short JMBCLR0OFF      : 1; /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
    unsigned short JMBCLR1OFF      : 1; /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
  } SYSJMBC_bit;

  struct
  {
    unsigned char SYSJMBC_L;
    unsigned char SYSJMBC_H;
  };
} @0x0186;

enum {
  JMBIN0FG        = 0x0001,
  JMBIN1FG        = 0x0002,
  JMBOUT0FG       = 0x0004,
  JMBOUT1FG       = 0x0008,
  JMBMODE         = 0x0010,
  JMBCLR0OFF      = 0x0040,
  JMBCLR1OFF      = 0x0080
};

__no_init volatile union
{
  unsigned short SYSJMBI0;   /* JTAG mailbox input 0 */
  struct
  {
    unsigned char SYSJMBI0_L;
    unsigned char SYSJMBI0_H;
  };
} @0x0188;

__no_init volatile union
{
  unsigned short SYSJMBI1;   /* JTAG mailbox input 1 */
  struct
  {
    unsigned char SYSJMBI1_L;
    unsigned char SYSJMBI1_H;
  };
} @0x018A;

__no_init volatile union
{
  unsigned short SYSJMBO0;   /* JTAG mailbox output 0 */
  struct
  {
    unsigned char SYSJMBO0_L;
    unsigned char SYSJMBO0_H;
  };
} @0x018C;

__no_init volatile union
{
  unsigned short SYSJMBO1;   /* JTAG mailbox output 1 */
  struct
  {
    unsigned char SYSJMBO1_L;
    unsigned char SYSJMBO1_H;
  };
} @0x018E;

__no_init volatile union
{
  unsigned short SYSCNF;   /* System Configuration Register */

  struct
  {
    unsigned short                : 2;
    unsigned short SVMOE           : 1; /* SYS - SVM output enable */
    unsigned short SVMPO           : 1; /* SYS - SVM based Ports off flag */
    unsigned short SVMPD           : 1; /* SYS - Incoming JTAG Mailbox 0 Flag */
    unsigned short SVMEN           : 1; /* SYS - SVM based port disable */
    unsigned short                : 2;
    unsigned short RAMLCK0         : 1; /* SYS - Write lock enable for configuration RAM */
    unsigned short RAMLCK1         : 1; /* SYS - Write lock enable for application’s code RAM */
  } SYSCNF_bit;

  struct
  {
    unsigned char SYSCNF_L;
    unsigned char SYSCNF_H;
  };
} @0x0190;

enum {
  SVMOE           = 0x0004,
  SVMPO           = 0x0008,
  SVMPD           = 0x0010,
  SVMEN           = 0x0020,
  RAMLCK0         = 0x0100,
  RAMLCK1         = 0x0200
};

__no_init volatile union
{
  unsigned short SYSBERRIV;   /* Bus Error vector generator */
  struct
  {
    unsigned char SYSBERRIV_L;
    unsigned char SYSBERRIV_H;
  };
} @0x0198;

__no_init volatile union
{
  unsigned short SYSUNIV;   /* User NMI vector generator */
  struct
  {
    unsigned char SYSUNIV_L;
    unsigned char SYSUNIV_H;
  };
} @0x019A;

__no_init volatile union
{
  unsigned short SYSSNIV;   /* System NMI vector generator */
  struct
  {
    unsigned char SYSSNIV_L;
    unsigned char SYSSNIV_H;
  };
} @0x019C;

__no_init volatile union
{
  unsigned short SYSRSTIV;   /* Reset vector generator */
  struct
  {
    unsigned char SYSRSTIV_L;
    unsigned char SYSRSTIV_H;
  };
} @0x019E;

#define __MSP430_HAS_SYS__            /* Definition to show that Module is available */
/* SYSCTL Control Bits */
#define SYSRIVECT_L         (0x0001u)  /* SYS - RAM based interrupt vectors */
#define SYSPMMPE_L          (0x0004u)  /* SYS - PMM access protect */
#define SYSBSLIND_L         (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L        (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L       (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L       (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L           (0x0004u)  /* SYS - RAM assigned to BSL */
#define SYSBSLOFF_H         (0x0040u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE_H          (0x0080u)  /* SYS - BSL Memory protection enabled */
/* SYSJMBC Control Bits */
#define JMBIN0FG_L          (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L          (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L         (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L         (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L           (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
#define JMBCLR0OFF_L        (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L        (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
#define SVMOE_L             (0x0004u)  /* SYS - SVM output enable */
#define SVMPO_L             (0x0008u)  /* SYS - SVM based Ports off flag */
#define SVMPD_L             (0x0010u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define SVMEN_L             (0x0020u)  /* SYS - SVM based port disable */
#define RAMLCK0_H           (0x0001u)  /* SYS - Write lock enable for configuration RAM */
#define RAMLCK1_H           (0x0002u)  /* SYS - Write lock enable for application’s code RAM */
/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002u)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004u)    /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_SYSBERRIV  (0x0006u)    /* SYSUNIV : Bus Error - SYSBERRIV */
/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSSNIV_SVMIFG     (0x0002u)    /* SYSSNIV : SVMLIFG */
#define SYSSNIV_VMAIFG     (0x0004u)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x0006u)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x0008u)    /* SYSSNIV : JMBOUTIFG */
/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000u)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002u)    /* SYSRSTIV : BOR */
#define SYSRSTIV_SVMBOR    (0x0004u)    /* SYSRSTIV : SVMBOR */
#define SYSRSTIV_RSTNMI    (0x0006u)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0008u)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_SECYV     (0x000Au)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_DOPOR     (0x000Cu)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x000Eu)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0010u)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_CCSKEY    (0x0012u)    /* SYSRSTIV : CCS Key violation */
#define SYSRSTIV_PMMKEY    (0x0014u)    /* SYSRSTIV : PMMKEY violation */
#define SYSRSTIV_PERF      (0x0016u)    /* SYSRSTIV : peripheral/config area fetch */

/*-------------------------------------------------------------------------
 *   Timer0_A3
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short TA0CTL;   /* Timer0_A3 Control */

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
  }TA0CTL_bit;
} @0x0340;


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
  unsigned short TA0CCTL0;   /* Timer0_A3 Capture/Compare Control 0 */

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
  }TA0CCTL0_bit;
} @0x0342;


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
  unsigned short TA0CCTL1;   /* Timer0_A3 Capture/Compare Control 1 */

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
  }TA0CCTL1_bit;
} @0x0344;


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
  unsigned short TA0CCTL2;   /* Timer0_A3 Capture/Compare Control 2 */

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
  }TA0CCTL2_bit;
} @0x0346;


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

  /* Timer0_A3 */
__no_init volatile unsigned short TA0R @ 0x0350;



  /* Timer0_A3 Capture/Compare 0 */
__no_init volatile unsigned short TA0CCR0 @ 0x0352;



  /* Timer0_A3 Capture/Compare 1 */
__no_init volatile unsigned short TA0CCR1 @ 0x0354;



  /* Timer0_A3 Capture/Compare 2 */
__no_init volatile unsigned short TA0CCR2 @ 0x0356;



  /* Timer0_A3 Interrupt Vector Word */
__no_init volatile unsigned short TA0IV @ 0x036E;



__no_init volatile union
{
  unsigned short TA0EX0;   /* Timer0_A3 Expansion Register 0 */

  struct
  {
    unsigned short TAIDEX0         : 1; /* Timer A Input divider expansion Bit: 0 */
    unsigned short TAIDEX1         : 1; /* Timer A Input divider expansion Bit: 1 */
    unsigned short TAIDEX2         : 1; /* Timer A Input divider expansion Bit: 2 */
  }TA0EX0_bit;
} @ 0x0360;


enum {
  TAIDEX0         = 0x0001,
  TAIDEX1         = 0x0002,
  TAIDEX2         = 0x0004
};



#define __MSP430_HAS_T0A3__           /* Definition to show that Module is available */

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continuous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */
#define MC__STOP            (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC__UP              (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINUOUS      (2*0x10u)  /* Timer A mode control: 2 - Continuous up */
#define MC__CONTINOUS       (2*0x10u)  /* Legacy define */
#define MC__UPDOWN          (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID__1               (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID__2               (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID__4               (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID__8               (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK       (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK        (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK       (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK       (3*0x100u) /* Timer A clock source select: 3 - INCLK */

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

#define TAIDEX_0            (0*0x0001u) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (1*0x0001u) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (2*0x0001u) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (3*0x0001u) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (4*0x0001u) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (5*0x0001u) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (6*0x0001u) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (7*0x0001u) /* Timer A Input divider expansion : /8 */
/* T0A3IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TA0CCR1       (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2       (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_3             (0x0006u)    /* Reserved */
#define TA0IV_4             (0x0008u)    /* Reserved */
#define TA0IV_5             (0x000Au)    /* Reserved */
#define TA0IV_6             (0x000Cu)    /* Reserved */
#define TA0IV_TA0IFG        (0x000Eu)    /* TA0IFG */

/*-------------------------------------------------------------------------
 *   Timer1_A3
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short TA1CTL;   /* Timer1_A3 Control */

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
  }TA1CTL_bit;
} @0x0380;


/*
enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200,
};

*/

__no_init volatile union
{
  unsigned short TA1CCTL0;   /* Timer1_A3 Capture/Compare Control 0 */

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
  }TA1CCTL0_bit;
} @0x0382;


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
  unsigned short TA1CCTL1;   /* Timer1_A3 Capture/Compare Control 1 */

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
  }TA1CCTL1_bit;
} @0x0384;


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
  unsigned short TA1CCTL2;   /* Timer1_A3 Capture/Compare Control 2 */

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
  }TA1CCTL2_bit;
} @0x0386;


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

  /* Timer1_A3 */
__no_init volatile unsigned short TA1R @ 0x0390;



  /* Timer1_A3 Capture/Compare 0 */
__no_init volatile unsigned short TA1CCR0 @ 0x0392;



  /* Timer1_A3 Capture/Compare 1 */
__no_init volatile unsigned short TA1CCR1 @ 0x0394;



  /* Timer1_A3 Capture/Compare 2 */
__no_init volatile unsigned short TA1CCR2 @ 0x0396;



  /* Timer1_A3 Interrupt Vector Word */
__no_init volatile unsigned short TA1IV @ 0x03AE;



__no_init volatile union
{
  unsigned short TA1EX0;   /* Timer1_A3 Expansion Register 0 */

  struct
  {
    unsigned short TAIDEX0         : 1; /* Timer A Input divider expansion Bit: 0 */
    unsigned short TAIDEX1         : 1; /* Timer A Input divider expansion Bit: 1 */
    unsigned short TAIDEX2         : 1; /* Timer A Input divider expansion Bit: 2 */
  }TA1EX0_bit;
} @ 0x03A0;


/*
enum {
  TAIDEX0         = 0x0001,
  TAIDEX1         = 0x0002,
  TAIDEX2         = 0x0004
};
*/



#define __MSP430_HAS_T1A3__            /* Definition to show that Module is available */
/* TA1IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TA1CCR1       (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2       (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_3             (0x0006u)    /* Reserved */
#define TA1IV_4             (0x0008u)    /* Reserved */
#define TA1IV_5             (0x000Au)    /* Reserved */
#define TA1IV_6             (0x000Cu)    /* Reserved */
#define TA1IV_TA1IFG        (0x000Eu)    /* TA1IFG */

/*-------------------------------------------------------------------------
 *   Watchdog Timer
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short WDTCTL;   /* Watchdog Timer Control */

  struct
  {
    unsigned short WDTIS0          : 1; /* WDT - Timer Interval Select 0 */
    unsigned short WDTIS1          : 1; /* WDT - Timer Interval Select 1 */
    unsigned short WDTIS2          : 1; /* WDT - Timer Interval Select 2 */
    unsigned short WDTCNTCL        : 1; /* WDT - Timer Clear */
    unsigned short WDTTMSEL        : 1; /* WDT - Timer Mode Select */
    unsigned short WDTSSEL0        : 1; /* WDT - Timer Clock Source Select 0 */
    unsigned short WDTSSEL1        : 1; /* WDT - Timer Clock Source Select 1 */
    unsigned short WDTHOLD         : 1; /* WDT - Timer hold */
  } WDTCTL_bit;

  struct
  {
    unsigned char WDTCTL_L;
    unsigned char WDTCTL_H;
  };
} @0x015C;

enum {
  WDTIS0          = 0x0001,
  WDTIS1          = 0x0002,
  WDTIS2          = 0x0004,
  WDTCNTCL        = 0x0008,
  WDTTMSEL        = 0x0010,
  WDTSSEL0        = 0x0020,
  WDTSSEL1        = 0x0040,
  WDTHOLD         = 0x0080
};



#define __MSP430_HAS_WDT_A__          /* Definition to show that Module is available */
/* WDTCTL Control Bits */
#define WDTIS0_L            (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1_L            (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2_L            (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L          (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL_L          (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0_L          (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L          (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L           (0x0080u)  /* WDT - Timer hold */

#define WDTPW               (0x5A00u)

#define WDTIS_0           (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS_1           (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS_2           (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3           (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS_4           (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS_5           (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6           (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS_7           (7*0x0001u)  /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G         (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M       (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K      (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K       (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K        (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192       (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512        (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS__64         (7*0x0001u)  /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0         (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1         (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2         (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3         (3*0x0020u)  /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK    (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK     (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO      (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */




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
* Interrupt Vectors (offset from 0xFFFF - 0x20)
************************************************************/

#define PORT2_VECTOR        (5 * 2u)  /* 0xFFEA Port 2 */
#define TIMER0_A1_VECTOR    (6 * 2u)  /* 0xFFEC Timer0_A3 CC1-2, TA1 */
#define TIMER0_A0_VECTOR    (7 * 2u)  /* 0xFFEE Timer0_A3 CC0 */
#define PORT1_VECTOR        (8 * 2u)  /* 0xFFF0 Port 1 */
#define APOOL_VECTOR        (9 * 2u)  /* 0xFFF2 Analog Pool */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define TIMER1_A1_VECTOR    (11 * 2u) /* 0xFFF6 Timer1_A5 CC1-4, TA */
#define TIMER1_A0_VECTOR    (12 * 2u) /* 0xFFF8 Timer1_A5 CC0 */
#define UNMI_VECTOR         (13 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (14 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */


#endif /* __IO430xxxx */
