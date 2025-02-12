/* 
 * File:   ecu_adc.h
 * Author: Mohamed olwi
 *
 * Created: 10/2/2025 7:49:00 AM
 */
#ifndef MCAL_ADC_H
#define	MCAL_ADC_H
 /*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
 /*----------------------------Macros Declarations-----------------------------*/
/*==================ADMUX REG==================*/
/*----------ADLAR Bits----------*/
#define _ADC_RESULT_LEFT_ADJUST                              1 /* ADC result left justify */
#define _ADC_RESULT_RIGHT_ADJUST                             0 /* ADC result right justify */
/*==================ADCSRA REG=================*/
/*----------ADIE Bit------------*/
#define _ADC_INTERRUPT_ENABLE                                1 /* ADC interrupt enable */
#define _ADC_INTERRUPT_DISABLE                               0 /* ADC interrupt disable */
/*----------ADIF Bit------------*/
#define _ADC_INTERRUPT_FLAG_CLEAR                            1 /* ADC interrupt flag clear */
/*----------ADSC Bit------------*/
#define _ADC_CONVERSION_START                                1 /* ADC conversion start */
#define _ADC_CONVERSION_STOP                                 0 /* ADC conversion stop */
/*----------ADEN Bit------------*/
#define _ADC_ENABLE                                          1 /* ADC enable */
#define _ADC_DISABLE                                         0 /* ADC disable */
 /*----------------------------DataTypes---------------------------------------*/
 /**
  * @brief ADMUX Register
  */
typedef union 
{
    struct 
    {
        uint8 MUX0_bit : 1;
        uint8 MUX1_bit : 1;
        uint8 MUX2_bit : 1;
        uint8 MUX3_bit : 1;
        uint8 : 1;
        uint8 ADLAR_bit : 1;
        uint8 REFS0_bit : 1;
        uint8 REFS1_bit : 1;
    };
    struct
    {
        uint8 MUX_bits : 4;
        uint8 : 1;
        uint8 : 1;
        uint8 REFS_bits : 2;
    };
    uint8 ADMUX_register;
}ADMUX_BITS_t;
extern volatile ADMUX_BITS_t ADMUX_bits __asm__("0x7C"); 

/**
 * @brief ADCSRA Register
 */
typedef union
{
    struct
    {
        uint8 ADPS0_bit : 1;
        uint8 ADPS1_bit : 1;
        uint8 ADPS2_bit : 1;
        uint8 ADIE_bit : 1;
        uint8 ADIF_bit : 1;
        uint8 ADATE_bit : 1;
        uint8 ADSC_bit : 1;
        uint8 ADEN_bit : 1;
    };
    struct
    {
        uint8 ADPS_bits : 3;
        uint8 : 5;
    };
    uint8 ADCSRA_register;
}ADCSRA_BITS_t;
extern volatile ADCSRA_BITS_t ADCSRA_bits __asm__("0x7A");

/**
 * @brief DIDR0 register
 */
typedef union
{
    struct
    {
        uint8 ADC0D_bit : 1;
        uint8 ADC1D_bit : 1;
        uint8 ADC2D_bit : 1;
        uint8 ADC3D_bit : 1;
        uint8 ADC4D_bit : 1;
        uint8 ADC5D_bit : 1;
        uint8 : 2;
    };
    struct
    {
        uint8 ADCD_bits : 6;
        uint8 : 2;
    };
    uint8 DIDR0_register;
}DIDR0_BITS_t;
extern volatile DIDR0_BITS_t DIDR0_bits __asm__("0x7E");

/**
 * @brief ADC mux selection
 */
typedef enum
{
    ADC0 = 0,
    ADC1 = 1,
    ADC2 = 2,
    ADC3 = 3,
    ADC4 = 4,
    ADC5 = 5,
    ADC6 = 6,
    ADC7 = 7,
    ADC8 = 8,
} ADC_MUX_t;
/**
 * @brief ADC reference selection
 */
typedef enum
{
    ADC_REF_AREF = 0,
    ADC_REF_AVCC = 1,
    ADC_REF_INTERNAL = 3
}ADC_REF_t;

/**
 * @brief ADC prescaler selection
 */
