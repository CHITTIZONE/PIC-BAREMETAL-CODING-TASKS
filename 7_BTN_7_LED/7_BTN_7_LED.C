#include<pic.h>
__CONFIG(0X2CE4);
void delay(unsigned int count)
{
	while(--count);
	}

	void main()
{
		PORTD=0X00;
		TRISD=0x00;
		PORTA=0X00;
		TRISA=0XFF;
		ANSEL=ANSELH=0X00;
		while(1)
{
			if (RA0==1)
				{
				RD0=1;
				}
				else if(RA1==1)
				{
					RD1=1;
					}
					else if(RA2==1)
						{
							RD2=1;
							}
						else if(RA3==1)
								{
									RD3=1;
									}
									else if(RA4==1)
									{
										RD4=1;
										}
										else if(RA5==1)
										{
											RD5=1;
											}
											else if(RA6==1)
											{
												RD6=1;
												}
												else if(RA7==1)
												{
													RD7=1;
													}
													else
{
														PORTD=0X00;
														}
														}
														}						