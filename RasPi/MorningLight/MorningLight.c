#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main (void)
{
	int count, bright;

	printf ("Starting 'Morning Light'\n") ;

	if (wiringPiSetup () == -1)
	exit (1);

	pinMode (1, PWM_OUTPUT);

	for (count = 0 ; count < 1800 ; ++count)
	{
		bright = exp( ( count * log(1023) ) / 1800 );
		pwmWrite (1, bright);
		delay (1000);
	}
	
	printf("Sun rised, now waiting for 10 minutes");
	delay(600000);
	
	for (bright = 1023; bright >= 0; --bright){
		pwmWrite(1, bright);
		delay(50);
	}

	return 0;
}