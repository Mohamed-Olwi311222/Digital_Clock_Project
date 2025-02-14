/* 
 * File:   mcal_timer0.c
 * Author: Mohamed olwi
 *
 * Created: 14/2/2025 8:15:00 AM
 */
#include "mcal_timer0.h"
static uint8 operating_pin = TIMER0_OC0A_PIN;

/**
 * @brief: Initialize the PWM with the needed duty cycle and freq on OC0A pin or OC0B pin
 * @param timer0_clk the source for the timer0 clock
 * @param duty_cycle the pwm duty_cylce
 * @param pin the pin to output the pwm
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType pwm_init(timer0_clk_select_t timer0_clk, uint8 duty_cycle, uint8 pin)
{
    Std_ReturnType ret_val = E_OK;

    /* Configure the pin to be output */
    if (TIMER0_OC0A_PIN == pin)
    {
        /* OC0A pin*/
        operating_pin = TIMER0_OC0A_PIN;
        DDRD |= (1 << DDD6);
        /* Set the duty cycle */
        OCR0A = duty_cycle;
    }
    else if (TIMER0_OC0B_PIN == pin)
    {
        /* OC0B pin*/
        operating_pin = TIMER0_OC0B_PIN;
        DDRD |= (1 << DDD5);
        /* Set the duty cycle */
        OCR0B = duty_cycle;
    }
    else
    {
        ret_val = E_NOT_OK;
    }

    if (E_OK == ret_val)
    {
        /* Selet PWM phase correct mode */
        TIMER0_PWM_PHASE_CORRECT_MODE();
        /* Non inverting mode */
        TIMER0_PWM_NON_INVERTING_CONFIG();
        /* Set the prescaler */
        TIMER0_CONFIGURE_CLK_SRC_CONFIG(timer0_clk);
    }
    return (ret_val);
}
/**
 * @brief: Update the TIMER0 pwm duty cycle
 * @param duty_cycle the pwm duty_cylce
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline pwm_update_duty_cycle(uint8 duty_cycle)
{
    Std_ReturnType ret_val = E_OK;

    if (TIMER0_OC0A_PIN == operating_pin)
    {
        /* Set the duty cycle */
        OCR0A = duty_cycle;
    }
    else if (TIMER0_OC0B_PIN == operating_pin)
    {
        /* Set the duty cycle */
        OCR0B = duty_cycle;
    }
    else
    {
        ret_val = E_NOT_OK;
    }
    return (ret_val);
}