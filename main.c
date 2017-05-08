#include <stdint.h>
#include <util/delay.h>
#include "sdebug.h"

void main(void)
{
  uint16_t count = 0;
  for(;;)
  {
    sdebug_printvarx16(count);
    _delay_ms(100);
    count++;
    if(!count)
    {
      sdebug_print(PSTR("Overflow!\n"));
    }
  }
}
