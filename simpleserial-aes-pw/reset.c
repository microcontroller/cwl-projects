#include <stdio.h>
#include <avr/interrupt.h>
#include "reset.h"

#if (PLATFORM == CW303) || (PLATFORM == CW301_XMEGA)

#define RST_SWRST_bm 0x01
#define CCP_IOREG_gc (0xD8<<0)

void soft_reset(void)
{
  CCP = (uint8_t)CCP_IOREG_gc;
  RST.CTRL = (uint8_t)RST_SWRST_bm;
}

#else  // PLATFORM

void wdt_init(void)
{
  MCUSR = 0;
  wdt_disable();
  return;
}

#endif // PLATFORM
