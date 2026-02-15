/*
 * GIE_program.c
 *
 *  Created on: Feb 15, 2026
 *      Author: uts
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"GIE_interface.h"
#include"GIE_private.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
