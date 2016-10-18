/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "mytimer.h"

UINT16 Time0out;
UINT16 Time1out;
UINT16 Time2out;

/****************************************
*��������:TMR0Init
*��    ��:��
*��    ��:��
*��    ��:��ʱ��0��ʼ��
******************************************/
void Init_TMR0(void)
{
    PROTECT_REG
	(
	  APBCLK |= TMR0_CLKEN;		//ʹ��TMR0ʱ��Դ 
		CLKSEL1 = (CLKSEL1 & (~TM0_CLK)) | TM0_22M;// ѡ��TMR0ʱ��ԴΪ�ڲ�22MHz

		//��λTMR0
		IPRSTC2 |=  TMR0_RST;
		IPRSTC2 &= ~TMR0_RST;
	
		//ѡ��TMR1�Ĺ���ģʽΪ����ģʽ	
		TCSR0 &= ~TMR_MODE;
		TCSR0 |=  MODE_PERIOD;		
		
		/* ������� = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
		TCSR0  = TCSR0 & 0xFFFFFF00;		// ����Ԥ��Ƶֵ [0~255] 

		TCSR0 |= TMR_IE;					//ʹ��TMR0�ж�
		NVIC_ISER |= TMR0_INT;	 
	)
}
/****************************************
*��������:TMR1Init
*��    ��:��
*��    ��:��
*��    ��:��ʱ��1��ʼ��
******************************************/
void Init_TMR1(void)
{
    PROTECT_REG
	(
	  APBCLK |= TMR1_CLKEN;		//ʹ��TMR1ʱ��Դ 
		CLKSEL1 = (CLKSEL1 & (~TM1_CLK)) | TM1_22M;// ѡ��TMR1ʱ��ԴΪ�ڲ�22MHz

		//��λTMR1
		IPRSTC2 |=  TMR1_RST;
		IPRSTC2 &= ~TMR1_RST;
	
		//ѡ��TMR1�Ĺ���ģʽΪ����ģʽ	
		TCSR1 &= ~TMR_MODE;
		TCSR1 |=  MODE_PERIOD;		
		
		/* ������� = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
		TCSR1  = TCSR1 & 0xFFFFFF00;		// ����Ԥ��Ƶֵ [0~255] 

		TCSR1 |= TMR_IE;					//ʹ��TMR1�ж�
		NVIC_ISER |= TMR1_INT;	 
	)
}

/****************************************
*��������:Init_TMR2
*��    ��:��
*��    ��:��
*��    ��:��ʱ��2��ʼ��
******************************************/
void Init_TMR2(void)
{
    PROTECT_REG
	(
        APBCLK |= TMR2_CLKEN;		//ʹ��TMR2ʱ��Դ 
        CLKSEL1 = (CLKSEL1 & (~TM2_CLK)) | TM2_22M;// ѡ��TMR2ʱ��ԴΪ�ڲ�22MHz

        //��λTMR2
        IPRSTC2 |=  TMR2_RST;
        IPRSTC2 &= ~TMR2_RST;

        //ѡ��TMR2�Ĺ���ģʽΪ����ģʽ	
        TCSR2 &= ~TMR_MODE;
        TCSR2 |=  MODE_PERIOD;

        /* ������� = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
        TCSR2  = TCSR2 & 0xFFFFFF00;		// ����Ԥ��Ƶֵ [0~255] 

        TCSR2 |= TMR_IE; //ʹ��TMR2�ж�
        NVIC_ISER |= TMR2_INT;	 
	)
}
/****************************************
*��������:StarTime0
*��    ��:time  ��ʱʱ��  ��λ����
*��    ��:��
*��    ��:������ʱ��0
******************************************/
void StarTime0(UINT16 time)
{
	Time0out = 0; 
	TCMPR0 = 22*time;		// ���ñȽ�ֵ [0~16777215]
	TCSR0 |= CRST;					//��λTMR0������				
	TCSR0 |= CEN;						//ʹ��TMR0  
}

/****************************************
*��������:StarTime1
*��    ��:time  ��ʱʱ��  ��λ����
*��    ��:��
*��    ��:������ʱ��1
******************************************/
void StarTime1(UINT16 time)
{
	Time1out = 0; 
	TCMPR1 = 22*time;		// ���ñȽ�ֵ [0~16777215]
	TCSR1 |= CRST;					//��λTMR1������				
	TCSR1 |= CEN;						//ʹ��TMR1
}


/****************************************
*��������:StarTime2
*��    ��:time  ��ʱʱ��
*��    ��:��
*��    ��:������ʱ��2  10us����
******************************************/
void StarTime2(UINT16 time)
{
	Time2out = 0; 
	TCMPR2 = 22*time;		// ���ñȽ�ֵ [0~16777215]  
	TCSR2 |= CRST;					//��λTMR2������				
	TCSR2 |= CEN;						//ʹ��TMR2  
}
/****************************************
*��������:StopTime0
*��    ��:��
*��    ��:��
*��    ��:�رն�ʱ��0
******************************************/
void StopTime0(void)
{
	TCSR0 |= CRST;		//��λTMR0������				
	TCSR0 &= ~CEN;		//�ر�TMR0 
	Time0out = 0;
} 

/****************************************
*��������:StopTime1
*��    ��:��
*��    ��:��
*��    ��:�رն�ʱ��1
******************************************/
void StopTime1(void)
{
	TCSR1 |= CRST;		//��λTMR1������				
	TCSR1 &= ~CEN;		//�ر�TMR1 
	Time1out = 0;
}  

/****************************************
*��������:StopTime2
*��    ��:��
*��    ��:��
*��    ��:�رն�ʱ��2
******************************************/
void StopTime2(void)
{
    TCSR2 |= CRST;		//��λTMR2������				
    TCSR2 &= ~CEN;		//�ر�TMR2 
    Time2out = 0;
} 

/****************************************
*��������:Delayms
*��    ��:��
*��    ��:��
*��    ��:ϵͳʱ��΢����ʱ
******************************************/ 
void Delayus(uint32_t unCnt)
{
    SYST_RVR = unCnt*22;
    SYST_CVR = 0;
    SYST_CSR |=1UL<<0;

    while((SYST_CSR & 1UL<<16)==0); 
}

 
/****************************************
*��������:Delayms
*��    ��:��
*��    ��:��
*��    ��:ϵͳʱ�Ӻ�����ʱ
******************************************/ 
void Delayms(uint32_t DelayTime)
{
 
    SYST_RVR = DelayTime*22000;
    SYST_CVR = 0;
    SYST_CSR |=1UL<<0;
  
    while((SYST_CSR & 1UL<<16)==0);  
}


/****************************************
*��������:TMR0_IRQHandler
*��    ��:��
*��    ��:��
*��    ��:��ʱ��0�жϷ�����
******************************************/
VOID TMR0_IRQHandler(VOID)
{
	//���TMR0�жϱ�־λ
	TISR0 |= TMR_TIF; 
	Time0out++;
}
 
/****************************************
*��������:TMR1_IRQHandler
*��    ��:��
*��    ��:��
*��    ��:��ʱ��1�жϷ�����
******************************************/  
VOID TMR1_IRQHandler(VOID)
{
	//���TMR1�жϱ�־λ
	TISR1 |= TMR_TIF; 
    Time1out++;
}

/****************************************
*��������:TMR2_IRQHandler
*��    ��:��
*��    ��:��
*��    ��:��ʱ��2�жϷ�����
******************************************/ 

VOID TMR2_IRQHandler(VOID)
{
	//���TMR2�жϱ�־λ
	TISR2 |= TMR_TIF;  
    Time2out++;
}

