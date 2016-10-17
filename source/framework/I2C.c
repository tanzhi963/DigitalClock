#include "I2C.h"

/*****************************************
*函数名称:I2CInit
*输    入:无
*输    出:无
*功    能:I2C初始化
******************************************/
void Init_I2C(void)
{
    P3_PMD &= ~(Px4_PMD | Px5_PMD);
	P3_PMD |= (Px4_OD | Px5_OD);               	//使能I2C0引脚

    P3_MFP &= ~(P34_T0_I2CSDA | P35_T1_I2CSCL);
	P3_MFP |= (I2CSDA | I2CSCL);     			//选择P3.4,P3.5作为I2C0功能引脚   
    
	APBCLK |= I2C0_CLKEN;                       //使能I2C0时钟
    I2CLK = I2C_CLOCK;                        	                                

    I2CON |= ENSI;                             	//使能I2C

}

/****************************************************
** 函数名称: I2C_Wake_Up
** 输    入: Addr：I2C设备地址
** 输    出: bool
** 功能描述: I2C唤醒
*****************************************************/

bool I2C_Wake_Up(uchar Addr)
{
	I2CON |= STA;          				//启动
    I2CON |= SI;               			//清空中断标志位        	

    while ((I2CON & SI) != SI);	       

    I2CON &= ((~STA)&(~SI));           	

    if (I2STATUS != 0x08)	            
    {
       	printf("I2C %x wake up Start fail,I2STATUS %02X\r\n",Addr,I2STATUS);
        I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
		
		return FALSE;
    }
	
    I2DAT = Addr | I2C_WR;             //进入读写控制操作 
    I2CON |= SI;
    while ((I2CON & SI) != SI);

    if (I2STATUS != 0x20)              //唤醒I2C模块不返回响应电平
    {
	    printf("I2C %x wake up write control fail %02X\r\n",Addr,I2STATUS);
        I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
		
	    return FALSE;
    }
	printf("I2C %x wake up success\r\n",Addr);
	
    I2CON |= STO;			//停止
    I2CON |= SI;
    while (I2CON & STO);
	
	return TRUE;
}


/****************************************************
** 函数名称: I2C_write
** 输    入: Addr：I2C设备地址 *writedata：输入数据的数组 datalength：输入数组的长度
** 输    出: bool
** 功能描述: I2C数据写入
*****************************************************/
bool I2C_write(uchar Addr,uchar *writedata,uint datalength)
{
	uint i;
	
	I2CON |= STA;          				//启动
    I2CON |= SI;               			//清空中断标志位        	

    while ((I2CON & SI) != SI);	       

    I2CON &= ((~STA)&(~SI));           	

    if (I2STATUS != 0x08)	            
    {
		printf("I2C %x write start fail %02X\r\n",Addr,I2STATUS);
        I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
        
		return FALSE;
    }

 
    //进入读写控制操作 
    I2DAT = Addr | I2C_WR;
    I2CON |= SI;
    while ((I2CON & SI) != SI);

    if (I2STATUS != 0x18)              
    {
		printf("I2C %x write write control fail %02X\r\n",Addr,I2STATUS);
        I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
       
	    return FALSE;
    }

	for(i=0; i<datalength; i++)
	{
	    I2DAT = *(writedata+i);
	    I2CON |= SI; 
	    while ((I2CON & SI) != SI);
	    if (I2STATUS != 0x28)              
	    {
			printf("I2C %x write write data fail %02X\r\n",Addr,I2STATUS);
			I2CON |= STO;
			I2CON |= SI;
			while (I2CON & STO);
			
		    return FALSE;
	    }	
	}
    I2CON |= STO;				//停止
    I2CON |= SI;
    while (I2CON & STO);               

	printf("I2C %x write success\r\n",Addr);      
                                       							
	return TRUE;											
}

