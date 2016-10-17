#include "DS3231.h"

#define DS3231_Addr				0xd0

uchar DS3231_data[19] = {0};
uchar DS3231_send[1] = {0};

bool get_DS3231_data(void)
{
	uchar i;
	if(I2C_command_read(DS3231_Addr,DS3231_send,1,DS3231_data,sizeof(DS3231_data)))
	{
		for(i=0;i<sizeof(DS3231_data);i++)
		{
			printf("%x ",DS3231_data[i]);
		}
		printf("\r\n");
		return TRUE;
	}
	else
	{
		printf("get DS3231 data fail");
		return FALSE;
	}
}
