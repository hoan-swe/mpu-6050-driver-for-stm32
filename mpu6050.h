

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

// mpu6000-datasheet 6.4 table device address:
// 0b1101000 = 0x68		Binary -> Hexadecimal
#define DEVICE_ADDRESS 0x68

// mpu6000-register-map 4.4 GYRO_CONFIG:
// 0b00001000 = 8		Binary -> Decimal
#define FS_GYRO_250		0
#define FS_GYRO_500		8
#define FS_GYRO_1000	9
#define FS_GYRO_2000	10

// ACCEL_CONFIG
#define FS_ACC_2G		0
#define FS_ACC_4G		8
#define FS_ACC_8G		9
#define FS_ACC_16G		10

// Register number
#define REG_CONFIG_GYRO		27		// Gyro register
#define RE_CONFIG_ACC		28		// Accel register
#define REG_USR_CTRL		107		// POWER_MANAGEMENT register-map 4.28
#define REG_DATA			59		// Start/First register
// regiester-map 4.7
// Accelerometer measurements: register 59 - 64
// Temperature measurements: register 65 - 66
// Gyroscope measurements: register 67 - 72


void mpu6050_init();
void mpu6050_read();

#endif /* INC_MPU6050_H_ */
