/* 
 * File:   ecu_keypad.h
 * Author: Mohamed olwi
 *
 * Created: 13/2/2025 7:25:00 AM
 */
#ifndef KEYPAD_H
#define	KEYPAD_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
#include "../../MCAL/ADC/mcal_adc.h"
#include <stdlib.h>
/*----------------------------Macros Declarations-----------------------------*/
#define KEYPAD_LEN                                           16
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the keypad pin
 * @param adc_channel the channel that the pin is connected to
 */
void inline keypad_init(ADC_MUX_t adc_channel);
/**
 * @brief: Read the value of the button pressed and store it in the address given
 * @param addr the address to store the readen value
 * @note Press the key once, the value is not known if keys pressed simultaneously or more than one key is pressed
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType keypad_read(uint8 *const addr);
#endif	/* ecu_keypad.h */