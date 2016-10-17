/*-----------------------------------------------------------------------------------------------*/
/*                                                                                               */
/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                               */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/
#ifndef __MACRO_TIMER_H__
#define __MACRO_TIMER_H__

#define setTMR0_CEN    		 TCSR0 |= CEN					// Start timer0 counter
#define clrTMR0_CEN    		 TCSR0 &= ~CEN					// Stop timer0 counter
#define setTMR0_IE     		 TCSR0 |= TMR_IE				// Enable timer0 interrupt
#define setTMR0_CRST    	 TCSR0 |= CRST					// Reset Timer¡¯s prescale counter, internal 24-bit up-counter and CEN bit
#define setTMR0_TDREN  		 TCSR0 |= TDR_EN

#define setTMR0_ONESHOT		 {TCSR0 &= ~TMR_MODE;\
							  TCSR0 |=	MODE_ONE_SHOT; }	// Set timer0 one-shot mode
#define setTMR0_PERIOD		 {TCSR0 &= ~TMR_MODE;\
							  TCSR0 |=	MODE_PERIOD; }		// Set timer0 period mode
#define setTMR0_CONTINUE	 {TCSR0 &= ~TMR_MODE;\
							  TCSR0 |=	MODE_CONTINUE; }	// Set timer0 continuous counting mode
#endif

