/*
 * stm32f103x8_SPI_driver.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Omar Zakaria
 *
 */

/* =========================== Includes =========================== */
#include "SPI.h"

/* ===================== Generic Variables ======================== */
static void (*SPI_INT_CALLBACK [2])(void);





/* ======================== Public APIs =========================== */

/* ================================================================
 * @Fn 				- MCAL_SPI_Init
 * @brief 			- Initializes SPIx according to the specified parameters in SPI_Config_t
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- Config : a pointer to SPI_Config_t structure that contains the configuration information for the specified SPI Module
 * @retval 			- None
 * Note 			- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 * 					- You have to configure RCC to select clock for the selected SPI Module
 */
void MCAL_SPI_Init( SPI_Config_t *Config)
{
	/* Safety for register, Using this technique for protect the peripheral form working before the full configurations */
	uint16_t tempReg_CR1 = 0;
	uint16_t tempReg_CR2 = 0;

	if(Config->SPIx == SPI1)
	{
		/* 1. Open the SPI1 RCC Clock */
		RCC_SPI1_CLK_EN();
	}
	else if(Config->SPIx == SPI2)
	{
		/* 1. Open the SPI1 RCC Clock */
		RCC_SPI2_CLK_EN();
	}

	/* 2. Enable the SPI */
	tempReg_CR1 |= (uint16_t)(1<<6); 	/* Bit 6 SPE: SPI enable */

	/* 3. Set Master or Slave */
	tempReg_CR1 |= Config->SPI_Mode;

	/* 4. Set Communication Mode */
	tempReg_CR1 |= Config->Communication_Mode;

	/* 5. Set Frame format */
	tempReg_CR1 |= Config->Frame_Format;

	/* 6. Set Data size */
	tempReg_CR1 |= Config->Frame_Size;

	/* 7. Set Clock Polarity */
	tempReg_CR1 |= Config->CLK_Polarity;

	/* 8. Set Clock Phase */
	tempReg_CR1 |= Config->CLK_Phase;

	/* 9. Set Slave Select Management */
	if(Config->NSS == NSS_HW_MASTER_SS_OUTPUT_ENABLED)
	{
		tempReg_CR2 |= Config->NSS;
	}
	else if(Config->NSS == NSS_HW_MASTER_SS_OUTPUT_DISABLED)
	{
		tempReg_CR2 &= Config->NSS;
	}
	else
	{
		tempReg_CR1 |= Config->NSS;
	}

	/* 10. Set BoudRate Pre-scaler */
	tempReg_CR1 |= Config->BaudRate_Prescaler;

	/* 11. Set Interrupt Type */
	if(Config->ERRI_INT_EN || Config->RXNE_INT_EN || Config->TXE_INT_EN)
	{
		SPI_INT_CALLBACK[0]=Config->SPI1_IRQ_CallBack;
		SPI_INT_CALLBACK[1]=Config->SPI2_IRQ_CallBack;
		tempReg_CR2 |= (Config->ERRI_INT_EN <<5) |(Config->RXNE_INT_EN <<6) |(Config->TXE_INT_EN <<7);

		/* 12. Open the global Interrupt for each peripheral */
		if (Config->SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;
		}
		else if(Config->SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	/*13. Config your register using the temp register used to protect the configurations */
	Config->SPIx->SPI_CR1 = tempReg_CR1;
	Config->SPIx->SPI_CR2 = tempReg_CR2;

}


/* ================================================================
 * @Fn 				- MCAL_SPI_DeInit
 * @brief 			- Resets Selected SPI Module
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}
/* ================================================================
 * @Fn 				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Must open clock for AFIO & GPIO After GPIO Initialization
 * 					- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_Config_t *Config)
{
	GPIO_PinConfig_t SPI_GPIO_Config;

	/* Depending the recommendation in data sheet -> Table 25. SPI 	*/
	/*  "SPI pin-out"    "Configuration"     "GPIO configuration" 	*/
	if (Config->SPIx == SPI1)
	{
		if(Config->SPI_Mode == SPI_MODE_MASTER) /* Master */
		{
			/* PA4 : SPI1_NSS */
			switch (Config->NSS)
			{
			 	 /* Input */
				case NSS_HW_MASTER_SS_OUTPUT_DISABLED:
					/* Hardware Master/Slave Input Floating */
					SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
					SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
					SPI_GPIO_Config.GPIO_Port= GPIOA;
					gpio_pin_intialize( &SPI_GPIO_Config);
					break;

				/* Output */
				case NSS_HW_MASTER_SS_OUTPUT_ENABLED:
					/* Hardware Master/NNS Output Alternate function push-pull */
					SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
					SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
					SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
					SPI_GPIO_Config.GPIO_Port = GPIOA;
					gpio_pin_intialize( &SPI_GPIO_Config);
					break;
			}

			/* PA5 : SPI1_SCK */
			/* Master Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize( &SPI_GPIO_Config);

			/* PA6 : SPI1_MISO */
			/* Full duplex / master Input floating / Input pull-up */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize( &SPI_GPIO_Config);

			/* PA7 : SPI1_MOSI */
			/* Full duplex / master Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize( &SPI_GPIO_Config);
		}
		else /* Slave */
		{
			/* PA4 : SPI1_NSS */
			if(Config->NSS == NSS_HW_SLAVE)
			{
				/* Hardware Master/Slave Input Floating */
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
				SPI_GPIO_Config.GPIO_Port = GPIOA;
				gpio_pin_intialize(&SPI_GPIO_Config);
			}

			/* PA5 : SPI1_SCK */
			/* Slave Input floating */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* PA6 : SPI1_MISO */
			/* Full duplex / slave (point to point) Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* TODO Full duplex / slave (multi-slave) Alternate function open drain */

			/* PA7 : SPI1_MOSI */
			/* Full duplex / slave Input floating / Input pull-up */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOA;
			gpio_pin_intialize(&SPI_GPIO_Config);		}
	}
	else if(Config->SPIx == SPI2)
	{
		if(Config->SPI_Mode == SPI_MODE_MASTER) /* Master */
		{
			/* PB12 : SPI2_NSS */
			switch (Config->NSS)
			{
				 /* Input */
				case NSS_HW_MASTER_SS_OUTPUT_DISABLED:
					/* Hardware Master/Slave Input Floating */
					SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12;
					SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
					SPI_GPIO_Config.GPIO_Port = GPIOB;
					gpio_pin_intialize(&SPI_GPIO_Config);
					break;

				/* Output */
				case NSS_HW_MASTER_SS_OUTPUT_ENABLED:
					/* Hardware Master/NNS Output Alternate function push-pull */
					SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12;
					SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
					SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
					SPI_GPIO_Config.GPIO_Port = GPIOB;
					gpio_pin_intialize(&SPI_GPIO_Config);
					break;
			}

			/* PB13 : SPI2_SCK */
			/* Master Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_13;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* PB14 : SPI2_MISO */
			/* Full duplex / master Input floating / Input pull-up */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_14;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* PB15 : SPI2_MOSI */
			/* Full duplex / master Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_15;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);
		}
		else /* Slave */
		{
			/* PB12 : SPI2_NSS */
			if(Config->NSS == NSS_HW_SLAVE)
			{
				/* Hardware Master/Slave Input Floating */
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12;
				SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
				SPI_GPIO_Config.GPIO_Port = GPIOB;
				gpio_pin_intialize(&SPI_GPIO_Config);
			}

			/* PB13 : SPI2_SCK */
			/* Slave Input floating */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_13;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* PB14 : SPI2_MISO */
			/* Full duplex / slave (point to point) Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_14;
			SPI_GPIO_Config.GPIO_MODE = GPIO_ALT_OUTPUT_PUSHPULL_MODE;
			SPI_GPIO_Config.GPIO_Output_Speed = GPIO_SPEED_10M;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);

			/* TODO Full duplex / slave (multi-slave) Alternate function open drain */

			/* PB15 : SPI2_MOSI */
			/* Full duplex / slave Input floating / Input pull-up */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_15;
			SPI_GPIO_Config.GPIO_MODE = GPIO_FLOATING_INPUT_MODE;
			SPI_GPIO_Config.GPIO_Port = GPIOB;
			gpio_pin_intialize(&SPI_GPIO_Config);
		}
	}
}

/* ================================================================
 * @Fn 				- MCAL_SPI_Send_Data
 * @brief 			- Send Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer Which holds the Tx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_SPI_Send_Data(SPI_Config_t *Config, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	// TODO Checker

	if(Polling_En == SPI_enable)
	{
		/* Wait for transmission complete */
		while(! (Config->SPIx->SPI_SR & SPI_SR_TXE));
	}

	/* Start transmission, Write data to SPI data register */
	Config->SPIx->SPI_DR = (*pTxBuffer);
}
/* ================================================================
 * @Fn 				- MCAL_SPI_Recieve_Data
 * @brief 			- Receive Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pRxBuffer : Pointer to buffer which holds Rx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_Recieve_Data(SPI_Config_t *Config, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == SPI_enable)
	{
		/* Wait for reception complete */
		while(! (Config->SPIx->SPI_SR & SPI_SR_RXNE));
	}

	/* Start reception, Write data to SPI data register */
	*(pRxBuffer) = Config->SPIx->SPI_DR;
}

/* ================================================================
 * @Fn 				- MCAL_SPI_TX_RX
 * @brief 			- Transmit and Receive Data
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer which holds Transmit and Received data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_TX_RX(SPI_Config_t *Config, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == SPI_enable)
	{
		/* Wait for transmission complete */
		while(! (Config->SPIx->SPI_SR & SPI_SR_TXE));
	}

	/* Start transmission, Write data to SPI data register */
	Config->SPIx->SPI_DR = *(pTxBuffer);

/* =================================================== */

	if(Polling_En == SPI_enable)
	{
		/* Wait for reception complete */
		while(! (Config->SPIx->SPI_SR & SPI_SR_RXNE));
	}

	/* Start reception, Write data to SPI data register */
	*(pTxBuffer) = Config->SPIx->SPI_DR;
}

/* ================= IRQ Function Definitions ===================== */
/* ================================================================ */

void SPI1_IRQHandler(void)
{
	SPI_INT_CALLBACK [0]();
}


void SPI2_IRQHandler(void)
{
	SPI_INT_CALLBACK [1]();
}
