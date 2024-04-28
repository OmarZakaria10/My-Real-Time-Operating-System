/*
 * keypad.h
 *
 * Created: 4/22/2021 6:32:00 PM
 *  Author: Marco
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_
/* ----------------- Includes -----------------*/
#include "STM32F103C6.h"
#include "GPIO.h"
/* ----------------- Macro Declarations -----------------*/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
	GPIO_PinConfig_t keypad_row_pins[ECU_KEYPAD_ROWS];
	GPIO_PinConfig_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/

Std_ReturnType keypad_initialize( keypad_t *_keypad_obj);
char keypad_get_value( keypad_t *_keypad_obj);
char keypad_get_value_blocking( keypad_t *_keypad_obj);

#endif /* KEYPAD_H_ */
