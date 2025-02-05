/* 
 * File:   main.h
 * Author: Mohamed olwi
 *
 * Created: 2/2/2025 8:15:36 AM
 */
#include "mcal_usart.h"

/*---------------Static Helper functions declerations---------------------------*/
static inline Std_ReturnType configure_usart_mode(const usart_t *const usart_obj);
static inline Std_ReturnType configure_usart_partiy(const usart_t *const usart_obj);
static inline Std_ReturnType configure_usart_char_size(const usart_t *const usart_obj);
/*---Baudrate Helper function---*/
static inline void usart_set_baudrate(const usart_t *const usart_obj);
/*---Transmit Helper functions--*/
static inline Std_ReturnType usart_configure_transmitter(const usart_t *const usart_obj);
static inline Std_ReturnType usart_configure_transmitter_stop_bits(const uint8 usart_stop_bits_number);
static inline Std_ReturnType usart_configure_transmitter_clk_polarity(const uint8 usart_transmitter_clk_polarity);
static inline Std_ReturnType usart_configure_transmitter_trans_speed(const uint8 usart_transmitter_transmission_speed);
/*---Receive Helper functions---*/
static inline Std_ReturnType usart_configure_receiver(const usart_t *const usart_obj);
static inline Std_ReturnType usart_configure_receiver_clk_polarity(const uint8 usart_receiver_clk_polarity);
/*---------------Static Helper functions declerations End-----------------------*/
/**
 * @brief: Initialize the USART module
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType usart_init(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == usart_obj)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Disable transmitter */
        USART_TRANSMITTER_DISABLE_CONFIG();
        /* Disable receiver */
        USART_RECEIVER_DISABLE_CONFIG();
        /* Disable interrupts */
        USART_TRANSMIT_COMPLET_INT_DISABLE_CONFIG();
        USART_RECEIVE_COMPLETE_INT_DISABLE_CONFIG();
        USART_DATA_REG_EMPTY_INT_DISABLE_CONFIG();
        /* Set the baudrate of the USART */
        usart_set_baudrate(usart_obj);
        /* Configure the mode of the USART */
        if (E_NOT_OK == configure_usart_mode(usart_obj))
        {
            /* Error happened while configuring */
            ret_val = E_NOT_OK;
        }
        /* Configure the parity mode of the USART */
        if (E_NOT_OK == configure_usart_partiy(usart_obj))
        {
            /* Error happened while configuring */
            ret_val = E_NOT_OK;
        }
        /* Configure the character size of the transmitter/receiver */
        if (E_NOT_OK == configure_usart_char_size(usart_obj))
        {
            /* Error happened while configuring */
            ret_val = E_NOT_OK;
        }
        /* Configure the transmitter of the usart and enable it */
        if (_USART_TRANSMITTER_ENABLE == usart_obj->usart_transmitter_enable)
        {
            /* transmitter is needed, enable and configure it */
            if (E_NOT_OK == usart_configure_transmitter(usart_obj))
            {
                /* Error happened while configuring */
                ret_val = E_NOT_OK;
            }
        }
        /* Configure the receiver of the usart and enable it */
        if (_USART_RECEIVER_ENABLE == usart_obj->usart_receiver_enable)
        {
            /* receiver is needed, enable and configure it */
            if (E_NOT_OK == usart_configure_receiver(usart_obj))
            {
                /* Error happened while configuring */
                ret_val = E_NOT_OK;
            }
        }
    }
    return (ret_val);
}

/**
 * @brief: Write data to transmit it using USART
 * @note: Will block CPU instruction until TSR is empty
 * @param data the 8-bit data to transmit
 */
void inline usart_write_data(const uint8 data)
{
    /* Check if the data register is empty */
    if (_USART_DATA_REGISTER_EMPTY == UCSR0A_bits.UDRE0_bit)
    {
        UDR0 = data;
        /* Wait until data is transmitted */
        while (!(_USART_TRANSMIT_COMPLETE == UCSR0A_bits.TXC0_bit));
    }
}
/**
 * @brief: Read data from USART
 * @param The address to store the read 8-bit data
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline usart_read_data(uint8 *const data)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL == data)
    {
        ret_val = E_NOT_OK;
    }
    else
    {

    }
    return (ret_val);
}

/**
 * @brief: set the baud rate of the usart 
 * @param usart_obj the usart module object
 */
