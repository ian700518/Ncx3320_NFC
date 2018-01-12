/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.c
**     Project     : Reader-Lib-HAL-PE
**     Processor   : MC9S12ZVL32MLC
**     Component   : MC9S12ZVL32_32
**     Version     : Component 01.003, Driver 02.08, CPU db: 3.00.000
**     Datasheet   : MC9S12ZVLRMV1 Rev. 0.09 December 10, 2012
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2016-03-30, 13:33, # CodeGen: 62
**     Abstract    :
**         This component "MC9S12ZVL32_32" implements properties, methods,
**         and events of the CPU.
**     Settings    :
**
**     Contents    :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**         Delay100US  - void Cpu_Delay100US(word us100);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 02.08
** @brief
**         This component "MC9S12ZVL32_32" implements properties, methods,
**         and events of the CPU.
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

#include "SPI.h"
#include "PIN_RESET.h"
#include "PIN_SSEL.h"
#include "LED_BIT.h"
#include "TMR0.h"
#include "TMR1.h"
#include "TMR2.h"
#include "Terminal.h"
#include "Inhr1.h"
#include "Utility.h"
#include "LED_R_BIT.h"
#include "EN_PWR.h"
#include "Events.h"
#include "Cpu.h"

#define CGM_DELAY  0x02FFU

#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT


/* Global variables */
volatile byte CCR_reg;                 /* Current CCR reegister */
#pragma CODE_SEG __NEAR_SEG NON_BANKED


/*
** ===================================================================
**     Method      :  Cpu_Cpu_Interrupt (component MC9S12ZVL32_32)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cpu_Interrupt)
{
  /*lint -save -e950 Disable MISRA rule (1.1) checking. */
  asm(BGND);
  /*lint -restore Enable MISRA rule (1.1) checking. */
}


/*
** ===================================================================
**     Method      :  Cpu_Delay100US (component MC9S12ZVL32_32)
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. The method
**         is independent on selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**                         - The value of zero results in maximal 
**                           delay of approx. 6.5 seconds.
**     Returns     : Nothing
** ===================================================================
*/
#pragma NO_ENTRY                       /* Suppress generation of prologue code in a function */
#pragma NO_EXIT                        /* Suppress generation of  epilogue code in a function */
void Cpu_Delay100US(word us100)
{
  /* irremovable overhead (ignored): 6.5 cycles */
  /* jsr:  2.5 cycles overhead (call this function) */
  /* LD D2,#x:  1 cycles overhead (load parameter into register) */
  /* rts:  3 cycles overhead (return from this function) */

  /* irremovable overhead for each 100us cycle (counted): 2.5 cycles */
  /* dbne:  4.5 cycles overhead */

  /*lint -save  -e950 -e522 Disable MISRA rule (1.1,14.2) checking. */
  asm {
    loop:
    /* 100 us delay block begin */
     
     
    /*
     * Delay
     *   - requested                  : 100 us @ 6.25MHz,
     *   - possible                   : 625 c, 100000 ns
     *   - without removable overhead : 620.5 c, 99280 ns
     */
    LD D6,#0x0071                      /* (1_5 c: 240 ns) number of iterations */
label0:
    DEC D6                             /* (1 c: 160 ns) decrement d1 */
    BNE label0                         /* (4 c: 640 ns) repeat 113x */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    /* 100 us delay block end */
    DBNE D2, loop                      /* us100 parameter is passed via D register */
  };
  /*lint -restore Enable MISRA rule (1.1,14.2) checking. */
}

#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MC9S12ZVL32_32)
**     Description :
**         Disable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MC9S12ZVL32_32)
**     Description :
**         Enable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component MC9S12ZVL32_32)
**     Description :
**         Set low power mode - Stop mode.
**         For more information about the stop mode see
**         documentation of this CPU.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component MC9S12ZVL32_32)
**     Description :
**         Set low power mode - Wait mode.
**         For more information about the wait mode see
**         documentation of this CPU.
**         Release from Wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED

/*
** ===================================================================
**     Method      :  _EntryPoint (component MC9S12ZVL32_32)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab of the CPU component. !!! ***/



