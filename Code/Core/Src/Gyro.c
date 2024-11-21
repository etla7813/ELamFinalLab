/*
 * Gyro.c
 *
 *  Created on: Nov 12, 2024
 *      Author: Ethan
 */

#include <Gyro.h>

static HAL_StatusTypeDef gyroHALStatus; //why is this unused
SPI_HandleTypeDef GyroInit = {0};

void Gyro_Init()
{
	//enable clocks
	__HAL_RCC_SPI5_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	//////////////////////////////

	GPIO_InitTypeDef Gyro_PinInit = {0};

	Gyro_PinInit.Pin = SPI5_SCK;
	Gyro_PinInit.Mode = GPIO_MODE_AF_PP;
	Gyro_PinInit.Speed = GPIO_SPEED_FREQ_LOW;
	Gyro_PinInit.Pull = GPIO_PULLUP;
	Gyro_PinInit.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(SPI5_PORT, &Gyro_PinInit);
	//miso config
	Gyro_PinInit.Pin = SPI5_MISO;
	HAL_GPIO_Init(SPI5_PORT, &Gyro_PinInit);
	//mosi config
	Gyro_PinInit.Pin = SPI5_MOSI;
	HAL_GPIO_Init(SPI5_PORT, &Gyro_PinInit);

	Gyro_PinInit.Pin = NCS_MEMS_SPI;
	Gyro_PinInit.Mode = GPIO_MODE_OUTPUT_PP;
	Gyro_PinInit.Pull = GPIO_NOPULL;
	Gyro_PinInit.Speed = GPIO_SPEED_FREQ_HIGH;
	Gyro_PinInit.Alternate = 0;
	HAL_GPIO_Init(NCS_PORT, &Gyro_PinInit);


	//read the ref manual to find macros commands etc
	GyroInit.Instance = SPI5;
	GyroInit.Init.Direction = SPI_DIRECTION_2LINES;
	GyroInit.Init.Mode = SPI_MODE_MASTER;
	GyroInit.Init.DataSize = SPI_DATASIZE_8BIT;
	GyroInit.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	GyroInit.Init.CLKPhase = SPI_PHASE_1EDGE;
	GyroInit.Init.CLKPolarity = SPI_POLARITY_LOW;
	GyroInit.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	GyroInit.Init.CRCPolynomial = 10;
	GyroInit.Init.FirstBit = SPI_FIRSTBIT_MSB;
	GyroInit.Init.NSS = SPI_NSS_SOFT; //(???)
	GyroInit.Init.TIMode = SPI_TIMODE_DISABLE;

	HAL_SPI_Init(&GyroInit);
}

void Gyro_getDeviceID()
{
	uint8_t	sentCommand = (I3G4250D_READ | WHO_AM_I); //who am i config
	uint16_t dataRecieved = 0;

	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_TransmitReceive(&GyroInit, &sentCommand, (uint8_t*)&dataRecieved, DATA_TRANSFER, TESTING_TIMEOUT);
	Gyro_checkHALStatus();

	uint16_t dataReturned = (0xFF00 & dataRecieved) >> 0;
	printf("Device ID: 0x%x \n", dataReturned);
	Gyro_disableSlaveComm();
}

void Gyro_PowerOn()
{
	uint8_t sentCommand = (I3G4250D_READ | CTRL_REG1);
	uint16_t dataRecieved = 0;

	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_TransmitReceive(&GyroInit, &sentCommand, (uint8_t*)&dataRecieved, DATA_TRANSFER, TESTING_TIMEOUT);

	uint16_t dataReturned = (0xFF00 & dataRecieved) >> 8;
	uint16_t command = (I3G4250D_WRITE | CTRL_REG1 | ((dataReturned) | 1 << PD_OFFSET) << 8);
	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_Transmit(&GyroInit, (uint8_t*)&command, DATA_TRANSFER, TESTING_TIMEOUT);
	Gyro_checkHALStatus();
	Gyro_disableSlaveComm();
}

void Gyro_getTemp()
{
	uint8_t sentCommand = (I3G4250D_READ | OUT_TEMP);
	uint16_t dataRecieved = 0;

	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_TransmitReceive(&GyroInit, &sentCommand, (uint8_t*)&dataRecieved, DATA_TRANSFER, TESTING_TIMEOUT);
	Gyro_checkHALStatus();

	uint16_t dataReturned = (0xFF00 & dataRecieved) >> 8;
	printf("Device Temperature: %d \n", dataReturned + 7); //account for offset
	Gyro_disableSlaveComm();
}

void Gyro_RegConfig() //we need to set bits only in CR1 and CR5, ignore the FIFO due to read the gyro coords which we don't need
{
	uint16_t sentCommand = (I3G4250D_WRITE | CTRL_REG1 | CR1_CONFIG);

	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_Transmit(&GyroInit,(uint8_t*)&sentCommand, DATA_TRANSFER, TESTING_TIMEOUT);
	Gyro_checkHALStatus();
	Gyro_disableSlaveComm();

	sentCommand = (I3G4250D_WRITE | CTRL_REG5 | CR5_CONFIG);
	Gyro_enableSlaveComm();
	while(HAL_GPIO_ReadPin(NCS_PORT, NCS_MEMS_SPI) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_Transmit(&GyroInit,(uint8_t*)&sentCommand, DATA_TRANSFER, TESTING_TIMEOUT);
	Gyro_checkHALStatus();
	Gyro_disableSlaveComm();
}

void Gyro_checkHALStatus()
{
	if(gyroHALStatus != HAL_OK)
		APPLICATION_ASSERT(0);
}

void Gyro_enableSlaveComm()
{
	HAL_GPIO_WritePin(NCS_PORT, NCS_MEMS_SPI, GPIO_PIN_RESET);
}

void Gyro_disableSlaveComm()
{
	HAL_GPIO_WritePin(NCS_PORT, NCS_MEMS_SPI, GPIO_PIN_SET);
}
