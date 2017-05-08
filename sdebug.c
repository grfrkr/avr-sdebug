#ifdef USE_SDEBUG

#include "sdebug.h"

#define SDEBUG_TICK		(F_CPU/SDEBUG_BPS)
#define SDEBUG_DELAY_BIT	{ __builtin_avr_delay_cycles(SDEBUG_TICK); }
#define SDEBUG_SETUP		{ SDEBUG_DDR |= (1<<SDEBUG_BIT); }
#define SDEBUG_TX0		{ SDEBUG_IO &= ~(1<<SDEBUG_BIT); }
#define SDEBUG_TX1		{ SDEBUG_IO |= (1<<SDEBUG_BIT); }

// send a single byte
void sdebug_putc(uint8_t data)
{
  uint8_t bit;

  cli();
  SDEBUG_SETUP;

// pull high
  SDEBUG_TX1;
  SDEBUG_DELAY_BIT;

// start bit
  SDEBUG_TX0;
  SDEBUG_DELAY_BIT;

// data bits
  for(bit=0;bit<8;bit++)
  {
    if (data & 0x01)
    {
      SDEBUG_TX1;
    }
    else
    {
      SDEBUG_TX0;
    }
    data >>= 1;
    SDEBUG_DELAY_BIT;
  }

// stop bit
  SDEBUG_TX1;
  SDEBUG_DELAY_BIT;

  sei();
}


// print a constant string stored in EEPROM
void sdebug_print(const char *string)
{
  unsigned char symbol;
  while((symbol = pgm_read_byte(&(*string++))))
  {
    if(symbol == '\n')
      sdebug_putc('\r');
    sdebug_putc(symbol);
  }
}


// print a string stored in RAM
void sdebug_prints(char *string)
{
  while(*string)
    sdebug_putc(*string++);
}


#ifdef SDEBUG_ENABLE_PRINTX8
// print 8-bit hexadecimal number
void sdebug_printx8(uint8_t data)
{
  const char* hexdigits = PSTR("0123456789ABCDEF");
  sdebug_putc(pgm_read_byte(hexdigits+(data>>4)));
  sdebug_putc(pgm_read_byte(hexdigits+(data&0x0F)));
}

#ifdef SDEBUG_ENABLE_PRINTX16
// print 16-bit hexadecimal number
void sdebug_printx16(uint16_t data)
{
  sdebug_printx8(data>>8);
  sdebug_printx8(data&0xFF);
}

#ifdef SDEBUG_ENABLE_PRINTX32
// print 32-bit hexadecimal number
void sdebug_printx32(uint32_t data)
{
  sdebug_printx16(data>>16);
  sdebug_printx16(data&0xFFFF);
}
#endif // SDEBUG_ENABLE_PRINTX32
#endif // SDEBUG_ENABLE_PRINTX16
#endif // SDEBUG_ENABLE_PRINTX8


#ifdef SDEBUG_ENABLE_PRINTD
// print decimal number
void sdebug_printd(uint32_t data)
{
  uint32_t divisor;
  uint8_t value;
  if (!data)
  {
    sdebug_putc('0');
    return;
  }
  for(divisor = 1000000000; divisor > data; divisor /= 10);
  for(; divisor > 0; divisor/=10)
  {
    value = (uint8_t)(data/divisor);
    data -= (divisor*value);
    sdebug_putc(value | '0');
  }
}
#endif // SDEBUG_ENABLE_PRINTD

#endif // USE_SDEBUG
