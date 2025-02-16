/* 
 * File:   ecu_rtc.h
 * Author: Mohamed olwi
 *
 * Created: 10/2/2025 7:49:00 AM
 */
#ifndef RTC_H
#define	RTC_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
#include "../../MCAL/I2C/mcal_i2c.h"
#include "../../MCAL/EEPROM/mcal_eeprom.h"
/*----------------------------Macros Declarations-----------------------------*/
#define RTC_ADDR											 (0x68) /* RTC addr*/
#define RTC_SECONDS_REG										 (0x00) /* RTC Seconds reg addr */
#define RTC_MINUTES_REG										 (0x01) /* RTC mintues reg addr */
#define RTC_HOURS_REG										 (0x02) /* RTC hours reg addr */
#define RTC_DAYS_REG										 (0x04) /* RTC days reg addr */
#define RTC_MONTHS_REG										 (0x05) /* RTC months reg addr */
#define RTC_YEARS_REG										 (0x06) /* RTC years reg addr */
#define RTC_SECONDS_IDX										 (0x00) /* RTC Seconds reg index */
#define RTC_MINUTES_IDX										 (0x01) /* RTC mintues reg index */
#define RTC_HOURS_IDX										 (0x02) /* RTC hours reg index */
#define RTC_DAYS_IDX										 (0x03) /* RTC days reg index */
#define RTC_MONTHS_IDX										 (0x04) /* RTC months reg index */
#define RTC_YEARS_IDX										 (0x05) /* RTC years reg index */
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Initialize the RTC DS1307
 */
void rtc_init(void);
/**
 * @brief: Write time to RTC using I2C
 * @param time The time to write to the RTC
 * @param time_len The length of time array (must be 6)
 * @note time array must be of length 6 (hours, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_set_time(uint8 *const time, const uint8 time_len);
/**
 * @brief: Read time from RTC using I2C
 * @param buffer The buffer to store the readen time
 * @param buffer_len The length of buffer array (must be 6)
 * @note time array must be of length 6 (seconds, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_read_time(uint8 *const buffer, const uint8 buffer_len);
/**
 * @brief: Write the time in EEPROM
 * @param start_addr The starting address of the EEPROM
 * @param time The time to store
 * @param time_len The length of time array (must be 6)
 * @note time array must be of length 6 (hours, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_write_time_eeprom(const uint16 start_addr ,const uint8 *const time, const uint8 time_len);

/**
 * @brief: Read the time from the EEPROM
 * @param start_addr The starting address of the EEPROM
 * @param buffer The buffer to store the readen value
 * @param buffer_len The length of buffer array (must be 6)
 * @note buffer array must be of length 6 (hours, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_read_time_eeprom(const uint16 start_addr , uint8 *const buffer, const uint8 buffer_len);

#endif	/* ecu_rtc.h */