#pragma NO_RETURN                      /* Suppress generation of return from a function */
void _EntryPoint(void)
{

  /*** !!! Here you can place your own code using property "User code before PE initialization" on the build options tab of the CPU compoennt. !!! ***/

  /* ### MC9S12ZVL32_32 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /* IVBR: IVB_ADDR=0x7FFF,??=0 */
  setReg16(IVBR, 0xFFFEU);              
  /* ECLKCTL: NECLK=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg8(ECLKCTL, 0x80U);              
  /*  System clock initialization */
  /* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
  setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock configuration registers */ 
  /* CPMUCLKS: PSTP=0 */
  clrReg8Bits(CPMUCLKS, 0x40U);         
  /* CPMUCLKS: PLLSEL=1 */
  setReg8Bits(CPMUCLKS, 0x80U);        /* Enable the PLL to allow write to divider registers */ 
  /* CPMUPOSTDIV: ??=0,??=0,??=0,POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=1,POSTDIV0=1 */
  setReg8(CPMUPOSTDIV, 0x03U);         /* Set the post divider register */ 
  /* Whenever changing PLL reference clock (REFCLK) frequency to a higher value
   it is recommended to write CPMUSYNR = 0x00 in order to stay within specified
   maximum frequency of the MCU */
  /* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=0,SYNDIV1=0,SYNDIV0=0 */
  setReg8(CPMUSYNR, 0x00U);            /* Set the multiplier register */ 
  /* CPMUPLL: ??=0,??=0,FM1=0,FM0=0,??=0,??=0,??=0,??=0 */
  setReg8(CPMUPLL, 0x00U);             /* Set the PLL frequency modulation */ 
  /* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=1,SYNDIV5=0,SYNDIV4=1,SYNDIV3=1,SYNDIV2=0,SYNDIV1=0,SYNDIV0=0 */
  setReg8(CPMUSYNR, 0x58U);            /* Set the multiplier register */ 
  while(CPMUIFLG_LOCK == 0U) {         /* Wait until the PLL is within the desired tolerance of the target frequency */
  }
  /* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
  setReg8(CPMUPROT, 0x00U);            /* Enable protection of clock configuration registers */ 
  /* CPMUCOP: RSBCK=0,WRTMASK=1 */
  clrSetReg8Bits(CPMUCOP, 0x40U, 0x20U); 
  /* CPMUHTCTL: ??=0,??=0,VSEL=0,??=0,HTE=0,HTDS=0,HTIE=0,HTIF=0 */
  setReg8(CPMUHTCTL, 0x00U);            
  /* CPMUVREGCTL: ??=0,??=0,??=0,??=0,??=0,??=0,EXTXON=0,INTXON=1 */
  setReg8(CPMUVREGCTL, 0x01U);          
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code using property "User code after PE initialization" on the build options tab of the CPU component. !!! ***/

  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  __asm(jmp _Startup);                 /* Jump to C startup code */
  /*lint -restore Enable MISRA rule (1.1) checking. */
}

