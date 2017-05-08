#!/usr/bin/make -f

PROJ		= sdebug_example


# for avr-gcc
MCU		= atmega328p


# for avrdude
CHIP		= m328p
PROGTOOL	= avrdude -c usbasp -P usb:16c0:05dc -p $(CHIP)
# http://www.engbedded.com/fusecalc/
LFUSE		= 0xE2
# be careful when changing HFUSE and EFUSE
# (don't change them unless you know what you do)
HFUSE		= 0xD9
EFUSE		= 0xFF


CC		= avr-gcc
CFLAGS		= -Wall -Wno-pointer-sign -Wno-main -O2 \
		  -mmcu=$(MCU) \
		  -DUSE_SDEBUG -DSDEBUG_BPS=38400 -DF_CPU=8000000UL
LD		= avr-gcc
LDFLAGS		= -s -static
OBJCPBIN	= avr-objcopy -j .text -j .data -O binary
OBJCPHEX	= avr-objcopy -j .text -j .data -O ihex
RM		= rm -f


SRC		= \
		sdebug.c \
		main.c
ELF		= $(PROJ).elf
BIN		= $(PROJ).bin
HEX		= $(PROJ).hex


all:		hex

flash:		hex
		$(PROGTOOL) \
		-U flash:w:$(HEX):i \
		-U lfuse:w:$(LFUSE):m \
		-U hfuse:w:$(HFUSE):m \
		-U efuse:w:$(EFUSE):m

hex:		$(ELF)
		$(OBJCPHEX) $(ELF) $(HEX)
		$(RM) $(ELF)

bin:		$(ELF)
		$(OBJCPBIN) $(ELF) $(BIN)
		$(RM) $(ELF)

clean:
		$(RM) $(ELF) $(HEX) $(BIN)


$(ELF):
		$(CC) $(CFLAGS) $(SRC) -o $(ELF) $(LDFLAGS)
