#ifndef __I2C_H__
#define __I2C_H__

#include "common.h"

#define I2C_WR				0x00
#define I2C_RD				0x01
#define I2C_CLOCK               13

void Init_I2C(void);
bool I2C_Wake_Up(uchar Addr);
bool I2C_write(uchar Addr,uchar *writedata,uint datalength);
bool I2C_read(uchar Addr,uchar *readdata,uint datalength);
bool I2C_command_read(uchar Addr,uchar *commanddata,uint commandlength,uchar *readdata,uint datalength);


#endif
