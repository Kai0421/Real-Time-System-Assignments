#include <stdio.h>
#include <errno.h>
#include <modes.h>
#include <string.h>
#include <signal.h>

main()
{
	error_code errno;
	path_id pipe_P1;
	u_int32 count;
	u_int32 pipe_size1;
	char msg[3];
	signal_code sig;
	u_int32 ticks;

	if((errno = _os_open("/pipe/ProcP1", S_IREAD, &pipe_P1)) !=0)
	{
		printf("No message available.. \n");
		exit(0);
	}
	count = 5;
	if((errno = _os_read(pipe_P1, &msg, &count)) !=0)
	{
		printf("Error :  message reading error, invalid message?");
		exit(0);
	}
	else
	{
		ticks = 500;
		if(errno = (_os_sleep(&ticks, &sig)) != 0)
			printf("Sleep - error");
			
		printf("Message Received\n");
		printf("\tMsg: %s", &msg);
	}
	_os_close(pipe_P1);
}