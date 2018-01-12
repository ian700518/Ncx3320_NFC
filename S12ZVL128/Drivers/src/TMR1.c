/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : TMR1.c
**     Project     : Reader-Lib-HAL-PE
**     Processor   : MC9S12ZVL32MLC
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.21, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2016-02-15, 16:16, # CodeGen: 59
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : TIM0_Counter (16-bit)
**         Compare name                : T0C1
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 26151 Hz
**           Initial period/frequency
**             Xtal ticks              : 499988
**             microseconds            : 499988
**             milliseconds            : 500
**             seconds (real)          : 0.499988
**             Hz                      : 2
**
**         Runtime setting             : period/frequency interval (continual setting)
**             ticks                   : 995 to 2500016 ticks
**             microseconds            : 995 to 2500016 microseconds
**             milliseconds            : 1 to 2500 milliseconds
**             seconds                 : 1 to 2 seconds
**             seconds (real)          : 0.00099424 to 2.50001648 seconds
**             Hz                      : 1 to 1005 Hz
**
**         Initialization:
**              Timer                  : Disabled
**              Events                 : Disabled
**
**         Timer registers
**              Counter                : TIM0TCNT  [0x05C4]
**              Mode                   : TIM0TIOS  [0x05C0]
**              Run                    : TIM0TSCR1 [0x05C6]
**              Prescaler              : TIM0TSCR2 [0x05CD]
**
**         Compare registers
**              Compare                : TIM0TC1   [0x05D2]
**
**         Flip-flop registers
**              Mode                   : TIM0TCTL2 [0x05C9]
**     Contents    :
**         Enable       - byte TMR1_Enable(void);
**         Disable      - byte TMR1_Disable(void);
**         EnableEvent  - byte TMR1_EnableEvent(void);
**         DisableEvent - byte TMR1_DisableEvent(void);
**         SetPeriodUS  - byte TMR1_SetPeriodUS(word Time);
**         SetPeriodMS  - byte TMR1_SetPeriodMS(word Time);
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
** @file TMR1.c
** @version 01.21
** @brief
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
*/         
/*!
**  @addtogroup TMR1_module TMR1 module documentation
**  @{
*/         

/* MODULE TMR1. */

#include "phOsal_S12Zvl_Int.h"
#include "TMR1.h"

#pragma DATA_SEG TMR1_DATA             /* Select data segment "TMR1_DATA" */
#pragma CODE_SEG TMR1_CODE
#pragma CONST_SEG DEFAULT              /* Use default segment for constants */

static bool EnUser;                    /* Enable/Disable device by user */

static word CmpVal;                    /* Value periodicly addded to compare register */

/* Internal method prototypes */


/* End of Internal methods declarations */

/*
** ===================================================================
**     Method      :  TMR1_Enable (component TimerInt)
**     Description :
**         This method enables the component - it starts the timer.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TMR1_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    TIM0TC1 = TIM0TCNT + CmpVal;       /* Store new value to the compare register */ 
    TIM0TIE_C1I = 1U;                  /* Enable interrupt */ 
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TMR1_Disable (component TimerInt)
**     Description :
**         This method disables the component - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TMR1_Disable(void)
{
  EnUser = FALSE;                      /* If yes then set the flag "device disabled" */
  TIM0TIE_C1I = 0U;                    /* Disable interrupt */ 
  TIM0TFLG1 = 0x02U;                   /* Reset interrupt request flag */ 
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TMR1_EnableEvent (component TimerInt)
*/
/*!
**     @brief
**         This method enables the events. The method is available only
**         if an event is enabled.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
byte TMR1_EnableEvent(void)
{
  if (TIM0TIE_C1I  == 0U) {            /* If source interrupt is disabled */
    TIM0TFLG1_C1F = 1U;                /* Reset interrupt request flag */
    TIM0TIE_C1I = 1U;                  /* Enable source interrupt */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TMR1_DisableEvent (component TimerInt)
*/
/*!
**     @brief
**         This method disables the events. The method is available
**         only if an event is enabled.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
  
  /*
  byte TMR1_DisableEvent(void)
  
  **      This method is implemented as a macro. See header module. **
  */
/*
** ===================================================================
**     Method      :  TMR1_SetPeriodUS (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in microseconds as a 16-bit
**         unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Period to set [in microseconds]
**                      (995 to 65535 microseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TMR1_SetPeriodUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */
  
  if (Time < 0x03E3U) {                /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, (dword)0x06B1CEBALU, &rtval); /* Multiply given value and High speed mode coefficient */
  if (PE_Timer_LngHi4(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 0x00010000 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpVal = rtword;                     /* Store given value to the variable CmpVal */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TMR1_SetPeriodMS (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in miliseconds as a 16-bit
**         unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Period to set [in miliseconds]
**                      (1 to 2500 milliseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TMR1_SetPeriodMS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */
  
  if ((Time > 0x09C4U) || (Time < 0x01U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, (dword)0x1A268F88LU, &rtval); /* Multiply given value and High speed mode coefficient */
  if (PE_Timer_LngHi3(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 0x00010000 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpVal = rtword;                     /* Store given value to the variable CmpVal */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TMR1_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TMR1_Init(void)
{
  EnUser = FALSE;                      /* Disable device */
  CmpVal = 0x3313U;                    /* Store given value to the variable CmpVal */
}

/*
** ===================================================================
**     Method      :  TMR1_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(TMR1_Interrupt)
{
  TIM0TC1 += CmpVal;                   /* Add value corresponding with period */
  TIM0TFLG1 = 0x02U;                   /* Reset interrupt request flag */
  TMR1_OnInterrupt();                  /* Invoke user event */
}

#pragma CODE_SEG TMR1_CODE

/* END TMR1. */

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
