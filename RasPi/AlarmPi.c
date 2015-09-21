
/**
 *
 * This programm uses i2c1 on raspberry pi.
 *
 */

#include <stdio.h>
#include "stdint.h"
#include </home/pi/wiringPi/wiringPi/wiringPiI2C.h>
#include </home/pi/wiringPi/wiringPi/wiringPi.h>

// I2C addresses for MPU6050
#define ACCSENSOR_H 0x69
#define ACCSENSOR_L 0x68

void main(void){
        int i, k, returnValue[4];
        uint8_t i2cData[6] = {0,0,0,0,0,0};
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

        // open I2C-Bus with device
        int fd = wiringPiI2CSetup(ACCSENSOR_H);

        // check if successful
        if (fd == -1) {
                printf("Error while opening I2C-Bus\n");
                return;
        }
		
        wiringPiI2CWriteReg8(fd, 0x19, 0x00); // No F_s-Divider
        wiringPiI2CWriteReg8(fd, 0x1A, 0x01); // Acc Bandwith 1kHz, Gyro F_s = 1kHz
        wiringPiI2CWriteReg8(fd, 0x1C, 0x00); // No self test, +-2g
        wiringPiI2CWriteReg8(fd, 0x6B, 0x01); // PLL with x axis gyro reference, no sleep mode

        returnValue[0] = wiringPiI2CReadReg8 (fd, 0x75);
        printf("Device address: %x\n", returnValue[0]);

        // initialize accArray
        for(i = 0; i < 3; i++){
                acc[i] = 0;
                for(k = 0; k < 3; k++){
                        accArray[i][k] = 0;
                }
        }
		
	while(1){

			// get data from acc sensor
			i2cData[0] = wiringPiI2CReadReg8 (fd, 0x3B);
			i2cData[1] = wiringPiI2CReadReg8 (fd, 0x3C);
			i2cData[2] = wiringPiI2CReadReg8 (fd, 0x3D);
			i2cData[3] = wiringPiI2CReadReg8 (fd, 0x3E);
			i2cData[4] = wiringPiI2CReadReg8 (fd, 0x3F);
			i2cData[5] = wiringPiI2CReadReg8 (fd, 0x40);

			// merge lower and upper bytes
			acc[0] = (i2cData[0] << 8 | i2cData[1]);
			acc[1] = (i2cData[2] << 8 | i2cData[3]);
			acc[2] = (i2cData[4] << 8 | i2cData[5]);

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

