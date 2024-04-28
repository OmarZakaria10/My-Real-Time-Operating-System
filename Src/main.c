/*
 * in this lab we will work on the ARM CPU Stack (MSP-PSP)
 */

#include "Scheduler.h"



void wait(uint32_t time)
{
	uint32_t i , j;

	for( i=0 ; i<time ; i++)
		for(j=0 ; j<255 ; j++);
}


void task1()
{

}

void task2()
{

}

void task3()
{

}


TASK Task1,Task2,Task3;

int main()
{
	MYRTOS_ErrorID error;
	if (MYRTOS_Init() != NoError)
		while (1);

	Task1.Stack_Size = 1024 ;
	Task1.p_TaskEntry =task1;
	Task1.Priority= 3 ;
	strcpy (Task1.TaskName, "task_1");

	Task2.Stack_Size = 1024 ;
	Task2.p_TaskEntry =task2;
	Task2.Priority= 3 ;
	strcpy (Task2.TaskName, "task_2");

	Task3.Stack_Size = 1024 ;
	Task3.p_TaskEntry =task3;
	Task3.Priority= 3 ;
	strcpy (Task3.TaskName, "task_3");

	error+=MYRTOS_CreateTask(&Task1);
	error+=MYRTOS_CreateTask(&Task2);
	error+=MYRTOS_CreateTask(&Task3);

	return 0 ;


}


