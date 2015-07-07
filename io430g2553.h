/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * msp430g2553 devices.
 *
 * Copyright 2011 IAR Systems AB.
 *
 *
 *
 ********************************************************************/

#ifndef __IO430G2553
#define __IO430G2553

#ifdef  __IAR_SYSTEMS_ICC__

#include "intrinsics.h"
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430g2553.h file for use with ICC430/A430 only
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
    unsigned char WDTIE           : 1; /* Watchdog Interrupt Enable */
    unsigned char OFIE            : 1; /* Osc. Fault  Interrupt Enable */
    unsigned char                : 2;
    unsigned char NMIIE           : 1; /* NMI Interrupt Enable */
    unsigned char ACCVIE          : 1; /* Flash Access Violation Interrupt Enable */
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
    unsigned char WDTIFG          : 1; /* Watchdog Interrupt Flag */
    unsigned char OFIFG           : 1; /* Osc. Fault Interrupt Flag */
    unsigned char PORIFG          : 1; /* Power On Interrupt Flag */
    unsigned char RSTIFG          : 1; /* Reset Interrupt Flag */
    unsigned char NMIIFG          : 1; /* NMI Interrupt Flag */
  }IFG1_bit;
} @0x0002;


enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  PORIFG          = 0x0004,
  RSTIFG          = 0x0008,
  NMIIFG          = 0x0010
};


__no_init volatile union
{
  unsigned char IE2;   /* Interrupt Enable 2 */

  struct
  {
    unsigned char UCA0RXIE        : 1; /*  */
    unsigned char UCA0TXIE        : 1; /*  */
    unsigned char UCB0RXIE        : 1; /*  */
    unsigned char UCB0TXIE        : 1; /*  */
  }IE2_bit;
} @0x0001;


enum {
  UCA0RXIE        = 0x0001,
  UCA0TXIE        = 0x0002,
  UCB0RXIE        = 0x0004,
  UCB0TXIE        = 0x0008
};


__no_init volatile union
{
  unsigned char IFG2;   /* Interrupt Flag 2 */

  struct
  {
    unsigned char UCA0RXIFG       : 1; /*  */
    unsigned char UCA0TXIFG       : 1; /*  */
    unsigned char UCB0RXIFG       : 1; /*  */
    unsigned char UCB0TXIFG       : 1; /*  */
  }IFG2_bit;
} @ 0x0003;


enum {
  UCA0RXIFG       = 0x0001,
  UCA0TXIFG       = 0x0002,
  UCB0RXIFG       = 0x0004,
  UCB0TXIFG       = 0x0008
};



#define UC0IE               IE2
#define UC0IFG              IFG2

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



  /* ADC10 Analog Enable 0 */
__no_init volatile unsigned char ADC10AE0 @ 0x004A;



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
    unsigned char RSEL3           : 1; /* Range Select Bit 3 */
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
  RSEL3           = 0x0008,
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
    unsigned char                : 1;
    unsigned char DIVS0           : 1; /* SMCLK Divider 0 */
    unsigned char DIVS1           : 1; /* SMCLK Divider 1 */
    unsigned char SELS            : 1; /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
    unsigned char DIVM0           : 1; /* MCLK Divider 0 */
    unsigned char DIVM1           : 1; /* MCLK Divider 1 */
    unsigned char SELM0           : 1; /* MCLK Source Select 0 */
    unsigned char SELM1           : 1; /* MCLK Source Select 1 */
  }BCSCTL2_bit;
} @0x0058;


enum {
  DIVS0           = 0x0002,
  DIVS1           = 0x0004,
  SELS            = 0x0008,
  DIVM0           = 0x0010,
  DIVM1           = 0x0020,
  SELM0           = 0x0040,
  SELM1           = 0x0080
};


__no_init volatile union
{
  unsigned char BCSCTL3;   /* Basic Clock System Control 3 */

  struct
  {
    unsigned char LFXT1OF         : 1; /* Low/high Frequency Oscillator Fault Flag */
    unsigned char XT2OF           : 1; /* High frequency oscillator 2 fault flag */
    unsigned char XCAP0           : 1; /* XIN/XOUT Cap 0 */
    unsigned char XCAP1           : 1; /* XIN/XOUT Cap 1 */
    unsigned char LFXT1S0         : 1; /* Mode 0 for LFXT1 (XTS = 0) */
    unsigned char LFXT1S1         : 1; /* Mode 1 for LFXT1 (XTS = 0) */
    unsigned char XT2S0           : 1; /* Mode 0 for XT2 */
    unsigned char XT2S1           : 1; /* Mode 1 for XT2 */
  }BCSCTL3_bit;
} @ 0x0053;


