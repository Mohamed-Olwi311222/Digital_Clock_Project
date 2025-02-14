/* 
 * File:   ecu_erm_motor.h
 * Author: Mohamed olwi
 *
 * Created: 14/2/2025 11:05:00 PM
 */
#ifndef ERM_MOTOR_H
#define	ERM_MOTOR_H
/*----------------------------Header Files------------------------------------*/
#include "../../MCAL/TIMER0/mcal_timer0.h"
#include "../../std_types.h"
/*----------------------------Macros Declarations-----------------------------*/
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the erm motor with the needed duty cycle, clock and pwm
 * @param timer0_clk the source for the timer0 clock for the function of PWM
 * @param duty_cycle the pwm duty_cylce (power of the vibration)
 * @param pin the pin to output the pwm  (OC0A pin or OC0B pin)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline erm_motor_init(timer0_clk_select_t pwm_clk, uint8 pin, uint8 duty_cycle);
/**
 * @brief: Update the power of the erm motor vibration
 * @param duty_cycle the pwm duty_cylce (power of the vibration)
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline erm_motor_update_power(uint8 duty_cycle);
#endif	/* ecu_keypad.h */