#ifndef __SDEBUG_CONFIG_H__
#define __SDEBUG_CONFIG_H__

#ifndef __SDEBUG_H__
#error "Please include sdebug.h instead of this file"
#endif


/*
  Debug pin; look at the datasheet and choose one.
  PD7 is good for ATmega8A/ATmega328P in PDIP-28
  PB4 is good for ATtiny13A/ATtiny85 in PDIP-8 or SOIC-8
*/

#ifndef SDEBUG_PORT
#define SDEBUG_PORT	D
#endif

#ifndef SDEBUG_BIT
#define SDEBUG_BIT	7
#endif


/*
  To ensure sync, we disable interrupts during the transmission.
  At 9600 bps every single byte is transmitted in 1 ms, which is
  acceptable for most applications while still allows the use of
  lower CPU frequencies. 19200 and 38400 bps may work better for
  higher frequencies.

  Don't change unless really necessary. See sdebug.c for details.
*/

#ifndef SDEBUG_BPS
#define SDEBUG_BPS	9600
#endif


/*
  Define these if you want to print hexadecimal numbers. Please
  note that SDEBUG_ENABLE_PRINTX16 implies SDEBUG_ENABLE_PRINTX8
  and SDEBUG_ENABLE_PRINTX32 implies SDEBUG_ENABLE_PRINTX16 - so
  #define SDEBUG_ENABLE_PRINTX32
  will include code for all 3 functions.
*/

// #define SDEBUG_ENABLE_PRINTX8
#define SDEBUG_ENABLE_PRINTX16
// #define SDEBUG_ENABLE_PRINTX32


/*
  Define this if you have enough EEPROM space and want to print
  decimal values as well. See sdebug.h and sdebug.c for details.

  Slow! :-/
*/

// #define SDEBUG_ENABLE_PRINTD

#endif // __SDEBUG_CONFIG_H__
