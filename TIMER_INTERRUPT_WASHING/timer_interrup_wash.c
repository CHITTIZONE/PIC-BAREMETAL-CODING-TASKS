#include<pic.h>
__CONFIG(0X2CE4);

unsigned int count=0;
unsigned char st[]="STARTED";
unsigned char sto[]="STOPED";
unsigned char w[]="WATER";
unsigned char Ri[]="RINSE";
unsigned char C[]="COMPLETED";
unsigned char t[]="TIME=";
	void delay(unsigned int c){
while(c--);
}
	void LCD(unsigned int a , unsigned int b){
RE0=a; // register select
PORTD=b;
RE1=1;
delay(100);
RE1=0;
delay(100);
}
void stop();
void interrupt isr()	
		{
			
if(T0IF==1){
count++;
T0IF=0;
TMR0=131;
}
}
void stop(){
	RE2=0;
	RE3=0;
for(int i=0;sto[i]!='\0';i++){
LCD(1,sto[i]);
}
}
void Lt(unsigned int value)
{
    static unsigned char sec = 4;
    if(count >= value)
    {
        count = 0;
        LCD(0,0xC5);          // Cursor after "TIME="
        LCD(1,'0' + sec);
        if(sec > 1)
            sec--;
    }
}

void start(){
	
if (count==125){
	RE2=1;
	LCD(0,0x01);
	LCD(0,0x80);
			for (int i=0;st[i]!='\0';i++){
LCD(1,st[i]);
Lt(125);
}
}
else if(count==250){
	RE2=1;
	LCD(0,0x01);
	LCD(0,0x80);
			for (int i=0;w[i]!='\0';i++){
LCD(1,w[i]);
Lt(250);
}
}
else if(count==1000)
	{
	RE2=0;
	RE3=1;
	LCD(0,0x01);
	LCD(0,0x80);
			for (int i=0;Ri[i]!='\0';i++){
LCD(1,Ri[i]);
Lt(1000);
}
}
else if(count==1250)
	{
	RE2=0;
	RE3=0;
	LCD(0,0x01);
	LCD(0,0x80);
			for (int i=0;C[i]!='\0';i++){
LCD(1,C[i]);
Lt(1250);
}
}
}
void main(){
PORTD=TRISD=PORTE=PORTB=TRISE=0x00;
TRISB=0x07;
ANSEL=ANSELH=0x00;

LCD(0,0x38);
LCD(0,0x0E);
//LCD(0,0x0C);
OPTION_REG=0x05;

TMR0=131;
GIE=1;
T0IE=1;

while (1){
	if(T0IF==1){
	
	TMR0=131;
	count++;
	T0IF=0;
	}
	
if(RB1==1){
			stop();
			RB1=0;
			}
else if (RB2==1){
main();
}
}
}
