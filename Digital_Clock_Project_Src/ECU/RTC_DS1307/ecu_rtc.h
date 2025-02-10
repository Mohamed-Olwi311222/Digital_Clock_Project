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
/*----------------------------Macros Declarations-----------------------------*/
#define RTC_ADDR											 (0x68) /* RTC Addr*/
#define RTC_SECONDS_REG										 (0x00) /* RTC Seconds reg addr */
#define RTC_MINUTES_REG										 (0x01) /* RTC mintues reg add */
#define RTC_HOURS_REG										 (0x02) /* RTC hours reg add */
#define RTC_DAYS_REG										 (0x04) /* RTC days reg add */
#define RTC_MONTHS_REG										 (0x05) /* RTC months reg add */
#define RTC_YEARS_REG										 (0x06) /* RTC years reg add */
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Initialize the RTC DS1307
 */
void rtc_init(void);
/**
 * @brief: initialize the I2C Comms with the RTC and read the RTC
 * @param hours hours to set
 * @param minutes minutes to set
 * @param seconds seconds to set
 * @param days days to set
 * @param months months to set
 * @param years years to set
 */
void rtc_set_time(uint8 hours, uint8 minutes, uint8 seconds, uint8 days, uint8 months, uint8 years);
/**
 * @brief: Read the time and store them in addresses given
 * @param hours hours address to store into the read value
 * @param minutes minutes address to store into the read value
 * @param seconds seconds address to store into the read value
 * @param days days address to store into the read value
 * @param months months address to store into the read value
 * @param years years address to store into the read value
 */
void rtc_read_time(uint8 *hours, uint8 *minutes, uint8 *seconds, uint8 *days, uint8 *months, uint8 *years);

#endif	/* ecu_rtc.h */