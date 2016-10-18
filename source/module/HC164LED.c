/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/


#include "HC164LED.h"


uchar LED_show_buff[4] = {1,2,3,4};


uchar LED_table[] = { 
 
                0x03,  //"0"
                0x9F,  //"1"
                0x25,  //"2"
                0x0D,  //"3"
                0x99,  //"4"
                0x49,  //"5"
                0x41,  //"6"
                0x1F,  //"7"
                0x01,  //"8"
                0x09,  //"9"
                0x11,  //"A"
                0xC1,  //"B"
                0x63,  //"C"
                0x85,  //"D"
                0x61,  //"E"
                0x71,  //"F"
                0x91,  //"H"
                0xE3,  //"L"
                0x13,  //"n"
                0x83,  //"u"
                0x31,  //"P"
                0xC5,  //"o"
                0xFD,  //"-"
                0xFF,  //Ï¨Ãð
                0xFF  //×Ô¶¨Òå
 
                         };

                         
                      

void send_data_to_HC164(uchar data)
{
    uchar tmp=0x00,i=0,a=0;
    for (i = 0;i<=7;i++)
    {
        tmp = ((data >> i)&0x01);
        lsdata = tmp;
        a++;
        a++;
        lsclk = 1;
        a++;
        a++;
        lsclk = 0;
        
    }
}





void LED_show(void)
{
    lsclk = 0;
     
	bit0 = 0;
    send_data_to_HC164(LED_table[LED_show_buff[0]]);
    bit0 = 0;
    Delayms(1);
    bit0 = 1;
    
   
    send_data_to_HC164(LED_table[LED_show_buff[1]]);
    bit1 = 0;
    Delayms(1);
    bit1 = 1;

    
    send_data_to_HC164(LED_table[LED_show_buff[2]]);
    bit2 = 0;
    Delayms(1);
    bit2 = 1;
    
    send_data_to_HC164(LED_table[LED_show_buff[3]]);
    bit3 = 0;
    Delayms(1);
    bit3 = 1;
    
}


void LED_reflash(uint num)
{
    LED_show_buff[0] = num/1000;
    LED_show_buff[1] = num%1000/100;
    LED_show_buff[2] = num%1000%100/10;
    LED_show_buff[3] = num%1000%100%10;
}


