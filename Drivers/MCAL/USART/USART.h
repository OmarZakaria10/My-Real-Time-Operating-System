/*
 * stm32f103x8_gpio_driver.h
 *
 *  
 *      Author: Omar Zakaria

 */

#ifndef USART_H_
#define USART_H_

//includes

#include "GPIO.h"
#include "RCC.h"





//Configuration structure
typedef struct
{
	USART_TypeDef 			  *USARTx;               // Specifies USART number

	uint8_t        			  USART_Mode;     		  // Specifies the TX/RX Mode.
	// This parameter must be set based on @ref UART_Mode_define

	uint32_t  			      BaudRate ; 		    // This member configures the UART communication baud rate
	// This parameter must be set based on @ref UART_BaudRate_define

	uint8_t 				  Payload_Length;			// Specifies the number of data bits transmitted or received in a frame.
	// This parameter must be set based on @ref UART_Payload_Length_define


	uint8_t 				  Parity ;					//Specifies the parity mode.
	//@ref UART_Parity_define


	uint8_t 				  StopBits ;				//Specifies the number of stop bits transmitted
	//@ref UART_StopBits_define

	uint8_t 				  HwFlowCtl ;				//Specifies whether the hardware flow control mode is enabled or disabled
	//@ref UART_HwFlowCtl_define

	uint8_t					 RXNEIE_IRQ_Enable:1;				//4bits to enable interrupt
	uint8_t					 TCIE_IRQ_Enable:1;				//4bits to enable interrupt
	uint8_t					 TXEIE_IRQ_Enable:1;				//4bits to enable interrupt
	uint8_t					 PEIE_IRQ_Enable:1;				//4bits to enable interrupt
	//  RXNEIE: RXNE interrupt enable // Received data ready to be read
	//  TCIE: Transmission complete interrupt enable // Transmission complete
	//	TXEIE: TXE interrupt enable // Transmit data register empty
	//	PEIE: PE interrupt enable // Parity error
	void(* P_IRQ_CallBack)(void) ;					//Set the C Function() which will be called once the IRQ  Happen



}UART_Config;



// * =======================================================================================
//Reference Macros
// * =======================================================================================

//UART_Mode_define

#define UART_MODE_RX                        (uint32_t) (1<<2)  //RE =1
#define UART_MODE_TX                       	(uint32_t) (1<<3) //TE =1
#define UART_MODE_TX_RX                     ((uint32_t)(1<<2 | 1<<3))

//UART_BaudRate_define

#define UART_BaudRate_2400                   2400
#define UART_BaudRate_9600                   9600
#define UART_BaudRate_19200                  19200
#define UART_BaudRate_57600                  57600
#define UART_BaudRate_115200                 115200
#define UART_BaudRate_230400                 230400
#define UART_BaudRate_460800                 460800
#define UART_BaudRate_921600                 921600
#define UART_BaudRate_2250000                2250000
#define UART_BaudRate_4500000                4500000


//UART_Payload_Length_define

#define UART_Payload_Length_8B                  (uint32_t)(0)
#define UART_Payload_Length_9B                  (uint32_t)(1<<12)

//@ref UART_Parity_define

#define UART_Parity__NONE                    (uint32_t)(0)
#define UART_Parity__EVEN                    ((uint32_t)1<<10)
#define UART_Parity__ODD                     ((uint32_t)(1<<10 | 1<<9))

//@ref UART_StopBits_define

#define UART_StopBits__half                  (uint32_t)(1<<12)
#define UART_StopBits__1                     (uint32_t)(0)
#define UART_StopBits__1_half                (uint32_t)(3<<12)
#define UART_StopBits__2                     (uint32_t)(2<<12)


//@ref UART_HwFlowCtl_define

#define UART_HwFlowCtl_NONE                  (uint32_t)(0)
#define UART_HwFlowCtl_RTS                   ((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS                   ((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS               ((uint32_t)(1<<8 | 1<<9))


//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE                      		(uint32_t)(0)
#define UART_IRQ_Enable_TXE                       		(uint32_t) (1<<7) //Transmit data register empty
#define UART_IRQ_Enable_TC                     			((uint32_t)(1<<6)) //Transmission complete
#define UART_IRQ_Enable_RXNEIE                       	(uint32_t) (1<<5) //Received data ready to be read & Overrun error detected
#define UART_IRQ_Enable_PE                       	     (uint32_t) (1<<8) //Parity error







//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =
// uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )







enum Polling_mechism{
	enable ,
	disable
};
// * =======================================================================================

/*
 *
 *
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */


/* Initialization/de-initialization functions  **********************************/

void MCAL_UART_Init ( UART_Config* UART_Config);
void MCAL_UART_DeInit (UART_Config* UART_Config);

void MCAL_UART_GPIO_Set_Pins (UART_Config* UART_Config);

void MCAL_UART_SendData	(UART_Config* UART_Config, uint16_t *pTxBuffer,enum Polling_mechism PollingEn );
void MCAL_UART_ReceiveData	(UART_Config* UART_Config, uint16_t *pTxBuffer ,enum Polling_mechism PollingEn );

void MCAL_UART_WAIT_TC (UART_Config* UART_Config) ;
void SendFrame (USART_TypeDef * uart, char str []);

















#endif /* STM32F103X8_USART_DRIVER_H_ */







