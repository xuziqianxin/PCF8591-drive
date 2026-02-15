/**
 * @file    PCF8951.h
 * @brief   This document contains all the function prototypes of the PCF8951.c file
 * @author  虚字潜心(xu_zi_qian_xin)
 * @version 1.1.0
 * @date    2026-02-15
 * 
 * @copyright Copyright (c) 2026 虚字潜心. All rights reserved.
 * @license  SPDX-License-Identifier: MIT
 */
 
#ifndef __PCF8951_H__
#define __PCF8951_H__

#ifdef __cplusplus
extern "C"{
#endif
/* IIC LIB Includes ----------------------------------------------------------*/
#include "ch32v30x_i2c.h"

/* Typedef ------------------------------------------------------------*/
/**
	* @brief Chip structure, facilitating communication management for multiple slave devices.
	*/
typedef struct PCF8951
{
	uint16_t PCF8951AddressWrite;			/* Chip Write Address */
	uint16_t PCF8951AddressRead;			/* Chip reading address */
	uint8_t PCF8951ControlByte;				/* controlByte The control byte used to initialize the chip can be generated using the PCF_CONTROL_BYTE macro. */
} PFC8951_Typedef;

/* Define ------------------------------------------------------------*/
/**
	* @brief Set the chip's reference voltage and ground voltage
	*/
#define PCF8951_VREF 3.3
#define PCF8951_VGND 0

/**
	* @brief Set the I2C address of the chip for read mode or write mode
	*/

#define PCF8951_ADR_W 0x90
#define PCF8951_ADR_R 0x91

/**
	* @brief Macro used for selecting channels
	*/
#define PCF_AD_CHANNEL_0 	00
#define PCF_AD_CHANNEL_1 	01
#define PCF_AD_CHANNEL_2 	10
#define PCF_AD_CHANNEL_3 	11

/**
	* @brief Macro used to select ADC mode
	*/
#define PCF_AD_MODE_SINGLE_ENDED 	00
#define PCF_AD_MODE_F_DIFFERENTIAL 	01
#define PCF_AD_MODE_MIXED 			10
#define PCF_AD_MODE_T_DIFFERENTIAL 	11

/**
	* @brief Used to select whether to enable the auto-increment bit
	*/
#define PCF_AUTO_INCREMENT_ENABLE	1
#define PCF_AUTO_INCREMENT_DISABLE 	0

/**
	* @brief Used to select whether it can simulate output
	*/
#define PCF_ANALOG_OUT_ENABLE 	1
#define PCF_ANALOG_OUT_DISABLE 	0

/**
	* @brief Array transformation mode used for selecting functions
	*/
#define PCF_DIGITAL_TO_FLAOT 		0
#define PCF_FLAOT_TO_DIGITAL		1

/**
	* @brief Macro used to send IIC data, replacing internal functions with functions of the target platform to complete the porting.
	* @param adr IIC device address
	* @param data Data that needs to be sent
	* @param size Data size
	*/
#define IIC_TRANSMIT(adr, data, size) \
do{\
	IIC_Transmit(I2C1, adr, data, size);\
}while(0)

/**
	* @brief Macro for receiving IIC data, with internal functions replaced by the target platform's functions to complete the porting.
	* @param adr IIC device address
	* @param data Data that needs to be sent
	* @param size Data size
	*/
#define IIC_RE(adr, data, size) \
do{\
	IIC_Receive(I2C1, adr, data, size);\
}while(0)

/**
	* @brief Get the macro for IIC communication errors and replace it with the function of the target platform to complete the porting.
	*/
#define IIC_ERROR_FLAG 0

/**
	* @brief Macro for generating control bytes
	* @param outputFlag Use the macro to select simulated output
	* @param inputMode Macro for selecting ADC input mode
	* @param autoIncrementFlag Use a macro to choose whether it is an auto-incrementing field
	* @param channelNumber Using macros to select channels
	*/
#define PCF_CONTROL_BYTE(outputFlag, inputMode, autoIncrementFlag, channelNumber) ((outputFlag << 6) + (inputMode << 4) + (autoIncrementFlag << 2) + channelNumber)

/* Function ------------------------------------------------------------*/
uint32_t PCF8951_Init(PFC8951_Typedef PCF8951);
uint32_t PCF8951_DAC_Output(PFC8951_Typedef PCF8951, uint8_t *pdata, uint16_t size);
uint32_t PCF8951_ADC_intput(PFC8951_Typedef PCF8951, uint8_t *pdata, uint16_t size);
uint32_t PCF8951_Data_Transformation(uint8_t *digitalArray, double *floatArray, uint16_t size, uint8_t transformatioMode);

void IIC_Transmit(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pdata, uint16_t size);
void IIC_Receive(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pdata, uint16_t size);

#ifdef __cplusplus
}
#endif
#endif /* __PCF8951_H__ */
