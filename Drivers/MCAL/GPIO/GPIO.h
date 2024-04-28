/*
 * stm32f103x8_gpio_driver.h
 *
 *  Created on: Aug 1, 2023
 *      Author: Omar Zakaria
 *      Mastering Embedded System Online Diploma
 *      www.learn-in-depth.com
 */
#ifndef GPIO_H_
#define GPIO_H_

#include "STM32F103C6.h"

#define HWREG8(_X)     (*((volatile uint8 *)(_X)))
#define BIT_MASK  (uint32_t) 1

#define SET_BIT(REG, BIT_POSN)     (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)   (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)  (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)


typedef enum {
	GPIO_ANALOG_MODE,
	GPIO_FLOATING_INPUT_MODE,
	GPIO_INPUT_PULLUP_MODE,
	GPIO_INPUT_PULLDOWN_MODE,
	GPIO_OUTPUT_PUSHPULL_MODE,
	GPIO_OUTPUT_OPENDRAIN_MODE,
	GPIO_ALT_OUTPUT_PUSHPULL_MODE,
	GPIO_ALT_OUTPUT_OPENDRAIN_MODE,
	GPIO_ALT_INPUT_MODE,

}GPIO_PinMODE_t;

/*	@ref GPIO_SPEED_define
		01: Output mode, max speed 10 MHz.
		10: Output mode, max speed 2 MHz.
		11: Output mode, max speed 50 MHz.
 */

typedef enum{
	GPIO_SPEED_10M=1,
	GPIO_SPEED_2M,
	GPIO_SPEED_50M
}GPIO_Output_Speed_t;




typedef enum {
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,

}GPIO_Pin_Num;

typedef struct
{
	GPIO_TypeDef *GPIO_Port ;

	GPIO_Pin_Num GPIO_PinNumber    ;     // Specifies the GPIO pins to be configured.
	// This parameter can be a value of @ref GPIO_PINS_define

	GPIO_PinMODE_t GPIO_MODE 	   	  ;		// Specifies the operating mode for the selected pins
	// This parameter can be a value of @ref GPIO_MODE_define

	GPIO_Output_Speed_t GPIO_Output_Speed ;    // Specifies the speed for the selected pins
	// This parameter can be a value of @ref GPIO_SPEED_define



}GPIO_PinConfig_t;
//================================
//Macros Configuration References
//================================


/*	@ref GPIO_MODE_define
		0: Analog mode
		1: Floating input (reset state)
		2: Input with pull-up
		3:  Input with  pull-down
		4: General purpose output push-pull
		5: General purpose output Open-drain
		6: Alternate function output Push-pull
		7: Alternate function output Open-drain
		8: Alternate function INPUT
 */

/*	@ref GPIO_PIN_OUTPUT_defines
 */
#define GPIO_PIN_SET                 1
#define GPIO_PIN_RESET               0


/*	@ref GPIO_Return_defines
 */
#define OK 						     1
#define ERROR 						 0


void gpio_pin_intialize(GPIO_PinConfig_t* PinConfig);
void gpio_pin_write_logic ( GPIO_PinConfig_t* PinConfig, logic_t logic);
void gpio_pin_toggle_logic ( GPIO_PinConfig_t* PinConfig);
logic_t gpio_pin_read_logic (GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit    (GPIO_TypeDef *GPIOx );

//READ  APIs
uint8_t  MCAL_GPIO_ReadPin		(GPIO_TypeDef *GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort		(GPIO_TypeDef *GPIOx);

//WRITE  APIs
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx , uint16_t Value);
void MCAL_GPIO_WritePin	(GPIO_TypeDef *GPIOx , uint16_t PinNumber, uint8_t Value);

void MCAL_GPIO_TogglePin		(GPIO_TypeDef *GPIOx , uint16_t PinNumber);


uint8_t MCAL_GPIO_LockPin	(GPIO_TypeDef *GPIOx , uint16_t PinNumber);




void delay_ms(uint32_t time) ;




#endif
