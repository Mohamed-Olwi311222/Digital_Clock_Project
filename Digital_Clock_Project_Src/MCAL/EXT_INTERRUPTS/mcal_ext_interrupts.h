/* 
 * File:   mcal_ext_interrupts.h
 * Author: Mohamed olwi
 *
 * Created: 21/2/2025 1:08:00 AM
 */
#ifndef MCAL_EXT_INTERRUPTS_H
#define	MCAL_EXT_INTERRUPTS_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*----------------------------Macros Declarations-----------------------------*/
#define EXT_INT0                                             0x00
#define EXT_INT1                                             0x01
/*----------------------------DataTypes---------------------------------------*/

/**
 * @brief EICRA register
 */
typedef union
{
    struct
    {
        uint8 ISC00_bit : 1;
        uint8 ISC01_bit : 1;
        uint8 ISC10_bit : 1;
        uint8 ISC11_bit : 1;
        uint8 : 4;
    };
    struct
    {
        uint8 ISC0x_bits : 2;
        uint8 ISC1x_bits : 2;
        uint8 : 4;
    };
    uint8 EICRA_register;
}EICRA_BITS_t;
#define EICRA_bits (*((volatile EICRA_BITS_t *)0x69)) /* EICRA regiter bits */


/**
 * @brief EIMSK register
 */
typedef union
{
    struct
    {
        uint8 INT0_bit : 1;
        uint8 INT1_bit : 1;
        uint8 : 6;
    };
    uint8 EIMSK_register;
}EIMSK_BITS_t;
#define EIMSK_bits (*((volatile EIMSK_BITS_t *)0x1D)) /* EIMSK regiter bits */

/**
 * @brief EIFR register
 */
typedef union
{
    struct
    {
        uint8 INTF0_bit : 1;
        uint8 INTF1_bit : 1;
        uint8 : 6;
    };
    uint8 EIFR_register;
}EIFR_BITS_t;
#define EIFR_bits (*((volatile EIFR_BITS_t *)0x1C)) /* EIFR regiter bits */

/**
 * The types of interrupt sense of INTx
 */
typedef enum
{
    INTERRUPT_ON_LOW_LEVEL,
    INTERRUPT_ON_CHANGE,
    INTERRUPT_ON_FALLING_EDGE,
    INTERRUPT_ON_RISING_EDGE
} EXT_INTx_SENSE_t;
/*----------------------------Macros Functions Declarations-------------------*/

/**
 * Set the external INT0 interrupt sense @ref EXT_INTx_SENSE_t
 */
#define SET_EXT_INT0_SENSE_CONFIG(__SENSE)                   (EICRA_bits.ISC0x_bits = __SENSE)
/**
 * Set the external INT1 interrupt sense @ref EXT_INTx_SENSE_t
 */
#define SET_EXT_INT1_SENSE_CONFIG(__SENSE)                   (EICRA_bits.ISC1x_bits = __SENSE)

/**
 * Enable the INT0 external interrupt
 */
#define EXT_INT0_ENABLE_CONFIG()                             (EIMSK_bits.INT0_bit = 1)
/**
 * Disable the INT0 external interrupt
 */
#define EXT_INT0_DISABLE_CONFIG()                            (EIMSK_bits.INT0_bit = 0)

/**
 * Enable the INT1 external interrupt
 */
#define EXT_INT1_ENABLE_CONFIG()                             (EIMSK_bits.INT1_bit = 1)
/**
 * Disable the INT1 external interrupt
 */
#define EXT_INT1_DISABLE_CONFIG()                            (EIMSK_bits.INT1_bit = 0)
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Initialize external interrupt INTx depending on the parameter
 * @param intx_type Which INTx interrupt to init
 * @param interrupt_sense When to trigger the external INTx interrupt
 * @param intx_isr A pointer to the ISR to set to the INTx interrupt
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline ext_intx_init(uint8 intx_type, EXT_INTx_SENSE_t interrupt_sense, void (*intx_isr)());
#endif /* mcal_ext_interrupts.h */