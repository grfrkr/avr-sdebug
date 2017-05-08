#ifndef __SDEBUG_H__
#define __SDEBUG_H__

/*
  Define USE_SDEBUG when debugging (example: -DUSE_SDEBUG in Makefile)
  Leave it undefined for production build
*/
#ifdef USE_SDEBUG

#include "sdebug_config.h"

/*
  Define F_CPU before including this file
  (example: -DF_CPU=8000000UL in Makefile)
*/
#ifndef F_CPU
#error F_CPU undefined - unable to calculate serial port timings
#endif

#include <stdint.h>
#include <avr/builtins.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define SDBG_CONC(x, y)		x ## y

#define SDBG_MKIO(p)		SDBG_CONC(PORT, p)
#define SDBG_MKDDR(p)		SDBG_CONC(DDR, p)

#define SDEBUG_IO		SDBG_MKIO(SDEBUG_PORT)
#define SDEBUG_DDR		SDBG_MKDDR(SDEBUG_PORT)

// for sdebug_print()
#define EOL			PSTR("\n")

// prototypes
void sdebug_putc(uint8_t);
void sdebug_print(const char *);
void sdebug_prints(char *);

#if (defined SDEBUG_ENABLE_PRINTX32 && ! defined SDEBUG_ENABLE_PRINTX16)
#define SDEBUG_ENABLE_PRINTX16
#endif

#if (defined SDEBUG_ENABLE_PRINTX16 && ! defined SDEBUG_ENABLE_PRINTX8)
#define SDEBUG_ENABLE_PRINTX8
#endif

#ifdef SDEBUG_ENABLE_PRINTX8
void sdebug_printx8(uint8_t);
#define sdebug_printvarx8(x)	{sdebug_print(PSTR(#x " = 0x")); sdebug_printx8(x); sdebug_print(EOL); }
#ifdef SDEBUG_ENABLE_PRINTX16
void sdebug_printx16(uint16_t);
#define sdebug_printvarx16(x)	{sdebug_print(PSTR(#x " = 0x")); sdebug_printx16(x); sdebug_print(EOL); }
#ifdef SDEBUG_ENABLE_PRINTX32
void sdebug_printx32(uint32_t);
#define sdebug_printvarx32(x)	{sdebug_print(PSTR(#x " = 0x")); sdebug_printx32(x); sdebug_print(EOL); }
#else // SDEBUG_ENABLE_PRINTX32
#define sdebug_printx32(x)	{}
#define sdebug_printvarx32(x)	{}
#endif // SDEBUG_ENABLE_PRINTX32
#else // SDEBUG_ENABLE_PRINTX16
#define sdebug_printx16(x)	{}
#define sdebug_printvarx16(x)	{}
#endif // SDEBUG_ENABLE_PRINTX16
#else // SDEBUG_ENABLE_PRINTX8
#define sdebug_printx8(x)	{}
#define sdebug_printvarx8(x)	{}
#endif // SDEBUG_ENABLE_PRINTX8

#ifdef SDEBUG_ENABLE_PRINTD
void sdebug_printd(uint32_t);
#define sdebug_printvard(x)	{sdebug_print(PSTR(#x " = ")); sdebug_printd(x); sdebug_print(EOL); }
#else // SDEBUG_ENABLE_PRINTD
#define sdebug_printd(x)	{}
#define sdebug_printvard(x)	{}
#endif // SDEBUG_ENABLE_PRINTD

#else // USE_SDEBUG

#define sdebug_putc(x)		{}
#define sdebug_print(x)		{}
#define sdebug_prints(x)	{}

#define sdebug_printx8(x)	{}
#define sdebug_printx16(x)	{}
#define sdebug_printx32(x)	{}

#define sdebug_printd(x)	{}

#define sdebug_printvarx8(x)	{}
#define sdebug_printvarx16(x)	{}
#define sdebug_printvarx32(x)	{}
#define sdebug_printvard(x)	{}

#endif // USE_SDEBUG

#endif // __SDEBUG_H__
