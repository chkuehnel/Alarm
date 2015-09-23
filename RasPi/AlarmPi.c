
/**
 *
 * This programm uses i2c1 on raspberry pi.
 *
 */

#include <stdio.h>
#include "stdint.h"
#include </home/pi/wiringPi/wiringPi/wiringPiI2C.h>
#include </home/pi/wiringPi/wiringPi/wiringPi.h>
#include </home/Alarm/RasPi/MPU6050/MPU6050.h>

void main(void){
	int i, k, returnValue[4];
	double acc[3];                          // new values from sensor
	/*
	Array to low pass filter the values from sensor
	[0][] x axis
	[1][] y axis
	[2][] z axis
	[x][0] new value
	[x][1] d - 1 value
	[x][2] d - 2 value
	*/
	double accArray[3][3];
	double accXSc, accYSc, accZSc;
	
	// initialize I2C channel
	if( initI2C() == -1 ){
		return;
	}
	
	// initialize MPU registers
	initMPU();

	// initialize accArray
	for(i = 0; i < 3; i++){
			acc[i] = 0;
			for(k = 0; k < 3; k++){
					accArray[i][k] = 0;
			}
	}
		
	while(1){
			
		// get new values from acc sensor on MPU
		getAccValues(acc);

		// shift old values
		for(i = 0; i < 3; i++){
				for(k = 1; k > 0; k--){
						accArray[i][k + 1] = accArray[i][k];
				}
				accArray[i][0] = acc[i];
		}

		// low pass filter values
		accXSc = (0.25 * accArray[0][0] + 0.5 * accArray[0][1] + 0.25 * accArray[0][2]) / 16384.0;
		accYSc = (0.25 * accArray[1][0] + 0.5 * accArray[1][1] + 0.25 * accArray[1][2]) / 16384.0;
		accZSc = (0.25 * accArray[2][0] + 0.5 * accArray[2][1] + 0.25 * accArray[2][2]) / 16384.0;
		printf("%f,%f,%f\n", accXSc, accYSc, accZSc);

	}// end while(1)
}// end main

