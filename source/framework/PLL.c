/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "PLL.h"


/****************************************
*��������:Init_Clock
*��    ��:��
*��    ��:��
*��    ��:ʱ�ӳ�ʼ��
******************************************/
void Init_Clock(void)
{ 	
	 PROTECT_REG											//ISP����ʱ����FLASH�洢��
	 (  						                   
			PWRCON |= OSC22M_EN;//Ĭ��ʱ��ԴΪ�ڲ�����
			while((CLKSTATUS & OSC22M_STB) == 0); 		//�ȴ�22MHzʱ���ȶ�	
		  
			PWRCON |= OSC10K_EN;		// ʹ���ڲ�10Kʱ�� 
			while((CLKSTATUS & OSC10K_STB) == 0); // �ȴ�10Kʱ���ȶ� 
			
			CLKSEL0 = (CLKSEL0 & (~HCLK)) | HCLK_22M;	//�����ڲ�����Ϊϵͳʱ�� 
	 ) 
}


