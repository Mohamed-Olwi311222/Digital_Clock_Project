/* 
 * File:   mcal_usart.h
 * Author: Mohamed olwi
 *
 * Created: 4/2/2025 9:26:32 AM
 */
#ifndef MCAL_USART_H
#define	MCAL_USART_H
/*----------------------------Header Files------------------------------------*/
#include "../../std_types.h"
/*----------------------------Macros Declarations-----------------------------*/
/*==================UCSR0A REG=================*/
/*----------MPCM0 Bit-----------*/
#define _USART_MULTI_PROCESSOR_COMMUNICATION_MODE            1		            /* USART Multi-processor communication mode */
#define _USART_SINGLE_PROCESSOR_COMMUNICATION_MODE           0		            /* USART Single-processor communication mode */
/*----------U2X0 Bit-----------*/
#define _USART_TRANSMIT_DOUBLE_SPEED_MODE                    1		            /* USART Double speed mode */
#define _USART_TRANSMIT_NORMAL_SPEED_MODE                    0		            /* USART Normal speed mode */
/*----------UPE0 Bit-----------*/
#define _USART_PARITY_ERROR                                  1		            /* USART Parity error */
#define _USART_NO_PARITY_ERROR                               0		            /* USART No parity error */
/*----------DOR0 Bit-----------*/
#define _USART_DATA_OVERRUN_ERROR                            1		            /* USART Data overrun error */
#define _USART_NO_DATA_OVERRUN_ERROR                         0		            /* USART No data overrun error */
/*----------FE0 Bit-----------*/
#define _USART_FRAME_ERROR                                   1		            /* USART Frame error */
#define _USART_NO_FRAME_ERROR                                0		            /* USART No frame error */
/*----------UDRE0 Bit-----------*/
#define _USART_DATA_REGISTER_EMPTY                           1		            /* USART Data register empty */
#define _USART_DATA_REGISTER_NOT_EMPTY                       0		            /* USART Data register not empty */
/*----------TXC0 Bit-----------*/
#define _USART_TRANSMIT_COMPLETE                             1		            /* USART Transmit complete */
#define _USART_TRANSMIT_IDLE                                 0		            /* USART Transmit idle */
/*----------RXC0 Bit-----------*/
#define _USART_RECEIVE_COMPLETE                              1		            /* USART Receive complete */
#define _USART_RECEIVE_IDLE                                  0		            /* USART Receive idle */
/*==================UCSR0B REG=================*/
/*----------UCSZ02 Bit----------*/
#define _USART_CHAR_SIZE_CZ2_SET                             1		            /* USART Character size UCSZ2 is 1 */
#define _USART_CHAR_SIZE_CZ2_CLEAR                           0		            /* USART Character size UCSZ2 is 0 */
/*----------TXEN0 Bit----------*/
#define _USART_TRANSMITTER_ENABLE                            1		            /* USART Transmitter enable */
#define _USART_TRANSMITTER_DISABLE                           0		            /* USART Transmitter disable */
/*----------RXEN0 Bit----------*/
#define _USART_RECEIVER_ENABLE                               1		            /* USART Receiver enable */
#define _USART_RECEIVER_DISABLE                              0		            /* USART Receiver disable */
/*----------UDRIE0 Bit----------*/
#define _USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE          1		            /* USART Data register empty interrupt enable */
#define _USART_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE         0		            /* USART Data register empty interrupt disable */
/*----------TXCIE0 Bit----------*/
#define _USART_TRANSMIT_COMPLETE_INTERRUPT_ENABLE            1		            /* USART Transmit complete interrupt enable */
#define _USART_TRANSMIT_COMPLETE_INTERRUPT_DISABLE           0		            /* USART Transmit complete interrupt disable */
/*----------RXCIE0 Bit----------*/
#define _USART_RECEIVE_COMPLETE_INTERRUPT_ENABLE             1		            /* USART Receive complete interrupt enable */
#define _USART_RECEIVE_COMPLETE_INTERRUPT_DISABLE            0		            /* USART Receive complete interrupt disable */
/*==================UCSR0C REG=================*/
/*----------UCPOL0 Bit----------*/
#define _USART_TRANSMIT_POLARITY_RISING_EDGE                 0		            /* USART Transmit polarity rising edge */
#define _USART_TRANSMIT_POLARITY_FALLING_EDGE                1		            /* USART Transmit polarity falling edge */
#define _USART_RECEIVE_POLARITY_RISING_EDGE                  1		            /* USART Receive polarity rising edge */
#define _USART_RECEIVE_POLARITY_FALLING_EDGE                 0		            /* USART Receive polarity falling edge */
/*----------UCSZ00 Bit----------*/
#define _USART_CHAR_SIZE_CZ0_CLEAR                           0		            /* USART Character size UCSZ0 is 0 */
#define _USART_CHAR_SIZE_CZ0_SET                             1		            /* USART Character size UCSZ0 is 1 */
/*----------UCSZ01 Bit----------*/
#define _USART_CHAR_SIZE_CZ1_CLEAR                           0		            /* USART Character size UCSZ1 is 0 */
#define _USART_CHAR_SIZE_CZ1_SET                             1		            /* USART Character size UCSZ1 is 1 */
/*----------USBS0 Bit----------*/
#define _USART_TRANSMITTER_STOP_BITS_1_BIT                   0		            /* USART Transmitter Stop bits 1 bit */
#define _USART_TRANSMITTER_STOP_BITS_2_BIT                   1		            /* USART Transmitter Stop bits 2 bit */
/*----------------------------DataTypes---------------------------------------*/

