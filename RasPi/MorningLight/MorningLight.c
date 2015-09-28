#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
	int bright ;

	printf ("Starting 'Morning Light'\n") ;

	if (wiringPiSetup () == -1)
	exit (1) ;

	pinMode (1, PWM_OUTPUT) ;

	for (bright = 0 ; bright < 1024 ; ++bright)
	{
		pwmWrite (1, bright) ;
		delay (1758) ;
	}
	
	printf("Sun rised, now waiting for 10 minutes");
	delay(600000);

	pwmWrite(1,0);

	return 0 ;
}