		/********************************************************************************/
		/*	Ren Kai Tam -- R00095982													*/
		/*	Problem 1.2																	*/
		/*	      																		*/
		/*	      																		*/
		/*	Generate Alarm																*/
		/********************************************************************************/


#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <types.h>
#include <cglob.h>

void signal_handler(signal_code sig)
{
	switch(sig)
	{
		case 500:
			printf("AlarmGenerator -- Car Door is open\n");
			break;

		case 600:
			printf("AlarmGenerator -- HandBrake is applied\n");
			break;

		case 700:
			printf("AlarmGenerator -- Number of Seat Taken \n");
			break;

		case 750:
			printf("AlarmGenerator -- Seat belt not fasten \n");
			break;

		case 800:
			printf("AlarmGenerator -- Car is Moving\n");
			break;

		default:
			printf("AlarmGenerator -- Incorrect Signal\n");
	}
	_os_rte();
}

main()
{
	signal_code signal;
	u_int32 sleepTime;
	error_code errno;


	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
		exit(errno);

    sleepTime = 0;
	while(1)
	{
		_os_sleep(&sleepTime, &signal);
	}
}