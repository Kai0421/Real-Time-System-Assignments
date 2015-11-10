#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <dexec.h>
#include <types.h>

main(int argc, char * argv[], char **envp)
{
	error_code err;
	process_id child_pid;
	status_code child_status;

	char *child_argv[] = {"P1", 0};
	
	if (err = (_os_exec(_os_fork, 0, 3, child_argv[0], child_argv, envp, 0,&child_pid, 0, 0) != 0))
		printf("Error1\n");

	printf("\n The child PID = %d\n", child_pid);

	if(err = (_os_wait(&child_pid, &child_status) != 0))
		printf("Error2\n");

	printf("The child PID = %d returned status = %d\n", child_pid, child_status);
}