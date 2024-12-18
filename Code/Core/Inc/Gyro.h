/*
 * Gyro.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Ethan
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include <ErrorHandling.h>
#include <stm32f4xx_hal.h>
#include <stdio.h>

//pin and port macros
#define SPI5_PORT	GPIOF
#define SPI5_SCK	GPIO_PIN_7
#define SPI5_MISO	GPIO_PIN_8
#define SPI5_MOSI	GPIO_PIN_9
#define NCS_PORT	GPIOC
#define NCS_MEMS_SPI	GPIO_PIN_1

//register defn (ignoring reserves)
#define	WHO_AM_I	0x0F
#define	CTRL_REG1	0x20
#define CTRL_REG2	0x21
#define CTRL_REG3	0x22
#define	CTRL_REG4	0x23
#define CTRL_REG5	0x24
#define REFERENCE	0x25
#define OUT_TEMP	0x26
#define STATUS_REG	0x27
#define OUT_X_L 	0x28
#define OUT_X_H		0x29
#define OUT_Y_L		0x2A
#define OUT_Y_H		0x2B
#define OUT_Z_L 	0x2C
#define OUT_Z_H		0x2D
#define FIFO_CTRL_REG	0x2E
#define FIFO_SRC_REG	0x2F
#define INT1_CFG	0x30
#define INT1_SRC	0x31
#define INT1_THS_XH	0x32
#define INT1_THS_XL 0x33
#define INT1_THS_YH	0x34
#define INT1_THS_YL	0x35
#define INT1_THS_ZH	0x36
#define INT1_THS_ZL	0x37
#define INT1_DURATION	0x38

//prototypes
void Gyro_Init();
void Gyro_getDeviceID();
void Gyro_PowerOn();
void Gyro_getTemp();
void Gyro_RegConfig();
void Gyro_readReg();
void Gyro_checkHALStatus();
void Gyro_enableSlaveComm();
void Gyro_disableSlaveComm();

//misc macros
#define	PD_OFFSET	3
#define CR1_CONFIG	(0x0F << 8)
#define CR5_CONFIG	(0xC0 << 8)
#define TESTING_TIMEOUT	2000
#define I3G4250D_READ	(1 << 7)
#define I3G4250D_WRITE	(0 << 7)
#define DATA_TRANSFER	2

#endif /* INC_GYRO_H_ */
