/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__

#include "common.h"


#define set_ADST        		ADCR |= ADST				// Start A/D convert 
#define clr_ADST        		ADCR &= ~ADST				// Stop A/D convert
#define set_DIFFEN      		ADCR |= DIFFEN				// A/D is in differential analog input mode
#define clr_DIFFEN      		ADCR &= ~DIFFEN				// A/D is in single-end analog input mode
#define set_TRGE        		ADCR |= TRGE_EN				// External trigger enable
#define clr_TRGE        		ADCR &= ~TRGE_EN			// External trigger disable

#define setAD_SIG				{ADCR &= ~ADMD;\
								 ADCR |= MD_SIG; }			// Set AD converter single mode
#define setAD_BURST				{ADCR &= ~ADMD;\
								 ADCR |= MD_BURST; }		// Set AD converter burst mode
#define setAD_SIGSCAN			{ADCR &= ~ADMD;\
								 ADCR |= MD_SIG_SCN; }		// Set AD converter single scan mode
#define setAD_CONSCAN			{ADCR &= ~ADMD;\
								 ADCR |= MD_CON_SCN; }		// Set AD converter continuous scan mode

#define set_ADIE        		ADCR |= ADIE				// Enable ADC interrupt
#define clr_ADIE        		ADCR &= ~ADIE				// Disable ADC interrupt
#define set_ADEN        		ADCR |= ADEN				// Enable AD Converter
#define clr_ADEN        		ADCR &= ~ADEN				// Disable AD Converter
															
#define set_ADC_RST     		IPRSTC2 |= ADC_RST          // ADC block reset        		                        		
#define clr_ADC_RST     		IPRSTC2 &= ~ADC_RST			// ADC block normal operation

#define set_ADEN_CLK			APBCLK |= ADC_CLKEN			// Enable ADC clock
#define clr_ADEN_CLK			APBCLK &= ~ADC_CLKEN		// Disable ADC clock

#define set_ADC7_channel    	{P1_MFP &= ~P17_AIN7_SPI0CLK;\
								 P1_MFP |= AIN7;	}		// Set P17 as ADC7 input
#define set_ADC6_channel    	{P1_MFP &= ~P16_AIN6_SPI0MISO;\
								 P1_MFP |= AIN6;	}		// Set P16 as ADC6 input
#define set_ADC5_channel    	{P1_MFP &= ~P15_AIN5_SPI0MOSI;\
								 P1_MFP |= AIN5;	}		// Set P15 as ADC5 input
#define set_ADC4_channel    	{P1_MFP &= ~P14_AIN4_SPI0SS;\
								 P1_MFP |= AIN4;	}		// Set P14 as ADC4 input
#define set_ADC3_channel    	{P1_MFP &= ~P13_AIN3_TXD1;\
								 P1_MFP |= AIN3;	}		// Set P13 as ADC3 input
#define set_ADC2_channel    	{P1_MFP &= ~P12_AIN2_RXD1;\
								 P1_MFP |= AIN2;	}		// Set P12 as ADC2 input
#define set_ADC1_channel    	{P1_MFP &= ~P11_AIN1_T3;\
								 P1_MFP |= AIN1;	}		// Set P11 as ADC1 input
#define set_ADC0_channel    	{P1_MFP &= ~P10_AIN0_T2;\
								 P1_MFP |= AIN0;	}		// Set P10 as ADC0 input
                            	
#define set_ADF     			ADSR |= ADF					// Clear A/D Conversion End Flag
  
#define P10_InputOnly   	{P1_PMD &= ~Px0_PMD; \
                            	 P1_PMD |= Px0_IN; }		// Set P1.0 input mode
#define P10_Output      	{P1_PMD &= ~Px0_PMD; \
                            	 P1_PMD |= Px0_OUT; }		// Set P1.0 output mode
#define P10_OpenDrain   	{P1_PMD &= ~Px0_PMD; \
                            	 P1_PMD |= Px0_OD; }		// Set P1.0 open-drain mode