enum {
  LFXT1OF         = 0x0001,
  XT2OF           = 0x0002,
  XCAP0           = 0x0004,
  XCAP1           = 0x0008,
  LFXT1S0         = 0x0010,
  LFXT1S1         = 0x0020,
  XT2S0           = 0x0040,
  XT2S1           = 0x0080
};



#define __MSP430_HAS_BC2__            /* Definition to show that Module is available */

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

#define XCAP_0              (0x00)   /* XIN/XOUT Cap : 0 pF */
#define XCAP_1              (0x04)   /* XIN/XOUT Cap : 6 pF */
#define XCAP_2              (0x08)   /* XIN/XOUT Cap : 10 pF */
#define XCAP_3              (0x0C)   /* XIN/XOUT Cap : 12.5 pF */

#define LFXT1S_0            (0x00)   /* Mode 0 for LFXT1 : Normal operation */
#define LFXT1S_1            (0x10)   /* Mode 1 for LFXT1 : Reserved */
#define LFXT1S_2            (0x20)   /* Mode 2 for LFXT1 : VLO */
#define LFXT1S_3            (0x30)   /* Mode 3 for LFXT1 : Digital input signal */

#define XT2S_0              (0x00)   /* Mode 0 for XT2 : 0.4 - 1 MHz */
#define XT2S_1              (0x40)   /* Mode 1 for XT2 : 1 - 4 MHz */
#define XT2S_2              (0x80)   /* Mode 2 for XT2 : 2 - 16 MHz */
#define XT2S_3              (0xC0)   /* Mode 3 for XT2 : Digital input signal */

/*-------------------------------------------------------------------------
 *   Comparator A
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char CACTL1;   /* Comparator A Control 1 */

  struct
  {
    unsigned char CAIFG           : 1; /* Comp. A Interrupt Flag */
    unsigned char CAIE            : 1; /* Comp. A Interrupt Enable */
    unsigned char CAIES           : 1; /* Comp. A Int. Edge Select: 0:rising / 1:falling */
    unsigned char CAON            : 1; /* Comp. A enable */
    unsigned char CAREF0          : 1; /* Comp. A Internal Reference Select 0 */
    unsigned char CAREF1          : 1; /* Comp. A Internal Reference Select 1 */
    unsigned char CARSEL          : 1; /* Comp. A Internal Reference Enable */
    unsigned char CAEX            : 1; /* Comp. A Exchange Inputs */
  }CACTL1_bit;
} @0x0059;


enum {
  CAIFG           = 0x0001,
  CAIE            = 0x0002,
  CAIES           = 0x0004,
  CAON            = 0x0008,
  CAREF0          = 0x0010,
  CAREF1          = 0x0020,
  CARSEL          = 0x0040,
  CAEX            = 0x0080
};


__no_init volatile union
{
  unsigned char CACTL2;   /* Comparator A Control 2 */

  struct
  {
    unsigned char CAOUT           : 1; /* Comp. A Output */
    unsigned char CAF             : 1; /* Comp. A Enable Output Filter */
    unsigned char P2CA0           : 1; /* Comp. A +Terminal Multiplexer */
    unsigned char P2CA1           : 1; /* Comp. A -Terminal Multiplexer */
    unsigned char P2CA2           : 1; /* Comp. A -Terminal Multiplexer */
    unsigned char P2CA3           : 1; /* Comp. A -Terminal Multiplexer */
    unsigned char P2CA4           : 1; /* Comp. A +Terminal Multiplexer */
    unsigned char CASHORT         : 1; /* Comp. A Short + and - Terminals */
  }CACTL2_bit;
} @0x005A;


enum {
  CAOUT           = 0x0001,
  CAF             = 0x0002,
  P2CA0           = 0x0004,
  P2CA1           = 0x0008,
  P2CA2           = 0x0010,
  P2CA3           = 0x0020,
  P2CA4           = 0x0040,
  CASHORT         = 0x0080
};


__no_init volatile union
{
  unsigned char CAPD;   /* Comparator A Port Disable */

  struct
  {
    unsigned char CAPD0           : 1; /* Comp. A Disable Input Buffer of Port Register .0 */
    unsigned char CAPD1           : 1; /* Comp. A Disable Input Buffer of Port Register .1 */
    unsigned char CAPD2           : 1; /* Comp. A Disable Input Buffer of Port Register .2 */
    unsigned char CAPD3           : 1; /* Comp. A Disable Input Buffer of Port Register .3 */
    unsigned char CAPD4           : 1; /* Comp. A Disable Input Buffer of Port Register .4 */
    unsigned char CAPD5           : 1; /* Comp. A Disable Input Buffer of Port Register .5 */
    unsigned char CAPD6           : 1; /* Comp. A Disable Input Buffer of Port Register .6 */
    unsigned char CAPD7           : 1; /* Comp. A Disable Input Buffer of Port Register .7 */
  }CAPD_bit;
} @ 0x005B;