/**
 * @brief: UCSR0A register bits
 */
typedef union
{
    struct
    {
        uint8 MPCM0_bit : 1;
        uint8 U2X0_bit : 1;
        uint8 UPE0_bit : 1;
        uint8 DOR0_bit : 1;
        uint8 FE0_bit : 1;
        uint8 UDRE0_bit : 1;
        uint8 TXC0_bit : 1;
        uint8 RXC0_bit : 1;
    };
    uint8 UCSR0A_register;
} UCSR0A_BITS_t;
extern volatile UCSR0A_BITS_t UCSR0A_bits __asm__("0xC0"); /* UCSR0A register */

/**
 * @brief: UCSR0B register bits
 */
typedef union
{
    struct
    {
        uint8 TXB80_bit : 1;
        uint8 RXB80_bit : 1;
        uint8 UCSZ02_bit : 1;
        uint8 TXEN0_bit : 1;
        uint8 RXEN0_bit : 1;
        uint8 UDRIE0_bit : 1;
        uint8 TXCIE0_bit : 1;
        uint8 RXCIE0_bit : 1;
    };
    uint8 UCSR0B_register;
} UCSR0B_BITS_t;
extern volatile UCSR0B_BITS_t UCSR0B_bits __asm__("0xC1"); 

/**
 * @brief: UCSR0C register bits
 */
typedef union
{
    struct
    {
        uint8 UCPOL0_bit : 1;
        uint8 UCSZ00_bit : 1;
        uint8 UCSZ01_bit : 1;
        uint8 USBS0_bit : 1;
        uint8 UPM00_bit : 1;
        uint8 UPM01_bit : 1;
        uint8 UMSEL00_bit : 1;
        uint8 UMSEL01_bit : 1;
    };
    struct 
    {
        uint8  : 4;
        uint8 UPMN_bits : 2;
        uint8 UMSELN_bits : 2;
    };
    uint8 UCSR0C_register;
} UCSR0C_BITS_t;
extern volatile UCSR0C_BITS_t UCSR0C_bits __asm__("0xC2"); 

/**
 * @brief: An enum for selecting the USART parity
 */
typedef enum
{
    USART_PARITY_DISABLED,
    USART_PARITY_EVEN = 2,
    USART_PARITY_ODD  = 3
} usart_parity_t;

/**
 * @brief: An enum for selecting the USART mode
 */
typedef enum
{
    ASYNC_USART,
    SYNC_USART,
    MASTER_SPI = 3
} usart_mode_t;

/**
 * @brief: The size of the USART character transmitted/received
 */
typedef enum
{
    USART_5_BIT_CHAR_SIZE,
    USART_6_BIT_CHAR_SIZE,
    USART_7_BIT_CHAR_SIZE,
    USART_8_BIT_CHAR_SIZE,
    USART_9_BIT_CHAR_SIZE = 7
} usart_char_size_t;

/**
 * struct usart_t - A Struct for USART peripheral
 * @usart_baudrate: The baudrate needed
 * @usart_parity: The USART parity mode
 * @usart_mode: The USART operating mode
 * @usart_char_size: The size of the character to transmit/receive
 */
typedef struct
{
    uint16 usart_baudrate;
    usart_parity_t usart_parity;
    usart_mode_t usart_mode;
    usart_char_size_t usart_char_size;
    uint8 usart_receiver_enable : 1;
    uint8 usart_receiver_clk_polarity : 1;
    uint8 usart_transmitter_enable : 1;
    uint8 usart_transmitter_clk_polarity : 1;
    uint8 usart_transmiter_stop_bits_number : 1;
    uint8 usart_transmitter_transmission_speed : 1;
    uint8 RESERVED : 2;
} usart_t;
/*----------------------------Macros Functions Declarations-------------------*/
/*==================UCSR0A REG=================*/
/*----------MPCM0 Bit-----------*/
/**
 * A macro function to set the USART multi-processor communication mode
 */
