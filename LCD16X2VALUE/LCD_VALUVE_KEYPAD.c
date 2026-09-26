#include<pic.h>
__CONFIG(0x2CE4);

void delay(unsigned int count){
	while(--count);
	}
	int i=0;
	char j[10];
	char c[10]={'O','P','E','N'};
	char nc[15]={'W','R','O','N','G','P','A','S','S','W','O','R','D'};
	int p=0;
	int m;
	
	void LCD(unsigned int a,unsigned int b)
		{
	RE0=a;
	PORTD=b;
	RE1=1;
	delay(1000);
	RE1=0;
	delay(1000);
	}
	
	void crt(){
	LCD(0,0XC0);
	for(int i=0;i<10;i++){
	RE0=1;
	PORTD=c[i];
	RE1=1;
	delay(100);
	RE1=0;
	delay(100);
	}
	}
	void ncrt(){
	LCD(0,0xC0);
	for(int i=0;i<15;i++){
	RE0=1;
	PORTD=nc[i];
	RE1=1;
	delay(100);
	RE1=0;
	delay(100);
	}
	}
	
	
	
void store(){
	j[p]=i+'0';
	p++;
	
	}
	void s(){
			LCD(0,0x80);
	for (int k=0;k<p;k++)
		{
	RE0=1;
	PORTD=j[k];
	RE1=1;
	delay(100);
	RE1=0;
	delay(100);		

	}
	m = (j[0]-'0')*1000 +
    (j[1]-'0')*100 +
    (j[2]-'0')*10 +
    (j[3]-'0');
	if(m==1234){
	crt();
	RE2=1;}
	else {
		ncrt();
		RE2=0;
	}
	}
	
	void main(){
PORTA=0x00;
PORTB=0X00;
PORTC=0X00;
PORTD=0X00;
PORTE=0X00;
TRISE=0X00;
TRISA=0XF0;
TRISD=0X00;
TRISC=0X00;
ANSEL=ANSELH=0X00;
	LCD(0,0X38);
	LCD(0,0X0E);
	LCD(0,0X0C);
	
	while(1){
	//C1 COLOUM ONE
RA1=1;RA2=0;RA3=0;
if(RA7==1){
	while(RA7);
LCD(0,0X80);
LCD(1,'1');	
i=1;
store();
} 
else if(RA6==1)
	{
while(RA6);
LCD(0,0x80);
LCD(1,'4');
i=4;
store();
}
else if(RA5==1){
	while(RA5);
LCD(0,0x80);
LCD(1,'7');
i=7;
store();
}
else if(RA4==1){
	while(RA4);
	//function call
	s();
}

//C2 COLOUM
RA1=0;RA2=1;RA3=0;
if(RA7==1){
	while(RA7);
LCD(0,0X80);
LCD(1,'2');
i=2;
store();
}

else if(RA6==1){
	while(RA6);
LCD(0,0X80);
LCD(1,'5');
i=5;
store();
}

else if(RA5==1){
	while(RA5);
LCD(0,0X80);
LCD(1,'8');
i=8;
store();
}

else if(RA4==1){
	while(RA4);
LCD(0,0X80);
LCD(1,'0');
i=0;
store();
}

// C3 

RA1=0;RA2=0;RA3=1;
if(RA7==1){
	while(RA7);
LCD(0,0X80);
LCD(1,'3');
i=3;
store();
}

else if (RA6==1){
	while(RA6);
LCD(0,0X80);
LCD(1,'6');
i=6;
store();
}
else if (RA5==1){
	while(RA5);
LCD(0,0X80);
LCD(1,'9');
i=9;
store();
}
else if (RA4==1){
main();	//nill
}
}
}
	