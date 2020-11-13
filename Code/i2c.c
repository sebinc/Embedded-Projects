
#include "includes.h"

void i2c_init(void)
{
	TRISB| = 0x03;//configuring sck and scl pins  as inputs
	SSPSTAT = 0X80;   //slew rate disabled 
	SSPCON1 = 0x28;  //master mode (clock = FOSC/(4 * (SSPADD + 1)) 
	SSPCON2 = 0x00;  //resetting the register
	SSPADD = 0x49; //calculated for i2c speed of 100 Mhz
	SSPEN =  1;
	_delay(10);
	return;
}
bit i2c_write_byte(unsigned char byte)
{
	SSPIF = 0;
	SSPBUF = byte;
	while(!SSPIF);
	SSPIF = 0;
	 return ACKSTAT;
}
void i2c_start(void)
{
	SSPIF = 0;
	SEN = 1; 
	while(!SSPIF);
	SSPIF = 0;
	return;
}
void i2c_repstart(void)
{
	SSPIF = 0;
	RSEN= 1;
	while(!SSPIF);
	SSPIF = 0;
	return;
}
void i2c_stop(void)
{
	SSPIF = 0;
	PEN  = 1;
	while(!SSPIF);
	SSPIF = 0;
	return;
}
void i2c_send_ack(void)
{
	SSPIF = 0;
	ACKDT = 0;
	ACKEN  = 1;
	while(!SSPIF);
	SSPIF = 0;
	return;
}
void i2c_send_nack(void)
{
	SSPIF = 0;
	ACKDT = 1;
	ACKEN = 1;
	while(!SSPIF);
	SSPIF = 0;
	return;
}
unsigned char i2c_read_byte(void)
{
	SSPIF = 0;
	RCEN = 1;
	while(!SSPIF);
	SSPIF  = 0;
	return SSPBUF;
}

