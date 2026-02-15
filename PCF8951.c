/**
 * @file    PCF8951.c
 * @brief   This file provides code for initializing and using the functions of the PCF8951.
 * @author  虚字潜心(xu_zi_qian_xin)
 * @version 1.1.0
 * @date    2026-02-15
 * 
 * @copyright Copyright (c) 2026 虚字潜心. All rights reserved.
 * @license  SPDX-License-Identifier: MIT
 */

#include "PCF8951.h"

/**
	* @brief Function to initialize the PCF8961
	* @param PCF8951 The chip structure can pass in different chip parameters to carry out multi-slave communication.
	* @return The error codes of IIC are provided by the library functions.
	* @note This function is used when using the ADC feature, it is not needed when using the DAC feature.
	*/
uint32_t PCF8951_Init(PFC8951_Typedef PCF8951)
{
	IIC_TRANSMIT(PCF8951.PCF8951AddressWrite, &PCF8951.PCF8951ControlByte, 1);
	return IIC_ERROR_FLAG;
}

/**
	* @brief Used to drive DAC function output voltage
	* @param PCF8951 The chip structure can pass in different chip parameters to carry out multi-slave communication.
	* @param pdata An array of output voltages, with the first byte of the array being the control byte.
	* @param size Array size
	* @return The error codes of IIC are provided by the library functions.
  * @note Due to API requirements, the first byte of the array in this function must be a control byte. 
	*				You cannot use this function to output directly after using the initialization function alone.
	*/
uint32_t PCF8951_DAC_Output(PFC8951_Typedef PCF8951, uint8_t *pdata, uint16_t size)
{
	IIC_TRANSMIT(PCF8951.PCF8951AddressWrite, pdata, size);
	return IIC_ERROR_FLAG;
}

/**
	* @brief Used to drive ADC to read voltage
	* @param PCF8951 The chip structure can pass in different chip parameters to carry out multi-slave communication.
	* @param pdata Array for storing read converted values
	* @param size Array size
	* @return The error codes of IIC are provided by the library functions.
	* @note Before using this function, the chip must be initialized and configured with the initialization function.
	*/
uint32_t PCF8951_ADC_intput(PFC8951_Typedef PCF8951, uint8_t *pdata, uint16_t size)
{
	IIC_RE(PCF8951.PCF8951AddressRead, pdata, size);
	return IIC_ERROR_FLAG;
}

/**
	* @brief Used to convert between floating-point arrays and digital arrays
	* @param digitalArray digital arrays
	* @param floatArray floating-point arrays
	* @param size Array size
	* @param transformatioMode
	* @return Returning 0 means normal, returning any other number indicates there is a problem with your mode selection.
	*/
uint32_t PCF8951_Data_Transformation(uint8_t *digitalArray, double *floatArray, uint16_t size, uint8_t transformatioMode)
{
	switch(transformatioMode)
	{
		case PCF_DIGITAL_TO_FLAOT:
			for(uint16_t i = 0; i < size; i++)
			{
				floatArray[i] = digitalArray[i] * (PCF8951_VREF - PCF8951_VGND) / 256;
			}
			break;
		case PCF_FLAOT_TO_DIGITAL:
			for(uint16_t i = 0; i < size; i++)
			{
				digitalArray[i] = floatArray[i] / (((PCF8951_VREF - PCF8951_VGND) / 256) + PCF8951_VGND);
			}
			break;
		default:
			return transformatioMode;
	}
	return 0;
}
