MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = COM10
BAUD = 115200

SRC = main.c
OBJ = $(SRC:.c=.o)
ELF = main.elf
HEX = main.hex

CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

all: $(HEX)

$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $< $@

$(ELF): $(OBJ)
	avr-gcc $(CFLAGS) -o $@ $<

%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<

upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):i

clean:
	rm -f $(OBJ) $(ELF) $(HEX)