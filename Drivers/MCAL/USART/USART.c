
/*
 * stm32f103x8_USART_driver.h
 *
 *      Author: Omar Zakaria
 */

#include <USART.h>



/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
static void (*USART_INT_CALLBACK [3])(void);
/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */


/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

/**================================================================
 * @Fn				-MCAL_UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for Now Asynch mode & Clock 8 MHZ S

 /  */

void MCAL_UART_Init ( UART_Config* UART_Config)
{
	uint32_t pclk ,BRR  ;

	//	enable the Clock for given USART peripheral
	if ( UART_Config->USARTx == USART1 ){
		RCC_USART1_CLK_EN();
		USART_INT_CALLBACK [0] = UART_Config->P_IRQ_CallBack;
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else if ( UART_Config->USARTx == USART2 ){
		RCC_USART2_CLK_EN();
		USART_INT_CALLBACK [1] = UART_Config->P_IRQ_CallBack;
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
	else if ( UART_Config->USARTx == USART3 ){
		RCC_USART3_CLK_EN();
		USART_INT_CALLBACK [2] = UART_Config->P_IRQ_CallBack;
		pclk = MCAL_RCC_GetPCLK1Freq();
	}


	//Enable USART Module
	//	USART_CR1  Bit 13 UE: USART enable
	UART_Config->USARTx->CR1 |= 1<<13 ;

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//	USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	UART_Config->USARTx->CR1 |= UART_Config->USART_Mode ;

	//PAYLOAD Width
	// USARTx->CR1  Bit 12 M: Word length
	UART_Config->USARTx->CR1 |= UART_Config->Payload_Length ;

	//Configuration of parity control bit fields
	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	UART_Config->USARTx->CR1 |= UART_Config->Parity ;

	//configure the number of stop bits
	//USART_CR2  Bits 13:12 STOP: STOP bits
	UART_Config->USARTx->CR2 |= UART_Config->StopBits ;


	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	UART_Config->USARTx->CR3 |= UART_Config->HwFlowCtl ;

	BRR = UART_BRR_Register(pclk, UART_Config->BaudRate) ;
	UART_Config->USARTx->BRR = BRR ;

	/* 9. ENABLE / DISABLE Interrupt */
	uint8_t interrupts =0;
	interrupts |= UART_Config->RXNEIE_IRQ_Enable
			| (UART_Config->TCIE_IRQ_Enable<<1)
			| (UART_Config->TXEIE_IRQ_Enable<<2)
			| (UART_Config->PEIE_IRQ_Enable<<3);
	UART_Config->USARTx->CR1 |=  interrupts<<5;

	if (UART_Config->USARTx == USART1)
		NVIC_IRQ37_USART1_Enable;

	else if (UART_Config->USARTx == USART2)
		NVIC_IRQ38_USART2_Enable;

	else if (UART_Config->USARTx == USART3)
		NVIC_IRQ39_USART3_Enable;

}
/* ================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief			- DEInit UART Asynchronous only
 * @param [in] 		- USARTx where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer buffer
 * @param [in] 		- Polling Enable or disable
 * @retval 			- none
 * Note				- Initialize UART first
 */
void MCAL_UART_DeInit(UART_Config* UART_Config)
{
	if (UART_Config->USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}

	else if (UART_Config->USARTx == USART3)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable;
	}

	else if (UART_Config->USARTx == USART2)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}
/* ================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- Send buffer on UART
 * @param [in] 		- USARTx where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer buffer
 * @param [in] 		- Polling Enable or disable
 * @retval 			- none
 * Note				- Initialize UART first
 * 					- when transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register)
 * 					- the value written in the MSB ( bit 7 or bit 8 depending on the data length ) has no effect
 * 					- because it is replaced by the parity
 * 					- when receiving with the parity enabled the value read in the MSB bit is the received parity bit
 */

void MCAL_UART_SendData	(UART_Config* UART_Config, uint16_t *pTxBuffer,enum Polling_mechism PollingEn )
{
	/* 1. Wait until TXE flag is set in the SR */
	if (PollingEn == enable)
	{
		/*
		 * The TXE bit is set by hardware and it indicates:
		 * The data has been moved from TDR to the shift register and the data transmission has started.
		 * The TDR register is empty.
		 * The next data can be written in the USART_DR register without overwriting the previous data.
		 */
		while (!(UART_Config->USARTx->SR & 1<<7));
	}

	/* 2. Check the USART_WordLength item for 9-bit or 8-bit in a frame */

	/* When Transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	 * the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	 * because it is replaced by the parity.
	 * When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
	 *
	 */
	if (UART_Config->Payload_Length == UART_Payload_Length_8B)
	{
		UART_Config->USARTx->DR = (*pTxBuffer) & (uint8_t)0xFF ;
	}
	else if (UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		UART_Config->USARTx->DR = (*pTxBuffer) & (uint16_t)0x1FF ;
	}


}
void SendFrame (USART_TypeDef * uart, char str []){
	uint32_t size =strlen(str);
	for (int i = 0; i < size; i++) {
		MCAL_UART_SendData(uart,(str+i), 1);
		MCAL_UART_WAIT_TC(uart);
	}
}

void MCAL_UART_WAIT_TC(UART_Config* UART_Config)
{
	/* Wait till TC flag is set in the SR */
	while(!(UART_Config->USARTx->SR & 1<<6));
}

void MCAL_UART_ReceiveData(UART_Config* UART_Config, uint16_t* pRxBuffer, enum Polling_mechism PollingEn)
{
	/* 1. Wait until RXNE flag is set in the SR */
	if (PollingEn == enable)
	{
		while (!(UART_Config->USARTx->SR & 1<<5));
	}

	/* 2. Check the USART_WordLength item for 9-bit or 8-bit in a frame */

	/* 9 Bits Data */
	if (UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		if (UART_Config->Parity == UART_Parity__NONE)
		{
			/* All 9 bits are data */
			*pRxBuffer = UART_Config->USARTx->DR ;
		}
		else
		{
			/* Just least byte is data */
			*pRxBuffer = UART_Config->USARTx->DR & (uint8_t)0xFF ;
		}
	}
	/* 8 Bits Data */
	else
	{
		if (UART_Config->Parity == UART_Parity__NONE)
		{
			/* All 8 bits are data */
			*pRxBuffer = UART_Config->USARTx->DR & (uint8_t)0xFF  ;
		}
		else
		{
			/* just least 7 bits are data */
			*pRxBuffer = UART_Config->USARTx->DR & (uint8_t)0x7F ;
		}
	}
}
/* ================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief			- Initializes GPIO Pins
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- None
 * @Notes			- Should enable the corresponding ALT & GPIO in RCC clock . Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins(UART_Config* UART_Config)
{

	GPIO_PinConfig_t Pin_Config;

	if (UART_Config->USARTx == USART1)
	{
		// PA9 Tx
		// PA10 Rx
		// PA11 CTS
		// PA12 RTS

		// PA9 Tx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_9;
		Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
		Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
		Pin_Config.GPIO_Port= GPIOA;

		gpio_pin_intialize(&Pin_Config);

		// PA10 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_10;
		Pin_Config.GPIO_MODE = GPIO_ALT_INPUT_MODE;
		Pin_Config.GPIO_Port= GPIOA;
		gpio_pin_intialize(&Pin_Config);

		if (UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA11 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_11;
			Pin_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			Pin_Config.GPIO_Port= GPIOA;
			gpio_pin_intialize( &Pin_Config);
		}

		if (UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA12 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_12;
			Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			Pin_Config.GPIO_Port= GPIOA;
			gpio_pin_intialize( &Pin_Config);
		}

	}
	else if (UART_Config->USARTx == USART2)
	{
		// PA2 Tx
		// PA3 Rx
		// PA0 CTS
		// PA1 RTS

		// PA2 Tx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_2;
		Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
		Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
		Pin_Config.GPIO_Port= GPIOA;
		gpio_pin_intialize( &Pin_Config);

		// PA3 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_3;
		Pin_Config.GPIO_MODE = GPIO_ALT_INPUT_MODE;
		Pin_Config.GPIO_Port= GPIOA;
		gpio_pin_intialize( &Pin_Config);

		if (UART_Config->HwFlowCtl || UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS)
		{
			// PA0 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_0;
			Pin_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			Pin_Config.GPIO_Port= GPIOA;
			gpio_pin_intialize( &Pin_Config);
		}



		if (UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA1 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_1;
			Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			Pin_Config.GPIO_Port= GPIOA;
			gpio_pin_intialize( &Pin_Config);
		}

	}
	else if (UART_Config->USARTx == USART3)
	{
		// PB10 Tx
		// PB11 Rx
		// PA13 CTS
		// PA14 RTS

		// PB10 Tx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_10;
		Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
		Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
		Pin_Config.GPIO_Port= GPIOB;
		gpio_pin_intialize( &Pin_Config);

		// PB11 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_11;
		Pin_Config.GPIO_MODE = GPIO_ALT_INPUT_MODE;
		Pin_Config.GPIO_Port= GPIOB;
		gpio_pin_intialize( &Pin_Config);

		if (UART_Config->HwFlowCtl || UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS)
		{
			// PA11 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_13;
			Pin_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			Pin_Config.GPIO_Port= GPIOB;
			gpio_pin_intialize( &Pin_Config);
		}



		if (UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA12 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_14;
			Pin_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			Pin_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			Pin_Config.GPIO_Port= GPIOA;
			gpio_pin_intialize( &Pin_Config);
		}
	}
}



void USART1_IRQHandler (void)
{
	USART_INT_CALLBACK [0]();
}

void USART2_IRQHandler (void)
{
	USART_INT_CALLBACK [1]();
}

void USART3_IRQHandler (void)
{
	USART_INT_CALLBACK [2]();
}
































