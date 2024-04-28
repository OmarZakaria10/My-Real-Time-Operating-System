#include "keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] =
{
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'#', '0', '=', '+'}
};



Std_ReturnType keypad_initialize( keypad_t *_keypad_obj){

	uint8 rows_counter = 0, columns_counter = 0;

	for(rows_counter=0; rows_counter<ECU_KEYPAD_ROWS; rows_counter++){
		gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
	}
	for(columns_counter=ZERO_INIT; columns_counter<ECU_KEYPAD_COLUMNS; columns_counter++){
		gpio_pin_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
	}
	//gpio_port_write_logic(GPIOA, 0xFF);

}




char keypad_get_value( keypad_t *_keypad_obj){
	int i, j , k;
	logic_t logic;
	//while (1){
		for (i = 0; i < 4; i++) {
			for (k=0 ; k<4 ;k++)
				//MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[k], GPIO_PIN_RESET);
				gpio_pin_write_logic(&(_keypad_obj->keypad_columns_pins[k]), GPIO_PIN_RESET);

			//MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[i], GPIO_PIN_SET);
			gpio_pin_write_logic(&(_keypad_obj->keypad_columns_pins[i]), GPIO_PIN_SET);
			for (j = 0; j < 4; j++) {

				if (gpio_pin_read_logic(&(_keypad_obj->keypad_row_pins[j])) == 1) {
					while (gpio_pin_read_logic(&(_keypad_obj->keypad_row_pins[j])) == 1);

					return btn_values[i][j];

				}
			}
		}

	//}
}

char keypad_get_value_blocking( keypad_t *_keypad_obj){
	int i, j , k;
	logic_t logic;
	while (1){
		for (i = 0; i < 4; i++) {
			for (k=0 ; k<4 ;k++)
				//MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[k], GPIO_PIN_RESET);
				gpio_pin_write_logic(&(_keypad_obj->keypad_columns_pins[k]), GPIO_PIN_RESET);

			//MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[i], GPIO_PIN_SET);
			gpio_pin_write_logic(&(_keypad_obj->keypad_columns_pins[i]), GPIO_PIN_SET);
			for (j = 0; j < 4; j++) {

				if (gpio_pin_read_logic(&(_keypad_obj->keypad_row_pins[j])) == 1) {
					while (gpio_pin_read_logic(&(_keypad_obj->keypad_row_pins[j])) == 1);

					return btn_values[i][j];

				}
			}
		}

	}
}




