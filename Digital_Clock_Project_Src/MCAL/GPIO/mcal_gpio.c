/* 
 * File:   mcal_gpio.c
 * Author: Mohamed olwi
 *
 * Created: 2/2/2025 8:15:36 AM
 */
#include "mcal_gpio.h"
/*----------------------------Global Variables--------------------------------*/
static volatile uint8 *const port_registers[] = {&PORTB, &PORTC, &PORTD}; /* array of pointers to the port registers */
static volatile uint8 *const ddr_registers[] = {&DDRB, &DDRC, &DDRD};     /* array of pointers to the ddr registers */
/*----------------------------Function Definitions-----------------------------*/
/**
 * @brief initialize the direction of a given pin
 * @param _pin_config_t the configration given (i.e led, motor, etc..)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config_t)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == _pin_config_t)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        switch (_pin_config_t->direction)
        {
            /* set the pin as input */
            case GPIO_DIRECTION_INPUT:
                CLEAR_BIT(*ddr_registers[_pin_config_t->port], _pin_config_t->pin);
                break;
            
            /* set the pin as output */
            case GPIO_DIRECTION_OUTPUT:
                SET_BIT(*ddr_registers[_pin_config_t->port], _pin_config_t->pin);
                break;

            default:
                ret_val = E_NOT_OK;
                break;
        }
    }
    return (ret_val);
}
/**
 * @brief write logic to a given pin in a port
 * @param _pin_config_t the configration given (i.e led, motor, etc..)
 * @param logic the logic to write @ref logic_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == _pin_config_t)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
            /* write logic high to the pin */
            case GPIO_HIGH:
                SET_BIT(*port_registers[_pin_config_t->port], _pin_config_t->pin);
                break;
            
            /* write logic low to the pin */
            case GPIO_LOW:
                CLEAR_BIT(*port_registers[_pin_config_t->port], _pin_config_t->pin);
                break;

            default:
                ret_val = E_NOT_OK;
                break;
        }
    }
    return (ret_val);
}
/**
 * @brief read the logic of a pin
 * @param _pin_config_t the pin configration given 
 * @param logic the address to store the read logic
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *const _pin_config_t, uint8 *const logic)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == _pin_config_t || NULL == logic)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config_t->port], _pin_config_t->pin);
    }
    return (ret_val);
}