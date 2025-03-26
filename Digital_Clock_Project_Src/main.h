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
#include "MCAL/USART/mcal_usart.h"
/*----------------------------Macros Declarations-----------------------------*/
#define RTC_BUFFER_LEN                                       0x06   /* The maximum length of the RTC buffer */
#define RTC_EEPROM_ADDR                                      0x150  /* The EEPROM Address of the stored date and time */
#define RTC_FIRST_BOOT_TRUE                                  0x01   /* RTC first boot flag true */
#define RTC_FIRST_BOOT_FALSE                                 0x00   /* RTC first boot flag false */
#define EEPROM_DEFAULT_ADDR_VAL                              0xFF   /* EEPROM default address value */
#define RTC_DAY_HOURS_END                                    0x00   /* The end of the RTC hours and starting a new day*/
#define FIRST_BOOT_READ                                      0x00   /* The first time the system boot will read the storen date and time*/
#define FIRST_BOOT_MODIFY                                    0x01   /* The first time the system boot will make the user modify first */
#define STOP_WATCH_ON                                        0x01   /* The stop watch is currently on */
#define STOP_WATCH_OFF                                       0x00   /* The stop watch is currently off */
/*----------------------------Data Types--------------------------------------*/
extern usart_t usart_debug;
extern uint8 rtc_time[RTC_BUFFER_LEN];
extern char_lcd_4bit_t lcd_1;
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Convert BCD to decimal
 * @param bcd The bcd value
 * @return The decimal value
 */
uint8 bcdToDec(uint8 bcd);
/**
 * @brief Convert decimal to BCD
 * @param dec The decimal value (0-99)
 * @return The BCD value
 */
uint8 decToBcd(uint8 dec);
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
/**
 * @brief Initialzie the rtc time
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_init_time(void);
/**
 * @brief print "Time: " and "Date: " identifiers
 */
inline void print_time_date_identifiers(void);
/*-------------------Setup_System------------------*/
/**
 * @brief Get the setup mode for the time depending on the user input
 * @return E_OK if success otherwise E_NOT_OK
 */
inline Std_ReturnType handle_setup_mode(void);

#endif	/* APPLICATION_H */