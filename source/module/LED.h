#ifndef __LED_H__
#define __LED_H__


#include "../framework/include.h"

#define bit0            P00_DOUT
#define bit1            P01_DOUT
#define bit2            P02_DOUT
#define bit3            P03_DOUT
#define lsclk           P05_DOUT 
#define lsdata          P04_DOUT   


void senddatatohc164(uchar data);
void LEDshow(void);
void LED_reflash(uint num);

#endif

