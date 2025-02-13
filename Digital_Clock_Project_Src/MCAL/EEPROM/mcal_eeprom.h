/* 
 * File:   mcal_eeprom.h
 * Author: Mohamed olwi
 *
 * Created: 13/2/2025 7:25:00 AM
 */
#ifndef MCAL_EEPROM_H
#define	EEPROM_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*----------------------------Macros Declarations-----------------------------*/
#define EEPROM_WRITE_IDLE                                    0
#define EEPROM_MAX_SIZE                                      1023
/*----------------------------DataTypes---------------------------------------*/
/**
 * @brief EECR register bits
 */
typedef union
{
    struct
    {
        uint8 EERE_bit : 1;
        uint8 EEPE_bit : 1;
        uint8 EEMPE_bit : 1;
        uint8 EERIE_bit : 1;
        uint8 EEPM0_bit : 1;
        uint8 EEPM1_bit : 1;
        uint8 : 2;
    };
    struct
    {
        uint8 : 4;
        uint8 EEPM_bits : 2;
        uint8 : 2;
    };
    uint8 EECR_register;
}EECR_BITS_t;
#define EECR_bits (*((volatile EECR_BITS_t *)0x3F)) /* EECR register bits */
/*----------------------------Macros Functions Declarations-------------------*/
/*==================EECR REG====================*/
/*----------EERE Bit------------*/
/**
 * Enable EEPROM Read mode
 */
#define EEPROM_READ_ENABLE_CONFIG()                          (EECR_bits.EERE_bit = 1)
/*----------EEPE Bit------------*/
/**
 * Enable EEPROM Write mode
 */
#define EEPROM_WRITE_ENABLE_CONFIG()                         (EECR_bits.EEPE_bit = 1)
/*----------EEMPE Bit-----------*/
/**
 * EEPROM Master Write Enable
 */
#define EEPROM_MASTER_WRITE_ENABLE_CONFIG()                  (EECR_bits.EEMPE_bit = 1)
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Write a byte to the EEPROM
 * @param addr the 9-bit address to write to it
 * @param byte the byte to write
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline eeprom_write_byte(const uint16 addr, const uint8 byte);
/**
 * @brief: Read a byte from the EEPROM
 * @param addr the 9-bit address to read from it
 * @param byte the address to store the readen value
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_read_byte(const uint16 addr, uint8 *const byte);
/**
 * @brief: Write a buffer to the EEPROM
 * @param addr the 9-bit address to start writing from it
 * @param buffer the buffer to write
 * @param buffer_len the length of the buffer
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_write_buffer(const uint16 start_addr, const uint8 *const buffer, const uint8 buffer_len);
/**
 * @brief: Read a buffer from the EEPROM
 * @param addr the 9-bit address to start reading from it
 * @param buffer the buffer to store the readen data
 * @param buffer_len the length of the data to read
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eeprom_read_buffer(const uint16 start_addr, uint8 *const buffer, const uint8 buffer_len);
#endif	/* ecu_keypad.h */