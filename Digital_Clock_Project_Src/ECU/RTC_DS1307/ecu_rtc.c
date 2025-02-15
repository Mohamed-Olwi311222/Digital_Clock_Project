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
/**
 * @brief: Write the time in EEPROM
 * @param start_addr The starting address of the EEPROM
 * @param time The time to store
 * @param time_len The length of time array (must be 6)
 * @note time array must be of length 6 (hours, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_write_time_eeprom(const uint16 start_addr ,const uint8 *const time, const uint8 time_len)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == time || 6 != time_len)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        ret_val = eeprom_write_buffer(start_addr, time, time_len);
    }
    return (ret_val);
}

/**
 * @brief: Read the time from the EEPROM
 * @param start_addr The starting address of the EEPROM
 * @param buffer The buffer to store the readen value
 * @param buffer_len The length of buffer array (must be 6)
 * @note buffer array must be of length 6 (hours, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_read_time_eeprom(const uint16 start_addr , uint8 *const buffer, const uint8 buffer_len)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == buffer || 6 != buffer_len)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        ret_val = eeprom_read_buffer(start_addr, buffer, buffer_len);
    }
    return (ret_val);
}