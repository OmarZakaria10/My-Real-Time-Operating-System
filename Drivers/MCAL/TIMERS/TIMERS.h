/*
 * TIMER.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar Zakaria
 */

#ifndef MCAL_TIMERS_TIMERS_H_
#define MCAL_TIMERS_TIMERS_H_

/* =========================== Includes =========================== */


#include "RCC.h"
#include "GPIO.h"


typedef struct{
	TIMERS_typeDef* TIMERx;
	uint32_t FREQUENCY;
	uint32_t CLOCK;

}TIMER_t;

void PWM(TIMER_t* CONF,uint32_t CH,uint32_t duty_cycle);
#endif /* MCAL_TIMERS_TIMERS_H_ */
