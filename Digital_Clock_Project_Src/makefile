MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = COM10
BAUD = 115200

# Directories
SRC_DIR = src
MCAL_DIR = MCAL
ECU_DIR = ECU
GPIO = $(MCAL_DIR)/GPIO/mcal_gpio.c
USART = $(MCAL_DIR)/USART/mcal_usart.c
CHAR_LCD = $(ECU_DIR)/Char_LCD/ecu_char_lcd.c
# Source files (Add all C files from different directories)
SRC = main.c $(GPIO) $(USART) $(CHAR_LCD)

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
