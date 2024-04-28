/*
 * STM32F103C8T6_ADC.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Omar Zakaria
 */

#ifndef STM32F103C6_ADC_H_
#define STM32F103C6_ADC_H_


#include "STM32F103C6.h"
#include "GPIO.h"

#define ADC_STATE_START  1
#define ADC_STATE_STOP   0

void MCAL_ADC_INIT(ADC_typeDef* ADCx,uint8_t ADC_STATE_);

uint16_t MCAL_ADC_READ(ADC_typeDef* ADCx,uint8_t ADC_pin);

void MCAL_ADC_DeInit(ADC_typeDef* ADCx);

#endif /* INC_STM32F103C6_ADC_H_ */
