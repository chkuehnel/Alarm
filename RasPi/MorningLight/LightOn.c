#include </home/pi/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{

	printf ("Light On.\n") ;

	if (wiringPiSetup () == -1)
	exit (1) ;

	pinMode (1, OUTPUT) ;

	digitalWrite (1, HIGH);
	
	return 0 ;
}