static void inline usart_set_baudrate(const usart_t *const usart_obj)
{
    uint16 UBRR0_value = 0;

    /* Set the UBRR0 value depending on the mode of the Async mode */
    if (_USART_TRANSMIT_NORMAL_SPEED_MODE == usart_obj->usart_transmitter_transmission_speed)
    {
        UBRR0_value = (uint16)(((float)F_CPU / (16.0 * usart_obj->usart_baudrate)) - 1);
    }
    else
    {
        UBRR0_value = (uint16)(((float)F_CPU / (8.0 * usart_obj->usart_baudrate)) - 1);
    }
    UBRR0H = (uint8)(UBRR0_value >> 8);
    UBRR0L = (uint8)(UBRR0_value);
}
/**
 * @brief: Configure the USART Mode
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType configure_usart_mode(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;
    uint8 usart_mode = 0;

    switch (usart_obj->usart_mode)
    {
        /* Async USART Mode */
        case ASYNC_USART:
            usart_mode = ASYNC_USART;
            break;
        /* Sync USART Mode */
        case SYNC_USART:
            usart_mode = SYNC_USART;
            break;
        /*Master SPI Mode */
        case MASTER_SPI:
            usart_mode = MASTER_SPI;
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    USART_SET_MODE_CONFIG(usart_mode);

    return (ret_val);
}
/**
 * @brief: Configure the USART parity bits
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType configure_usart_partiy(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;
    uint8 parity_mode = 0;

    switch (usart_obj->usart_parity)
    {
        /* USART parity disable */
        case USART_PARITY_DISABLED:
            parity_mode = USART_PARITY_DISABLED;
            break;
        /* USART parity even */
        case USART_PARITY_EVEN:
            parity_mode = USART_PARITY_EVEN;
            break;
        /* USART parity odd */
        case USART_PARITY_ODD:
            parity_mode = USART_PARITY_ODD;
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    USART_SET_PARITY_MODE_CONFIG(parity_mode);

    return (ret_val);
}
/**
 * @brief: Configure the USART character size
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType configure_usart_char_size(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;

    switch (usart_obj->usart_char_size)
    {
        /* USART char size is 5 bit */
        case USART_5_BIT_CHAR_SIZE:
            USART_CHAR_SIZE_CZ0_CLEAR_CONFIG();
            USART_CHAR_SIZE_CZ1_CLEAR_CONFIG();
            USART_CHAR_SIZE_CZ2_CLEAR_CONFIG();
            break;
        /* USART char size is 6 bit */
        case USART_6_BIT_CHAR_SIZE:
            USART_CHAR_SIZE_CZ0_SET_CONFIG();
            USART_CHAR_SIZE_CZ1_CLEAR_CONFIG();
            USART_CHAR_SIZE_CZ2_CLEAR_CONFIG();
            break;
        /* USART char size is 7 bit */
        case USART_7_BIT_CHAR_SIZE:
            USART_CHAR_SIZE_CZ0_CLEAR_CONFIG();
            USART_CHAR_SIZE_CZ1_SET_CONFIG();
            USART_CHAR_SIZE_CZ2_CLEAR_CONFIG();
            break;
        /* USART char size is 8 bit */
        case USART_8_BIT_CHAR_SIZE:
            USART_CHAR_SIZE_CZ0_SET_CONFIG();
            USART_CHAR_SIZE_CZ1_SET_CONFIG();
            USART_CHAR_SIZE_CZ2_CLEAR_CONFIG();
            break;
        /* USART char size is 9 bit */
        case USART_9_BIT_CHAR_SIZE:
            USART_CHAR_SIZE_CZ0_SET_CONFIG();
            USART_CHAR_SIZE_CZ1_SET_CONFIG();
            USART_CHAR_SIZE_CZ2_SET_CONFIG();
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    return (ret_val);
}
/**
 * @brief: configure the usart transmiterr (clock polartiy, no.stop bits)
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType usart_configure_transmitter(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;

    /* Configure the Clock polarity */
    if (E_NOT_OK == usart_configure_transmitter_clk_polarity(usart_obj->usart_transmitter_clk_polarity))
    {
            ret_val = E_NOT_OK;
    }
    /* Configure the number of stop bits */
    if (E_NOT_OK == usart_configure_transmitter_stop_bits(usart_obj->usart_transmiter_stop_bits_number))
    {
            ret_val = E_NOT_OK;
    }
    /* Configure the USART transmission speed */
    if (E_NOT_OK == usart_configure_transmitter_trans_speed(usart_obj->usart_transmitter_transmission_speed))
    {
            ret_val = E_NOT_OK;
    }
    /* Enable the USART transmitter */
    USART_TRANSMITTER_ENABLE_CONFIG();

   return (ret_val);
}
/**
 * @brief: Configure the clock polarity of the USART transmitter
 * @param usart_transmitter_clk_polarity the current usart chosen polarity
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType usart_configure_transmitter_clk_polarity(const uint8 usart_transmitter_clk_polarity)
{
    Std_ReturnType ret_val = E_OK;

    switch (usart_transmitter_clk_polarity)
    {
        /* Clock polarity of the transmiter is falling edge */
        case _USART_TRANSMIT_POLARITY_FALLING_EDGE:
            USART_TRANSMIT_POLARITY_FALLING_EDGE_CONFIG();
            break;
        /* Clock polarity of the transmiter is rising edge */
        case _USART_TRANSMIT_POLARITY_RISING_EDGE:
            USART_TRANSMIT_POLARITY_RISING_EDGE_CONFIG();
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
}
/**
 * @brief: Configure the number of stop bits of the USART transmitter
 * @param usart_stop_bits_number the current usart chosen number of stop bits
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType usart_configure_transmitter_stop_bits(const uint8 usart_stop_bits_number)
{
    Std_ReturnType ret_val = E_OK;

    switch (usart_stop_bits_number)
    {
        /* the number of stop bits is 1 */
        case _USART_TRANSMITTER_STOP_BITS_1_BIT:
            USART_TRANSMIT_STOP_BITS_1_BIT_CONFIG();
            break;
        /* the number of stop bits is 2 */
        case _USART_TRANSMITTER_STOP_BITS_2_BIT:
            USART_TRANSMIT_STOP_BITS_2_BIT_CONFIG();
            break; 
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    return (ret_val);
}
/**
 * @brief: Configure the USART transmitter transmisson speed
 * @param usart_transmitter_transmission_speed the current usart chosen transmission speed
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType usart_configure_transmitter_trans_speed(const uint8 usart_transmitter_transmission_speed)
{
    Std_ReturnType ret_val = E_OK;
    switch (usart_transmitter_transmission_speed)
    {
        /* Set the transmission speed to doub.e speed */
        case _USART_TRANSMIT_DOUBLE_SPEED_MODE:
            USART_TRANSMIT_SET_DOUBLE_SPEED_MODE();
            break;
        /* Set the transmission speed to normal speed */
        case _USART_TRANSMIT_NORMAL_SPEED_MODE:
            USART_TRANSMIT_SET_NORMAL_SPEED_MODE();
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    return (ret_val);
}

static inline Std_ReturnType usart_configure_receiver(const usart_t *const usart_obj)
{
    Std_ReturnType ret_val = E_OK;

    /* Configure the Clock polarity */
    if (E_NOT_OK == usart_configure_receiver_clk_polarity(usart_obj->usart_receiver_clk_polarity))
    {
            ret_val = E_NOT_OK;
    }
    /* Enable the USART receiver */
    USART_RECEIVER_ENABLE_CONFIG();

    return (ret_val);
}
static inline Std_ReturnType usart_configure_receiver_clk_polarity(const uint8 usart_receiver_clk_polarity)
{
    Std_ReturnType ret_val = E_OK;

    switch (usart_receiver_clk_polarity)
    {
        /* Clock polarity of the receiver is falling edge */
        case _USART_RECEIVE_POLARITY_FALLING_EDGE:
            USART_RECEIVE_POLARITY_FALLING_EDGE_CONFIG();
            break;
        /* Clock polarity of the receiver is rising edge */
        case _USART_RECEIVE_POLARITY_RISING_EDGE:
            USART_RECEIVE_POLARITY_RISING_EDGE_CONFIG();
            break;
        /* Error, undefined value */
        default:
            ret_val = E_NOT_OK;
            break;
    }
    return (ret_val);
}
