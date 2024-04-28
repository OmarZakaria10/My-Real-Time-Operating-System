/*
 * Scheduler.c
 *
 *  Created on: Apr 26, 2024
 *      Author: Omar Zakaria
 */

#include "Scheduler.h"
#include "MYRTOS_FIFO.h"



struct {
	TASK *OSTasks[100];
	uint32_t _S_MSP;
	uint32_t _E_MSP;
	uint32_t PSP_Task_Locator;
	uint32_t N_Active_Tasks;
	TASK *CurreuntTask;
	TASK *NexttTask;
	enum {
		Os_Suspended, Os_Running
	} OSMode;
} OS_Control;

FIFO_Buf_t Ready_QUEUE;
TASK* Ready_QUEUE_FIFO[100] ;
TASK MYRTOS_idleTask ;

void OS_SVC(int *Stack_Frame) {
	/*args = r0 -> MSP or PSP*/
	//OS_SVC Stack end -> r0
	//OS_SVC Stack : old r0-r1-r2-r3-r12-lr-pc-xpsr
	unsigned char SVC_Number;
	unsigned int val1, val2;
	SVC_Number = *((unsigned char*) ((unsigned char*) Stack_Frame[6] - 2));

	switch (SVC_Number) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}
}
void PendSV_Handler() {

}

int OS_SVC_Set(int SVC_ID) {
	int result;
	switch (SVC_ID) {
	case 1: //add
		__asm("SVC #0x01");
		break;
	case 2: //sub
		__asm("SVC #0x02");
		break;
	case 3: //mull
		__asm("SVC #0x03");
		break;
	}
//	return result;
}

void MYRTOS_Handle_idleTask (){
	while(1)
	{
		__asm("NOP");
	}
}

MyRTOS_Create_TaskStack(TASK* Tref){
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */
	Tref->Current_PSP = Tref->_S_PSP_Task ;

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = 0x01000000;         //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry ; //PC

	Tref->Current_PSP-- ; //LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP
	*(Tref->Current_PSP)  = 0xFFFFFFFD ;

	for (int  j=0 ; j< 13 ; j++ )
	{
		Tref->Current_PSP-- ;
		*(Tref->Current_PSP)  = 0 ;

	}



}


RTOS_Create_MainStack() {
	OS_Control._S_MSP = &_estack;
	OS_Control._E_MSP = OS_Control._S_MSP - MainStackSize;

	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP - 8);
}

MYRTOS_ErrorID MYRTOS_Init() {
	MYRTOS_ErrorID error = NoError;
	OS_Control.OSMode = Os_Suspended;
	RTOS_Create_MainStack();
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100)!= FIFO_NO_ERROR){
		error += Ready_Queue_init_error;
	}
	//Configure IDLE TASK
	strcpy (MYRTOS_idleTask.TaskName, "idleTask");
	MYRTOS_idleTask.Priority = 255 ;
	MYRTOS_idleTask.p_TaskEntry = MYRTOS_Handle_idleTask ;
	MYRTOS_idleTask.Stack_Size = 300 ;

	error += MYRTOS_CreateTask(&MYRTOS_idleTask);

	return error ;
}

MYRTOS_ErrorID MYRTOS_CreateTask(TASK* Tref)
{
	MYRTOS_ErrorID error = NoError ;

	//Create Its OWN PSP stack
	//Check task stack size exceeded the PSP stack
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;

	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-
	//
	if(Tref->_E_PSP_Task < (unsigned int)(& _eheab));
	{
		return Task_exceeded_StackSize ;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator= (Tref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack( Tref);



	return error ;

}