#define USART_RECEIVE_SET_MULTI_PROCESSOR_COMMS_MODE()       (UCSR0A_bits.MPCM0_bit = _USART_MULTI_PROCESSOR_COMMUNICATION_MODE)
/*----------U2X0 Bit-----------*/
/**
 * A macro function to set the USART double speed mode
 */
#define USART_TRANSMIT_SET_DOUBLE_SPEED_MODE()               (UCSR0A_bits.U2X0_bit = _USART_TRANSMIT_DOUBLE_SPEED_MODE)
/**
 * A macro function to set the USART normal speed mode
 */
#define USART_TRANSMIT_SET_NORMAL_SPEED_MODE()               (UCSR0A_bits.U2X0_bit = _USART_TRANSMIT_NORMAL_SPEED_MODE)
/*----------UPE0 Bit-----------*/
/**
 * A macro function to read the USART parity error flag
 */
#define USART_READ_PARITY_ERROR_CONFIG(__ADDR)               (*_ADDR = UCSR0A_bits.UPE0_bit)
/*----------DOR0 Bit-----------*/
/**
 * A macro function to read the USART data overrun flag
 */
#define USART_READ_DATA_OVERRUN_CONFIG(__ADDR)               (*_ADDR = UCSR0A_bits.DOR0_bit)
/*----------FE0 Bit-----------*/
/**
 * A macro function to read the USART frame error flag
 */
#define USART_READ_FRAME_ERROR_CONFIG(__ADDR)               (*_ADDR = UCSR0A_bits.FE0_bit)
/*----------UDRE0 Bit-----------*/
/**
 * A macro function to read the USART data register empty flag
 */
#define USART_READ_DATA_REGISTER_EMPTY_CONFIG(__ADDR)        (*_ADDR = UCSR0A_bits.UDRE0_bit)
/*----------TXC0 Bit-----------*/
/**
 * A macro function to read the USART transmit complete flag
*/
#define USART_READ_TRANSMIT_FLAG_CONFIG(__ADDR)              (*_ADDR = UCSR0A_bits.TXC0_bit)
/*----------RXC0 Bit-----------*/
/**
 * A macro function to read the USART receive complete flag
*/
#define USART_READ_RECEIVE_FLAG_CONFIG(__ADDR)               (*_ADDR = UCSR0A_bits.RXC0_bit)
/*==================UCSR0B REG=================*/
/*----------UCSZ02 Bit----------*/
/**
 * A macro function to set the USART character size UCSZ2
 */
#define USART_CHAR_SIZE_CZ2_SET_CONFIG()                     (UCSR0B_bits.UCSZ02_bit = _USART_CHAR_SIZE_CZ2_SET)
/**
 * A macro function to clear the USART character size UCSZ2
 */
#define USART_CHAR_SIZE_CZ2_CLEAR_CONFIG()                   (UCSR0B_bits.UCSZ02_bit = _USART_CHAR_SIZE_CZ2_CLEAR)
/*----------TXEN0 Bit----------*/
/**
 * A macro function to enable the USART transmitter
 */
#define USART_TRANSMITTER_ENABLE_CONFIG()                    (UCSR0B_bits.TXEN0_bit = _USART_TRANSMITTER_ENABLE)
/**
 * A macro function to disable the USART transmitter
 */
#define USART_TRANSMITTER_DISABLE_CONFIG()                    (UCSR0B_bits.TXEN0_bit = _USART_TRANSMITTER_DISABLE)
/*----------RXEN0 Bit----------*/
/**
 * A macro function to enable the USART receiver
 */
#define USART_RECEIVER_ENABLE_CONFIG()                       (UCSR0B_bits.RXEN0_bit = _USART_RECEIVER_ENABLE)
/**
 * A macro function to disable the USART receiver
 */
#define USART_RECEIVER_DISABLE_CONFIG()                      (UCSR0B_bits.RXEN0_bit = _USART_RECEIVER_DISABLE)
/*----------UDRIE0 Bit----------*/
/**
 * A macro function to enable the USART data register empty interrupt
 */
#define USART_DATA_REG_EMPTY_INT_ENABLE_CONFIG()             (UCSR0B_bits.UDRIE0_bit = _USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE)
/**
 * A macro function to disable the USART data register empty interrupt
 */
#define USART_DATA_REG_EMPTY_INT_DISABLE_CONFIG()            (UCSR0B_bits.UDRIE0_bit = _USART_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE)
/*----------TXCIE0 Bit----------*/
/**
 * A macro function to enable the USART transmit complete interrupt
 */
#define USART_TRANSMIT_COMPLET_INT_ENABLE_CONFIG()           (UCSR0B_bits.TXCIE0_bit = _USART_TRANSMIT_COMPLETE_INTERRUPT_ENABLE)
/**
 * A macro function to disable the USART transmit complete interrupt
 */