enum {
  CAPD0           = 0x0001,
  CAPD1           = 0x0002,
  CAPD2           = 0x0004,
  CAPD3           = 0x0008,
  CAPD4           = 0x0010,
  CAPD5           = 0x0020,
  CAPD6           = 0x0040,
  CAPD7           = 0x0080
};



#define __MSP430_HAS_CAPLUS__         /* Definition to show that Module is available */

#define CAREF_0             (0x00)    /* Comp. A Int. Ref. Select 0 : Off */
#define CAREF_1             (0x10)    /* Comp. A Int. Ref. Select 1 : 0.25*Vcc */
#define CAREF_2             (0x20)    /* Comp. A Int. Ref. Select 2 : 0.5*Vcc */
#define CAREF_3             (0x30)    /* Comp. A Int. Ref. Select 3 : Vt*/

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
    unsigned short LOCKA           : 1; /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
    unsigned short FAIL            : 1; /* Last Program or Erase failed */
  }FCTL3_bit;
} @ 0x012C;


enum {
  BUSY            = 0x0001,
  KEYV            = 0x0002,
  ACCVIFG         = 0x0004,
  WAIT            = 0x0008,
  LOCK            = 0x0010,
  EMEX            = 0x0020,
  LOCKA           = 0x0040,
  FAIL            = 0x0080
};



#define __MSP430_HAS_FLASH2__         /* Definition to show that Module is available */

#define FRKEY               (0x9600u)  /* Flash key returned by read */
#define FWKEY               (0xA500u)  /* Flash key for write */
#define FXKEY               (0x3300u)  /* for use with XOR instruction */
#define SEGWRT              (0x0080u)  /* old definition */ /* Enable bit for Flash segment write */

#define FSSEL_0             (0x0000u)  /* Flash clock select: 0 - ACLK */
#define FSSEL_1             (0x0040u)  /* Flash clock select: 1 - MCLK */
#define FSSEL_2             (0x0080u)  /* Flash clock select: 2 - SMCLK */
#define FSSEL_3             (0x00C0u)  /* Flash clock select: 3 - SMCLK */

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
  unsigned char P1SEL2;   /* Port 1 Selection 2 */

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
  }P1SEL2_bit;
} @0x0041;


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
  unsigned char P1REN;   /* Port 1 Resistor Enable */

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
  }P1REN_bit;
} @0x0027;


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
} @0x002E;


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
  unsigned char P2SEL2;   /* Port 2 Selection 2 */

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
  }P2SEL2_bit;
} @0x0042;


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
  unsigned char P2REN;   /* Port 2 Resistor Enable */

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
  }P2REN_bit;
} @ 0x002F;


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



#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port 3/4
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
} @0x001B;


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
  unsigned char P3SEL2;   /* Port 3 Selection 2 */

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
  }P3SEL2_bit;
} @0x0043;


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
  unsigned char P3REN;   /* Port 3 Resistor Enable */

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
  }P3REN_bit;
} @ 0x0010;


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



#define __MSP430_HAS_PORT3_R__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Timer0_A3
 *-------------------------------------------------------------------------*/



  /* Timer0_A3 Interrupt Vector Word */
__no_init volatile unsigned __READ short TA0IV @ 0x012E;



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

  /* Timer0_A3 */
__no_init volatile unsigned short TA0R @ 0x0170;



  /* Timer0_A3 Capture/Compare 0 */
__no_init volatile unsigned short TA0CCR0 @ 0x0172;



  /* Timer0_A3 Capture/Compare 1 */
__no_init volatile unsigned short TA0CCR1 @ 0x0174;



  /* Timer0_A3 Capture/Compare 2 */
__no_init volatile unsigned short TA0CCR2 @ 0x0176;


