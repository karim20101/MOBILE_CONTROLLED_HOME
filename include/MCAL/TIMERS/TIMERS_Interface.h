/*
 * TIMERS_Interface.h
 *
 *  Created on: Jan 13, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_

typedef enum{
	STOP_TIMER=0,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_CLK_FALLING,
	EXTERNAL_CLK_RISING
}CLK_E;

typedef enum{
	NORMAL=0,
	NON_INVERTING=2,
	INVERTING=3
}OC_PWM_MODE;

void MTIMER0_voidInit (void);
void MTIMER0_voidStopTimer (void);
void MTIMER0_voidSetPreLoadValue (const u8 A_u8PreloadValue);
void MTIMER0_voidSetOVFCallback (void (*ptrToFunc)(void));
void MTIMER0_voidSetOCR0Value (u8 A_u8Value);
void MTIMER0_voidSetCTCCallback (void (*ptrToFunc)(void));
void MTIMER1_voidInit (void);
void MTIMER1_voidSetOCR1AValue (u16 A_u16Value);



#endif /* INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_ */
