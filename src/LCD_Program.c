/*
 * LCD_Program.c
 *
 *  Created on: Dec 3, 2022
 *      Author: abdelrahmanhossam
 */



// Built in Library
#include <util/delay.h>
// Library Layer
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
// MCAL
#include "../include/MCAL/DIO/DIO_Interface.h"
// HAL
#include "../include/HAL/LCD/LCD_Interface.h"
#include "../include/HAL/LCD/LCD_Private.h"
#include "../include/HAL/LCD/LCD_Cfg.h"

#define F_CPU 8000000UL


void HLCD_voidSendCommand (const u8 A_u8Command)
{
	// RS --> 0 , RW --> 0
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);

	// send command to LCD
	MDIO_voidSetPortValue(LCD_DATA_PORT, A_u8Command);

	// Set Pulse on E Pin for 2 msec
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_HIGH);
	_delay_ms (E_DELAY);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW);
}

void HLCD_voidSendData    (const u8 A_u8Data)
{
	// RS --> 0 , RW --> 0
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_HIGH);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);

	// send Data to LCD
	MDIO_voidSetPortValue(LCD_DATA_PORT, A_u8Data);

	// Set Pulse on E Pin for 2 msec
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_HIGH);
	_delay_ms (E_DELAY);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW);
}

void HLCD_voidInit (void)
{
	// Wait for more than 30ms after VDD rises to 4.5V.
	_delay_ms (INIT_VDD_DELAY);

	// Send Function Set Instruction
	HLCD_voidSendCommand(FUNCTION_SET);

	//Wait for more than 39us
	_delay_ms (1);

	// send Display ON/OFF Control instruction
	HLCD_voidSendCommand(DISPLAY_ON_OFF_CONTROL);

	//Wait for more than 39us
	_delay_ms (1);

	// send Display Clear instruction
	HLCD_voidSendCommand(DISPLAY_CLEAR);

	//Wait for more than 1.53 ms
	_delay_ms (2);

	// send Display ClearEntry Mode Set instruction
	HLCD_voidSendCommand(ENTRY_MODE_SET);
}

void HLCD_voidClearDisplay()
{
	// send Display Clear instruction
	HLCD_voidSendCommand(DISPLAY_CLEAR);

	//Wait for more than 1.53 ms
	_delay_ms (2);
}

void HLCD_voidSendString (const u8 *A_pu8String)
{
	while (*A_pu8String > 0)
	{
		HLCD_voidSendData(*A_pu8String++);
	}
}


void HLCD_voidGoToPos (const u8 A_u8RowNumber, const u8 A_u8ColNumber)
{
	switch (A_u8RowNumber)
	{
	case ROW_ONE: HLCD_voidSendCommand(LCD_ROW_1_ADDRESS + A_u8ColNumber); break;
	case ROW_TWO: HLCD_voidSendCommand(LCD_ROW_2_ADDRESS + A_u8ColNumber); break;
	}
}

void HLCD_voidDisplayNumber (u32 A_u32Number)
{
  u32 local_u32Number = 1;
  if (A_u32Number == 0)
  {
	  HLCD_voidSendData('0');
  }
  else
  {
	  while (A_u32Number != 0)
	  {
		  local_u32Number = ((local_u32Number*10)+(A_u32Number%10));
		  A_u32Number = A_u32Number / 10;
	  }
	  while (local_u32Number !=1)
	  {
		  HLCD_voidSendData((local_u32Number%10)+48);
		  local_u32Number = local_u32Number /10;
	  }
  }
}

void HLCD_voidSendSpecialPattern (const u8 *A_pu8PatternArr,const u8 A_u8PatternNum,const u8 A_u8RowNumber, const u8 A_u8ColNumber )
{
	// CGRAM Address --> 0 to 63  --> need 6 bits from bit 0 to bit 5
	u8 local_u8Counter ,local_u8CGRAMAddress = A_u8PatternNum * 8;
	SET_BIT(local_u8CGRAMAddress,6);
	// Send command to set CGRAM Address
	HLCD_voidSendCommand(local_u8CGRAMAddress);

	for (local_u8Counter=0; local_u8Counter < 8; local_u8Counter++)
	{
		// Send Byte from Pattern Array
		HLCD_voidSendData(A_pu8PatternArr[local_u8Counter]);
	}

	// Send Command to Set the DDRAM Address
	HLCD_voidGoToPos(A_u8RowNumber, A_u8ColNumber);
	// Display The required Pattern from CGRAM
	HLCD_voidSendData(A_u8PatternNum);
}