#define __MSP430_HAS_TA3__            /* Definition to show that Module is available */
/* Alternate register names */
#define TAIV                TA0IV     /* Timer A Interrupt Vector Word */
#define TACTL               TA0CTL    /* Timer A Control */
#define TACCTL0             TA0CCTL0  /* Timer A Capture/Compare Control 0 */
#define TACCTL1             TA0CCTL1  /* Timer A Capture/Compare Control 1 */
#define TACCTL2             TA0CCTL2  /* Timer A Capture/Compare Control 2 */
#define TAR                 TA0R      /* Timer A */
#define TACCR0              TA0CCR0   /* Timer A Capture/Compare 0 */
#define TACCR1              TA0CCR1   /* Timer A Capture/Compare 1 */
#define TACCR2              TA0CCR2   /* Timer A Capture/Compare 2 */
#define TAIV_               TA0IV_    /* Timer A Interrupt Vector Word */
#define TACTL_              TA0CTL_   /* Timer A Control */
#define TACCTL0_            TA0CCTL0_ /* Timer A Capture/Compare Control 0 */
#define TACCTL1_            TA0CCTL1_ /* Timer A Capture/Compare Control 1 */
#define TACCTL2_            TA0CCTL2_ /* Timer A Capture/Compare Control 2 */
#define TAR_                TA0R_     /* Timer A */
#define TACCR0_             TA0CCR0_  /* Timer A Capture/Compare 0 */
#define TACCR1_             TA0CCR1_  /* Timer A Capture/Compare 1 */
#define TACCR2_             TA0CCR2_  /* Timer A Capture/Compare 2 */
/* Alternate register names 2 */
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
/* T0_A3IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TACCR1        (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2        (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_6             (0x0006u)    /* Reserved */
#define TA0IV_8             (0x0008u)    /* Reserved */
#define TA0IV_TAIFG         (0x000Au)    /* TA0IFG */

/*-------------------------------------------------------------------------
 *   Timer1_A3
 *-------------------------------------------------------------------------*/



  /* Timer1_A3 Interrupt Vector Word */
__no_init volatile unsigned __READ short TA1IV @ 0x011E;



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
} @0x0180;


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
} @0x0182;


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
} @0x0184;


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
} @0x0186;


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
__no_init volatile unsigned short TA1R @ 0x0190;



  /* Timer1_A3 Capture/Compare 0 */
__no_init volatile unsigned short TA1CCR0 @ 0x0192;



  /* Timer1_A3 Capture/Compare 1 */
__no_init volatile unsigned short TA1CCR1 @ 0x0194;



  /* Timer1_A3 Capture/Compare 2 */
__no_init volatile unsigned short TA1CCR2 @ 0x0196;


#define __MSP430_HAS_T1A3__           /* Definition to show that Module is available */
/* T1_A3IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TACCR1        (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TACCR2        (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_TAIFG         (0x000Au)    /* TA1IFG */

/*-------------------------------------------------------------------------
 *   USCI_A0  UART Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned char UCA0CTL0;   /* USCI A0 Control Register 0 */

  struct
  {
    unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
    unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
    unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
    unsigned char UCSPB           : 1; /* Async. Mode: Stop Bits  0:one / 1: two */
    unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
    unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
    unsigned char UCPAR           : 1; /* Async. Mode: Parity     0:odd / 1:even */
    unsigned char UCPEN           : 1; /* Async. Mode: Parity enable */
  } UCA0CTL0_bit;

  unsigned char UCA0CTL0__SPI;   /*  */
  struct
  {
    unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
    unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
    unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
    unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
    unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
    unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
    unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
    unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
  } UCA0CTL0__SPI_bit;

} @0x0060;

enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCSPB           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCPAR           = 0x0040,
  UCPEN           = 0x0080
};

__no_init volatile union
{
  unsigned char UCA0CTL1;   /* USCI A0 Control Register 1 */

  struct
  {
    unsigned char UCSWRST         : 1; /* USCI Software Reset */
    unsigned char UCTXBRK         : 1; /* Send next Data as Break */
    unsigned char UCTXADDR        : 1; /* Send next Data as Address */
    unsigned char UCDORM          : 1; /* Dormant (Sleep) Mode */
    unsigned char UCBRKIE         : 1; /* Break interrupt enable */
    unsigned char UCRXEIE         : 1; /* RX Error interrupt enable */
    unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
    unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
  } UCA0CTL1_bit;

  unsigned char UCA0CTL1__SPI;   /*  */
  struct
  {
    unsigned char UCSWRST         : 1; /* USCI Software Reset */
    unsigned char                : 5;
    unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
    unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
  } UCA0CTL1__SPI_bit;

} @0x0061;

enum {
  UCSWRST         = 0x0001,
  UCTXBRK         = 0x0002,
  UCTXADDR        = 0x0004,
  UCDORM          = 0x0008,
  UCBRKIE         = 0x0010,
  UCRXEIE         = 0x0020,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080
};

__no_init volatile union
{
  unsigned char UCA0BR0;   /* USCI A0 Baud Rate 0 */
  unsigned char UCA0BR0__SPI;   /*  */
} @0x0062;

__no_init volatile union
{
  unsigned char UCA0BR1;   /* USCI A0 Baud Rate 1 */
  unsigned char UCA0BR1__SPI;   /*  */
} @0x0063;

