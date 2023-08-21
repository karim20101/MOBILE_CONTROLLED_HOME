/*
 * LCD_Cfg.h
 *
 *  Created on: Dec 3, 2022
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_HAL_LCD_LCD_CFG_H_
#define INCLUDE_HAL_LCD_LCD_CFG_H_


#define LCD_DATA_PORT	    DIO_PORTD
#define LCD_CONTROL_PORT	DIO_PORTC

#define LCD_RS_PIN	PIN5
#define LCD_RW_PIN	PIN6
#define LCD_E_PIN	PIN7

// 0 --> 1 Line
// 1 --> 2 Lines
#define NO_OF_LINES	1

// 0 --> 5*7
// 1 --> 5*10
#define CHARACTER_FONT 0

// 0 --> Off
// 1 --> On
#define DISPLAY_STATUS 	1

// 0 --> Hidden
// 1 --> Displayed
#define CURSOR_DISPLAY  1

// 0 --> Fixed
// 1 --> Blink
#define CURSOR_BLINK	1


// 0 --> Decrease
// 1 --> Increase
#define I_D	1

// 0 --> Shift is off
// 1 --> Shift is on
#define SHIFT 0

#endif /* INCLUDE_HAL_LCD_LCD_CFG_H_ */
