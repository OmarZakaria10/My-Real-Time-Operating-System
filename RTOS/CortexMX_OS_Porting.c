/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Apr 26, 2024
 *      Author: Omar Zakaria
 */
#include "CortexMX_OS_porting.h"

void HardFault_Handler(void) {
	while (1)
		;
}
void MemManage_Handler(void) {
	while (1)
		;
}
void BusFault_Handler(void) {
	while (1)
		;
}
void UsageFault_Handler(void) {
	while (1)
		;
}

__attribute((naked)) void SVC_Handler() {
	//Switch_CPU_Access_Mode(privilege);
	/*
	 * ---> We will make this SVC_Hnadler as assembly ==> No caller stack pushing
	 * 1- Know we were in which stack MSP/PSP -> r0
	 * 2- call a c-function that take a pointer as arg (r0)
	 * */
	__asm("TST LR,#0x4 \n\t"
			"ITE EQ \n\t"
			"MRSEQ r0,MSP \n\t"
			"MRSNE r0,PSP \n\t"
			"B OS_SVC");

}
