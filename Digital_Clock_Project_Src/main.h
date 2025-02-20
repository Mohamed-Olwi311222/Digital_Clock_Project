/* 
 * File:   main.h
 * Author: Mohamed olwi
 *
 * Created: 2/2/2025 8:15:36 AM
 */
#ifndef MAIN_H
#define	MAIN_H
/*----------------------------Header Files------------------------------------*/
#include "std_types.h"
#include "ECU/RTC_DS1307/ecu_rtc.h"
#include "ECU/Char_LCD/ecu_char_lcd.h"
#include "ECU/ERM_Motor/ecu_erm_motor.h"
#include "ECU/Keypad/ecu_keypad.h"
/*----------------------------Macros Declarations-----------------------------*/
#define RTC_BUFFER_LEN                                       0x06
#define RTC_EEPROM_ADDR                                      0x150
#define RTC_FIRST_BOOT_TRUE                                  0x01
#define RTC_FIRST_BOOT_FALSE                                 0x00
#define EEPROM_DEFAULT_ADDR_VAL                              0xFF
#define RTC_DAY_HOURS_END                                    0x00
/*----------------------------Data Types--------------------------------------*/
#endif	/* APPLICATION_H */