/****************************************************
** 函数名称: I2C_read
** 输    入: Addr：I2C设备地址 *readdata：接收数据的数组 datalength：接收数组的长度
** 输    出: bool
** 功能描述: I2C数据读取
*****************************************************/
bool I2C_read(uchar Addr,uchar *readdata,uint datalength)
{
	uint i;
	
	I2CON |= STA;          
    I2CON |= SI;                               	
    while ((I2CON & SI) != SI);                	
    I2CON &= ((~STA)&(~SI));                   	

    if (I2STATUS != 0x08)                      	
    {
		printf("I2C %x read start fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);

		return FALSE;
    }
	
	//进入读操作  
    I2DAT = Addr | I2C_RD;
    I2CON |= SI;
    while ((I2CON & SI) != SI);	    

    if (I2STATUS != 0x40)              
    {
		printf("I2C %x read write control fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
		
        return FALSE;
    }
	
	//读取数据
	I2CON |= AA;

	for(i=0; i<datalength; i++)
	{
		
	    I2CON |= SI; 
	    while ((I2CON & SI) != SI);
	
	    if (I2STATUS != 0x50)              
	    {
			printf("I2C %x read fail %02X\r\n",Addr,I2STATUS);
			I2CON |= STO;
			I2CON |= SI;
			while (I2CON & STO);
			
	        return FALSE;
	    }
	
		*(readdata+i) = I2DAT;	
	} 
	
    I2CON &= (~AA);					//发送NACK到I2C模块，执行断开连接操作
    I2CON |= SI; 
    while ((I2CON & SI) != SI);
        
    I2CON |= STO;					//停止
    I2CON |= SI;
    while (I2CON & STO);                      

	printf("I2C %x read success\r\n",Addr);   

	return TRUE;
}

/****************************************************
** 函数名称: I2C_command_read
** 输    入: Addr：I2C设备地址 *senddata：接收数据的数组 datalength：接收数组的长度
** 输    出: bool
** 功能描述: I2C先发送命令，然后开始接接收
*****************************************************/
bool I2C_command_read(uchar Addr,uchar *commanddata,uint commandlength,uchar *readdata,uint datalength)
{
	uint i;
	
	I2CON |= STA;          			    //启动
    I2CON |= SI;                       	

    while ((I2CON & SI) != SI);	        

    I2CON &= ((~STA)&(~SI));           	

    if (I2STATUS != 0x08)	            
    {
		printf("I2C %x command read start fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
        
		return FALSE;
    }

    //进入读写控制操作  
    I2DAT = Addr | I2C_WR;
    I2CON |= SI;
    while ((I2CON & SI) != SI);

    if (I2STATUS != 0x18)              
    {
		printf("I2C %x command read write control fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
       
	    return FALSE;
    }

	for(i=0; i<commandlength; i++)
	{
	    I2DAT = *(commanddata+i);
	    I2CON |= SI; 
	    while ((I2CON & SI) != SI);
	    if (I2STATUS != 0x28)              
	    {
			printf("I2C %x command read write data fail %02X\r\n",Addr,I2STATUS);
			I2CON |= STO;
			I2CON |= SI;
			while (I2CON & STO);
			
		    return FALSE;
	    }	
	}
	
	//重新启动
	I2CON |= STA;          
    I2CON |= SI;                               	
    while ((I2CON & SI) != SI);                	
    I2CON &= ((~STA)&(~SI));                   	

    if (I2STATUS != 0x10)                      	
    {
		printf("I2C %x command read repeated start fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);

		return FALSE;
    }
	
	//进入读操作  
    I2DAT = Addr | I2C_RD;
    I2CON |= SI;
    while ((I2CON & SI) != SI);	    

    if (I2STATUS != 0x40)              
    {
		printf("I2C %x command read write control fail %02X\r\n",Addr,I2STATUS);
		I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
		
        return FALSE;
    }
	
	//读取数据
	I2CON |= AA;

	for(i=0; i<datalength; i++)
	{
		
	    I2CON |= SI; 
	    while ((I2CON & SI) != SI);
	
	    if (I2STATUS != 0x50)              
	    {
			printf("I2C %x command read read fail %02X\r\n",Addr,I2STATUS);
			I2CON |= STO;
			I2CON |= SI;
			while (I2CON & STO);
	        return FALSE;
	    }
	
		*(readdata+i) = I2DAT;	
	} 
	
	//发送NACK到I2C模块，执行断开连接操作
    I2CON &= (~AA);
    I2CON |= SI; 
    while ((I2CON & SI) != SI);
        
    //停止
    I2CON |= STO;
    I2CON |= SI;
    while (I2CON & STO);                      

	printf("I2C %x command read success\r\n",Addr);

	return TRUE;
}