__no_init volatile union
{
  unsigned char UCA0MCTL;   /* USCI A0 Modulation Control */

  struct
  {
    unsigned char UCOS16          : 1; /* USCI 16-times Oversampling enable */
    unsigned char UCBRS0          : 1; /* USCI Second Stage Modulation Select 0 */
    unsigned char UCBRS1          : 1; /* USCI Second Stage Modulation Select 1 */
    unsigned char UCBRS2          : 1; /* USCI Second Stage Modulation Select 2 */
    unsigned char UCBRF0          : 1; /* USCI First Stage Modulation Select 0 */
    unsigned char UCBRF1          : 1; /* USCI First Stage Modulation Select 1 */
    unsigned char UCBRF2          : 1; /* USCI First Stage Modulation Select 2 */
    unsigned char UCBRF3          : 1; /* USCI First Stage Modulation Select 3 */
  } UCA0MCTL_bit;

  unsigned char UCA0MCTL__SPI;   /*  */
} @0x0064;

enum {
  UCOS16          = 0x0001,
  UCBRS0          = 0x0002,
  UCBRS1          = 0x0004,
  UCBRS2          = 0x0008,
  UCBRF0          = 0x0010,
  UCBRF1          = 0x0020,
  UCBRF2          = 0x0040,
  UCBRF3          = 0x0080
};

__no_init volatile union
{
  unsigned char UCA0STAT;   /* USCI A0 Status Register */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char UCADDR          : 1; /* USCI Address received Flag */
    unsigned char UCRXERR         : 1; /* USCI RX Error Flag */
    unsigned char UCBRK           : 1; /* USCI Break received */
    unsigned char UCPE            : 1; /* USCI Parity Error Flag */
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA0STAT_bit;

  unsigned char UCA0STAT__SPI;   /*  */
  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA0STAT__SPI_bit;

} @0x0065;

enum {
  UCBUSY          = 0x0001,
  UCADDR          = 0x0002,
  UCRXERR         = 0x0004,
  UCBRK           = 0x0008,
  UCPE            = 0x0010,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080
};

__no_init volatile union
{
  unsigned __READ char UCA0RXBUF;   /* USCI A0 Receive Buffer */
  unsigned char UCA0RXBUF__SPI;   /*  */
} @0x0066;

__no_init volatile union
{
  unsigned char UCA0TXBUF;   /* USCI A0 Transmit Buffer */
  unsigned char UCA0TXBUF__SPI;   /*  */
} @0x0067;


__no_init volatile union
{
  unsigned char UCA0ABCTL;   /* USCI A0 LIN Control */

  struct
  {
    unsigned char UCABDEN         : 1; /* Auto Baud Rate detect enable */
    unsigned char                : 1;
    unsigned char UCBTOE          : 1; /* Break Timeout error */
    unsigned char UCSTOE          : 1; /* Sync-Field Timeout error */
    unsigned char UCDELIM0        : 1; /* Break Sync Delimiter 0 */
    unsigned char UCDELIM1        : 1; /* Break Sync Delimiter 1 */
  }UCA0ABCTL_bit;
} @0x005D;


enum {
  UCABDEN         = 0x0001,
  UCBTOE          = 0x0004,
  UCSTOE          = 0x0008,
  UCDELIM0        = 0x0010,
  UCDELIM1        = 0x0020
};


__no_init volatile union
{
  unsigned char UCA0IRTCTL;   /* USCI A0 IrDA Transmit Control */

  struct
  {
    unsigned char UCIREN          : 1; /* IRDA Encoder/Decoder enable */
    unsigned char UCIRTXCLK       : 1; /* IRDA Transmit Pulse Clock Select */
    unsigned char UCIRTXPL0       : 1; /* IRDA Transmit Pulse Length 0 */
    unsigned char UCIRTXPL1       : 1; /* IRDA Transmit Pulse Length 1 */
    unsigned char UCIRTXPL2       : 1; /* IRDA Transmit Pulse Length 2 */
    unsigned char UCIRTXPL3       : 1; /* IRDA Transmit Pulse Length 3 */
    unsigned char UCIRTXPL4       : 1; /* IRDA Transmit Pulse Length 4 */
    unsigned char UCIRTXPL5       : 1; /* IRDA Transmit Pulse Length 5 */
  }UCA0IRTCTL_bit;
} @0x005E;


enum {
  UCIREN          = 0x0001,
  UCIRTXCLK       = 0x0002,
  UCIRTXPL0       = 0x0004,
  UCIRTXPL1       = 0x0008,
  UCIRTXPL2       = 0x0010,
  UCIRTXPL3       = 0x0020,
  UCIRTXPL4       = 0x0040,
  UCIRTXPL5       = 0x0080
};


