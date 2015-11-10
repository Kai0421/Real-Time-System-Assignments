#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <dexec.h>
#include <types.h>

main(int argc, char * argv[], char **envp)
{
	error_code err1;
	process_id child_pid1;
	status_code child_status1;
	
	error_code err2;
	process_id child_pid2;
	status_code child_status2;

	error_code err3;
	process_id child_pid3;
	status_code child_status3;

	
	char *child_argv1[] = {"P1", 0};
	char *child_argv2[] = {"P2", "A", "AB", "ABC", 0};
	char *child_argv3[] = {"P3", "3", "-", "2", 0};	
	
   	if (err1 = (_os_exec(_os_fork, 0, 3, child_argv1[0], child_argv1, envp, 0, &child_pid1, 0, 0) != 0))
		printf("Error-forking child1\n");
			
   		
	printf("\n The P1 PID = %d\n", child_pid1);															 
	printf("The P1 PID = %d returned status = %d\n", child_pid1, child_status1);	

		 
  	if (err2 = (_os_exec(_os_fork, 0, 3, child_argv2[0], child_argv2, envp, 0, &child_pid2, 0, 0) != 0))
		printf("Error-forking child2\n");

	printf("\n The P2 PID = %d\n", child_pid2);
	printf("The P2 PID = %d returned status = %d\n", child_pid2, child_status2);



 	if (err3 = (_os_exec(_os_fork, 0, 3, child_argv3[0], child_argv3, envp, 0, &child_pid3, 0, 0) != 0))
		printf("Error-forking child3\n");

	printf("\n The P3 PID = %d\n", child_pid3);
	printf("The P3 PID = %d returned status = %d\n", child_pid3, child_status3);  
	
	/* OS WAIT */ 

	if (err1 = (_os_wait(&child_pid1, &child_status1) != 0))
		printf("Error-child1\n");
	
	if (err2 = (_os_wait(&child_pid2, &child_status2) != 0))
		printf("Error-child2\n");

	if (err3 = (_os_wait(&child_pid3, &child_status3) != 0))
		printf("Error-child3\n");	 

 }