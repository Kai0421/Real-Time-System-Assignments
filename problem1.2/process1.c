#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <alarm.h>
#include <types.h>
#include <cglob.h>

void signal_handler(signal_code sig)
{
	switch(sig)
	{
		case 500:
		   _os_exit(0);
		   break;
		default:
			printf("Incorrect Signal");
	}
	_os_rte();
}

main()
{
	signal_code signal, wakeUpCall;
	u_int32 sleepTime, timeToDelay;
	alarm_id alarmID;
	error_code errno;


	int temp[] = {20, 25, 20, 12, 8, 15, 16};
	int i = 0;

	timeToDelay = 5.3 * 1000;
	wakeUpCall = 1;
	
	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
		exit(errno);

	if((errno=_os_alarm_cycle(&alarmID, wakeUpCall, timeToDelay)) != 0)
	{
		printf("Error creating alarm");
		exit(errno);
	}
	  
	printf("Starting loop");
	sleepTime = 5300;
	while(1)
	{
		if(i == 7)
		{	i = 0;}

		_os_sleep(&sleepTime, &signal);
		if(signal == 0)
			printf("Wake up call caused by alarm cycle\nThe number in the temp-array position %d is %d\n", i, temp[i]);
		else
			printf("The signal value which caused the alarm is %d\n", signal);
		
		i++;
	}

}