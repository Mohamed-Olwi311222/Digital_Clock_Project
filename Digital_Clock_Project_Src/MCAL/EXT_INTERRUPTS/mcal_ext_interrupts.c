/* 
 * File:   mcal_ext_interrupts.c
 * Author: Mohamed olwi
 *
 * Created: 21/2/2025 1:08:00 AM
 */
#include "mcal_ext_interrupts.h"
static volatile void (*EXT_INT0_INTERRUPT_HANDLER)() = NULL; /* Interrupt handler of INT0 */
static volatile void (*EXT_INT1_INTERRUPT_HANDLER)() = NULL; /* Interrupt handler of INT1 */

static Std_ReturnType inline set_intx_isr(uint8 intx_type ,void (*intx_isr)());

ISR(INT0_vect)
{
    if (EXT_INT0_INTERRUPT_HANDLER)
    {
        EXT_INT0_INTERRUPT_HANDLER();
    }
}
ISR(INT1_vect)
{
    if (EXT_INT1_INTERRUPT_HANDLER)
    {
        EXT_INT1_INTERRUPT_HANDLER();
    }
}
/**
 * @brief Initialize external interrupt INTx depending on the parameter
 * @param intx_type Which INTx interrupt to init
 * @param interrupt_sense When to trigger the external INTx interrupt
 * @param intx_isr A pointer to the ISR to set to the INTx interrupt
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline ext_intx_init(uint8 intx_type, EXT_INTx_SENSE_t interrupt_sense, void (*intx_isr)())
{
    Std_ReturnType ret_val = E_OK;

    if (EXT_INT0 == intx_type)
    {
        /* Disable INT0 interrupt */
        EXT_INT0_DISABLE_CONFIG();
        /* Set the INT0 interrupt sense */
        SET_EXT_INT0_SENSE_CONFIG(interrupt_sense);
        /* Enable INT0 interrupt*/
        EXT_INT0_ENABLE_CONFIG();
    }
    else if (EXT_INT1 == intx_type)
    {
        /* Disable INT1 interrupt */
        EXT_INT1_DISABLE_CONFIG();
        /* Set the INT1 interrupt sense */
        SET_EXT_INT1_SENSE_CONFIG(interrupt_sense);
        /* Enable INT1 interrupt*/
        EXT_INT1_ENABLE_CONFIG();
    }
    else
    {
        /* wrong or unsupported INTx interrupt */
        ret_val = E_NOT_OK;
    }
    if (E_OK == ret_val)
    {
        ret_val = set_intx_isr(intx_type, intx_isr);
    }
    return (ret_val);
}
/**
 * @brief Set the interrupt handler of the INTx
 * @param intx_type Which INTx interrupt to set its ISR
 * @param intx_isr A pointer to the ISR
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType inline set_intx_isr(uint8 intx_type ,void (*intx_isr)())
{
    Std_ReturnType ret_val = E_OK;

    if (EXT_INT0 == intx_type)
    {
        EXT_INT0_INTERRUPT_HANDLER = intx_isr;
    }
    else if (EXT_INT1 == intx_type)
    {
        EXT_INT1_INTERRUPT_HANDLER = intx_isr;
    }
    else
    {
        /* wrong or unsupported INTx interrupt */
        ret_val = E_NOT_OK;
    }
    return (ret_val);
}