#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <types.h>
#include <module.h>
#include "MemoryModule.h"

main(int argc, char * argv[], char **envp)
{
	error_code errno;
	u_int16 attr_rev, type_lang, perm, memory_size;
	u_int32 sleepValue;
	mh_com mod_head;
	signal_code signal;
	process_id child_pid[6];
	status_code child_status;
	int i;
	struct MemoryModule *memPID; 

	char *child_argv1[] = {"P1", 0};
	char *child_argv2[] = {"P2", 0};
	char *child_argv3[] = {"P3", 0};
	char *child_argv4[] = {"P4", 0};
	char *child_argv5[] = {"P5", 0};
	char *child_argv6[] = {"P6", 0};

	
	memory_size = PID_ARRAY;
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);
	
	perm = MP_OWNER_READ|MP_OWNER_WRITE;

	
   if(errno = _os_datmod(MEMORY_MODULE, memory_size, &attr_rev, &type_lang, perm, (void **)&memPID, (mh_data **) &mod_head) !=0)
	{
		fprintf(stderr, "Error :  Connot create memory Module");
		_os_exit(errno);
	}	
	
	if (errno = (_os_exec(_os_fork, 0, 3, child_argv1[0], child_argv1, envp, 0,&child_pid[0], 0, 0) != 0))
			printf("Error1 -- child 1\n");

	printf("\n The child PID = %d\n",&child_pid[0]);
	memPID->childrenPID[1] = child_pid[0];
   		
   
   
   	if (errno = (_os_exec(_os_fork, 0, 3, child_argv2[0], child_argv2, envp, 0,&child_pid[1], 0, 0) != 0))
			printf("Error1\n");

	printf("\n The child PID = %d\n", &child_pid[1]);
	memPID->childrenPID[2] = child_pid[1];

	
		
	if (errno = (_os_exec(_os_fork, 0, 3, child_argv3[0], child_argv3, envp, 0, &child_pid[2], 0, 0) != 0))
			printf("Error1\n");

	printf("\n The child PID = %d\n", &child_pid[2]);
	memPID->childrenPID[3] = child_pid[2];

	if(errno = (_os_wait(&child_pid[2], &child_status) != 0))
		printf("Error2\n");
		
	

	if (errno = (_os_exec(_os_fork, 0, 3, child_argv4[0], child_argv4, envp, 0,&child_pid[3], 0, 0) != 0))
			printf("Error1\n");

	printf("\n The child PID = %d\n", &child_pid[3]);
	memPID->childrenPID[4] = child_pid[3];

	if(errno = (_os_wait(&child_pid[3], &child_status) != 0))
		printf("Error2\n");
		


	if (errno = (_os_exec(_os_fork, 0, 3, child_argv5[0], child_argv5, envp, 0,&child_pid[4], 0, 0) != 0))
			printf("Error1\n");

	printf("\n The child PID = %d\n", &child_pid[4]);
	memPID->childrenPID[5] = child_pid[4];

	if(errno = (_os_wait(&child_pid[4], &child_status) != 0))
		printf("Error2\n");
		

	if (errno = (_os_exec(_os_fork, 0, 3, child_argv6[0], child_argv6, envp, 0,&child_pid[5], 0, 0) != 0))
			printf("Error1\n");

	printf("\n The child PID = %d\n", &child_pid[5]);
	memPID->childrenPID[6] = child_pid[5];

	   									
   																  
	if(errno = (_os_wait(&child_pid[0], &child_status) != 0))
		printf("Error2\n");

	if(errno = (_os_wait(&child_pid[1], &child_status) != 0))
		printf("Error2\n");
	
	if(errno = (_os_wait(&child_pid[0], &child_status) != 0))
		printf("Error2\n");

	if(errno = (_os_wait(&child_pid[1], &child_status) != 0))
		printf("Error2\n");

	if(errno = (_os_wait(&child_pid[0], &child_status) != 0))
		printf("Error2\n");

	if(errno = (_os_wait(&child_pid[1], &child_status) != 0))
		printf("Error2\n");

}