/* 
 * File:   mcal_timer0.h
 * Author: Mohamed olwi
 *
 * Created: 14/2/2025 8:15:00 AM
 */
#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*----------------------------Macros Declarations-----------------------------*/
#define TIMER0_OC0A_PIN                                      0 /* OC0A timer0 pin */
#define TIMER0_OC0B_PIN                                      1 /* OC0B timer0 pin */
/*--------------------------DataTypes-----------------------------------------*/

/**
 * @brief: TCCR0A register bits
 */
typedef union
{
    struct
    {
        uint8 WGM00_bit : 1;
        uint8 WGM01_bit : 1;
        uint8 : 2;
        uint8 COM0B0_bit : 1;
        uint8 COM0B1_bit : 1;
        uint8 COM0A0_bit : 1;
        uint8 COM0A1_bit : 1;
    };
    struct
    {
        uint8 WGM0x_bits : 2;
        uint8 : 2;
        uint8 COM0Bx_bits : 2;
        uint8 COM0Ax_bits : 2;
    };
    uint8 TCCR0A_register;
} TCCR0A_BITS_t;
#define TCCR0A_bits (*((volatile TCCR0A_BITS_t*) 0x44)) /* TCCR0A regiter bits */

/**
 * @brief: TCCR0B register bits
 */
typedef union
{
    struct
    {
        uint8 CS00_bit : 1;
        uint8 CS01_bit : 1;
        uint8 CS02_bit : 1;
        uint8 WGM02_bit : 1;
        uint8 : 2;
        uint8 FOC0B_bit : 1;
        uint8 FOC0A_bit : 1;
    };
    struct
    {
        uint8 CS0x_bits : 3;
        uint8 : 5;
    };
    uint8 TCCR0B_register;
} TCCR0B_BITS_t;
#define TCCR0B_bits (*((volatile TCCR0B_BITS_t*) 0x45)) /* TCCR0B regiter bits */

/**
 * @brief: TIMSK0 register bits
 */
typedef union
{
    struct
    {
        uint8 TOIE0_bit : 1;
        uint8 OCIE0A_bit : 1;
        uint8 OCIE0B_bit : 1;
        uint8 : 5;
    };
    uint8 TIMSK0_register;
} TIMSK0_BITS_t;
#define TIMSK0_bits (*((volatile TIMSK0_BITS_t*) 0x6E)) /* TIMSK0 regiter bits */

/**
 * @brief: Wavefrom generation modes
 */
typedef enum
{
    NORMAL_MODE,
    PWM_PHASE_CORRECT_MODE,
    CTC,
    FAST_PWM,
    PWM_PHASE_CORRECT_OCCRA_TOP_MODE = 0X05,
    FAST_PWM_OCRA_TOP_MODE = 0X07
} waveform_gen_mode_t;

/**
 * @brief: Timer0 Clock sources
 */
typedef enum
{
    TIMER0_DISABLED,
    TIMER0_CLK_DIV_1,
    TIMER0_CLK_DIV_8,
    TIMER0_CLK_DIV_64,
    TIMER0_CLK_DIV_256,
    TIMER0_CLK_DIV_1024,
    TIMER0_T0_EXT_CLK_FALLING_EDGE,
    TIMER0_T0_EXT_CLK_RISING_EDGE
} timer0_clk_select_t;
/*--------------------------Macro Functions-----------------------------------*/

/**
 *  Configure the timer0 clock source
 */
#define TIMER0_CONFIGURE_CLK_SRC_CONFIG(__CLK)               (TCCR0B_bits.CS0x_bits = __CLK)

/**
 * Configure timer0 in PWM phase correct mode
 */
#define TIMER0_PWM_PHASE_CORRECT_MODE()                                                            \
                                                            do                                     \
                                                            {                                      \
                                                                TCCR0A_bits.WGM00_bit = 1;         \
                                                                TCCR0A_bits.WGM01_bit = 0;         \
                                                                TCCR0B_bits.WGM02_bit = 0;         \
                                                            } while(0)

/**
 * Configure Timer0 in non inverting mode
 */
#define TIMER0_PWM_NON_INVERTING_CONFIG()                                                          \
                                                            do                                     \
                                                            {                                      \
                                                                TCCR0A_bits.COM0A0_bit = 0;        \
                                                                TCCR0A_bits.COM0A1_bit = 1;        \
                                                                TCCR0A_bits.COM0B0_bit = 0;        \
                                                                TCCR0A_bits.COM0B1_bit = 1;        \
                                                            } while(0)

/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief: Initialize the PWM with the needed duty cycle and freq on OC0A pin or OC0B pin
 * @param timer0_clk the source for the timer0 clock
 * @param duty_cycle the pwm duty_cylce
 * @param pin the pin to output the pwm
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType pwm_init(timer0_clk_select_t timer0_clk, uint8 duty_cycle, uint8 pin);

/**
 * @brief: Update the TIMER0 pwm duty cycle
 * @param duty_cycle the pwm duty_cylce
 */
Std_ReturnType inline pwm_update_duty_cycle(uint8 duty_cycle);
#endif	/* mcal_timer0.h */