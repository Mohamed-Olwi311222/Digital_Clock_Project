/* 
 * File:   ecu_rtc.c
 * Author: Mohamed olwi
 *
 * Created: 10/2/2025 7:49:00 AM
 */
#include "ecu_rtc.h"

/**
 * @brief Initialize the RTC DS1307
 */
void rtc_init(void)
{
	i2c_init(I2C_STANDARD_MODE_100KHZ);
}
/**
 * @brief: initialize the I2C Comms with the RTC and read the RTC
 * @param hours hours to set
 * @param minutes minutes to set
 * @param seconds seconds to set
 * @param days days to set
 * @param months months to set
 * @param years years to set
 */
void rtc_set_time(uint8 hours, uint8 minutes, uint8 seconds, uint8 days, uint8 months, uint8 years)
{
    seconds = seconds & 0x7F;  // Ensure CH bit (bit 7) is cleared

    i2c_master_write_buffer(RTC_ADDR, RTC_SECONDS_REG, seconds);
    _delay_us(1000);
    i2c_master_write_buffer(RTC_ADDR, RTC_MINUTES_REG, minutes);
    _delay_us(1000);
    i2c_master_write_buffer(RTC_ADDR, RTC_HOURS_REG, hours);
    _delay_us(1000);
    i2c_master_write_buffer(RTC_ADDR, RTC_DAYS_REG, days);
    _delay_us(1000);
    i2c_master_write_buffer(RTC_ADDR, RTC_MONTHS_REG, months);
    _delay_us(1000);
    i2c_master_write_buffer(RTC_ADDR, RTC_YEARS_REG, years);
}
/**
 * @brief: Read the time and store them in addresses given
 * @param hours hours address to store into the read value
 * @param minutes minutes address to store into the read value
 * @param seconds seconds address to store into the read value
 * @param days days address to store into the read value
 * @param months months address to store into the read value
 * @param years years address to store into the read value
 */
void rtc_read_time(uint8 *hours, uint8 *minutes, uint8 *seconds, uint8 *days, uint8 *months, uint8 *years)
{
    i2c_master_read_data(RTC_ADDR, RTC_SECONDS_REG, seconds);
    _delay_us(1000);
    i2c_master_read_data(RTC_ADDR, RTC_MINUTES_REG, minutes);
    _delay_us(1000);
    i2c_master_read_data(RTC_ADDR, RTC_HOURS_REG, hours);
    _delay_us(1000);
    i2c_master_read_data(RTC_ADDR, RTC_DAYS_REG, days);
    _delay_us(1000);
    i2c_master_read_data(RTC_ADDR, RTC_MONTHS_REG, months);
    _delay_us(1000);
    i2c_master_read_data(RTC_ADDR, RTC_YEARS_REG, years);
}