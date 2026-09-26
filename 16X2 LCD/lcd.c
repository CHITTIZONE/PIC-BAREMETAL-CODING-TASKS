#include<pic.h>
__CONFIG(0X2CE4);

void delay(unsigned int count){
	while(--count);
	}
	
	unsigned char val[5]={'H','E','L','L','O'};
	void main()
		{
			
	PORTD=0X00;
	PORTE=0X00;
	TRISD=0X00;
	TRISE=0X00;
	ANSEL=ANSELH=0;
	//COMMAND MODE TO INSIATE 16X2 LCD
	RE0=0;
	PORTD=0X38;
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	// COMMAND MODE TO ENABLE THE LCD START AND CURSON ON 
	RE0=0;
	PORTD=0X0E;
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	//POSTION OF CURSOR ON THE FIRST SEGMENT 0X80 FIRST ROW AND 0XC0 SECOND ROW
	RE0=0;
	PORTD=0X80;
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	while(1)
		{
	/*RE0=1; //0 - for command mode and 1 is for the data mode
	PORTD='O';
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	
	delay(10000);
	
	RE0=0;
	PORTD=0x01;// clear screen
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	
	RE0=1;
	PORTD='L';
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	RE0=0;
	PORTD=0x01;// clear screen
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	
	RE0=1;
	PORTD='L';
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	*/
	RE0=0;
		PORTD=0x01;// clear screen
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	delay(10000);
	delay(10000);
		for (int i=0 ; i<5;i++)
			{
	
	RE0=1;
	PORTD=val[i];
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	
	delay(10000);
	}
	}
	
	}