__no_init volatile union
{
  unsigned char UCA0IRRCTL;   /* USCI A0 IrDA Receive Control */

  struct
  {
    unsigned char UCIRRXFE        : 1; /* IRDA Receive Filter enable */
    unsigned char UCIRRXPL        : 1; /* IRDA Receive Input Polarity */
    unsigned char UCIRRXFL0       : 1; /* IRDA Receive Filter Length 0 */
    unsigned char UCIRRXFL1       : 1; /* IRDA Receive Filter Length 1 */
    unsigned char UCIRRXFL2       : 1; /* IRDA Receive Filter Length 2 */
    unsigned char UCIRRXFL3       : 1; /* IRDA Receive Filter Length 3 */
    unsigned char UCIRRXFL4       : 1; /* IRDA Receive Filter Length 4 */
    unsigned char UCIRRXFL5       : 1; /* IRDA Receive Filter Length 5 */
  }UCA0IRRCTL_bit;
} @ 0x005F;


enum {
  UCIRRXFE        = 0x0001,
  UCIRRXPL        = 0x0002,
  UCIRRXFL0       = 0x0004,
  UCIRRXFL1       = 0x0008,
  UCIRRXFL2       = 0x0010,
  UCIRRXFL3       = 0x0020,
  UCIRRXFL4       = 0x0040,
  UCIRRXFL5       = 0x0080
};



#define __MSP430_HAS_USCI__           /* Definition to show that Module is available */
#define UCMODE_0            (0x00)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x02)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x04)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x06)    /* Sync. Mode: USCI Mode: 3 */
#define UCSSEL_0            (0x00)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x40)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x80)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0xC0)    /* USCI 0 Clock Source: 3 */

#define UCBRF_0             (0x00)    /* USCI First Stage Modulation: 0 */
#define UCBRF_1             (0x10)    /* USCI First Stage Modulation: 1 */
#define UCBRF_2             (0x20)    /* USCI First Stage Modulation: 2 */
#define UCBRF_3             (0x30)    /* USCI First Stage Modulation: 3 */
#define UCBRF_4             (0x40)    /* USCI First Stage Modulation: 4 */
#define UCBRF_5             (0x50)    /* USCI First Stage Modulation: 5 */
#define UCBRF_6             (0x60)    /* USCI First Stage Modulation: 6 */
#define UCBRF_7             (0x70)    /* USCI First Stage Modulation: 7 */
#define UCBRF_8             (0x80)    /* USCI First Stage Modulation: 8 */
#define UCBRF_9             (0x90)    /* USCI First Stage Modulation: 9 */
#define UCBRF_10            (0xA0)    /* USCI First Stage Modulation: A */
#define UCBRF_11            (0xB0)    /* USCI First Stage Modulation: B */
#define UCBRF_12            (0xC0)    /* USCI First Stage Modulation: C */
#define UCBRF_13            (0xD0)    /* USCI First Stage Modulation: D */
#define UCBRF_14            (0xE0)    /* USCI First Stage Modulation: E */
#define UCBRF_15            (0xF0)    /* USCI First Stage Modulation: F */

#define UCBRS_0             (0x00)    /* USCI Second Stage Modulation: 0 */
#define UCBRS_1             (0x02)    /* USCI Second Stage Modulation: 1 */
#define UCBRS_2             (0x04)    /* USCI Second Stage Modulation: 2 */
#define UCBRS_3             (0x06)    /* USCI Second Stage Modulation: 3 */
#define UCBRS_4             (0x08)    /* USCI Second Stage Modulation: 4 */
#define UCBRS_5             (0x0A)    /* USCI Second Stage Modulation: 5 */
#define UCBRS_6             (0x0C)    /* USCI Second Stage Modulation: 6 */
#define UCBRS_7             (0x0E)    /* USCI Second Stage Modulation: 7 */
#define UCIDLE              (0x02)    /* USCI Idle line detected Flag */

/*-------------------------------------------------------------------------
 *   USCI_A0  SPI Mode
 *-------------------------------------------------------------------------*/


enum {
/*  UCSYNC          = 0x0001, */
/*  UCMODE0         = 0x0002, */
/*  UCMODE1         = 0x0004, */
  UCMST           = 0x0008,
/*  UC7BIT          = 0x0010, */
/*  UCMSB           = 0x0020, */
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080
};

/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
/*-------------------------------------------------------------------------
 *   USCI_B0  SPI Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned char UCB0CTL0__SPI;   /*  */

  struct
  {
    unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
    unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
    unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
    unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
    unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
    unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
    unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
    unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
  } UCB0CTL0__SPI_bit;

  unsigned char UCB0CTL0;   /* USCI B0 Control Register 0 */
  struct
  {
    unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
    unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
    unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
    unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
    unsigned char                : 1;
    unsigned char UCMM            : 1; /* Multi-Master Environment */
    unsigned char UCSLA10         : 1; /* 10-bit Slave Address Mode */
    unsigned char UCA10           : 1; /* 10-bit Address Mode */
  } UCB0CTL0_bit;

} @0x0068;

