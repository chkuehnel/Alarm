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

	for (bright = 0 ; bright < 1024 ; ++bright)
	{
		pwmWrite (1, bright) ;
		pwmWrite (4, bright) ;
		pwmWrite (5, bright) ;
		delay (50) ;
	}
	
	delay(1000);

	for (bright = 1023 ; bright >= 0 ; --bright)
	{
		pwmWrite (1, bright) ;
		pwmWrite (4, bright) ;
		pwmWrite (5, bright) ;
		delay (50) ;
	}


	return 0 ;
}