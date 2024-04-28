/*
 * PWM.c
 *
 *  Created on: Sep 15, 2023
 *      Author: Omar Zakaria
 */
#include <TIMERS.h>
void PWM(TIMER_t* CONF,uint32_t CH,uint32_t duty_cycle){
	CONF->TIMERx->CR1 &=~(1<<0);//Counter disabled
	GPIO_PinConfig_t pin;
	char user_flage=1;
	uint32_t AUTO_RELOAD=0;
	uint32_t PRESCALE=1;

	while(user_flage==1){
		AUTO_RELOAD = (CONF->CLOCK)/(CONF->FREQUENCY * PRESCALE );
		if(AUTO_RELOAD>=32000){
			PRESCALE+=2;
		}
		else{
			user_flage=0;
		}
	}

	if(CONF->TIMERx == TIM2){
		RCC_TIMER2_Enable();
		RCC_GPIOA_CLK_EN();
		RCC_AFIO_CLK_EN();

		if(CH==1){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=0 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);

			CONF->TIMERx->CCMR1 |=(1<<3);
			CONF->TIMERx->CCER |=(1<<0);
			CONF->TIMERx->CCMR1 |=(0b110<<4);
			CONF->TIMERx->CCR1=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b11<<0);
		}
		else if(CH==2){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=1 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);
			CONF->TIMERx->CCMR1 |=(1<<11);
			CONF->TIMERx->CCER |=(1<<4);
			CONF->TIMERx->CCMR1 |=(0b110<<12);
			CONF->TIMERx->CCR2=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b101<<0);
		}
		else if(CH==3){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=2 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);
			CONF->TIMERx->CCMR2 |=(1<<3);
			CONF->TIMERx->CCER |=(1<<8);
			CONF->TIMERx->CCMR2 |=(0b110<<4);
			CONF->TIMERx->CCR3=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b1001<<0);
		}
		else if(CH==4){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=3 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);
			CONF->TIMERx->CCMR2 |=(1<<11);
			CONF->TIMERx->CCER |=(1<<12);
			CONF->TIMERx->CCMR2 |=(0b110<<12);
			CONF->TIMERx->CCR4=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b10001<<0);
		}
	}
	else if (CONF->TIMERx==TIM3){
		RCC_TIMER3_Enable();//enable timer3 clock
		RCC_GPIOA_CLK_EN();
		RCC_GPIOB_CLK_EN();
		RCC_AFIO_CLK_EN();

		if(CH==1){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=6 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);

			CONF->TIMERx->CCMR1 |=(1<<3);
			CONF->TIMERx->CCER |=(1<<0);
			CONF->TIMERx->CCMR1 |=(0b110<<4);
			CONF->TIMERx->CCR1=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b11<<0);
		}
		else if(CH==2){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=7 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);

			CONF->TIMERx->CCMR1 |=(1<<11);
			CONF->TIMERx->CCER |=(1<<4);
			CONF->TIMERx->CCMR1 |=(0b110<<12);
			CONF->TIMERx->CCR2=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b101<<0);
		}
		else if(CH==3){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=0 ;
			pin.GPIO_Port =GPIOB;
			gpio_pin_intialize(&pin);

			CONF->TIMERx->CCMR2 |=(1<<3);
			CONF->TIMERx->CCER |=(1<<8);
			CONF->TIMERx->CCMR2 |=(0b110<<4);
			CONF->TIMERx->CCR3=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b1001<<0);
		}
		else if(CH==4){
			pin.GPIO_MODE =GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			pin.GPIO_Output_Speed =GPIO_SPEED_50M;
			pin.GPIO_PinNumber=1 ;
			pin.GPIO_Port =GPIOA;
			gpio_pin_intialize(&pin);

			CONF->TIMERx->CCMR2 |=(1<<11);
			CONF->TIMERx->CCER |=(1<<12);
			CONF->TIMERx->CCMR2 |=(0b110<<12);
			CONF->TIMERx->CCR4=(AUTO_RELOAD*duty_cycle*10/1000);//duty cycle
			CONF->TIMERx->DIER |=(0b10001<<0);
		}
	}


	//	ARPE: Auto-reload preload enable
	//	0: TIMx_ARR register is not buffered
	//	1: TIMx_ARR register is buffered
	CONF->TIMERx->CR1 |=(1<<7);


	//	110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1


	CONF->TIMERx->ARR=AUTO_RELOAD;//frec peak value

	CONF->TIMERx->PSC=(PRESCALE-1);//prescaller

	//	Bit 15 MOE: Main output enable
	//	This bit is cleared asynchronously by hardware as soon as the break input is active. It is set
	//	by software or automatically depending on the AOE bit. It is acting only on the channels
	//	which are configured in output.
	//	0: OC and OCN outputs are disabled or forced to idle state.
	//	1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in
	//	TIMx_CCER register).
	//	See OC/OCN enable description for more details
	//TIMERx->TIMx_BDTR |=(1<<15);

	//	Bit 2 CC2IE: Capture/Compare 2 interrupt enable
	//	0: CC2 interrupt disabled
	//	1: CC2 interrupt enabled
	//	Bit 1 CC1IE: Capture/Compare 1 interrupt enable
	//	0: CC1 interrupt disabled
	//	1: CC1 interrupt enabled
	//	Bit 0 UIE: Update interrupt enable
	//	0: Update interrupt disabled
	//	1: Update interrupt enabled
	//TIMERx->TIMx_DIER |=(0b101<<0);

	//	UG: Update generation
	//	This bit can be set by software, it is automatically cleared by hardware.
	//	0: No action
	//	1: Reinitialize the counter and generates an update of the registers. Note that the prescaler
	//	counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared if
	//	the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload
	//	value (TIMx_ARR) if DIR=1 (downcounting).
	CONF->TIMERx->EGR |=(1<<0);
	//CONF->TIMERx->CCMR1 |=0b110<((CH - 1) * 4);
	CONF->TIMERx->CR1 |=(1<<0);//enable the timer

}





