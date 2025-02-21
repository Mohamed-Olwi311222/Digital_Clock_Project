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
#include "MCAL/EXT_INTERRUPTS/mcal_ext_interrupts.h"
/*----------------------------Macros Declarations-----------------------------*/
#define RTC_BUFFER_LEN                                       0x06
#define RTC_EEPROM_ADDR                                      0x150
#define RTC_FIRST_BOOT_TRUE                                  0x01
#define RTC_FIRST_BOOT_FALSE                                 0x00
#define EEPROM_DEFAULT_ADDR_VAL                              0xFF
#define RTC_DAY_HOURS_END                                    0x00
/*----------------------------Data Types--------------------------------------*/
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Convert BCD to decimal
 * @param bcd The bcd value
 * @return The decimal value
 */
uint8 bcdToDec(uint8 bcd);
/**
 * @brief Print the time on the lcd
 * @param rtc_time the rtc time buffer to print its time to the LCD
 */
void print_time_on_lcd(const uint8 *const rtc_time);
/**
 * @brief Print the Date on the lcd
 * @param rtc_time the rtc time buffer to print its date to the LCD
 */
void print_date_on_lcd(const uint8 *const rtc_time);
/**
 * @brief The ISR to execute when INT0 interrupt triggers
 */
void int0_isr(void);
/**
 * @brief Initialze the ECU drivers
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ecu_init(void);
#endif	/* APPLICATION_H */