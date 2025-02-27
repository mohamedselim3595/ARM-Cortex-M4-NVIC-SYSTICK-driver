/*
 * SysTick.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Mohamed Selim
 */

#include "std_types.h"
#include "tm4c123gh6pm_registers.h"  // Device header for Tiva C series


// Global variable to hold the callback function
static volatile void (*g_SysTickCallback)(void) = 0;

/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): a_TimeInMilliSeconds - Time period in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the SysTick timer with the specified time in milliseconds using interrupts.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds) {
    uint32 reloadValue = (16000 * a_TimeInMilliSeconds) - 1; // Assuming 16MHz clock

    // Disable SysTick during configuration
    SYSTICK_CTRL_REG = 0;

    // Set reload value
    SYSTICK_RELOAD_REG = reloadValue;

    // Clear the current value
    SYSTICK_CURRENT_REG = 0;

    // Enable SysTick with system clock and interrupts
    SYSTICK_CTRL_REG = 0x07; // ENABLE | INTEN | CLK_SRC
}

/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stops the SysTick timer.
**********************************************************************/
void SysTick_Stop(void) {
    SYSTICK_CTRL_REG &= ~0x01; // Clear the ENABLE bit
}

/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): a_TimeInMilliSeconds - Time period in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts the SysTick timer with the specified time in milliseconds using busy-wait technique.
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds) {
    uint32 reloadValue = (16000 * a_TimeInMilliSeconds) - 1; // Assuming 16MHz clock

    // Disable SysTick during configuration
    SYSTICK_CTRL_REG = 0;

    // Set reload value
    SYSTICK_RELOAD_REG = reloadValue;

    // Clear the current value
    SYSTICK_CURRENT_REG = 0;

    // Enable SysTick with system clock but no interrupts
    SYSTICK_CTRL_REG = 0x05; // ENABLE | CLK_SRC

    // Wait until the COUNT flag is set
    while ((SYSTICK_CTRL_REG & 0x10000) == 0);

    // Stop SysTick timer
    SysTick_Stop();
}

/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Asynchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: SysTick interrupt handler that executes the registered callback function.
**********************************************************************/
void SysTick_Handler(void) {
    if (g_SysTickCallback != 0) {
        g_SysTickCallback();
    }
}

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Ptr2Func - Pointer to the callback function
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Registers a callback function to be executed in the SysTick interrupt handler.
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void)) {
    g_SysTickCallback = Ptr2Func;
}



/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts or resumes the SysTick timer.
**********************************************************************/
void SysTick_Start(void) {
    SYSTICK_CTRL_REG |= 0x01; // Set the ENABLE bit
}

/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: De-initializes the SysTick timer.
**********************************************************************/
void SysTick_DeInit(void) {
    // Disable SysTick and clear all configurations
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    g_SysTickCallback = 0;
}
