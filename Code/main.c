#include "includes.h"

//#define _XTAL_FREQ 8000000


__CONFIG(1,UNPROTECT);

__CONFIG(2, VREGEN & PWRTDIS & BOREN & BORV20 & WDTDIS & WDTPS32K);

__CONFIG(3, PBDIGITAL & LPT1DIS & MCLREN);

__CONFIG(4, XINSTDIS & STVREN & LVPDIS & ICPORTDIS & DEBUGDIS);

__CONFIG(5, UNPROTECT);
__CONFIG(6, UNPROTECT);
__CONFIG(7, UNPROTECT);


unsigned char data;

/* Sample DAC values for various signals */
unsigned char triag[32]={0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,254,240,224,208,192,176,160,144,128,112,96,80,64,48,32,16};
unsigned char sine[32]={128,152,176,200,218,234,246,253,255,253,246,234,218,200,176,152,128,103,79,56,37,21,9,2,0,2,9,21,37,56,79,103};
unsigned char saw[32]={0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,253};

/* Send an 8bit data to DAC */
void send_dac(unsigned char x)
{
	i2c_start();
	i2c_write_byte(0x9E);	//slave address
	i2c_write_byte(0x40);	//control register
	i2c_write_byte(x);
	i2c_stop();
	__delay_ms(12);
}


void main()
{
	TRISB = 0XFF;
	TRISD = 0;
	TRISC = 0;
	RB2=1;
	i2c_init();
	unsigned char count;
	count=0;

	
	
	while(1)// continous loop
	{
	    data=PORTD; // Check the PORTD signal for generating signal
	    	
	    count++;
	    if (data==1)
	    {
	    	send_dac(sine[count]);
	    }
	    else if (data==2)
	    {
	    	send_dac(saw[count]);
	    }
	    else if (data==4)		
	    {
	    	send_dac(triag[count]);
	    }		
	    else
	    {
	        send_dac(sine[count]);

	    }
	    
	    if (count==31)
	    count=0;
	}
}	
