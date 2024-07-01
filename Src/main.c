

#include <stdint.h>


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "Scheduler.h"

TASK Task1, Task2, Task3, Task4 ;
unsigned char Task1LED,Task2LED,Task3LED,Task4LED ;
Mutex_ref Mutex1 ;
unsigned char payload[3] = {1,2,3} ;

void task1()
{
	static int Count = 0 ;
	while (1){
		Task1LED ^= 1;
		Count++ ;
		if (Count == 100 )
		{
			MYRTOS_AcquireMutex(&Mutex1, &Task1);
			MYRTOS_ActivateTask(&Task2);
		}
		if (Count == 200 )
		{
			Count = 0 ;
			MYRTOS_ReleaseMutex(&Mutex1);
		}
	}
}
void task2()
{
	static int Count = 0 ;
	while (1){
		Task2LED ^= 1;
		Count++ ;
		if (Count == 100 )
		{
			MYRTOS_ActivateTask(&Task3);
		}
		if (Count == 200 )
		{
			Count = 0 ;
			MYRTOS_TerminateTask(&Task2);

		}
	}
}
void task3()
{
	static int Count = 0 ;
	while (1){
		Task3LED ^= 1;
		Count++ ;
		if (Count == 100 )
		{
			MYRTOS_ActivateTask(&Task4);
		}
		if (Count == 200 )
		{
			Count = 0 ;
			MYRTOS_TerminateTask(&Task3);

		}
	}
}

void task4()
{
	static int Count = 0 ;
	while (1){
		Task4LED ^= 1;
		Count++ ;
		if (Count == 3 )
		{
			MYRTOS_AcquireMutex(&Mutex1, &Task4);
		}

		if (Count == 200 )
		{
			Count = 0 ;
			MYRTOS_ReleaseMutex(&Mutex1);
			MYRTOS_TerminateTask(&Task4);

		}
	}
}
//priority inversion Example
int main(void)
{

	MYRTOS_ErrorID error;
	//HW_Init (Initialize ClockTree, RestController)
	HW_init();

	if (MYRTOS_Init() != NoError)
		while (1);

	Mutex1.PayloadSize = 3 ;
	Mutex1.Ppayload = payload ;
	strcpy (Mutex1.MutexName, "Mutex1");

	Task1.Stack_Size = 1024 ;
	Task1.p_TaskEntry =task1;
	Task1.Priority= 4 ;
	strcpy (Task1.TaskName, "task_1");

	Task2.Stack_Size = 1024 ;
	Task2.p_TaskEntry =task2;
	Task2.Priority= 3 ;
	strcpy (Task2.TaskName, "task_2");

	Task3.Stack_Size = 1024 ;
	Task3.p_TaskEntry =task3;
	Task3.Priority= 2 ;
	strcpy (Task3.TaskName, "task_3");

	Task4.Stack_Size = 1024 ;
	Task4.p_TaskEntry =task4;
	Task4.Priority= 1 ;
	strcpy (Task4.TaskName, "task_4");

	error += MYRTOS_CreateTask(&Task1);
	error += MYRTOS_CreateTask(&Task2);
	error += MYRTOS_CreateTask(&Task3);
	error += MYRTOS_CreateTask(&Task4);


	MYRTOS_ActivateTask(&Task1);


	MYRTOS_StartOS() ;

	while (1)
	{

	}


}
