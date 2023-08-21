/*
 * TIMERS_Program.c
 *
 *  Created on: Jan 13, 2023
 *      Author: abdelrahmanhossam
 */

#include <util/delay.h>
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/TIMERS/TIMERS_Interface.h"
#include "../include/MCAL/TIMERS/TIMERS_Private.h"
#include "../include/MCAL/TIMERS/TIMERS_Cfg.h"
#include "../include/MCAL/TIMERS/TIMER1_Private.h"

#define NULL 0

void (*Timer0_OVF_CALLBACK)(void) = NULL;
void (*Timer0_CTC_CALLBACK)(void) = NULL;

void MTIMER1_voidInit (void)
{
	// Select Timer 1 mode --> 14
	CLR_BIT (TCCR1A,0);
	SET_BIT (TCCR1A,1);
	SET_BIT (TCCR1B,3);
	SET_BIT (TCCR1B,4);
	// Select HW Action on OC1A --> Non Inverting
	CLR_BIT (TCCR1A,6);
	SET_BIT (TCCR1A,7);
	// set top Value at ICR1
	ICR1= 19999;
	// Set Angle of Servo --> OCR1A Value
	OCR1A =1500;
	// Start Timer
	CLR_BIT(TCCR1B,2);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,0);
}

void MTIMER1_voidSetOCR1AValue (u16 A_u16Value)
{
	OCR1A = A_u16Value;
}

void MTIMER0_voidInit (void)
{
	// Normal Mode
#if TIMER0_MODE == NORMAL

	// Set wave Generation Mode to Normal Mode
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);

	// Turn on OVF Interrupt
	SET_BIT(TIMSK,0);
	CLR_BIT(TIMSK,1);

	// start Timer
	TCCR0 &= 0b11111000;
	TCCR0 |= CLK_CFG;
#elif TIMER0_MODE == CTC
	// Set wave Generation Mode to CTC Mode
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	// Turn on CTC Interrupt
	CLR_BIT(TIMSK,0);
	SET_BIT(TIMSK,1);
	// Set compare match unit value --> must be CFG
	OCR0 = OCR0_VALUE;
	// start Timer
	TCCR0 &= 0b11111000;
	TCCR0 |= CLK_CFG;
#elif TIMER0_MODE == PHASE_CORRECT

#elif TIMER0_MODE == PWM
	// Set wave Generation Mode to Fast PWM Mode
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
	// Turn OFF CTC and OVF Interrupts
	CLR_BIT(TIMSK,0);
	CLR_BIT(TIMSK,1);
	// Set compare match unit value --> must be CFG
	OCR0 = OCR0_VALUE;
	// start Timer and set OC0 Pin CFG
	TCCR0 &= 0b11001000;
	TCCR0 |= (CLK_CFG|(FAST_PWM_OC0_PIN_CFG<<4));
#endif

}

void MTIMER0_voidStopTimer (void)
{
	TCCR0 &= 0b11111000;
}

void MTIMER0_voidSetPreLoadValue (const u8 A_u8PreloadValue)
{
	TCNT0 = A_u8PreloadValue;
}

void MTIMER0_voidSetOCR0Value (u8 A_u8Value)
{
	OCR0 = A_u8Value;
}

void MTIMER0_voidSetOVFCallback (void (*ptrToFunc)(void))
{
	if (ptrToFunc!= NULL)
	{
		Timer0_OVF_CALLBACK = ptrToFunc;
	}
}

void MTIMER0_voidSetCTCCallback (void (*ptrToFunc)(void))
{
	if (ptrToFunc!= NULL)
	{
		Timer0_CTC_CALLBACK = ptrToFunc;
	}
}


void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	if (Timer0_CTC_CALLBACK != NULL)
	{
		Timer0_CTC_CALLBACK();
	}
}


void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	if (Timer0_OVF_CALLBACK != NULL)
	{
		Timer0_OVF_CALLBACK();
	}
}
