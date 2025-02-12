/* 
 * File:   std_types.h
 * Author: Mohamed olwi
 *
 * Created: 2/2/2025 8:15:36 AM
 */
#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/*----------------------------Macros Declarations-----------------------------*/
#define F_CPU		                                         16000000UL		    /* MCU Clock */
#define ZERO_INIT		                                     0x00		        /* Initial value of a variable */
/*----------------------------Header Files------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
/*----------------------------DataTypes---------------------------------------*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef char sint8;
typedef short sint16;
typedef long sint32;
typedef uint8 Std_ReturnType;
/*----------------------------Macros Declarations-----------------------------*/
#define STD_HIGH        0x01    /* Physical state 5V or 3.3V */
#define STD_LOW         0x00    /* Physical state 0V */


#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01    /* Logical state active */
#define STD_IDLE        0x01    /* Logical state idle */

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK            (Std_ReturnType)0x00u
#define E_NOT_OK        (Std_ReturnType)0x01u
#endif
#define BIT_MASK                     (uint8)1
/*--------------------------Macro Functions-----------------------------------*/
/**
 * @brief set, clear, toggle, read a bit in a register
 */
#define CLEAR_BIT(_REG, BIT_POS)     (_REG &= ~(BIT_MASK << BIT_POS))
#define SET_BIT(_REG, BIT_POS)       (_REG |= (BIT_MASK << BIT_POS))
#define TOGGLE_BIT(_REG, BIT_POS)    (_REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(_REG, BIT_POS)      ((_REG & (BIT_MASK << BIT_POS)) >> BIT_POS)
#endif	/* MCAL_STD_TYPES_H */