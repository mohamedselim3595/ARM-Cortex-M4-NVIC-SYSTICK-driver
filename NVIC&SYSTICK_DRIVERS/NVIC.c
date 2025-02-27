/*
 * NVIC.c
 *
 *  Created on: Dec 12, 2024
 *      Author: Mohamed Selim
 */


#include "tm4c123gh6pm_registers.h"  // Device header for Tiva C series
#include "std_types.h"
#include "NVIC.h"



/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): IRQ_Num - Interrupt request number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables Interrupt request for the specified IRQ.
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num) {
    volatile uint32 *reg = (volatile uint32 *)(NVIC_BASE + NVIC_ENABLE_REG_OFFSET + ((IRQ_Num / 32) * 4));
    *reg |= (1 << (IRQ_Num % 32)); // Enable the specific IRQ
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): IRQ_Num - Interrupt request number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables Interrupt request for the specified IRQ.
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num) {
    volatile uint32 *reg = (volatile uint32 *)(NVIC_BASE + NVIC_DISABLE_REG_OFFSET + ((IRQ_Num / 32) * 4) + 0x80);
    *reg |= (1 << (IRQ_Num % 32)); // Disable the specific IRQ
}

/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): IRQ_Num - Interrupt request number
*                 IRQ_Priority - Priority value for the IRQ
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the priority value for the specified IRQ.
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority) {
    volatile uint32 *reg = (volatile uint32 *)(NVIC_BASE + NVIC_PRIORITY_REG_OFFSET + ((IRQ_Num / 4) * 4));
    uint8 shift = (IRQ_Num % 4) * NVIC_PRIORITY_BITS;
    *reg = (*reg & ~(0xFF << shift)) | (IRQ_Priority << shift); // Set priority
}

/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Exception_Num - System or fault exception number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables the specified ARM system or fault exception.
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num) {
    NVIC_SYSTEM_SYSHNDCTRL |= (1 << Exception_Num); // Enable specific system exception
}

/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Exception_Num - System or fault exception number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables the specified ARM system or fault exception.
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num) {
    NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << Exception_Num); // Disable specific system exception
}

/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Exception_Num - System or fault exception number
*                 Exception_Priority - Priority value for the exception
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the priority value for the specified system or fault exception.
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority) {
    volatile uint32 *reg = &NVIC_SYSTEM_PRI3_REG - (SYSTEM_PRIORITY_START - (Exception_Num / 4));
    uint8 shift = ((Exception_Num % 4) * BITS_PER_PRIORITY);
    *reg = (*reg & ~(0xFF << shift)) | (Exception_Priority << shift); // Set priority
}
