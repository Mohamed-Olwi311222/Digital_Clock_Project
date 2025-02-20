/*
 * main.c
 *
 * Created: 2/2/2025 8:15:36 AM
 *  Author: Mohamed olwi
 */ 
#include "main.h"
#include "MCAL/USART/mcal_usart.h"
usart_t usart_debug = {
    .usart_baudrate = 9600,
    .usart_parity = USART_PARITY_DISABLED,
    .usart_mode = ASYNC_USART,
    .usart_char_size = USART_8_BIT_CHAR_SIZE,
    .usart_receiver_enable = _USART_RECEIVER_DISABLE,
    .usart_receiver_clk_polarity = _USART_RECEIVE_POLARITY_FALLING_EDGE,
    .usart_transmitter_enable = _USART_TRANSMITTER_ENABLE,
    .usart_transmitter_clk_polarity = _USART_TRANSMIT_POLARITY_RISING_EDGE,
    .usart_transmiter_stop_bits_number = _USART_TRANSMITTER_STOP_BITS_1_BIT,
    .usart_transmitter_transmission_speed = _USART_TRANSMIT_NORMAL_SPEED_MODE
};

uint8 rtc_time[RTC_BUFFER_LEN] = {'\0'};
char_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTB_INDEX,
    .lcd_rs.pin = GPIO_PIN4,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.port = PORTB_INDEX,
    .lcd_en.pin = GPIO_PIN3,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].port = PORTB_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].port = PORTB_INDEX,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].port = PORTB_INDEX,
    .lcd_data[2].pin = GPIO_PIN0,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN7,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
};
uint8 bcdToDec(uint8 bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
void print_time_on_lcd(const uint8 *const rtc_time)
{
    uint8 rtc_str[BYTE_STR_SIZE];
    uint8 temp = 0;
    sint8 i = 2;
    uint8 x = 0;

    lcd_4bit_send_char_data_pos(&lcd_1, 2, 11, ':');
    lcd_4bit_send_char_data_pos(&lcd_1, 2, 14, ':');
    for (; i >= 0; i--)
    {
        temp = bcdToDec(rtc_time[i]);
        convert_uint8_to_string(temp, rtc_str);
        lcd_4bit_send_string_pos(&lcd_1, 2, 9 + x, rtc_str);
        x += 3;
    }
}
void print_date_on_lcd(const uint8 *const rtc_time)
{
    uint8 rtc_str[BYTE_STR_SIZE];
    uint8 temp = 0;
    sint8 i = 3;
    uint8 x = 0;

    
    lcd_4bit_send_char_data_pos(&lcd_1, 4, 11, '/');
    lcd_4bit_send_char_data_pos(&lcd_1, 4, 14, '/');
    for (; i < 6; i++)
    {
        temp = bcdToDec(rtc_time[i]);
        convert_uint8_to_string(temp, rtc_str);
        lcd_4bit_send_string_pos(&lcd_1, 4, 9 + x, rtc_str);
        x += 3;
    }
}
Std_ReturnType ecu_init(void)
{
    Std_ReturnType ret_val = E_OK;

    ret_val |= usart_init(&usart_debug);
    ret_val |= lcd_4bit_initialize(&lcd_1);
    rtc_init();
    keypad_init(ADC0);
    sei();
    return (ret_val);
}
Std_ReturnType rtc_init_time(void)
{
    Std_ReturnType ret_val = E_OK;
    uint8 rtc_first_boot = RTC_FIRST_BOOT_FALSE;
    uint8 i = 0;

    /* Read the time and store in the rtc_time buffer */
    ret_val |= rtc_read_time_eeprom(RTC_EEPROM_ADDR, rtc_time, RTC_BUFFER_LEN);
    /* Check if the current boot is the first boot */
    for (i = 0; i < RTC_BUFFER_LEN; i++)
    {
        if (EEPROM_DEFAULT_ADDR_VAL == rtc_time[i])
        {
            rtc_first_boot = RTC_FIRST_BOOT_TRUE;
            break;
        }
    }
    /* If it is not the first boot of the System, set the stored value in the EEPROM of the RTC time */
    if (RTC_FIRST_BOOT_FALSE == rtc_first_boot)
    {
        ret_val |= rtc_read_time_eeprom(RTC_EEPROM_ADDR, rtc_time, RTC_BUFFER_LEN);
    }
    else
    {
        /* if it is the first boot just set these predefined values */
        rtc_time[RTC_SECONDS_IDX] = 0x50;
        rtc_time[RTC_MINUTES_IDX] = 0x10;
        rtc_time[RTC_HOURS_IDX] = 0x23;
        rtc_time[RTC_DAYS_IDX] = 0x20;
        rtc_time[RTC_MONTHS_IDX] = 0x02;
        rtc_time[RTC_YEARS_IDX] = 0x25;
    }
    ret_val |= rtc_set_time(rtc_time, RTC_BUFFER_LEN);

    return (ret_val);
}
int main(void)
{
    Std_ReturnType ret_val = E_OK;
    uint8 key = 0;
    uint8 i = 0;

    /* Initialize the ecu layer modules */
    ret_val = ecu_init();
    /* Initialize the starting time */
    ret_val |= rtc_init_time();
    /* Print the date on the screen as it rarely changes */
    print_date_on_lcd(rtc_time);
    lcd_4bit_send_string_pos(&lcd_1, 1, 0,(uint8 *) "Time: ");
    lcd_4bit_send_string_pos(&lcd_1, 3, 0, (uint8 *) "Date: ");
	while(1)
    {
        // keypad_read(&key);
        _delay_ms(250);
        /* Read the time from the RTC */
        ret_val = rtc_read_time(rtc_time, RTC_BUFFER_LEN);
        /* If the Hours become 0x00, a new day starts so print the date again */
        if (RTC_DAY_HOURS_END == rtc_time[RTC_HOURS_IDX])
        {
            print_date_on_lcd(rtc_time);
        }
        /* Print the time */
        print_time_on_lcd(rtc_time);
        /* Save the written time incase of power went out */
        rtc_write_time_eeprom(RTC_EEPROM_ADDR, rtc_time, RTC_BUFFER_LEN);
        // lcd_4bit_send_char_data(&lcd_1, key);
    }
}
