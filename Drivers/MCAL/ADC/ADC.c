/*
 * STM32F103C8T6_ADC.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Omar Zakaria
 */

#include "ADC.h"

uint8_t flag_ADC_INIT=0;

void MCAL_ADC_INIT(ADC_typeDef* ADCx,uint8_t ADC_STATE_){

	if(ADC_STATE_==ADC_STATE_START){
		if(ADCx==ADC1){
			RCC_ADC1_Enable();
		}
		else if(ADCx==ADC2){
			RCC_ADC2_Enable();
		}
		//		Bit 0 ADON: A/D converter ON / OFF
		//		This bit is set and cleared by software. If this bit holds a value of zero and a 1 is written to it
		//		then it wakes up the ADC from Power Down state.
		//		Conversion starts when this bit holds a value of 1 and a 1 is written to it. The application
		//		should allow a delay of tSTAB between power up and start of conversion. Refer to Figure 23.
		//		0: Disable ADC conversion/calibration and go to power down mode.
		//		1: Enable ADC and to start conversion
		ADCx->CR2 |=(1<<0);


		//		Bit 1 CONT: Continuous conversion
		//		This bit is set and cleared by software. If set conversion takes place continuously till this bit is
		//		reset.
		//		0: Single conversion mode
		//		1: Continuous conversion mode
		ADCx->CR2 &=~(1<<1);

		//		Bit 2 CAL: A/D Calibration
		//		This bit is set by software to start the calibration. It is reset by hardware after calibration is
		//		complete.
		//		0: Calibration completed
		//		1: Enable calibratio
		ADCx->CR2 |=(1<<2);
		while(((ADCx->CR2>>2)&1)){};

		flag_ADC_INIT=1;
	}
	else{

		ADCx->CR2 &=~(1<<0);
		RCC_ADC1_DISABLE();
		RCC_ADC2_DISABLE();
		flag_ADC_INIT=0;
	}
}

uint16_t MCAL_ADC_READ(ADC_typeDef* ADCx,uint8_t ADC_pin){

	if(flag_ADC_INIT){


	GPIO_PinConfig_t ADC_Pin;
	if(ADC_pin<0b0111){
		GPIO_PinConfig_t ADC_Pin={
				.GPIO_MODE= GPIO_ANALOG_MODE,
				.GPIO_Output_Speed =GPIO_SPEED_10M,
				.GPIO_Port= GPIOA,
				.GPIO_PinNumber=ADC_pin};
	}
	else{
		GPIO_PinConfig_t ADC_Pin={
				.GPIO_MODE= GPIO_ANALOG_MODE,
				.GPIO_Output_Speed =GPIO_SPEED_10M,
				.GPIO_Port= GPIOB,
				.GPIO_PinNumber=ADC_pin };
	}

	gpio_pin_intialize(&ADC_Pin);

	ADCx->CR2=0;
	ADCx->SQR3 =0;

	//Bits 4:0 SQ1[4:0]: first conversion in regular sequence
	ADCx->SQR3 |=(ADC_pin << 0);






	//		Bit 0 ADON: A/D converter ON / OFF
	//		This bit is set and cleared by software. If this bit holds a value of zero and a 1 is written to it
	//		then it wakes up the ADC from Power Down state.
	//		Conversion starts when this bit holds a value of 1 and a 1 is written to it. The application
	//		should allow a delay of tSTAB between power up and start of conversion. Refer to Figure 23.
	//		0: Disable ADC conversion/calibration and go to power down mode.
	//		1: Enable ADC and to start conversion
	ADCx->CR2 |=(1<<0);
	ADCx->CR2 |=(1<<0);

	//		Bit 22 SWSTART: Start conversion of regular channels
	//		This bit is set by software to start conversion and cleared by hardware as soon as
	//		conversion starts. It starts a conversion of a group of regular channels if SWSTART is
	//		selected as trigger event by the EXTSEL[2:0] bits.
	//		0: Reset state
	//		1: Starts conversion of regular channels
	ADCx->CR2 |=(1<<22);

	//		Bit 1 EOC: End of conversion
	//		This bit is set by hardware at the end of a group channel conversion (regular or injected). It is
	//		cleared by software or by reading the ADC_DR.
	//		0: Conversion is not complete
	//		1: Conversion complete
	while(! ((ADCx->SR>>1)&1) ){};

	return((uint16_t)ADCx->DR);

	}
	else{
		return 0;
	}

}



