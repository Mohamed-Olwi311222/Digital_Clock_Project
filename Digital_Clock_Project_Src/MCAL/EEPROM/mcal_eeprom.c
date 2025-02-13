/* 
 * File:   mcal_eeprom.c
 * Author: Mohamed olwi
 *
 * Created: 13/2/2025 7:25:00 AM
 */
#include "mcal_eeprom.h"
/**
 * @brief: Write a byte to the EEPROM
 * @param addr the 9-bit address to write to it
 * @param byte the byte to write
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_write_byte(const uint16 addr, const uint8 byte)
{
    Std_ReturnType ret_val = E_OK;

    if (addr > EEPROM_MAX_SIZE)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Wait for completion of previous write */
        while (!(EEPROM_WRITE_IDLE == EECR_bits.EEPE_bit));
        /* Set up address and Data Registers */
        EEARH = (uint8) ((addr & 0xFF00) >> 8);
        EEARL = (uint8) (addr & 0x00FF);
        EEDR = byte;
        /* Write logical one to EEMPE */
        EEPROM_MASTER_WRITE_ENABLE_CONFIG();
        /* Start eeprom write by setting EEPE */
        EEPROM_WRITE_ENABLE_CONFIG();
    }
    return (ret_val);
}
/**
 * @brief: Read a byte from the EEPROM
 * @param addr the 9-bit address to read from it
 * @param byte the address to store the readen value
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_read_byte(const uint16 addr, uint8 *const byte)
{
    Std_ReturnType ret_val = E_OK;

    if (addr > EEPROM_MAX_SIZE)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        /* Wait for completion of previous write */
        while (!(EEPROM_WRITE_IDLE == EECR_bits.EEPE_bit));
        /* Set up address register */
        EEARH = (uint8) ((addr & 0xFF00) >> 8);
        EEARL = (uint8) (addr & 0x00FF);
        /* Start eeprom read by writing EERE */
        EEPROM_READ_ENABLE_CONFIG();
        /* Return data from Data Register */
        *byte = EEDR;
    }
    return (ret_val);
}
/**
 * @brief: Write a buffer to the EEPROM
 * @param addr the 9-bit address to start writing from it
 * @param buffer the buffer to write
 * @param buffer_len the length of the buffer
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_write_buffer(const uint16 start_addr, const uint8 *const buffer, const uint8 buffer_len)
{
    Std_ReturnType ret_val = E_OK;
    uint8 i = ZERO_INIT;

    if (start_addr > EEPROM_MAX_SIZE || (start_addr + buffer_len) > EEPROM_MAX_SIZE ||
        NULL == buffer || buffer_len == 0)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        for (; i < buffer_len; i++)
        {
            ret_val = eeprom_write_byte(start_addr + i, buffer[i]);
            if (E_NOT_OK == ret_val)
            {
                break;
            }
        }
    }
    return (ret_val);
}
/**
 * @brief: Read a buffer from the EEPROM
 * @param addr the 9-bit address to start reading from it
 * @param buffer the buffer to store the readen data
 * @param buffer_len the length of the data to read
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_read_buffer(const uint16 start_addr, uint8 *const buffer, const uint8 buffer_len)
{
    Std_ReturnType ret_val = E_OK;
    uint8 i = ZERO_INIT;

    if (start_addr > EEPROM_MAX_SIZE || (start_addr + buffer_len) > EEPROM_MAX_SIZE ||
        NULL == buffer || buffer_len == 0)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        for (; i < buffer_len; i++)
        {
            ret_val = eeprom_read_byte(start_addr + i, &(buffer[i]));
            if (E_NOT_OK == ret_val)
            {
                break;
            }
        }
    }
    return (ret_val);
}