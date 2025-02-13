MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = COM10
BAUD = 115200

# Directories
SRC_DIR = src
#MCAL Layer Module
MCAL_DIR = MCAL
GPIO = $(MCAL_DIR)/GPIO/mcal_gpio.c
USART = $(MCAL_DIR)/USART/mcal_usart.c
I2C = $(MCAL_DIR)/I2C/mcal_i2c.c
ADC = $(MCAL_DIR)/ADC/mcal_adc.c
#MCAL Modules
MCAL_MODULES = $(GPIO) $(USART) $(I2C) $(ADC)
#ECU Layer Module
ECU_DIR = ECU
CHAR_LCD = $(ECU_DIR)/Char_LCD/ecu_char_lcd.c
RTC_DS1307 = $(ECU_DIR)/RTC_DS1307/ecu_rtc.c
KEYPAD = $(ECU_DIR)/KEYPAD/ecu_keypad.c
#ECU modules
ECU_MODULES = $(CHAR_LCD) $(RTC_DS1307) $(KEYPAD)
# Source files (Add all C files from different directories)
SRC = main.c $(MCAL_MODULES) $(ECU_MODULES)

# Object files
OBJ = $(SRC:.c=.o)

# Output files
ELF = main.elf
HEX = main.hex

# Compiler flags
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -I$(MCAL_DIR) -I$(ECU_DIR) -I$(SRC_DIR) -I.

# Build HEX file from ELF
all: $(HEX)

$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $< $@

# Build ELF from object files
$(ELF): $(OBJ)
	avr-gcc $(CFLAGS) -o $@ $^

# Compile C files to object files
%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<

# Upload to MCU using avrdude
upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):i

# Clean build files
clean:
	rm -f $(OBJ) $(ELF) $(HEX)
