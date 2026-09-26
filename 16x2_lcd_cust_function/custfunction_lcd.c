#include<pic.h>
__CONFIG(0x2CE4);

void delay(unsigned int count )
	{
while(--count);
}
void LCD(unsigned int a,unsigned int b)
	{
RE0=a;
PORTD=b;
RE1=1;
delay(1000);
RE1=0;
delay(1000);

}

void main(){
PORTD=0x00;
PORTB=0x00;
PORTE=0X00;
TRISB=0XF0;
TRISD=0X00;
TRISE=0X00;
ANSEL= ANSELH=0X00;
LCD(0,0X38);
LCD(0,0X0E);



	
while(1){

	
//C1 COLOUM ONE
RB1=1;RB2=0;RB3=0;
if(RB7==1){
LCD(0,0X80);
LCD(1,'1');	
LCD(0,0x0C);
} 
else if(RB6==1){
LCD(0,0x80);
LCD(1,'4');
LCD(0,0x0C);
}
else if(RB5==1){
LCD(0,0x80);
LCD(1,'7');
LCD(0,0X0C);
}
else if(RB4==1){
LCD(0,0X80);
LCD(1,'*');
LCD(0,0X0C);
}

//C2 COLOUM
RB1=0;RB2=1;RB3=0;
if(RB7==1){
LCD(0,0X80);
LCD(1,'2');
LCD(0,0X0C);
}

else if(RB6==1){
LCD(0,0X80);
LCD(1,'5');
LCD(0,0X0C);
}

else if(RB5==1){
LCD(0,0X80);
LCD(1,'8');
LCD(0,0X0C);}

else if(RB4==1){
LCD(0,0X80);
LCD(1,'0');
LCD(0,0X0C);
}

// C3 

RB1=0;RB2=0;RB3=1;
if(RB7==1){
LCD(0,0X80);
LCD(1,'3');
LCD(0,0X0C);
}

else if (RB6==1){
LCD(0,0X80);
LCD(1,'6');
LCD(0,0X0C);
}
else if (RB5==1){
LCD(0,0X80);
LCD(1,'9');
LCD(0,0X0C);
}
else if (RB4==1){
LCD(0,0X80);
LCD(1,'#');
LCD(0,0X0C);
}
}
}


