/* 
 * File:   ecu_rtc.c
 * Author: Mohamed olwi
 *
 * Created: 10/2/2025 7:49:00 AM
 */
#include "ecu_rtc.h"
static Std_ReturnType inline rtc_set_day_time(uint8 *const time);
static Std_ReturnType inline rtc_set_date(uint8 *const date);
static Std_ReturnType inline rtc_read_day_time(uint8 *const buffer);
static Std_ReturnType inline rtc_read_date(uint8 *const date);

/**
 * @brief Initialize the RTC DS1307
 */
void rtc_init(void)
{
	i2c_init(I2C_STANDARD_MODE_100KHZ);
}
/**
 * @brief: Write time to RTC using I2C
 * @param time The time to write to the RTC
 * @param time_len The length of time array (must be 6)
 * @note time array must be of length 6 (seconds, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_set_time(uint8 *const time, const uint8 time_len)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == time || 6 != time_len)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Set time */
        ret_val |= rtc_set_day_time(time);
        ret_val |= rtc_set_date(time);
    }
    return (ret_val);
}
/**
 * @brief: Set the RTC date (Days, months, years)
 * @param date The date to set
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType inline rtc_set_date(uint8 *const date)
{
    Std_ReturnType ret_val = E_OK;
    uint8 current_date_idx = RTC_DAYS_IDX;
    uint8 current_reg_idx = RTC_DAYS_REG;

    for (; current_date_idx <= RTC_YEARS_IDX; current_date_idx++)
    {
        ret_val = i2c_master_write_buffer(RTC_ADDR, current_reg_idx, date[current_date_idx]);
        _delay_us(1000);
        if (E_NOT_OK == ret_val)
        {
            break;
        }
        current_reg_idx++;
    }
    return (ret_val);
}
/**
 * @brief: Set the RTC day time (Seconds, minutes, hours)
 * @param time The time to set
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType inline rtc_set_day_time(uint8 *const time)
{
    Std_ReturnType ret_val = E_OK;
    uint8 current_reg_idx = RTC_SECONDS_REG;

    time[RTC_SECONDS_IDX] = time[RTC_SECONDS_IDX] & 0x7F;  // Ensure CH bit (bit 7) is cleared
    for (; current_reg_idx < RTC_DAYS_IDX; current_reg_idx++)
    {
        ret_val = i2c_master_write_buffer(RTC_ADDR, current_reg_idx, time[current_reg_idx]);
        _delay_us(1000);
        if (E_NOT_OK == ret_val)
        {
            break;
        }
    }
    return (ret_val);
}
/**
 * @brief: Read time from RTC using I2C
 * @param buffer The buffer to store the readen time
 * @param buffer_len The length of buffer array (must be 6)
 * @note time array must be of length 6 (seconds, minutes, seconds, days, months, years)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_read_time(uint8 *const buffer, const uint8 buffer_len)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == buffer || 6 != buffer_len)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Set time */
        ret_val |= rtc_read_day_time(buffer);
        ret_val |= rtc_read_date(buffer);
    }
    return (ret_val);
}
/**
 * @brief: Read the RTC date (Days, months, years)
 * @param buffer The buffer to store the readen date
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType inline rtc_read_date(uint8 *const buffer)
{
    Std_ReturnType ret_val = E_OK;
    uint8 current_date_idx = RTC_DAYS_IDX;
    uint8 current_reg_idx = RTC_DAYS_REG;

    for (; current_date_idx <= RTC_YEARS_IDX; current_date_idx++)
    {
        ret_val = i2c_master_read_data(RTC_ADDR, current_reg_idx, &buffer[current_date_idx]);
        _delay_us(1000);
        if (E_NOT_OK == ret_val)
        {
            break;
        }
        current_reg_idx++;
    }
    return (ret_val);
}
/**
 * @brief: Read the RTC day time (Seconds, minutes, hours)
 * @param buffer The buffer to store the readen time
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType inline rtc_read_day_time(uint8 *const buffer)
{
    Std_ReturnType ret_val = E_OK;
    uint8 current_reg_idx = RTC_SECONDS_REG;

    for (; current_reg_idx < RTC_DAYS_IDX; current_reg_idx++)
    {
        ret_val = i2c_master_read_data(RTC_ADDR, current_reg_idx, &buffer[current_reg_idx]);
        _delay_us(1000);
        if (E_NOT_OK == ret_val)
        {
            break;
        }
    }
    return (ret_val);
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