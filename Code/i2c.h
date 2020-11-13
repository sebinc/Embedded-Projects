#ifndef _i2c_h
#define _i2c_h


void i2c_init(void);						//To initialise i2c module in master mode
bit i2c_write_byte(unsigned char byte); //To send an 8 bit byte 
void i2c_start(void);					//To send a start bit 
void i2c_repstart(void);				//To send a repeated start 
void i2c_stop(void); 					// To send a stop bit 
unsigned char i2c_read_byte(void);	//Read a byte of data 
void i2c_send_ack(void);				//To send acknowledge bit 
void i2c_send_nack(void);				//To send no acknowledge bit

#endif