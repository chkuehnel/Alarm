/*
* 
*/

// I2C addresses for MPU6050
#define MPU6050_I2C_ADDR_H 0x69
#define MPU6050_I2C_ADDR_L 0x68

// Configuration registers of MPU
#define SMPLRT_DIV 	0x19
#define CONFIG 		0x1A
#define ACCL_CONFIG 0x1C
#define PWR_MNGT 	0x6B
#define ACEL_XOUT_H 0x3B
#define ACEL_XOUT_L 0x3C
#define ACEL_YOUT_H 0x3D
#define ACEL_YOUT_L 0x3E
#define ACEL_ZOUT_H 0x3F
#define ACEL_ZOUT_L 0x40

// descriptor used for I2C channel
int fd;

// initialize I2C channel
int initI2C();

// initialize MPUs registers
void initMPU();

// get accerleration data from MPU
void getAccValues(double *acc);