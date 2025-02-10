/* 
 * File:   mcal_i2c.c
 * Author: Mohamed olwi
 *
 * Created: 6/2/2025 7:05:36 AM
 */

#include "mcal_i2c.h"
/*---------------Static Data types----------------------------------------------*/
volatile uint8 I2C_STATUS_CODE;
/*---------------Static Data types End------------------------------------------*/
/*---------------Static Helper functions declerations---------------------------*/
static void inline i2c_set_freq(const uint8 i2c_freq);
static inline Std_ReturnType i2c_poll_status(const uint8 status);
static inline Std_ReturnType i2c_master_send_start_cond(void);
static inline void i2c_master_send_stop_cond(void);
static Std_ReturnType i2c_send_byte(const uint8 byte, const uint8 ack);
static Std_ReturnType i2c_receive_data(const uint8 ack, uint8 *const addr);
/*---------------Static Helper functions declerations End-----------------------*/

/**
 * @brief: Initialize the I2C module
 * @param i2c_freq the I2C module freq
 */
void i2c_init(const uint8 i2c_freq)
{
    /* Set the i2c frequency and prescalter */
    i2c_set_freq(i2c_freq);
    /* Enable I2C */
    I2C_ENABLE_CONFIG();
}
/**
 * @brief: Read data from RTC DS1307 using I2C
 * @param slave_addr the slave address
 * @param reg the reg to read from it in the RTC DS1307
 * @param addr the address to store the data in it
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType i2c_master_read_data(const uint8 slave_addr, const uint8 reg, uint8 *const addr)
{
    Std_ReturnType ret_val = E_OK;
    uint8 slave_with_ack = (uint8)((slave_addr << 1) | I2C_WRITE_MODE);

    /* Send start condition */
    ret_val = i2c_master_send_start_cond();
    if (E_OK == ret_val)
    {
        /* Write the slave address */
        ret_val = i2c_send_byte(slave_with_ack, I2C_SLAVE_ADDRESS_AND_WRITE_ACK);
        if (E_OK == ret_val)
        {
            /* Send the reg to read from it */
            ret_val = i2c_send_byte(reg, I2C_DATA_TRANSMITTED_ACK);
            if (E_OK == ret_val)
            {
                ret_val = i2c_master_send_start_cond();
                ret_val = i2c_send_byte(slave_with_ack | I2C_READ_MODE, I2C_SLAVE_ADDRESS_AND_READ_ACK);
                if (E_OK == ret_val)
                {
                    /* Receive the data from the reg in DS1307 */
                    ret_val = i2c_receive_data(_I2C_NACKNOWLEDGE, addr);
                    _delay_us(1000);
                    if (E_OK == ret_val)
                    {
                        ret_val = E_NOT_OK;
                    }
                }
            }
        }
    }
    /* end comms */
    i2c_master_send_stop_cond();
    return (ret_val);
}
/**
 * @brief: Send Buffer using I2C to RTC DS1307
 * @param slave_addr the slave address
 * @param reg the reg to write to it in the RTC DS1307
 * @param data the data to send
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType i2c_master_write_buffer(const uint8 slave_addr, const uint8 reg, const uint8 data)
{
    Std_ReturnType ret_val = E_OK;
    uint8 slave_with_ack = (uint8)((slave_addr << 1) | I2C_WRITE_MODE);

    /* Send start condition */
    ret_val = i2c_master_send_start_cond();
    if (E_OK == ret_val)
    {
        /* Write the slave address */
        ret_val = i2c_send_byte(slave_with_ack, I2C_SLAVE_ADDRESS_AND_WRITE_ACK);
        if (E_OK == ret_val)
        {
            /* Send the reg to write to it */
            ret_val = i2c_send_byte(reg, I2C_DATA_TRANSMITTED_ACK);
            if (E_OK == ret_val)
            {
                ret_val = i2c_send_byte(data, I2C_DATA_TRANSMITTED_ACK);
                _delay_us(1000);
            }
        }
    }
    /* end comms */
    i2c_master_send_stop_cond();
    return ret_val;
}
/**
 * @brief: Send a start condition in I2C master mode
 */
static inline Std_ReturnType i2c_master_send_start_cond(void)
{
    Std_ReturnType ret_val = E_OK;
    TWCR_bits.TWCR_register = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    /* poll until status is received */
    ret_val = i2c_poll_status(I2C_START_BIT_TRANSMITTED);
    return (ret_val);
}
/**
 * @brief: Send a stop condition in I2C master mode
 */
static inline void i2c_master_send_stop_cond(void)
{
    TWCR_bits.TWCR_register = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
/**
 * @brief: Send data in I2C master mode
 * @param ack the acknowledge status to wait for it
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType i2c_send_byte(const uint8 byte, const uint8 ack)
{
    Std_ReturnType ret_val = E_OK;

    /* Write data to TWDR register */
    I2C_WRITE_DATA_CONFIG(byte);
    TWCR_bits.TWCR_register = (1 << TWINT) | (1 << TWEN);
    /* Wait until the status is received and clear the interrupt flag */
    ret_val = i2c_poll_status(ack);
    return (ret_val);
}
/**
 * @brief: Recieve data using i2c
 * @param addr The addr to store the data recieved
 * @param ack The acknowledge to wait for it (SLAVE_ACK and SLAVE_NACK)
 */
static Std_ReturnType i2c_receive_data(const uint8 ack, uint8 *const addr)
{
    Std_ReturnType ret_val = E_OK;

    if (NULL != addr)
    {
        if(_I2C_ACKNOWLEDGE == ack)
        {
            /* ack, so more bytes will be received */
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
            ret_val = i2c_poll_status(I2C_DATA_RECEIVED_ACK);
        }
        else
        {
            /* Not ack, then it is the last byte to receive */
            TWCR = (1 << TWINT) | (1 << TWEN);
            ret_val = i2c_poll_status(I2C_DATA_RECEIVED_NACK);
        }
        if (E_OK == ret_val)
        {
            /* Store the data */
            *addr = TWDR;
        }
    }
    else
    {
        ret_val = E_NOT_OK;
    }
    return (ret_val);
}
/**
 * @brief: Poll the I2C Status  bits and clear the interrupt flag
 * @status: Status to poll on it
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType i2c_poll_status(const uint8 status)
{
    Std_ReturnType ret_val = E_OK;
    uint16 timeout = I2C_TIME_OUT;

    while (I2C_STATUS_CODE != status)
    {
        timeout--;
        I2C_GET_STATUS_CONFIG(&I2C_STATUS_CODE);
        if (0 == timeout)
        {
            ret_val = E_NOT_OK;
            break;
        }
    }

    /* Wrong status received or timeout happened */
    if (I2C_STATUS_CODE != status)
    {
        ret_val = E_NOT_OK;
    }
    
    I2C_CLEAR_INTERRUPT_FLAG_CONFIG();  // Clear the flag
    return (ret_val);
}
/**
 * @brief: Set the frequency of the I2C
 * @param i2c_freq the I2C module object
 */
static inline void i2c_set_freq(const uint8 i2c_freq)
{
    uint8 i2c_bit_rate = 0;
    uint32 scl_freq = i2c_freq * 1000UL;  // Convert kHz to Hz

    /* Set the prescaler */
    I2C_SET_PRESCALER_CONFIG(I2C_PRESCALER_DIV_1);

    /* I2C bit rate calculation */
    i2c_bit_rate = (uint8)((((float)F_CPU / scl_freq) - 16) / (2));

    /* Set the bit rate */
    I2C_SET_BIT_RATE_CONFIG(i2c_bit_rate);
}
