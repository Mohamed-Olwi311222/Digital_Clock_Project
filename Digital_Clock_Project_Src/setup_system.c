#include "main.h"
#include "setup_system.h"
static inline void default_screen(void);
static Std_ReturnType rtc_user_modify(void);
static inline Std_ReturnType check_input_validality(uint8 key);
static uint8 take_input(uint8 *current_input);
static Std_ReturnType handle_time_input(void);
static Std_ReturnType handle_date_input(void);
static Std_ReturnType check_date_time_validality(uint8 time_or_date);

/**
 * @brief Get the setup mode for the time depending on the user input
 * @return E_OK if success otherwise E_NOT_OK
 */
inline Std_ReturnType handle_setup_mode(void)
{
    Std_ReturnType ret_val = E_OK;
    uint8 key = 0;

    ret_val |= rtc_read_time_eeprom(RTC_EEPROM_ADDR, rtc_time, RTC_BUFFER_LEN);
    while (1)
    {
        default_screen();
        keypad_read(&key);
        if (0x01 == key)
        {
            rtc_user_modify();
            rtc_write_time_eeprom(RTC_EEPROM_ADDR, rtc_time, RTC_BUFFER_LEN);
            break;
        }
        else if (0x02 == key)
        {
            break;
        }
    } 
    lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    _delay_ms(250);
    /* Initialize the starting time */
    ret_val |= rtc_init_time();
    return (ret_val);
}

/**
 * @brief Output the default menu screen when the system starts up
 */
static inline void default_screen(void)
{
    lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    _delay_ms(250);
    print_time_date_identifiers();
    print_time_on_lcd(rtc_time);
    print_date_on_lcd(rtc_time);
    _delay_ms(3000);
    lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    _delay_ms(250);
    lcd_4bit_send_string_pos(&lcd_1, 1, 0, (uint8 *)"1=> Modify");
    lcd_4bit_send_string_pos(&lcd_1, 2, 0, (uint8 *)"2=> Leave as it is");
}
/**
 * @brief Get the user time and date
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType rtc_user_modify(void)
{
    Std_ReturnType ret_val = E_OK;
    uint8 i = 0;
    uint8 rtc_str[BYTE_STR_SIZE];
    while (1) 
    {
        ret_val = handle_time_input();
        if (E_OK == ret_val)
        {
            break;
        }
    }
    while (1) 
    {
        ret_val = handle_date_input();
        if (E_OK == ret_val)
        {
            break;
        }
    }

    return (ret_val);
}
/**
 * @brief A helper function to handle time input
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType handle_time_input(void)
{
        uint8 key = 0;
        Std_ReturnType ret_val = E_OK;

        lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        _delay_ms(20);
        lcd_4bit_send_string_pos(&lcd_1, 0, 0, "Set Time:");
        lcd_4bit_send_string_pos(&lcd_1, 1, 0, "HH:__ MM:__ SS:__");
        _delay_ms(3000);
        lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        _delay_ms(20);

        // Input Hours
        key = take_input("Input H1: ");
        rtc_time[RTC_HOURS_IDX] = key * 10;
        key = take_input("Input H2: ");
        rtc_time[RTC_HOURS_IDX] += key;
        rtc_time[RTC_HOURS_IDX] = decToBcd(rtc_time[RTC_HOURS_IDX]);
    
        // Input Minutes
        key = take_input("Input M1: ");
        rtc_time[RTC_MINUTES_IDX] = key * 10;
        key = take_input("Input M2: ");
        rtc_time[RTC_MINUTES_IDX] += key;
        rtc_time[RTC_MINUTES_IDX] = decToBcd(rtc_time[RTC_MINUTES_IDX]);

        // Input Seconds
        key = take_input("Input S1: ");
        rtc_time[RTC_SECONDS_IDX] = key * 10;
        key = take_input("Input S2: ");
        rtc_time[RTC_SECONDS_IDX] += key;
        rtc_time[RTC_SECONDS_IDX] = decToBcd(rtc_time[RTC_SECONDS_IDX]);


        ret_val = check_date_time_validality(CHECK_TIME);
        return (ret_val);
}
/**
 * @brief A helper function to handle date input
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType handle_date_input(void)
{
        uint8 key = 0;
        Std_ReturnType ret_val = E_OK;

        lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        _delay_ms(20);
        lcd_4bit_send_string_pos(&lcd_1, 0, 0, "Set Date:");
        lcd_4bit_send_string_pos(&lcd_1, 1, 0, "DD/MM/YY");
        _delay_ms(3000);
        lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        _delay_ms(20);

        // Input Days
        key = take_input("Input D1: ");
        rtc_time[RTC_DAYS_IDX] = key * 10;
        key = take_input("Input D2: ");
        rtc_time[RTC_DAYS_IDX] += key;
        rtc_time[RTC_DAYS_IDX] = decToBcd(rtc_time[RTC_DAYS_IDX]);
    
        // Input Months
        key = take_input("Input M1: ");
        rtc_time[RTC_MONTHS_IDX] = key * 10;
        key = take_input("Input M2: ");
        rtc_time[RTC_MONTHS_IDX] += key;
        rtc_time[RTC_MONTHS_IDX] = decToBcd(rtc_time[RTC_MONTHS_IDX]);
    
        // Input Years
        key = take_input("Input Y1: ");
        rtc_time[RTC_YEARS_IDX] = key * 10;
        key = take_input("Input Y2: ");
        rtc_time[RTC_YEARS_IDX] += key;
        rtc_time[RTC_YEARS_IDX] = decToBcd(rtc_time[RTC_YEARS_IDX]);
        
        ret_val = check_date_time_validality(CHECK_DATE);
        _delay_ms(50);

        return (ret_val);
}
/**
 * @brief A helper function to check if the inputed time/date is correct
 * @param time_or_date the identifier to make function check which one
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType check_date_time_validality(uint8 time_or_date)
{
    Std_ReturnType ret_val = E_OK;
    uint8 key = 0;
    void (*print_time_date_function)(const uint8 *const);

    if (time_or_date == CHECK_TIME)
    {
        print_time_date_function = print_time_on_lcd;
    }
    else
    {
        print_time_date_function = print_date_on_lcd;
    }
    lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    _delay_ms(50);
    while (1)
    {
        print_time_date_function(rtc_time);
        key = take_input("Is this Correct? ");
        if (key == INPUTED_YES)
        {
            ret_val = E_OK;
            break;
        }
        else
        {
            ret_val = E_NOT_OK;
            break;
        }
    }
    return (ret_val);
}
/**
 * @brief A helper function to handle input of the user
 * @param current_input The string to print to tell the user to input it
 * @return the entered number on the keypad
 */
