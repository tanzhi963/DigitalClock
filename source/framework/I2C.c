#include "I2C.h"

/*****************************************
*��������:I2CInit
*��    ��:��
*��    ��:��
*��    ��:I2C��ʼ��
******************************************/
void Init_I2C(void)
{
    P3_PMD &= ~(Px4_PMD | Px5_PMD);
	P3_PMD |= (Px4_OD | Px5_OD);               	//ʹ��I2C0����

    P3_MFP &= ~(P34_T0_I2CSDA | P35_T1_I2CSCL);
	P3_MFP |= (I2CSDA | I2CSCL);     			//ѡ��P3.4,P3.5��ΪI2C0��������   
    
	APBCLK |= I2C0_CLKEN;                       //ʹ��I2C0ʱ��
    I2CLK = I2C_CLOCK;                        	                                

    I2CON |= ENSI;                             	//ʹ��I2C

}

/****************************************************
** ��������: I2C_Wake_Up
** ��    ��: Addr��I2C�豸��ַ
** ��    ��: bool
** ��������: I2C����
*****************************************************/

bool I2C_Wake_Up(uchar Addr)
{
	I2CON |= STA;          				//����
    I2CON |= SI;               			//����жϱ�־λ        	

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
	
    I2DAT = Addr | I2C_WR;             //�����д���Ʋ��� 
    I2CON |= SI;
    while ((I2CON & SI) != SI);

    if (I2STATUS != 0x20)              //����I2Cģ�鲻������Ӧ��ƽ
    {
	    printf("I2C %x wake up write control fail %02X\r\n",Addr,I2STATUS);
        I2CON |= STO;
		I2CON |= SI;
		while (I2CON & STO);
		
	    return FALSE;
    }
	printf("I2C %x wake up success\r\n",Addr);
	
    I2CON |= STO;			//ֹͣ
    I2CON |= SI;
    while (I2CON & STO);
	
	return TRUE;
}


/****************************************************
** ��������: I2C_write
** ��    ��: Addr��I2C�豸��ַ *writedata���������ݵ����� datalength����������ĳ���
** ��    ��: bool
** ��������: I2C����д��
*****************************************************/
bool I2C_write(uchar Addr,uchar *writedata,uint datalength)
{
	uint i;
	
	I2CON |= STA;          				//����
    I2CON |= SI;               			//����жϱ�־λ        	

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

 
    //�����д���Ʋ��� 
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
    I2CON |= STO;				//ֹͣ
    I2CON |= SI;
    while (I2CON & STO);               

	printf("I2C %x write success\r\n",Addr);      
                                       							
	return TRUE;											
}

/****************************************************
** ��������: I2C_read
** ��    ��: Addr��I2C�豸��ַ *readdata���������ݵ����� datalength����������ĳ���
** ��    ��: bool
** ��������: I2C���ݶ�ȡ
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
	
	//���������  
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
	
	//��ȡ����
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
	
    I2CON &= (~AA);					//����NACK��I2Cģ�飬ִ�жϿ����Ӳ���
    I2CON |= SI; 
    while ((I2CON & SI) != SI);
        
    I2CON |= STO;					//ֹͣ
    I2CON |= SI;
    while (I2CON & STO);                      

	printf("I2C %x read success\r\n",Addr);   

	return TRUE;
}

/****************************************************
** ��������: I2C_command_read
** ��    ��: Addr��I2C�豸��ַ *senddata���������ݵ����� datalength����������ĳ���
** ��    ��: bool
** ��������: I2C�ȷ������Ȼ��ʼ�ӽ���
*****************************************************/
bool I2C_command_read(uchar Addr,uchar *commanddata,uint commandlength,uchar *readdata,uint datalength)
{
	uint i;
	
	I2CON |= STA;          			    //����
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

    //�����д���Ʋ���  
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
	
	//��������
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
	
	//���������  
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
	
	//��ȡ����
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
	
	//����NACK��I2Cģ�飬ִ�жϿ����Ӳ���
    I2CON &= (~AA);
    I2CON |= SI; 
    while ((I2CON & SI) != SI);
        
    //ֹͣ
    I2CON |= STO;
    I2CON |= SI;
    while (I2CON & STO);                      

	printf("I2C %x command read success\r\n",Addr);

	return TRUE;
}


