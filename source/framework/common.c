/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/


#include "common.h"
 

/*-----------------------------------------------------------------------------
  Function:			Un_Lock_Reg                                                                             
  Parameter:  	None                                     
  Returns:    	None                                                                                      
  Description:  Unlock protected register bits, so as user can access to.                                    
 *-----------------------------------------------------------------------------*/
void Un_Lock_Reg(void)
{
    RegLockAddr = 0x59;
    RegLockAddr = 0x16;
    RegLockAddr = 0x88;
}

/*-----------------------------------------------------------------------------
  Function:			Lock_Reg                                                                                 
  Parameter:  	None                                     
  Returns:   		None                                                                                      
  Description:	Lock protected register bits, avoiding unknown errors when access illegally. 			                                   
 *-----------------------------------------------------------------------------*/
void Lock_Reg(void)
{
    RegLockAddr = 0x00;
}

/*-----------------------------------------------------------------------------
  Function:			PLL_Enable                                                                                  
  Parameter: 		None                                     
  Returns:  		None                                                                                      
  Description:	Enable PLL function.                                    
 *-----------------------------------------------------------------------------*/
void PLL_Enable(void)
{
    PLLCON &= ~(PLL_OE|PLL_PD);
}

/*-----------------------------------------------------------------------------
  Function:			NSR_Enable                                                                                
  Parameter:  	None                                     
  Returns:     	None                                                                                      
  Description:	Enable nosie sensitivity reduction function.                                    
 *-----------------------------------------------------------------------------*/
void NSR_Enable(void) //Noise Sensitivity Recuduction
{
    Un_Lock_Reg();
    PORCR = 0x00005AA5;
}

/*-----------------------------------------------------------------------------
  Function:			NSR_Disable                                                                                
  Parameter: 		None                                     
  Returns:  		None                                                                                      
  Description:	Disable nosie sensitivity reduction function.                                    
 *-----------------------------------------------------------------------------*/
void NSR_Disable(void) //Noise Sensitivity Recuduction Disable
{
    Un_Lock_Reg();
    PORCR = 0x00000000;
}


