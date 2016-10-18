#ifndef __HC164LED_H__
#define __HC164LED_H__


#include "../framework/include.h"

#define bit0            P00_DOUT
#define bit1            P01_DOUT
#define bit2            P02_DOUT
#define bit3            P03_DOUT
#define lsclk           P05_DOUT 
#define lsdata          P04_DOUT   


void send_data_to_HC164(uchar data);
void LED_show(void);
void LED_reflash(uint num);

#endif