/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCMST           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCB0CTL1__SPI;   /*  */

  struct
  {
    unsigned char UCSWRST         : 1; /* USCI Software Reset */
    unsigned char                : 5;
    unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
    unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
  } UCB0CTL1__SPI_bit;

  unsigned char UCB0CTL1;   /* USCI B0 Control Register 1 */
  struct
  {
    unsigned char UCSWRST         : 1; /* USCI Software Reset */
    unsigned char UCTXSTT         : 1; /* Transmit START */
    unsigned char UCTXSTP         : 1; /* Transmit STOP */
    unsigned char UCTXNACK        : 1; /* Transmit NACK */
    unsigned char UCTR            : 1; /* Transmit/Receive Select/Flag */
    unsigned char                : 1;
    unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
    unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
  } UCB0CTL1_bit;

} @0x0069;

/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCB0BR0__SPI;   /*  */
  unsigned char UCB0BR0;   /* USCI B0 Baud Rate 0 */
} @0x006A;

__no_init volatile union
{
  unsigned char UCB0BR1__SPI;   /*  */
  unsigned char UCB0BR1;   /* USCI B0 Baud Rate 1 */
} @0x006B;

__no_init volatile union
{
  unsigned char UCB0STAT__SPI;   /*  */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB0STAT__SPI_bit;

  unsigned char UCB0STAT;   /* USCI B0 Status Register */
  struct
  {
    unsigned char UCALIFG         : 1; /* Arbitration Lost interrupt Flag */
    unsigned char UCSTTIFG        : 1; /* START Condition interrupt Flag */
    unsigned char UCSTPIFG        : 1; /* STOP Condition interrupt Flag */
    unsigned char UCNACKIFG       : 1; /* NAK Condition interrupt Flag */
    unsigned char UCBBUSY         : 1; /* Bus Busy Flag */
    unsigned char UCGC            : 1; /* General Call address received Flag */
    unsigned char UCSCLLOW        : 1; /* SCL low */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB0STAT_bit;

} @0x006D;

/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCB0RXBUF__SPI;   /*  */
  unsigned __READ char UCB0RXBUF;   /* USCI B0 Receive Buffer */
} @0x006E;

__no_init volatile union
{
  unsigned char UCB0TXBUF__SPI;   /*  */
  unsigned char UCB0TXBUF;   /* USCI B0 Transmit Buffer */
} @0x006F;

/*-------------------------------------------------------------------------
 *   USCI_B0  I2C Mode
 *-------------------------------------------------------------------------*/


enum {
/*  UCSYNC          = 0x0001, */
/*  UCMODE0         = 0x0002, */
/*  UCMODE1         = 0x0004, */
/*  UCMST           = 0x0008, */
  UCMM            = 0x0020,
  UCSLA10         = 0x0040,
  UCA10           = 0x0080
};

enum {
/*  UCSWRST         = 0x0001, */
  UCTXSTT         = 0x0002,
  UCTXSTP         = 0x0004,
  UCTXNACK        = 0x0008,
  UCTR            = 0x0010
/*  UCSSEL0         = 0x0040, */
/*  UCSSEL1         = 0x0080, */
};


__no_init volatile union
{
  unsigned char UCB0I2CIE;   /* USCI B0 I2C Interrupt Enable Register */

  struct
  {
    unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
    unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
    unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
    unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
  }UCB0I2CIE_bit;
} @0x006C;


enum {
  UCALIE          = 0x0001,
  UCSTTIE         = 0x0002,
  UCSTPIE         = 0x0004,
  UCNACKIE        = 0x0008
};

enum {
  UCALIFG         = 0x0001,
  UCSTTIFG        = 0x0002,
  UCSTPIFG        = 0x0004,
  UCNACKIFG       = 0x0008,
  UCBBUSY         = 0x0010,
  UCGC            = 0x0020,
  UCSCLLOW        = 0x0040
/*  UCLISTEN        = 0x0080, */
};


