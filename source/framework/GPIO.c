/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/


#include "GPIO.h"



/****************************************
*函数名称:init_GPIO
*输    入:无
*输    出:无
*功    能:通用输入输出初始化
******************************************/
void Init_GPIO(void)
{
	GPIO_set(0,0,1);				   
	GPIO_set(0,1,1);                    
    GPIO_set(0,2,1);  
	GPIO_set(0,3,1);				   
	GPIO_set(0,4,1);                    
    GPIO_set(0,5,1);  
	
	bit_set(0,1,1);

}

/****************************************
*函数名称:GPIO_set
*输    入:uchar port,uchar bit,uchar direct
*输    出:无
*功    能:设置某一位通用IO的方向
******************************************/

void GPIO_set(uchar port,uchar bit,uchar direct)
{
    if (direct == 1)
    {
        switch(port)
        {
            case 0:
				P0_PMD &= ~(0x03<<(bit*2));
                P0_PMD |= (0x01<<(bit*2));
                break;
			
			case 1:
				P1_PMD &= ~(0x03<<(bit*2));
                P1_PMD |= (0x01<<(bit*2));
                break;
            
            case 2:
                P2_PMD &= ~(0x03<<(bit*2));
                P2_PMD |= (0x01<<(bit*2));
				break;
			
			case 3:
                P3_PMD &= ~(0x03<<(bit*2));
                P3_PMD |= (0x01<<(bit*2));
				break;
            
            default:break;
        }
    }
    else if (direct == 0)
    {
        switch(port)
        {
            case 0:
				P0_PMD &= ~(0x03<<(bit*2));
                break;
			
			case 1:
				P1_PMD &= ~(0x03<<(bit*2));
                break;
            
            case 2:
                P2_PMD &= ~(0x03<<(bit*2));
				break;
			
			case 3:
                P3_PMD &= ~(0x03<<(bit*2));
				break;
            
            default:break;
        }
    }
}

/****************************************
*函数名称:bit_set
*输    入:uchar port,uchar bit,uchar value
*输    出:无
*功    能:设置某一位通用输出高低电平
******************************************/


void bit_set(uchar port,uchar bit,uchar value)
{
	if (value == 1)
    {
        switch(port)
        {
            case 0:
				P0_DOUT &= ~(1<<bit);
                P0_DOUT |= (1<<bit);
                break;
			
			case 1:
				P1_DOUT &= ~(1<<bit);
                P1_DOUT |= (1<<bit);
                break;
            
            case 2:
                P2_DOUT &= ~(1<<bit);
                P2_DOUT |= (1<<bit);
				break;
			
			case 3:
                P3_DOUT &= ~(1<<bit);
                P3_DOUT |= (1<<bit);
				break;
            
            default:break;
        }
    }
    else if (value == 0)
    {
        switch(port)
        {
            case 0:
				P0_DOUT &= ~(1<<bit);
                break;
			
			case 1:
				P1_DOUT &= ~(1<<bit);
                break;
            
            case 2:
                P2_DOUT &= ~(1<<bit);
				break;
			
			case 3:
                P3_DOUT &= ~(1<<bit);
				break;
            
            default:break;
        }
    }
}

/****************************************
*函数名称:bit_turn
*输    入:uchar port,uchar bit
*输    出:无
*功    能:转换某一位通用输出高低电平
******************************************/


void bit_turn(uchar port,uchar bit)
{
	uchar temp;
	switch(port)
	{
		case 0:
			temp = (P0_DOUT>>bit)&0x01;
			break;
		case 1:
			temp = (P1_DOUT>>bit)&0x01;
			break;
		case 2:
			temp = (P2_DOUT>>bit)&0x01;
			break;
		case 3:
			temp = (P3_DOUT>>bit)&0x01;
			break;
		
		default:break;
	}
	if(temp == 1)
	{
		bit_set(port,bit,0);
	}
	else if(temp == 0)
	{
		bit_set(port,bit,1);
	}
}


/****************************************
*函数名称:bit_get
*输    入:uchar port,uchar bit,uchar value
*输    出:无
*功    能:获取某一位通用输入高低电平
******************************************/


bool bit_get(uchar port,uchar bit)
{
    switch(port)
    {
        case 0:
			if((P0_PIN>>bit)&0x01)
            {
                return 1;
            }
            else
            {
                return 0;
            }
		case 1:
			if((P1_PIN>>bit)&0x01)
            {
                return 1;
            }
            else
            {
                return 0;
            }
		case 2:
			if((P2_PIN>>bit)&0x01)
            {
                return 1;
            }
            else
            {
                return 0;
            }
		case 3:
			if((P3_PIN>>bit)&0x01)
            {
                return 1;
            }
            {
                return 0;
            }
		default:break;
    }
    return 0;
}
