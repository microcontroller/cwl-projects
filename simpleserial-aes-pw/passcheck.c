/*
    This file is part of an example target for the ChipWhisperer family
    Copyright (C) 2015 Patrick Henry <syntactic.net@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uart.h"
#include <stdint.h>
#include "passcheck.h"
#include "hal.h"

static uint8_t password[256] = DEFAULT_PW;
static uint8_t passwlen      = DEFAULT_PW_LEN;
static uint8_t received[256] = {0,};
static uint8_t n_received    = 0;

uint8_t read_pass()
{
  for(uint8_t inchar = getch(); inchar != 0 && inchar != 0xa && inchar != 0xd; inchar = getch())
  {
#if PASS_VULN_TRIVIAL
    if (n_received >= passwlen || inchar != password[n_received])
    {
      putch(n_received);
      putch(inchar);
      putch(password[n_received]);
      return 1;
    }
    n_received++;
#else
    received[n_received++] = inchar;
#endif
  }
  return 0;
}

uint8_t test_pass()
{
#if PASS_VULN_TRIVIAL
  // This function not necessary
  return n_received != passwlen;
#else
  uint8_t result = 0;
  
  if (n_received != passwlen)
  {
#if PASS_VULN_EASY
    return 1;
#else
    result |= 1;
#endif
  }
  for(uint8_t ii = 0; ii < n_received; ii++)
  {
    if (received[ii] != password[ii])
    {
#if PASS_VULN_EASY
      return 2;
#else
      result |= 2;
#endif
    }
  }
  return result;
#endif
}