typedef enum
{
    ADC_PRESCALER_2 = 0,
    ADC_PRESCALER_4 = 2,
    ADC_PRESCALER_8 = 3,
    ADC_PRESCALER_16 = 4,
    ADC_PRESCALER_32 = 5,
    ADC_PRESCALER_64 = 6,
    ADC_PRESCALER_128 = 7
}ADC_PRESCALER_t;
/*----------------------------Macros Functions Declarations-------------------*/
/*==================ADMUX REG==================*/
/*----------MUX0:3 Bits---------*/
/**
 * Set the ADC Analog Channel
 */
#define ADC_SET_MUX_CONFIG(__ADC_MUX)                        (ADMUX_bits.MUX_bits = __ADC_MUX)
/*----------ADLAR Bits----------*/
/**
 * Set the ADC Result Left Adjust
 */
#define ADC_SET_LEFT_ADJUST_RESULT_CONFIG()                  (ADMUX_bits.ADLAR_bit = _ADC_RESULT_LEFT_ADJUST)
/**
 * Set the ADC Result Right Adjust
 */
#define ADC_SET_RIGHT_ADJUST_RESULT_CONFIG()                 (ADMUX_bits.ADLAR_bit = _ADC_RESULT_RIGHT_ADJUST)
/*----------REFS1:0 Bits--------*/
/**
 * Set the ADC Reference Selection
 */
#define ADC_SET_REF_CONFIG(__ADC_REF)                        (ADMUX_bits.REFS_bits = __ADC_REF)
/*==================ADCSRA REG=================*/
/*----------ADPS0:2 Bits--------*/
/**
 * Set the ADC Prescaler Selection
 */
#define ADC_SET_PRESCALER_CONFIG(__ADC_PRESCALER)            (ADCSRA_bits.ADPS_bits = __ADC_PRESCALER)
/*----------ADIE Bit------------*/
/**
 * Enable the ADC Interrupt
 */
#define ADC_ENABLE_INTERRUPT_CONFIG()                        (ADCSRA_bits.ADIE_bit = _ADC_INTERRUPT_ENABLE)
/**
 * Disable the ADC Interrupt
 */
#define ADC_DISABLE_INTERRUPT_CONFIG()                       (ADCSRA_bits.ADIE_bit = _ADC_INTERRUPT_DISABLE)
/*----------ADIF Bit------------*/
/**
 * Clear the ADC Interrupt Flag
 */
#define ADC_CLEAR_INTERRUPT_FLAG_CONFIG()                    (ADCSRA_bits.ADIF_bit = _ADC_INTERRUPT_FLAG_CLEAR)
/*----------ADSC Bit------------*/
/**
 * Start the ADC Conversion
 */
#define ADC_START_CONVERSION_CONFIG()                        (ADCSRA_bits.ADSC_bit = _ADC_CONVERSION_START)
/*----------ADEN Bit------------*/
/**
 * Enable the ADC
 */
#define ADC_ENABLE_CONFIG()                                  (ADCSRA_bits.ADEN_bit = _ADC_ENABLE)
/**
 * Disable the ADC
 */
#define ADC_DISABLE_CONFIG()                                 (ADCSRA_bits.ADEN_bit = _ADC_DISABLE)
/*==================DIDR0 REG==================*/
/*----------ADC0D:5D Bits-------*/
/**
 * Disable Digital input
 */
#define ADC_DISABLE_DIGITAL_INPUT(__ADC_MUX)                 (DIDR0_bits.ADPS_bits = __ADC_MUX)
 /*----------------------------Function Prototypes-----------------------------*/
/**
 *  @brief ADC Initialization
 * @param ref the ADC reference selection
 */
void inline adc_init(const ADC_REF_t ref);
/**
 * @brief: Enalbe the selected channel to work as a analog input
 * @param mux The channel to configure
 */
void inline adc_enable_channel(const ADC_MUX_t mux);
/**
 * @brief: disable the selected channel to work as a digital input
 * @param mux The channel to configure
 */
void inline adc_disable_channel(const ADC_MUX_t mux);
/**
 * @brief: Select the given channel to listen to it
 * @param mux The ADC pin to listen to it
 */
void inline adc_pin_select(const ADC_MUX_t mux);
/**
 * @brief ADC Start Conversion and store the readen value
 * @param addr the address to store the value in it
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline adc_convert(uint16 *const addr);
 #endif	/* mcal_adc.h */