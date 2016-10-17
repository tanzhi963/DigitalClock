/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "ADC.h"

#define DEBUGMSG              printf
#define ADC_CLOCK_DIVIDER     0x00040000
#define ADC_CLK_Source        0x00000008
#define AREF_VOLTAGE          5000




void Init_ADC(void)
{
//     if(ADC_CLK_Source==0x00000004)
//     {
//         PLLCON |= PLL_SEL;
//         PLL_Enable();

// 		while((CLKSTATUS & PLL_STB) == 0);        //�ȴ�PLL�ȶ�
// 	} 
//    
//     set_ADC_RST;                                  //��λADC
//     clr_ADC_RST;
//       
//     set_ADEN_CLK;                                 //ADCʱ��ʹ��
//     if (ADC_CLK_Source==0x00000000 )
//     {
//         ADCClkSource_ex12MHZ;                     //ʹ��Ϊ�ⲿ12MHzʱ��
//     }
//     else if(ADC_CLK_Source==0x00000004 )
//     {
//         ADCClkSource_PLL;                          //ʹ��Ϊ���໷ʱ��
//     }
//     else if(ADC_CLK_Source==0x00000008 )
//     {
//         ADCClkSource_int22MHZ;                     //ʹ��Ϊ�ڲ�22MHzʱ��
//     }

//     CLKDIV=ADC_CLOCK_DIVIDER;                      //����ADC��Ƶ��
// 	 
//     set_ADEN;                                       //ADCʹ��
//     set_CALEN;			                            //��ʼADC��У׼

// 	while(!(ADCALR&CALDONE));                       //�ȴ���У׼���

//     setAD_SIG;                                      //����ת��ģʽ         
//     clr_DIFFEN;                                     //�������ģʽ

//     set_CHEN0;                                      //����ADCͨ��0
//     set_ADC0_channel;                               //ʹ��P1.0Ϊģ����������
// 	P1_OFFD |= OFFD0;                               //��ֹP1.0��������ͨ��
//     P10_InputOnly;                                  //����P1.0����Ϊ����ģʽConfigure P1.0 as input mode
//     set_ADF;  		                                //���ADC�жϱ�־λ  
//     
    
/*   set_ADEN_CLK;                                   // ADC block reset
    clr_ADEN_CLK;                                    // ADC block normal operation
    set_ADEN_CLK;
    
    
    
    ADCR &= ~DIFFEN;                                 //�رղ������ģʽ��������ģʽ
    ADCR &= ~TRGE_EN;                                //�ر��ⲿ����
    ADCR |= MD_CON_SCN;                              //�ɼ�ģʽ�������ɼ�ģʽ
    ADCR |= ADIE;                                    //�ж�ʹ��
    ADCR |= ADEN;                                    //��ADCģ�飨ת��ʹ�ܣ�*/

	IPRSTC2 |= ADC_RST;                        		//��λADC����
	IPRSTC2 &= ~ADC_RST;                        	//ADCģ��Ӹ�λ״̬�ָ�����������״̬
	APBCLK  |= ADC_CLKEN;                        	//ʹ��ADCʱ��
	CLKSEL1  = CLKSEL1 & (~ADC_CLK) | ADC_22M;  	//ѡ��Ȳ�������ΪADCʱ��Դ
	CLKDIV  |= 0x000f0000;                       	//ADCʱ��16��Ƶ
	ADCR    |= ADEN;                             	//ʹ��ADC
	ADCALR |= CALEN;                             	//ʹ��ADC��У�鹦��
	while(!(ADCALR & CALDONE));                  	//�ȴ�У�����
  
	setAD_CONSCAN;					//����ADC����ת��        
	clr_DIFFEN;							//�趨ADģ���ѹ����ģʽΪ��������
	set_CHEN0; 							//����ADCͨ��Ϊͨ��5 
	set_ADC0_channel;				//ʹ��P1.5Ϊģ���������� 
	P1_OFFD |= OFFD0;				//��ֹP1.5��������ͨ��
	P10_InputOnly; 					//����P1.5����Ϊ����ģʽ
	
	ADSR |= ADF;   					//���ADC�жϱ�־λ 

}

/*void enable_ADchannel(uchar ch)
{
    ADCHER |= CH7_VBGI;
    ADCHER |= (1<<ch);
}*/


uint start_ADC(void)
{

    uint unVoltageValue;
    
    set_ADST;  							        	  //����ADC
    while(ADSR&ADF==0);					        	  //�ȴ�ADC����
    set_ADF;							        	  //���ADC������־λ

    unVoltageValue = AREF_VOLTAGE*(ADDR0&0xFFF)/4096; //��ADCֵת��Ϊ��ѹֵ
    
    return unVoltageValue;
}



