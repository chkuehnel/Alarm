#include </home/Alarm/RasPi/MPU6050/MPU6050.h>
#include </home/pi/wiringPi/wiringPi/wiringPiI2C.h>
#include </home/pi/wiringPi/wiringPi/wiringPi.h>

int initI2C(){
	
	// open I2C-Bus with device
	fd = wiringPiI2CSetup(MPU6050_I2C_ADDR_H);

	// check if successful
	if (fd == -1) {
			printf("Error while opening I2C-Bus\n");
	}
	
	return fd;
}

void initMPU(){

	wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x00);		// No F_s-Divider
	wiringPiI2CWriteReg8(fd, CONFIG, 0x01); 		// Acc Bandwith 1kHz, Gyro F_s = 1kHz
	wiringPiI2CWriteReg8(fd, ACCL_CONFIG, 0x00);	// No self test, +-2g
	wiringPiI2CWriteReg8(fd, PWR_MNGT, 0x01); 		// PLL with x axis gyro reference, no sleep mode
}

void getAccValues(double *acc){

	uint8_t i2cData[6] = {0,0,0,0,0,0};

	// get data from acc sensor
	i2cData[0] = wiringPiI2CReadReg8 (fd, ACEL_XOUT_H);
	i2cData[1] = wiringPiI2CReadReg8 (fd, ACEL_XOUT_L);
	i2cData[2] = wiringPiI2CReadReg8 (fd, ACEL_YOUT_H);
	i2cData[3] = wiringPiI2CReadReg8 (fd, ACEL_YOUT_L);
	i2cData[4] = wiringPiI2CReadReg8 (fd, ACEL_ZOUT_H);
	i2cData[5] = wiringPiI2CReadReg8 (fd, ACEL_ZOUT_L);

	// merge lower and upper bytes
	*acc[0] = (i2cData[0] << 8 | i2cData[1]);
	*acc[1] = (i2cData[2] << 8 | i2cData[3]);
	*acc[2] = (i2cData[4] << 8 | i2cData[5]);
	
	return;
}