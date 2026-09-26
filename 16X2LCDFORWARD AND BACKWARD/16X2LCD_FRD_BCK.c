#include<pic.h>
__CONFIG(0x2CE4);
void delay(unsigned int count){
while(count--);
}
void LCD(int a , int b){
RE0=a;
PORTD=b;
RE1=1;
delay(1000);
RE1=0;
delay(1000);
}

// main funtion
void main(){
PORTD=0x00;
PORTE=0x00;
TRISD=0x00;
TRISE=0x00;
ANSEL=ANSEL=0x00;
LCD(0,0x38);
LCD(0,0x0E);
LCD(1,0x80);
while(1){
for(int i=0;i<1000;i++){
	int k=1000-1-i;
int t= i/1000+'0';
int h=(i/100)%10+'0';
int te=(i/10)%10+'0';
int o=i%10+'0';
LCD(0,0x80);
LCD(1,t);
LCD(1,h);
LCD(1,te);
LCD(1,o);
LCD(0,0xCC);
int t=k/1000+'0';
int h=(k/100)%10+'0';
int te=(k/10)%10+'0';
int o=k%10+'0';
LCD(1,t);
LCD(1,h);
LCD(1,te);
LCD(1,o);
delay(1000);
}

}
}