__no_init volatile union
{
  unsigned short UCB0I2COA;   /* USCI B0 I2C Own Address */

  struct
  {
    unsigned short UCOA0           : 1; /* I2C Own Address 0 */
    unsigned short UCOA1           : 1; /* I2C Own Address 1 */
    unsigned short UCOA2           : 1; /* I2C Own Address 2 */
    unsigned short UCOA3           : 1; /* I2C Own Address 3 */
    unsigned short UCOA4           : 1; /* I2C Own Address 4 */
    unsigned short UCOA5           : 1; /* I2C Own Address 5 */
    unsigned short UCOA6           : 1; /* I2C Own Address 6 */
    unsigned short UCOA7           : 1; /* I2C Own Address 7 */
    unsigned short UCOA8           : 1; /* I2C Own Address 8 */
    unsigned short UCOA9           : 1; /* I2C Own Address 9 */
    unsigned short                : 5;
    unsigned short UCGCEN          : 1; /* I2C General Call enable */
  }UCB0I2COA_bit;
} @0x0118;


enum {
  UCOA0           = 0x0001,
  UCOA1           = 0x0002,
  UCOA2           = 0x0004,
  UCOA3           = 0x0008,
  UCOA4           = 0x0010,
  UCOA5           = 0x0020,
  UCOA6           = 0x0040,
  UCOA7           = 0x0080,
  UCOA8           = 0x0100,
  UCOA9           = 0x0200,
  UCGCEN          = 0x8000
};


__no_init volatile union
{
  unsigned short UCB0I2CSA;   /* USCI B0 I2C Slave Address */

  struct
  {
    unsigned short UCSA0           : 1; /* I2C Slave Address 0 */
    unsigned short UCSA1           : 1; /* I2C Slave Address 1 */
    unsigned short UCSA2           : 1; /* I2C Slave Address 2 */
    unsigned short UCSA3           : 1; /* I2C Slave Address 3 */
    unsigned short UCSA4           : 1; /* I2C Slave Address 4 */
    unsigned short UCSA5           : 1; /* I2C Slave Address 5 */
    unsigned short UCSA6           : 1; /* I2C Slave Address 6 */
    unsigned short UCSA7           : 1; /* I2C Slave Address 7 */
    unsigned short UCSA8           : 1; /* I2C Slave Address 8 */
    unsigned short UCSA9           : 1; /* I2C Slave Address 9 */
  }UCB0I2CSA_bit;
} @ 0x011A;


enum {
  UCSA0           = 0x0001,
  UCSA1           = 0x0002,
  UCSA2           = 0x0004,
  UCSA3           = 0x0008,
  UCSA4           = 0x0010,
  UCSA5           = 0x0020,
  UCSA6           = 0x0040,
  UCSA7           = 0x0080,
  UCSA8           = 0x0100,
  UCSA9           = 0x0200
};



#define __MSP430_HAS_USCI__           /* Definition to show that Module is available */

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
 *   Calibration Data
 *-------------------------------------------------------------------------*/



  /* DCOCTL  Calibration Data for 16MHz */
__no_init volatile unsigned __READ char CALDCO_16MHZ @ 0x10F8;



  /* BCSCTL1 Calibration Data for 16MHz */
__no_init volatile unsigned __READ char CALBC1_16MHZ @ 0x10F9;



  /* DCOCTL  Calibration Data for 12MHz */
__no_init volatile unsigned __READ char CALDCO_12MHZ @ 0x10FA;



  /* BCSCTL1 Calibration Data for 12MHz */
__no_init volatile unsigned __READ char CALBC1_12MHZ @ 0x10FB;



  /* DCOCTL  Calibration Data for 8MHz */
__no_init volatile unsigned __READ char CALDCO_8MHZ @ 0x10FC;



  /* BCSCTL1 Calibration Data for 8MHz */
__no_init volatile unsigned __READ char CALBC1_8MHZ @ 0x10FD;



  /* DCOCTL  Calibration Data for 1MHz */
__no_init volatile unsigned __READ char CALDCO_1MHZ @ 0x10FE;



  /* BCSCTL1 Calibration Data for 1MHz */
__no_init volatile unsigned __READ char CALBC1_1MHZ @ 0x10FF;






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
#define USCIAB0TX_VECTOR    (6 * 2u)  /* 0xFFEC USCI A0/B0 Transmit */
#define USCIAB0RX_VECTOR    (7 * 2u)  /* 0xFFEE USCI A0/B0 Receive */
#define TIMER0_A1_VECTOR    (8 * 2u)  /* 0xFFF0 Timer0)A CC1, TA0 */
#define TIMER0_A0_VECTOR    (9 * 2u)  /* 0xFFF2 Timer0_A CC0 */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (11 * 2u) /* 0xFFF6 Comparator A */
#define TIMER1_A1_VECTOR    (12 * 2u) /* 0xFFF8 Timer1_A CC1-4, TA1 */
#define TIMER1_A0_VECTOR    (13 * 2u) /* 0xFFFA Timer1_A CC0 */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */


#endif /* __IO430xxxx */
