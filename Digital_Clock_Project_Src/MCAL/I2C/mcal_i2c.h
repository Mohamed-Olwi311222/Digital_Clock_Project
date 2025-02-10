/* 
 * File:   mcal_i2c.h
 * Author: Mohamed olwi
 *
 * Created: 6/2/2025 7:05:36 AM
 */
#ifndef MCAL_I2C_H
#define MCAL_I2C_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*---------------------------Macros Declarations-------------------------------*/
#define I2C_WRITE_MODE                                       0 /* I2C Write Mode */
#define I2C_READ_MODE                                        1 /* I2C Read Mode */
#define I2C_TIME_OUT                                         3000 /* I2C timeout of polling */
#define I2C_DATA_LEN                                         10 /* The length of the data transmitted/received array */
/*==================TWCR REG====================*/
/*----------TWIE Bit------------*/
#define _I2C_ENABLE_INTERRUPT                                1 /* I2C Enable interrupt */
#define _I2C_DISABLE_INTERRUPT                               0 /* I2C Disable interrupt */
/*----------TWEN Bit------------*/
#define _I2C_ENABLE                                          1 /* I2C Enable */
#define _I2C_DISABLE                                         0 /* I2C Disable */
/*----------TWWC Bit------------*/
#define _I2C_WRITE_COLLISION                                 1 /* I2C Write Collision */
#define _I2C_NO_WRITE_COLLISION                              0 /* I2C No Write Collision */
/*----------TWSTO Bit------------*/
#define _I2C_STOP_CONDITION                                  1 /* I2C Stop Condition */
#define _I2C_NO_STOP_CONDITION                               0 /* I2C No Stop Condition */
/*----------TWSTA Bit------------*/
#define _I2C_START_CONDITION                                 1 /* I2C Start Condition */
#define _I2C_NO_START_CONDITION                              0 /* I2C No Start Condition */
/*----------TWEA Bit------------*/
#define _I2C_ACKNOWLEDGE                                     1 /* I2C Acknowledge */
#define _I2C_NACKNOWLEDGE                                    0 /* I2C Not Acknowledge */
/*----------TWINT Bit------------*/
#define _I2C_INTERRUPT_FLAG                                  1 /* I2C Interrupt Flag */
#define _I2C_NO_INTERRUPT_FLAG                               0 /* I2C No Interrupt Flag */
/*--------------------------DataTypes-----------------------------------------*/
/**
 * @brief: TWBR register bits
 */
typedef union
{
    struct
    {
        uint8 TWBR0_bit: 1;
        uint8 TWBR1_bit: 1;
        uint8 TWBR2_bit: 1;
        uint8 TWBR3_bit: 1;
        uint8 TWBR4_bit: 1;
        uint8 TWBR5_bit: 1;
        uint8 TWBR6_bit: 1;
        uint8 TWBR7_bit: 1;
    };
    uint8 TWBR_register;
} TWBR_BITS_t;
extern volatile TWBR_BITS_t TWBR_bits __asm__("0xB8");  /* TWBR register */

/**
 * @brief: TWCR register bits
 */
typedef union
{
    struct
    {
        uint8 TWIE_bit : 1;
        uint8 : 1;
        uint8 TWEN_bit : 1;
        uint8 TWWC_bit : 1;
        uint8 TWSTO_bit : 1;
        uint8 TWSTA_bit : 1;
        uint8 TWEA_bit : 1;
        uint8 TWINT_bit : 1;
    };
    uint8 TWCR_register;
}TWCR_BITS_t;
extern volatile TWCR_BITS_t TWCR_bits __asm__("0xBC");  /* TWCR register */

/**
 * @brief: TWSR register bits
 */
typedef union
{
    struct
    {
        uint8 TWPS0_bit : 1;
        uint8 TWPS1_bit : 1;
        uint8 : 1;
        uint8 TWS3_bit : 1;
        uint8 TWS4_bit : 1;
        uint8 TWS5_bit : 1;
        uint8 TWS6_bit : 1;
        uint8 TWS7_bit : 1;
    };
    struct 
    {
        uint8 TWPS_bits : 2;
        uint8 : 1;
        uint8 TWS_bits : 5;
    };
    uint8 TWSR_register;
}TWSR_BITS_t;
extern volatile TWSR_BITS_t TWSR_bits __asm__("0xB9");  /* TWSR register */

/**
 * @brief: I2C prescaler
 */
typedef enum
{
    I2C_PRESCALER_DIV_1 = 0,
    I2C_PRESCALER_DIV_4,
    I2C_PRESCALER_DIV_16,
    I2C_PRESCALER_DIV_64
} i2c_prescaler_t;

/**
 * @brief: I2C master status
 */
typedef enum 
{
    I2C_START_BIT_TRANSMITTED = 0x08,
    I2C_REPEATED_START_BIT_TRANSMITTED = 0x10,
    I2C_SLAVE_ADDRESS_AND_WRITE_ACK = 0x18,
    I2C_SLAVE_ADDRESS_AND_WRITE_NACK = 0x20,
    I2C_DATA_TRANSMITTED_ACK = 0x28,
    I2C_DATA_TRANSMITTED_NACK = 0x30,
    I2C_ARBITRATION_LOST = 0x38,
    I2C_SLAVE_ADDRESS_AND_READ_ACK = 0x40,
    I2C_SLAVE_ADDRESS_AND_READ_NACK = 0x48,
    I2C_DATA_RECEIVED_ACK = 0x50,
    I2C_DATA_RECEIVED_NACK = 0x58,
} i2c_master_status_t;