#pragma CODE_SEG DEFAULT
/*
** ===================================================================
**     Method      :  PE_low_level_init (component MC9S12ZVL32_32)
**
**     Description :
**         Initializes components and provides common register 
**         initialization. The method is called automatically as a part 
**         of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /* Int. priority initialization */
  /*                                        No. Address Pri XGATE Name                 Description */
  setReg8(INT_CFADDR, 0x70U);           
  setReg8(INT_CFDATA1, 0x04U);         /*  0x71  0x00FFFFC4   4   no   ivVtim0ch2           used by PE */ 
  setReg8(INT_CFDATA2, 0x04U);         /*  0x72  0x00FFFFC8   4   no   ivVtim0ch1           used by PE */ 
  setReg8(INT_CFDATA3, 0x05U);         /*  0x73  0x00FFFFCC   5   no   ivVtim0ch0           used by PE */ 
  /* Common initialization of the CPU registers */
  /* PTS: PTS3=0,PTS2=0 */
  clrReg8Bits(PTS, 0x0CU);              
  /* DDRS: DDRS3=1,DDRS2=1,DDRS1=1,DDRS0=0 */
  clrSetReg8Bits(DDRS, 0x01U, 0x0EU);   
  /* PIEP: PIEP7=0,PIEP1=0 */
  clrReg8Bits(PIEP, 0x82U);             
  /* PTP: PTP7=0,PTP1=0 */
  clrReg8Bits(PTP, 0x82U);              
  /* PERP: PERP7=0,PERP1=0 */
  clrReg8Bits(PERP, 0x82U);             
  /* DDRP: DDRP7=1,DDRP6=1,DDRP4=1,DDRP2=1,DDRP1=1,DDRP0=1 */
  setReg8Bits(DDRP, 0xD7U);             
  /* PIES: PIES3=0 */
  clrReg8Bits(PIES, 0x08U);             
  /* WOMS: WOMS3=0 */
  clrReg8Bits(WOMS, 0x08U);             
  /* DIENADL: DIENADL1=1,DIENADL0=1 */
  setReg8Bits(DIENADL, 0x03U);          
  /* PIEADL: PIEADL1=0,PIEADL0=0 */
  clrReg8Bits(PIEADL, 0x03U);           
  /* PTADL: PTADL1=0,PTADL0=0 */
  clrReg8Bits(PTADL, 0x03U);            
  /* PERADL: PERADL1=0,PERADL0=0 */
  clrReg8Bits(PERADL, 0x03U);           
  /* DDRADL: DDRADL7=1,DDRADL6=1,DDRADL1=1,DDRADL0=1 */
  setReg8Bits(DDRADL, 0xC3U);           
  /* TIM0TSCR1: TEN=0,TSWAI=0,TSFRZ=0,TFFCA=0,PRNT=1,??=0,??=0,??=0 */
  setReg8(TIM0TSCR1, 0x08U);            
  /* TIM0OCPD: OCPD2=1,OCPD1=1,OCPD0=1 */
  setReg8Bits(TIM0OCPD, 0x07U);         
  /* TIM0TIOS: IOS2=1,IOS1=1,IOS0=1 */
  setReg8Bits(TIM0TIOS, 0x07U);         
  /* TIM0TCTL2: OM2=0,OL2=0,OM1=0,OL1=0,OM0=0,OL0=0 */
  clrReg8Bits(TIM0TCTL2, 0x3FU);        
  /* TIM0TTOV: TOV2=0,TOV1=0,TOV0=0 */
  clrReg8Bits(TIM0TTOV, 0x07U);         
  /* TIM0PTPSR: PTPS7=1,PTPS6=1,PTPS5=1,PTPS4=0,PTPS3=1,PTPS2=1,PTPS1=1,PTPS0=0 */
  setReg8(TIM0PTPSR, 0xEEU);            
  /* TIM0TIE: C2I=0,C1I=0,C0I=0 */
  clrReg8Bits(TIM0TIE, 0x07U);          
  /* MODRR0: SCI1RR=0 */
  clrReg8Bits(MODRR0, 0x08U);           
  /* PTT: PTT1=1 */
  setReg8Bits(PTT, 0x02U);              
  /* DDRT: DDRT7=1,DDRT6=1,DDRT5=1,DDRT4=1,DDRT3=1,DDRT1=1,DDRT0=0 */
  clrSetReg8Bits(DDRT, 0x01U, 0xFAU);   
  /* CPMUINT: LOCKIE=0,OSCIE=0 */
  clrReg8Bits(CPMUINT, 0x12U);          
  /* CPMULVCTL: LVIE=0 */
  clrReg8Bits(CPMULVCTL, 0x02U);        
  /* ECCIE: SBEEIE=0 */
  clrReg8Bits(ECCIE, 0x01U);            
  /* ECCDCMD: ECCDRR=0 */
  clrReg8Bits(ECCDCMD, 0x80U);          
  /* DDRADH: DDRADH1=1,DDRADH0=1 */
  setReg8Bits(DDRADH, 0x03U);           
  /* DDRJ: DDRJ1=1,DDRJ0=1 */
  setReg8Bits(DDRJ, 0x03U);             
  /* RDRP: RDRP7=0,RDRP5=0,RDRP3=0,RDRP1=0 */
  clrReg8Bits(RDRP, 0xAAU);             
  /* IRQCR: IRQEN=0 */
  clrReg8Bits(IRQCR, 0x40U);            
  /* ### MC9S12ZVL32_32 "Cpu" init code ... */
  /* ###  Synchro master "SPI" init code ... */
  SPI_Init();
  /* ### BitIO "PIN_RESET" init code ... */
  /* ### BitIO "PIN_SSEL" init code ... */
  /* ### BitIO "LED_BIT" init code ... */
  /* ### TimerInt "TMR0" init code ... */
  
  
  TMR0_Init();
  /* ### TimerInt "TMR1" init code ... */
  
  
  TMR1_Init();
  /* ### TimerInt "TMR2" init code ... */
  
  
  TMR2_Init();
  /* ### Asynchro serial "Inhr1" init code ... */
  Inhr1_Init();
  /* ###  "Terminal" init code ... */
  /* ### BitIO "LED_R_BIT" init code ... */
  /* ### BitIO "EN_PWR" init code ... */
  /* Common peripheral initialization - ENABLE */
  /* TIM0TSCR1: TEN=1,TSWAI=0,TSFRZ=0,TFFCA=0,PRNT=0,??=0,??=0,??=0 */
  setReg8(TIM0TSCR1, 0x80U);            
  __EI();                              /* Enable interrupts */
}

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
/* Initialization of the CPU registers in FLASH */
/*lint -restore Enable MISRA rule (1.1) checking. */

/* END Cpu. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/
