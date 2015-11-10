#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <dexec.h>
#include <types.h>
#include <signal.h>

main()
{
	error_code err;
	process_id child_pid;
	status_code child_status;
	u_int32 ticks; 										  
	signal_code dummySignal;
	
	char *child_argv[] = {"procs", "-e", "-a", 0};
	
   	printf("_os_getsys() ....\nenables a process to examine a system global variable. These variables have a d_ prefix in the system header file sysglob.h. Consult the files in the DEFS directory for a description of the system global variables.\n"); 
	ticks = 1500;
	printf("\nSleeping now\n");
	if (err = (_os_sleep(&ticks, &dummySignal) != 0))
		printf("ErrorSleep1 -- sleep error\n");



	printf("_os_getdl ....\n is a pointer to the location where _os_getdl()stores the pointer to the first entry in the device list.\n");
	ticks = 1500;
	printf("\nSleeping now\n");
	if (err = (_os_sleep(&ticks, &dummySignal) != 0))
		printf("ErrorSleep2 -- sleep error\n");


   printf("_os_gettime ....\nreturns the current system time in the number of seconds since a date specified in Greenwich Mean Time. To determine the specified date, refer to the applicable manual, OS-9 for 68K Technical Manual or OS-9 Technical Manual.\n");
}