/**
 * @brief the I2C Supported freq
 */
typedef enum
{
    I2C_STANDARD_MODE_100KHZ = 100,
    I2C_FAST_MODE_400KHZ = 400
} i2c_freq_t;

/*--------------------------Macro Functions-----------------------------------*/
/*==================TWBR REG====================*/
/**
 * I2C set bit rate
 */
#define I2C_SET_BIT_RATE_CONFIG(__BIT_RATE)                  (TWBR_bits.TWBR_register = __BIT_RATE)
/*==================TWCR REG====================*/
/*----------TWIE Bit------------*/
/**
 * I2C enable interrupt
 */
#define I2C_ENABLE_INTERRUPT_CONFIG()                        (TWCR_bits.TWIE_bit = _I2C_ENABLE_INTERRUPT)
/**
 * I2C disable interrupt
 */
#define I2C_DISABLE_INTERRUPT_CONFIG()                       (TWCR_bits.TWIE_bit = _I2C_DISABLE_INTERRUPT)
/*----------TWEN Bit------------*/
/**
 * I2C enable
 */
#define I2C_ENABLE_CONFIG()                                  (TWCR_bits.TWEN_bit = _I2C_ENABLE)
/**
 * I2C disable
 */
#define I2C_DISABLE_CONFIG()                                 (TWCR_bits.TWEN_bit = _I2C_DISABLE)
/*----------TWWC Bit------------*/
/**
 * I2C write collision and store it in an address
 */
#define I2C_READ_WRITE_COLLISION_CONFIG(__ADDR)              (*__ADDR = TWCR_bits.TWWC_bit)
/*----------TWSTO Bit------------*/
/**
 * I2C send stop condition
 */
#define I2C_SEND_STOP_CONDITION_CONFIG()                     (TWCR_bits.TWSTO_bit = _I2C_STOP_CONDITION)
/**
 * I2C clear stop condition
 */
#define I2C_CLEAR_STOP_CONDITION_CONFIG()                     (TWCR_bits.TWSTO_bit = _I2C_NO_STOP_CONDITION)
/*----------TWSTA Bit------------*/
/**
 * I2C send start condition
 */
#define I2C_SEND_START_CONDITION_CONFIG()                    (TWCR_bits.TWSTA_bit = _I2C_START_CONDITION)
/**
 * I2C cleaar start condition
 */
#define I2C_CLEAR_START_CONDITION_CONFIG()                   (TWCR_bits.TWSTA_bit = _I2C_NO_START_CONDITION)
/*----------TWEA Bit------------*/
/**
 * I2C enable acknowledge
 */
#define I2C_ENABLE_ACKNOWLEDGE_CONFIG()                      (TWCR_bits.TWEA_bit = _I2C_ACKNOWLEDGE_ENABLE)
/**
 * I2C disable acknowledge
 */
#define I2C_DISABLE_ACKNOWLEDGE_CONFIG()                     (TWCR_bits.TWEA_bit = _I2C_ACKNOWLEDGE_DISABLE)
/*----------TWINT Bit------------*/
/**
 * I2C Set interrupt flag
 */
#define I2C_SET_INTERRUPT_FLAG_CONFIG()                      (TWCR_bits.TWINT_bit = _I2C_INTERRUPT_FLAG)
/**
 * I2C clear interrupt flag
 */
#define I2C_CLEAR_INTERRUPT_FLAG_CONFIG()                    (TWCR_bits.TWINT_bit = _I2C_NO_INTERRUPT_FLAG)
/*==================TWSR REG====================*/
/**
 * I2C set prescaler
 */
#define I2C_SET_PRESCALER_CONFIG(__PRESCALER)                (TWSR_bits.TWPS_bits = __PRESCALER)
/**
 * I2C get status and store it in an address
 */
#define I2C_GET_STATUS_CONFIG(__ADDR)                        (*__ADDR = TWSR_bits.TWSR_register & 0xF8)
/*==================TWDR REG====================*/
/**
 * I2C write data
 */
#define I2C_WRITE_DATA_CONFIG(__DATA)                        (TWDR = __DATA)
/**
 * I2C read data
 */
#define I2C_READ_DATA_CONFIG(__ADDR)                         (*__ADDR = TWDR)
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the I2C module
 * @param i2c_freq the I2C module freq
 */
void i2c_init(const uint8 i2c_freq);
/**
 * @brief: Read data from RTC DS1307 using I2C
 * @param slave_addr the slave address
 * @param reg the reg to read from it in the RTC DS1307
 * @param addr the address to store the data in it
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType i2c_master_read_data(const uint8 slave_addr, const uint8 reg, uint8 *const addr);
/**
 * @brief: Send Buffer using I2C to RTC DS1307
 * @param slave_addr the slave address
 * @param reg the reg to write to it in the RTC DS1307
 * @param data the data to send
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType i2c_master_write_buffer(const uint8 slave_addr, const uint8 reg, const uint8 data);

#endif /* mcal_i2c.h */