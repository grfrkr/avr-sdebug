AVR serial debug

Use any pin of AVR microcontroller as a debugging output-only
serial interface.


Using the serial port for output of debugging information is
a common well-known solution, which is simple and convenient.
However, when the UART is used to communicate with an external
device (like modem), we need to use something else.

This library module alows using almost any pin of AVR family
microcontroller (both ATmega and ATtiny) as a output-only
serial interface for debugging purposes. It may bring some
side effects, as the program execution is halted for a
millisecond when transmitting every single byte, but that
shouldn't affect properly written programs.

Said that, here it is. See the LICENSE.txt if you care of
copyshit.
