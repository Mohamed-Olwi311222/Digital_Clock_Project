/* 
 * File:   ecu_adc.c
 * Author: Mohamed olwi
 *
 * Created: 10/2/2025 7:49:00 AM
 */
#include "mcal_adc.h"
static volatile uint8 adc_conversion_done = 0;
ISR(ADC_vect)
{
    /* Set the ADC conversion done flag */
    adc_conversion_done = 1;
    /* Clear ADC Interrupt Flag */
    ADC_CLEAR_INTERRUPT_FLAG_CONFIG();
}

/**
 *  @brief ADC Initialization
 * @param ref: the ADC reference selection
 */
void adc_init(const ADC_REF_t ref)
{
    /* Disable ADC */
    ADC_DISABLE_CONFIG();
    /* Set prescaler */
    ADC_SET_PRESCALER_CONFIG(ADC_PRESCALER_128);
    /* Set the ADC result reference voltage */
    ADC_SET_REF_CONFIG(ref);
    /* Set the result to be right justify */
    ADC_SET_RIGHT_ADJUST_RESULT_CONFIG();
    /* Enable ADC and its interrupt */
    ADC_ENABLE_INTERRUPT_CONFIG();
    /* Enable ADC */
    ADC_ENABLE_CONFIG();
}
/**
 * @brief: Enalbe the selected channel to work as a analog input
 * @param mux The channel to configure
 */
void inline adc_enable_channel(const ADC_MUX_t mux)
{
    /* Set the pin to be input */
    CLEAR_BIT(DDRC, mux);
    /* Set the current channel to accept analog data */
    SET_BIT(DIDR0, mux);
}
/**
 * @brief: disable the selected channel to work as a digital input
 * @param mux The channel to configure
 */
void inline adc_disable_channel(const ADC_MUX_t mux)
{
    CLEAR_BIT(DIDR0, mux);
}
/**
 * @brief: Select the given channel to listen to it
 * @param mux The ADC pin to listen to it
 */
void inline adc_pin_select(const ADC_MUX_t mux)
{
    /* Select the channel to listen to it */
    ADC_SET_MUX_CONFIG(mux);
}
/**
 * @brief ADC Start Conversion and store the readen value
 * @param addr the address to store the value in it
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline adc_convert(uint16 *const addr)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == addr)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Start Conversion */
        ADC_START_CONVERSION_CONFIG();
        /* Wait until conversion is done */
        while (0 == adc_conversion_done);  // Wait until ADC conversion completes
        adc_conversion_done = 0;
        /* Read the value */
        *addr = ADC;
    }
    return (ret_val);
}