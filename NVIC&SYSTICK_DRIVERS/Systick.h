/*
 * Systick.h
 *
 *  Created on: Dec 11, 2024
 *      Author: dell
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


#ifndef SYSTICK_DRIVER_H
#define SYSTICK_DRIVER_H

#include "std_types.h"
/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))


void SysTick_Init(uint16 a_TimeInMilliSeconds);


void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);


void SysTick_Handler(void);


void SysTick_SetCallBack(volatile void (*Ptr2Func)(void));


void SysTick_Stop(void);


void SysTick_Start(void);


void SysTick_DeInit(void);

#endif // SYSTICK_DRIVER_H



#endif /* SYSTICK_H_ */
