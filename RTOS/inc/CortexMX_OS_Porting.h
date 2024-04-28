/*
 * CortexMX_OS_Porting.h
 *
 *  Created on: Apr 26, 2024
 *      Author: GTX
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "ARMCM3.h"
#include "core_cm3.h"
extern int _estack;
extern int _eheab ;
#define MainStackSize	3072
#define OS_SET_PSP(add)				__asm("MOV R0,%0 \t\n MSR PSP,R0" : :"r"(add))
#define OS_GET_PSP(add)				__asm("MRS R0,PSP \t\n MOV %0,R0" : :"=r"(add))
#define OS_Switch_SP_PSP			__asm("MRS R0,CONTROL \t\n ORR R0,R0,#0x2 \t\n MSR CONTROL,R0")
#define OS_Switch_SP_MSP			__asm("MRS R0,CONTROL \t\n AND R0,R0,#0x5 \t\n MSR CONTROL,R0")

#define CPU_Access_Level_Unprivileged(){__asm("MRS R3,CONTROL");\
		__asm("ORR R3,R0,#0x01");\
		__asm("MSR CONTROL,R3");\
}

#define CPU_Access_Level_Privileged(){__asm("MRS R3,CONTROL");\
		__asm("LSR R3,R3,#0x01");\
		__asm("LSL R3,R3,#0x01");\
		__asm("MSR CONTROL,R3");\
}



#endif /* INC_CORTEXMX_OS_PORTING_H_ */
