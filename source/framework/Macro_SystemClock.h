/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                               */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/
#ifndef __MACRO_SYSTEMCLOCK_H__
#define __MACRO_SYSTEMCLOCK_H__

#define TMR0_Clock_EN     APBCLK |= TMR0_CLKEN			// Enable timer0 clock
#define TMR1_Clock_EN     APBCLK |= TMR1_CLKEN			// Enable timer1 clock
#define TMR2_Clock_EN     APBCLK |= TMR2_CLKEN			// Enable timer2 clock
#define TMR3_Clock_EN     APBCLK |= TMR3_CLKEN			// Enable timer3 clock
#define I2C0_Clock_EN     APBCLK |= I2C0_CLKEN			// Enable I2C0 clock
#define SPI0_Clock_EN     APBCLK |= SPI0_CLKEN			// Enable SPI0 clock
#define SPI1_Clock_EN     APBCLK |= SPI1_CLKEN			// Enable SPI1 clock
#define UART0_Clock_EN    APBCLK |= UART0_CLKEN			// Enable UART0 clock
#define UART1_Clock_EN    APBCLK |= UART1_CLKEN			// Enable UART1 clock
#define PWM01_Clock_EN    APBCLK |= PWM01_CLKEN			// Enable PWM0, PWM1 clock
#define PWM23_Clock_EN    APBCLK |= PWM23_CLKEN			// Enable PWM2, PWM3 clock
#define ADC_Clock_EN      APBCLK |= ADC_CLKEN			// Enable ADC clock

// Configure system clock source asexternal 12M Crystal
#define SysClock_ex12MHz	(CLKSEL0 = ((CLKSEL0 &(~HCLK)) | HCLK_12M))
                           
// Configure system clock source as PLL
#define SysClock_PLL		(CLKSEL0 = ((CLKSEL0 &(~HCLK)) | HCLK_PLL))
	
// Configure system clock source as internal 10K Oscillator
#define SysClock_in10KHz	(CLKSEL0 = ((CLKSEL0 &(~HCLK)) | HCLK_10K))

// Configure system clock source as internal 22M Oscillator
#define SysClock_in22MHz	(CLKSEL0 = ((CLKSEL0 &(~HCLK)) | HCLK_10K))		


// Configure timer0 clock source as external 12M Crystal
#define TMR0ClkSource_ex12MHz	(CLKSEL1 = ((CLKSEL1 & (~TM0_CLK)) | TM0_12M))
                               	
// Configure timer0 clock source as system clock
#define TMR0ClkSource_HCLK		(CLKSEL1 = ((CLKSEL1 & (~TM0_CLK)) | TM0_HCLK))
                               	
// Configure timer0 clock source as external input from P3.4
#define TMR0ClkSource_exTRG		(CLKSEL1 = ((CLKSEL1 & (~TM0_CLK)) | TM0_EXT))
                               
// Configure timer0 clock source as internal 22M Oscillator
#define TMR0ClkSource_in22MHz	(CLKSEL1 = ((CLKSEL1 & (~TM0_CLK)) | TM0_22M))

	
// Configure UART clock source as external 12M Crystal
#define UARTClkSource_ex12MHZ	(CLKSEL1 = ((CLKSEL1 & (~UART_CLK)) | UART_12M))

// Configure UART clock source as PLL
#define UARTClkSource_PLL		(CLKSEL1 = ((CLKSEL1 & (~UART_CLK)) | UART_PLL))

// Configure UART clock source as internal 22M Oscillator	
#define UARTClkSource_int22MHZ	(CLKSEL1 = ((CLKSEL1 & (~UART_CLK)) | UART_22M))
                             

#define setXTL12M_EN         PWRCON |= XTL12M_EN 		// Enable external 12M clock
#define setOSC22M_EN         PWRCON |= OSC22M_EN		// Enable internal 22M clock
#define setOSC10K_EN         PWRCON |= OSC10K_EN 		// Enable internal 10K clock
#define setWU_DLY            PWRCON |= WU_DLY 			// Enable the 64 clock cycle delay
#define setWINT_EN           PWRCON |= PD_WU_IE			// When wakeup from power down mode, an interupt occurs 
#define setPD_WU_STS         PWRCON |= PD_WU_STS		// Clear chip power down wake up status flag
#define setPWR_DOWN          PWRCON |= PWR_DOWN_EN		// Enable power down mode, chip can enter into power down mode 
#define setPD_WAIT_CPU       PWRCON |= PD_WAIT_CPU 		// Chip entry power down mode when the both PWR_DOWN and CPU run WFE/WFI instruction

#define clrXTL12M_EN         PWRCON &= ~XTL12M_EN 		// Disable external 12M clock
#define clrOSC22M_EN         PWRCON &= ~OSC22M_EN		// Disable internal 22M clock
#define clrOSC10K_EN         PWRCON &= ~OSC10K_EN		// Disable internal 10K clock
#define clrWU_DLY            PWRCON &= ~WU_DLY			// Disable the 64 clock cycle delay
#define clrWINT_EN           PWRCON &= ~PD_WU_IE		// Interrupt don't occur When wakeup from power down mode
#define clrPWR_DOWN          PWRCON &= ~PWR_DOWN_EN		// Disable power down mode
#define clrPD_WAIT_CPU       PWRCON &= ~PD_WAIT_CPU		// Chip entry power down mode when the PWR_DOWN bit is set

#endif