static uint8 take_input(uint8 *current_input)
{
    uint8 key = 0;
    lcd_4bit_send_string_pos(&lcd_1, 1, 0, current_input);
    while (1)
    {
        keypad_read(&key);
        if (E_NOT_OK == check_input_validality(key))
        {
            lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
            _delay_ms(20);
            lcd_4bit_send_string_pos(&lcd_1, 1, 0, current_input);
        }
        else
        {
            break;
        }
    }
    return (key);
}
/**
 * @brief check input validality of the user
 * @param key The input given by the user
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType check_input_validality(uint8 key)
{
    uint8 i = 0x00;
    Std_ReturnType ret_val = E_OK;
    uint8 str[BYTE_STR_SIZE];

    for (i = 0x0A; i < 0x0F; i++)
    {
        if (i == key)
        {
            ret_val = E_NOT_OK;
            break;
        }
    }
    if ((E_OK == ret_val) && (0xDD == key || 0xFF == key))
    {
        ret_val = E_NOT_OK;
    }
    if (E_OK == ret_val)
    {
        _delay_ms(200);
        lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        _delay_ms(10);
        lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Is this ur input?");
        convert_uint8_to_string(key, str);
        lcd_4bit_send_string_pos(&lcd_1, 2, 5, str);
        lcd_4bit_send_string_pos(&lcd_1, 3, 1, "1 ==> YES");
        lcd_4bit_send_string_pos(&lcd_1, 4, 1, "2 ==> NO");
        while (1)
        {
            keypad_read(&key);
            if (key == INPUTED_YES || key == INPUTED_NO)
            {
                break;
            }
        }
        _delay_ms(200);
        if (INPUTED_NO == key)
        {
            ret_val = E_NOT_OK;
        }
    }
    lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    _delay_ms(10);
    return (ret_val);
}