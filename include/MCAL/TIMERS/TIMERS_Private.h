/*
 * TIMERS_Private.h
 *
 *  Created on: Jan 13, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_


#define TCCR0	(*((volatile u8 *)0x53))
#define TCNT0	(*((volatile u8 *)0x52))
#define OCR0	(*((volatile u8 *)0x5C))
#define TIMSK	(*((volatile u8 *)0x59))
#define TIFR	(*((volatile u8 *)0x58))


//typedef enum
//{
//	NORMAL=0,
//	PHASE_CORRECT,
//	CTC,
//	PWM
//}TIMER_MODES;

#define NORMAL 0
#define PHASE_CORRECT 1
#define	CTC 2
#define	PWM 3



#endif /* INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_ */