#define USART_TRANSMIT_COMPLET_INT_DISABLE_CONFIG()          (UCSR0B_bits.TXCIE0_bit = _USART_TRANSMIT_COMPLETE_INTERRUPT_DISABLE)
/*----------RXCIE0 Bit----------*/
/**
 * A macro function to enable the USART receive complete interrupt
 */
#define USART_RECEIVE_COMPLETE_INT_ENABLE_CONFIG()           (UCSR0B_bits.RXCIE0_bit = _USART_RECEIVE_COMPLETE_INTERRUPT_ENABLE)
/**
 * A macro function to disable the USART receive complete interrupt
 */
#define USART_RECEIVE_COMPLETE_INT_DISABLE_CONFIG()          (UCSR0B_bits.RXCIE0_bit = _USART_RECEIVE_COMPLETE_INTERRUPT_DISABLE)
/*==================UCSR0C REG=================*/
/*----------UCPOL0 Bit----------*/
/**
 * A macro function to set the USART transmit polarity falling edge
 */
#define USART_TRANSMIT_POLARITY_RISING_EDGE_CONFIG()         (UCSR0C_bits.UCPOL0_bit = _USART_TRANSMIT_POLARITY_RISING_EDGE)
/**
 * A macro function to set the USART transmit polarity falling edge
 */
#define USART_TRANSMIT_POLARITY_FALLING_EDGE_CONFIG()        (UCSR0C_bits.UCPOL0_bit = _USART_TRANSMIT_POLARITY_FALLING_EDGE)
/**
 * A macro function to set the USART receive polarity rising edge
 */
#define USART_RECEIVE_POLARITY_RISING_EDGE_CONFIG()          (UCSR0C_bits.UCPOL0_bit = _USART_RECEIVE_POLARITY_RISING_EDGE)
/**
 * A macro function to set the USART receive polarity falling edge
 */
#define USART_RECEIVE_POLARITY_FALLING_EDGE_CONFIG()         (UCSR0C_bits.UCPOL0_bit = _USART_RECEIVE_POLARITY_FALLING_EDGE)
/*----------UCSZ00 Bit----------*/
/**
 * A macro function to set the USART character size UCSZ0
 */
#define USART_CHAR_SIZE_CZ0_SET_CONFIG()                     (UCSR0C_bits.UCSZ00_bit = _USART_CHAR_SIZE_CZ0_SET)
/**
 * A macro function to clear the USART character size UCSZ0
 */
#define USART_CHAR_SIZE_CZ0_CLEAR_CONFIG()                   (UCSR0C_bits.UCSZ00_bit = _USART_CHAR_SIZE_CZ0_CLEAR)
/*----------UCSZ01 Bit----------*/
/**
 * A macro function to set the USART character size UCSZ1
 */
#define USART_CHAR_SIZE_CZ1_SET_CONFIG()                     (UCSR0C_bits.UCSZ01_bit = _USART_CHAR_SIZE_CZ1_SET)
/**
 * A macro function to clear the USART character size UCSZ1
 */
#define USART_CHAR_SIZE_CZ1_CLEAR_CONFIG()                   (UCSR0C_bits.UCSZ01_bit = _USART_CHAR_SIZE_CZ1_CLEAR)
/*----------USBS0 Bit----------*/
/**
 * A macro function to set the USART stop bits 1 bit
 */
#define USART_TRANSMIT_STOP_BITS_1_BIT_CONFIG()              (UCSR0C_bits.USBS0_bit = _USART_TRANSMITTER_STOP_BITS_1_BIT)
/**
 * A macro function to set the USART stop bits 2 bit
 */
#define USART_TRANSMIT_STOP_BITS_2_BIT_CONFIG()              (UCSR0C_bits.USBS0_bit = _USART_TRANSMITTER_STOP_BITS_2_BIT)
/*----------UPMn Bits----------*/
/**
 * A macro function to set the parity mode of the USART
 */
#define USART_SET_PARITY_MODE_CONFIG(__PARITY)               (UCSR0C_bits.UPMN_bits = __PARITY)
/*----------UMSELn Bits--------*/
/**
 * A macro function to set the mode of the USART
 */
#define USART_SET_MODE_CONFIG(__MODE)                        (UCSR0C_bits.UMSELN_bits = __MODE)
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the USART module
 * @param usart_obj the usart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType usart_init(const usart_t *const usart_obj);

/**
 * @brief: Write data to transmit it using USART
 * @note: Will block CPU instruction until TSR is empty
 * @param data the 8-bit data to transmit
 */
void inline usart_write_data(const uint8 data);
/**
 * @brief: Read data from USART
 * @param The address to store the read 8-bit data
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline usart_read_data(uint8 *const data);

#endif    /* MCAL_USART_H */