/* 
 * File:   mcal_gpio.h
 * Author: Mohamed olwi
 *
 * Created: 2/2/2025 8:15:36 AM
 */
#ifndef MCAL_GPIO__H
#define MCAL_GPIO__H

/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*--------------------------DataTypes-----------------------------------------*/

/**
 * @brief DDRB register bits
 */
typedef union
{
    struct
    {
        uint8 DDRB_0 : 1;
        uint8 DDRB_1 : 1;
        uint8 DDRB_2 : 1;
        uint8 DDRB_3 : 1;
        uint8 DDRB_4 : 1;
        uint8 DDRB_5 : 1;
        uint8 DDRB_6 : 1;
        uint8 DDRB_7 : 1;
    };
    uint8 DDRB_register;
}DDRB_BITS_t;
#define DDRB_bits (*((volatile DDRB_BITS_t *)0x24)) /* DDRB regiter bits */

/**
 * @brief PORTB register bits
 */
typedef union
{
    struct
    {
        uint8 PORTB_0 : 1;
        uint8 PORTB_1 : 1;
        uint8 PORTB_2 : 1;
        uint8 PORTB_3 : 1;
        uint8 PORTB_4 : 1;
        uint8 PORTB_5 : 1;
        uint8 PORTB_6 : 1;
        uint8 PORTB_7 : 1;
    };
    uint8 PORTB_register;
}PORTB_BITS_t;
#define PORTB_bits (*((volatile PORTB_BITS_t *)0x25)) /* PORTB regiter bits */
/**
 * @brief PINB register bits
 */
typedef union
{
    struct
    {
        uint8 PINB_0 : 1;
        uint8 PINB_1 : 1;
        uint8 PINB_2 : 1;
        uint8 PINB_3 : 1;
        uint8 PINB_4 : 1;
        uint8 PINB_5 : 1;
        uint8 PINB_6 : 1;
        uint8 PINB_7 : 1;
    };
    uint8 PINB_register;
}PINB_BITS_t;
#define PINB_bits (*((volatile PINB_BITS_t *)0x23)) /* PINB regiter bits */

/**
 * @brief DDRC register bits
 */
typedef union
{
    struct
    {
        uint8 DDRC_0 : 1;
        uint8 DDRC_1 : 1;
        uint8 DDRC_2 : 1;
        uint8 DDRC_3 : 1;
        uint8 DDRC_4 : 1;
        uint8 DDRC_5 : 1;
        uint8 DDRC_6 : 1;
        uint8 DDRC_RESERVED_BIT_7 : 1;
    };
    uint8 DDRC_register;
}DDRC_BITS_t;
#define DDRC_bits (*((volatile DDRC_BITS_t *)0x27)) /* DDRC regiter bits */

/**
 * @brief PORTC register bits
 */
typedef union
{
    struct
    {
        uint8 PORTC_0 : 1;
        uint8 PORTC_1 : 1;
        uint8 PORTC_2 : 1;
        uint8 PORTC_3 : 1;
        uint8 PORTC_4 : 1;
        uint8 PORTC_5 : 1;
        uint8 PORTC_6 : 1;
        uint8 PORTC_RESERVED_BIT_7 : 1;
    };
    uint8 PORTC_register;
}PORTC_BITS_t;
#define PORTC_bits (*((volatile PORTC_BITS_t *)0x28)) /* PORTC regiter bits */

/**
 * @brief PINC register bits
 */
typedef union
{
    struct
    {
        uint8 PINC_0 : 1;
        uint8 PINC_1 : 1;
        uint8 PINC_2 : 1;
        uint8 PINC_3 : 1;
        uint8 PINC_4 : 1;
        uint8 PINC_5 : 1;
        uint8 PINC_6 : 1;
        uint8 PINC_RESERVED_BIT_7 : 1;
    };
    uint8 PINC_register;
}PINC_BITS_t;
#define PINC_bits (*((volatile PINC_BITS_t *)0x26)) /* PINC regiter bits */

/**
 * @brief DDRD register bits
 */
typedef union
{
    struct
    {
        uint8 DDRD_0 : 1;
        uint8 DDRD_1 : 1;
        uint8 DDRD_2 : 1;
        uint8 DDRD_3 : 1;
        uint8 DDRD_4 : 1;
        uint8 DDRD_5 : 1;
        uint8 DDRD_6 : 1;
        uint8 DDRD_7 : 1;
    };
    uint8 DDRD_register;
}DDRD_BITS_t;
#define DDRD_bits (*((volatile DDRD_BITS_t *)0x2A)) /* DDRD regiter bits */

/**
 * @brief PORTD register bits
 */
typedef union
{
    struct
    {
        uint8 PORTD_0 : 1;
        uint8 PORTD_1 : 1;
        uint8 PORTD_2 : 1;
        uint8 PORTD_3 : 1;
        uint8 PORTD_4 : 1;
        uint8 PORTD_5 : 1;
        uint8 PORTD_6 : 1;
        uint8 PORTD_7 : 1;
    };
    uint8 PORTD_register;
}PORTD_BITS_t;
#define PORTD_bits (*((volatile PORTD_BITS_t *)0x2B)) /* PORTD regiter bits */

/**
 * @brief PIND register bits
 */
typedef union
{
    struct
    {
        uint8 PIND_0 : 1;
        uint8 PIND_1 : 1;
        uint8 PIND_2 : 1;
        uint8 PIND_3 : 1;
        uint8 PIND_4 : 1;
        uint8 PIND_5 : 1;
        uint8 PIND_6 : 1;
        uint8 PIND_7 : 1;
    };
    uint8 PIND_register;
}PIND_BITS_t;
#define PIND_bits (*((volatile PIND_BITS_t *)0x29)) /* PIND regiter bits */

/**
 * @brief logic levels 1(HIGH) and 0(LOW)
 */
typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

/**
 * @brief direction of the pin input or output
 */
typedef enum
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

/**
 * @brief pin index
 */
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

/**
 * @brief port index
 */
typedef enum
{
    PORTB_INDEX = 0,
    PORTC_INDEX,
    PORTD_INDEX,
}port_index_t;

/**
 * @brief pin configuration
 * @port: the port index @ref port_index_t
 * @pin: the pin index @ref pin_index_t
 * @direction: the direction of the pin @ref direction_t
 */
typedef struct
{
    uint8 port : 2;             /*@ref use port_index_t */
    uint8 pin  : 3;             /*@ref use pin_index_t  */
    uint8 direction : 1;        /*@ref use direction_t  */
    uint8 RESERVED : 2;         /* reserved bits */
}pin_config_t;

/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief initialize the direction of a given pin
 * @param _pin_config_t the configration given (i.e led, motor, etc..)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config_t);
/**
 * @brief write logic to a given pin in a port
 * @param _pin_config_t the configration given (i.e led, motor, etc..)
 * @param logic the logic to write @ref logic_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic);
/**
 * @brief read the logic of a pin
 * @param _pin_config_t the pin configration given 
 * @param logic the address to store the read logic
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *const _pin_config_t, uint8 *const logic);

#endif /* mcal_gpio.h */