#include <stdio.h>
#include <errno.h>
#include <modes.h>
#include <string.h>
#include <signal.h>

main()
{
	error_code errno;
	path_id pipe_P4, pipe_P1;
	u_int32 count;
	u_int32 pipe_size1;
	char msg[3];
	signal_code sig;
	u_int32 ticks;

	if((errno = _os_open("/pipe/ProcP4", S_IREAD, &pipe_P4)) !=0)
	{
		printf("No message available.. \n");
		exit(0);
	}
	count = 5;
	if((errno = _os_read(pipe_P4, &msg, &count)) !=0)
	{
		printf("Error :  message reading error, invalid message?");
		exit(0);
	}
	else
	{
		ticks = 5300;
		if(errno = (_os_sleep(&ticks, &sig)) != 0)
			printf("Sleep - error");
			
		printf("Message Received\n");
		printf("\tMsg: %s", &msg);
	}
	_os_close(pipe_P4);
	
		if((errno = _os_create("/pipe/ProcP1", S_IREAD | S_ISIZE, &pipe_P1, FAP_READ | FAP_GREAD | FAP_WRITE | FAP_GWRITE, 501)) != 0)
	{
		printf("The pipe for process 1 has a message already ?\n");

		count = 5;
		if((errno = _os_open("/pipe/ProcP1", S_IWRITE, &pipe_P4)) != 0)
		{
			printf("Error -- cannot open a pipe to send to???\n ");
			exit(0);
		}

		strcpy(msg,"P0");
		if((errno = _os_write(pipe_P1, msg, &count)) != 0)
		{
			printf("Error -- Cannot send a message to P1??\n");
			printf("Error number = %d\n", errno);
			exit(0);
			
		}
	 exit(0);
	}

	_os_gs_size(pipe_P1, &pipe_size1);
	printf("Reading pipe size = %d\n", pipe_size1);
	
	strcpy(msg, "P0");
	count = 5;
	if((errno = _os_write(pipe_P1, msg, &count)) != 0)
		printf("Error -- write");
	
	_os_close(pipe_P1);	   
}