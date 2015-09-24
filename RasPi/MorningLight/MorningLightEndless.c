#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
	int bright ;

	printf ("Raspberry Pi wiringPi PWM test program\n") ;

	if (wiringPiSetup () == -1)
	exit (1) ;

	pinMode (1, PWM_OUTPUT) ;
	pinMode (4, PWM_OUTPUT) ;
	pinMode (5, PWM_OUTPUT) ;


while(1){
	pwmWrite(1, 1023);
	pwmWrite(4, 1023);
	pwmWrite(5, 1023);
	
/*	for (bright = 0 ; bright < 1024 ; ++bright)
	{
		pwmWrite (1, bright) ;
		delay (1) ;
	}
	
	delay(1000);

	for (bright = 1023 ; bright >= 0 ; --bright)
	{
		pwmWrite (1, bright) ;
		delay (1) ;
	}*/
}

	return 0 ;
}