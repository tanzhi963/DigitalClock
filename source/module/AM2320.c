#include "AM2320.h"

#define AM2320_Addr				0xb8
uchar get_humiture_code[] = {0x03,0x00,0x04};



void AM2320_run_one_time(void)
{
	uchar buf[8] = {0};
	uint temperature, humidity;
	
	
	I2C_Wake_Up(AM2320_Addr);
	I2C_write(AM2320_Addr,get_humiture_code,sizeof(get_humiture_code));
	I2C_read(AM2320_Addr,buf,8);
	
	
	humidity = (buf[2]*256+buf[3]);
	temperature = (buf[4]*256+buf[5]);
	
	printf("%d,%d\r\n",humidity,temperature);
//	LED_reflash(temperature*100+humidity);
}




