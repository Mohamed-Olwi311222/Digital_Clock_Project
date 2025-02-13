/* 
 * File:   ecu_keypad.c
 * Author: Mohamed olwi
 *
 * Created: 13/2/2025 7:25:00 AM
 */
#include "ecu_keypad.h"
#include "../../MCAL/USART/mcal_usart.h"
usart_t usart_obj = {
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
static uint16 keypad_dig_value[KEYPAD_LEN] = {931, 913, 895, 878,
                                              853, 838, 823, 809,
                                              788, 775, 762, 750,
                                              731, 720, 709, 698};
static uint8 keypad_keys[KEYPAD_LEN] = {'1', '2', '3', 'A',
                                        '4', '5', '6', 'B', 
                                        '7', '8', '9', 'C',
                                        '*', '0', '#', 'D'};
/**
 * @brief: Initialize the keypad pin
 * @param adc_channel the channel that the pin is connected to
 */
void inline keypad_init(ADC_MUX_t adc_channel)
{
    adc_init(ADC_REF_AVCC);
    adc_enable_channel(adc_channel);
    adc_pin_select(adc_channel);
}
/**
 * @brief: Read the value of the button pressed and store it in the address given
 * @param addr the address to store the readen value
 * @note Press the key once, the value is not known if keys pressed simultaneously or more than one key is pressed
 * @note Doesnt manage key bouncing
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType keypad_read(uint8 *const addr)
{
    Std_ReturnType ret_val = E_NOT_OK;
    uint16 adc_res = ZERO_INIT;
    uint8 i = ZERO_INIT;

    if (NULL != addr)
    {
        while (1)
        {
            adc_convert(&adc_res);
            /* Restart scanning until a key is found*/
            if (i == KEYPAD_LEN)
            {
                i = 0;
            }
            /* If the difference is close enough, then a key is found */
            if (abs(adc_res - keypad_dig_value[i]) < 5)
            {
                *addr = keypad_keys[i];
                break;
            }
            i++;
        }
        ret_val = E_OK;
    }
    return (ret_val);
}