#define P10_Qusci       	{P1_PMD &= ~Px0_PMD; \
                            	 P1_PMD |= Px0_QB; }    	// Set P1.0 Quasi-bidirectional mode
								 
#define P11_InputOnly   	{P1_PMD &= ~Px1_PMD; \
                            	 P1_PMD |= Px1_IN; }		// Set P1.1 input mode
#define P11_Output      	{P1_PMD &= ~Px1_PMD; \
                            	 P1_PMD |= Px1_OUT; }		// Set P1.1 output mode
#define P11_OpenDrain   	{P1_PMD &= ~Px1_PMD; \
                            	 P1_PMD |= Px1_OD; }		// Set P1.1 open-drain mode
#define P11_Qusci       	{P1_PMD &= ~Px1_PMD; \
                            	 P1_PMD |= Px1_QB; }    	// Set P1.1 Quasi-bidirectional mode

#define P12_InputOnly   	{P1_PMD &= ~Px2_PMD; \
                            	 P1_PMD |= Px2_IN; }	   	// Set P1.2 input mode
#define P12_Output      	{P1_PMD &= ~Px2_PMD; \
                            	 P1_PMD |= Px2_OUT; }		// Set P1.2 output mode
#define P12_OpenDrain   	{P1_PMD &= ~Px2_PMD; \
                            	 P1_PMD |= Px2_OD; }		// Set P1.2 open-drain mode
#define P12_Qusci       	{P1_PMD &= ~Px2_PMD; \
                            	 P1_PMD |= Px2_QB; }     	// Set P1.2 Quasi-bidirectional mode 

#define P13_InputOnly   	{P1_PMD &= ~Px3_PMD; \
                            	 P1_PMD |= Px3_IN; }		// Set P1.3 input mode
#define P13_Output      	{P1_PMD &= ~Px3_PMD; \
                            	 P1_PMD |= Px3_OUT; }		// Set P1.3 output mode
#define P13_OpenDrain   	{P1_PMD &= ~Px3_PMD; \
                            	 P1_PMD |= Px3_OD; }		// Set P1.3 open-drain mode
#define P13_Qusci       	{P1_PMD &= ~Px3_PMD; \
                            	 P1_PMD |= Px3_QB; } 		// Set P1.3 Quasi-bidirectional mode							                     

#define P14_InputOnly   	{P1_PMD &= ~Px4_PMD; \
                            	 P1_PMD |= Px4_IN; }		// Set P1.4 input mode
#define P14_Output      	{P1_PMD &= ~Px4_PMD; \
                            	 P1_PMD |= Px4_OUT; }		// Set P1.4 output mode
#define P14_OpenDrain   	{P1_PMD &= ~Px4_PMD; \
                            	 P1_PMD |= Px4_OD; }		// Set P1.4 open-drain mode
#define P14_Qusci       	{P1_PMD &= ~Px4_PMD; \
                            	 P1_PMD |= Px4_QB; } 		// Set P1.4 Quasi-bidirectional mode

#define P15_InputOnly   	{P1_PMD &= ~Px5_PMD; \
                            	 P1_PMD |= Px5_IN; }		// Set P1.5 input mode
#define P15_Output      	{P1_PMD &= ~Px5_PMD; \
                            	 P1_PMD |= Px5_OUT; }		// Set P1.5 output mode
#define P15_OpenDrain   	{P1_PMD &= ~Px5_PMD; \
                            	 P1_PMD |= Px5_OD; }		// Set P1.5 open-drain mode
#define P15_Qusci       	{P1_PMD &= ~Px5_PMD; \
                            	 P1_PMD |= Px5_QB; } 		// Set P1.5 Quasi-bidirectional mode

#define P16_InputOnly   	{P1_PMD &= ~Px6_PMD; \
                            	 P1_PMD |= Px6_IN; }		// Set P1.6 input mode
#define P16_Output      	{P1_PMD &= ~Px6_PMD; \
                            	 P1_PMD |= Px6_OUT; }		// Set P1.6 output mode
