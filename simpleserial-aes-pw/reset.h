#ifndef   __AVR_RESET_H
#define   __AVR_RESET_H

#if (PLATFORM == CW303) || (PLATFORM == CW301_XMEGA)
void soft_reset(void);

#else  // PLATFORM

#include <avr/wdt.h>

// A soft reset is achieved through the use of the watchdog timer.
#define soft_reset()     \
do                       \
{                        \
  wdt_enable(WDTO_15MS); \
  for(;;);               \
} while(0)

// On newer AVRs we need to disable the watchdog timer immediately after boot.
void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

#endif // PLATFORM

#endif // __AVR_RESET_H