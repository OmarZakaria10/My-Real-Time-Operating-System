/*
 * Scheduler.h
 *
 *  Created on: Apr 26, 2024
 *      Author: GTX
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_Porting.h"

typedef enum {
	NoError, Ready_Queue_init_error, Task_exceeded_StackSize
} MYRTOS_ErrorID;

typedef enum {
	NO, YES
} AutoStart_t;

typedef struct {
	uint32_t Stack_Size;
	uint8_t Priority;
	void (*p_TaskEntry)(void); // pointer to task function
	AutoStart_t AutoStart;
	uint32_t _S_PSP_Task;
	uint32_t _E_PSP_Task;
	uint32_t *Current_PSP;
	unsigned char TaskName[30];
	enum {
		Suspended, Waiting, Ready, Running
	} TaskState;
	struct {
		enum {
			Disable_blocking, Enable_blocking
		} BlockingState;
		unsigned int Ticks_Count;
	} TimeWaiting;

} TASK;

MYRTOS_ErrorID MYRTOS_Init();
MYRTOS_ErrorID MYRTOS_CreateTask(TASK *Tref);

#endif /* INC_SCHEDULER_H_ */
