/* 
 * File:   ecu_keypad.c
 * Author: Mohamed olwi
 *
 * Created: 13/2/2025 7:25:00 AM
 */
#include "ecu_keypad.h"
#include "../../MCAL/USART/mcal_usart.h"

static uint16 keypad_dig_value[KEYPAD_LEN] = {931, 913, 895, 878,
                                              853, 838, 823, 809,
                                              788, 775, 762, 750,
                                              731, 720, 709, 698};
static uint8 keypad_keys[KEYPAD_LEN] = {1, 2, 3, 0x0A,
                                        4, 5, 6, 0x0B, 
                                        7, 8, 9, 0x0C,
                                        0xDD, 0x00, 0xFF, 0x0D};
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
    uint16 timeout = 1500;

    if (NULL != addr)
    {
        while (0 != timeout)
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
            timeout--;
        }
        ret_val = E_OK;
    }
    return (ret_val);
}