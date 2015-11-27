		/********************************************************************************/
		/*	Ren Kai Tam -- R00095982													*/
		/*	Problem 1.5 --  Self Sriving Car											*/
		/*	      																		*/
		/*	      																		*/
		/*	startup																        */
		/********************************************************************************/


#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <types.h>
#include <module.h>
#include <cglob.h>
#include <signal.h>
#include <memory.h>

#include "DataModule.h"
#include "InfoModule.h"

main(int argc, char * argv[], char **envp)
{
	error_code errno;
	u_int16 attr_rev, type_lang, perm, memory_size;
	u_int32 sleepValue;
	mh_com mod_head;
	signal_code signal;
	process_id child_pid[7];
	status_code child_status;
	int i;
	struct MemoryModule *memPID; 
	struct CarInfo *carData;

	signal_code DummySignal;
	u_int32 SleepValue;
	event_id ev_id;


	char *child_argv1[] = {"CarDoor", 0};
	char *child_argv2[] = {"HandBrake", 0};
	char *child_argv3[] = {"GenerateAlarm", 0};
	char *child_argv4[] = {"Seat", 0};
	char *child_argv5[] = {"SeatBelt", 0};
	char *child_argv6[] = {"MovingCar", 0};  
	char *child_argv7[] = {"EnterValue", 0}; 

 	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);
	
	perm = MP_OWNER_READ|MP_OWNER_WRITE;

	if((errno = _os_ev_creat(1, -1, perm, &ev_id, SEMA_EVENT, 1, MEM_ANY)) != 0)
	{
		printf("Error : Creating SemaEvent error\n");
		exit(errno);
	}

printf("St step1\n");
    if(errno = _os_datmod(MEMORY_MODULE, PID_ARRAY, &attr_rev, &type_lang, perm, (void **)&memPID, (mh_data **) &mod_head) !=0)
	{
		fprintf(stderr, "Error :  Connot create memory Module\n");
		_os_exit(errno);
	}
	
printf("St step2\n");
	if(errno = _os_datmod(INFO_MODULE, CAR_INFO_SIZE, &attr_rev, &type_lang, perm, (void **)&carData, (mh_data **) &mod_head) !=0)
	{
		fprintf(stderr, "Error :  Connot create memory Module\n");
		_os_exit(errno);
	}	
	
printf("St step3\n");
	carData->carDoorClose = FALSE;

	carData->numberOfSeatIsOccupied = 3;
	
	carData->seatBeltFasten[0] = FALSE;
	carData->seatBeltFasten[1] = FALSE;
	carData->seatBeltFasten[2] = FALSE;
	carData->seatBeltFasten[3] = FALSE;

	carData->handBrakeIsOff = TRUE;

	carData->carMoving = FALSE;

	printf("St step4\n	");

 	if (errno = (_os_exec(_os_fork, 0, 3, child_argv1[0], child_argv1, envp, 0,&child_pid[0], 0, 0) != 0))
			printf("Error1 -- child 1\n");

	memPID->childrenPID[1] = child_pid[0];
   		
   
 
   	if (errno = (_os_exec(_os_fork, 0, 3, child_argv2[0], child_argv2, envp, 0,&child_pid[1], 0, 0) != 0))
			printf("Error1\n");
											 
	memPID->childrenPID[2] = child_pid[1];

	

		
   	if (errno = (_os_exec(_os_fork, 0, 3, child_argv3[0], child_argv3, envp, 0, &child_pid[2], 0, 0) != 0))
			printf("Error1\n");

   	memPID->childrenPID[3] = child_pid[2];		


	

 	if (errno = (_os_exec(_os_fork, 0, 3, child_argv4[0], child_argv4, envp, 0,&child_pid[3], 0, 0) != 0))
			printf("Error1\n");

	memPID->childrenPID[4] = child_pid[3];



   
	if (errno = (_os_exec(_os_fork, 0, 3, child_argv5[0], child_argv5, envp, 0,&child_pid[4], 0, 0) != 0))
			printf("Error1\n");

   	memPID->childrenPID[5] = child_pid[4];



	
 	if (errno = (_os_exec(_os_fork, 0, 3, child_argv6[0], child_argv6, envp, 0,&child_pid[5], 0, 0) != 0))
			printf("Error1\n");

	memPID->childrenPID[6] = child_pid[5];	   

/*	if (errno = (_os_exec(_os_fork, 0, 3, child_argv7[0], child_argv7, envp, 0, &child_pid[6], 0, 0) != 0))
			printf("Error : EnterValue Fork Error\n");
															*/

	   									
   																  
 	if(errno = (_os_wait(&child_pid[0], &child_status) != 0))
		printf("Error -- P1 \n");

	if(errno = (_os_wait(&child_pid[1], &child_status) != 0))
		printf("Error -- P2 \n");
	
	if(errno = (_os_wait(&child_pid[2], &child_status) != 0))
		printf("Error -- P3 \n");

  	if(errno = (_os_wait(&child_pid[3], &child_status) != 0))
		printf("Error -- P4\n");

	if(errno = (_os_wait(&child_pid[4], &child_status) != 0))
		printf("Error -- P5");

   	if(errno = (_os_wait(&child_pid[5], &child_status) != 0))	
		printf("Error -- P6\n");							
			
 /*	if(errno = (_os_wait(&child_pid[6], &child_status) != 0))
		printf("Error -- EnterValue \n");
															    */
	
}