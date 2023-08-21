/*
 * GI_program.c
 *
 *  Created on: Dec 23, 2022
 *      Author: abdelrahmanhossam
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/GI/GI_Interface.h"
#include "../include/MCAL/GI/GI_Private.h"
#include "../include/MCAL/GI/GI_Cfg.h"

void MGI_voidEnable()
{
	SET_BIT(SREG,INTERRUPT_ENABLE_BIT);
}
void MGI_voidDisable()
{
	CLR_BIT(SREG,INTERRUPT_ENABLE_BIT);
}
