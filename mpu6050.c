#include <mpu6050.h>

// extern meaning the variable is defined in another file (main.h)
#include <main.h>
extern I2C_HandleTypeDef hi2c1;

// Call this function in main.c to initialize MPU6050
void mpu6050_init()
{
	// (DEVICE_ADDRESS <<1) + 0
	// 0b 11 01 00 0  left shift 1 and add 0 (Write mode)
	// 0b 11 01 00 00
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADDRESS <<1) + 0, 1, 100);
	if (ret == HAL_OK)
	{
	  printf("The device is ready\n");
	}
	else
	{
	  printf("Not OK\n");
	}
	// HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	// MemAddSize = 1 (Each register is 1 byte = 8 bits)

	/* CONFIGURE GYROSCOPE */
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, REG_CONFIG_GYRO, 1, FS_GYRO_500, 1, 100);
	if (ret == HAL_OK)
	{
	  printf("Writing to register 27 (Gyro-config) \n");
	}
	else
	{
	  printf("Failed to write to register 27 (Gyro-config) \n");
	}

	/* CONFIGURE ACCELEROMETER */
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, RE_CONFIG_ACC, 1, FS_ACC_4G, 1, 100);
	if (ret == HAL_OK)
	{
	  printf("Writing to register 28 (Accel-config) \n");
	}
	else
	{
	  printf("Failed to write to register 27 (Accel-config) \n");
	}

	/* CONFIGURE POWER MANAGEMENT */
	// register-map 4.28
	// wake up from sleep mode		1 = sleep (default)
	// enable temperature sensor	1 = disable (default)
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, REG_USR_CTRL, 1, 0, 1, 100);
	if (ret == HAL_OK)
	{
	  printf("Exiting sleep mode \n");
	}
	else
	{
	  printf("Failed to wake up \n");
	}
}

void mpu6050_read()
{
	// (DEVICE_ADDRESS <<1) + 0
	// 0b 11 01 00 0  left shift 1 and add 1 (Read mode)
	// 0b 11 01 00 00
	uint8_t data[2]; // Buffer
	int16_t x_acc;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) + 1, REG_DATA, 1, data, 2, 100);

	// register-map 4.17
	// x_acc = 0b xx xx yy yy (16 bits, 2 bytes)
	// data[0] = 0b xx xx (8 bits, 4 bytes)
	// data[1] = 0b yy yy (8 bits, 4 bytes)
	x_acc = ((int16_t)data[0] <<8) + data[1];
	printf("x axis acceleration: %d \n", x_acc);
}