#define P16_OpenDrain   	{P1_PMD &= ~Px6_PMD; \
                            	 P1_PMD |= Px6_OD; }		// Set P1.6 open-drain mode
#define P16_Qusci       	{P1_PMD &= ~Px6_PMD; \
                            	 P1_PMD |= Px6_QB; } 		// Set P1.6 Quasi-bidirectional mode

#define P17_InputOnly   	{P1_PMD &= ~Px7_PMD; \
                            	 P1_PMD |= Px7_IN; }		// Set P1.7 input mode
#define P17_Output      	{P1_PMD &= ~Px7_PMD; \
                            	 P1_PMD |= Px7_OUT; }		// Set P1.7 output mode
#define P17_OpenDrain   	{P1_PMD &= ~Px7_PMD; \
                            	 P1_PMD |= Px7_OD; }		// Set P1.7 open-drain mode
#define P17_Qusci       	{P1_PMD &= ~Px7_PMD; \
                            	 P1_PMD |= Px7_QB; } 		// Set P1.7 Quasi-bidirectional mode

#define set_CHEN0     	 		ADCHER |= CHEN0				// Enable Analog input channel 0
#define set_CHEN1     	 		ADCHER |= CHEN1				// Enable Analog input channel 1
#define set_CHEN2     	 		ADCHER |= CHEN2				// Enable Analog input channel 2
#define set_CHEN3     	 		ADCHER |= CHEN3				// Enable Analog input channel 3
#define set_CHEN4     	 		ADCHER |= CHEN4				// Enable Analog input channel 4
#define set_CHEN5     	 		ADCHER |= CHEN5				// Enable Analog input channel 5
#define set_CHEN6     	 		ADCHER |= CHEN6				// Enable Analog input channel 6
#define set_CHEN7     	 		ADCHER |= CHEN7				// Enable Analog input channel 7


#define clr_CHEN0   			ADCHER &= ~CHEN0			// Disable Analog input channel 0
#define clr_CHEN1   			ADCHER &= ~CHEN1			// Disable Analog input channel 1
#define clr_CHEN2   			ADCHER &= ~CHEN2			// Disable Analog input channel 2
#define clr_CHEN3   			ADCHER &= ~CHEN3			// Disable Analog input channel 3
#define clr_CHEN4   			ADCHER &= ~CHEN4			// Disable Analog input channel 4
#define clr_CHEN5   			ADCHER &= ~CHEN5			// Disable Analog input channel 5
#define clr_CHEN6   			ADCHER &= ~CHEN6			// Disable Analog input channel 6
#define clr_CHEN7   			ADCHER &= ~CHEN7			// Disable Analog input channel 7

#define set_CALEN     	 		ADCALR |= CALEN				// Enable ADC self calibration
#define set_CALDONE      		ADCALR |= CALDONE			// Calibration Trigger
#define clr_CALEN   			ADCALR &= ~CALEN			// Disable ADC self calibration
#define clr_CALDONE  			ADCALR &= ~CALDONE			// When 0 is written to CALEN bit, CALDONE bit is cleared by hardware immediately

#define setCH7_ADC7				{ADCHER &= ~CH7_MODE;\
								 ADCHER |= CH7_ADC7; }		// Set ADC channel 7 as ADC7 input
#define setCH7_VBGI				{ADCHER &= ~CH7_MODE;\
								 ADCHER |= CH7_VBGI; }		// Set ADC channel 7 as Bandgap (VBG) Analog Input

// Select ADC clock source as external 12M Crystal
#define ADCClkSource_ex12MHZ	(CLKSEL1 = ((CLKSEL1 & (~ADC_CLK)) | ADC_12M))

// Select ADC clock source as PLL output	
#define ADCClkSource_PLL		(CLKSEL1 = ((CLKSEL1 & (~ADC_CLK)) | ADC_PLL))

// Select ADC clock source as internal 22M Oscillator		
#define ADCClkSource_int22MHZ	(CLKSEL1 = ((CLKSEL1 & (~ADC_CLK)) | ADC_22M))	







void Init_ADC(void);
uint start_ADC(void);



#endif

