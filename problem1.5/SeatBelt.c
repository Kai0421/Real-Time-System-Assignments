		/********************************************************************************/
		/*	Ren Kai Tam -- R00095982													*/
		/*	Problem 1.5	-- Self Driving Car												*/
		/*	      																		*/
		/*	      																		*/
		/*	SeatBelt																	*/
		/********************************************************************************/


#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <module.h>
#include <types.h>
#include <cglob.h>
#include <alarm.h>


#include "DataModule.h"
#include "InfoModule.h"


void signal_handler(signal_code sig)
{
	switch(sig)
	{
		case 600:
		  	 printf("CarDoor -- Signal Received!!Car door is closed %d\n", sig);
			 break;
		default:
			printf("Incorrect Signal - SeatBelt\n");
	}
	_os_rte();
}

main()
{	
	signal_code dummySig, signal, wakeUpCall, sig;
	u_int16 attr_rev, type_lang, mem_size;
	mh_com mod_head;
   	char *ptrMemName;
   	char *ptrMemName2;
	process_id nextTemp;
	struct MemoryModule *pidMem;
	struct CarInfo *carData;
   	u_int32 sleepTime, timeToDelay, ticks;
	alarm_id alarmID;	
   	event_id ev_id;
	u_int32 value;
	int countSeatBelt = 0, count =0;

	
	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
			exit(errno);
	
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);

	ptrMemName = INFO_MODULE;
	ptrMemName2 = MEMORY_MODULE;


	if(errno = _os_link(&ptrMemName, (mh_com **) &mod_head, (void **)&carData, &type_lang, &attr_rev) != 0)
	{
		fprintf(stderr, "%d: Couldn't link to data module!\n");
		exit(errno);
	}

	if(errno = _os_link(&ptrMemName2, (mh_com **) &mod_head, (void **)&pidMem, &type_lang, &attr_rev) != 0)
	{
		fprintf(stderr, "%d: Couldn't link to data module!\n");
		exit(errno);
	}

	if((errno = _os_ev_link(SEMA_EVENT, &ev_id)) != 0)
	{
		printf("Error : Fail to link SEMA_EVENT\n");
		exit(errno);
	}


	ticks = 200;
	_os_sleep(&ticks, &dummySig);

	timeToDelay = 6 * 1000;
	wakeUpCall = 1;


   if((errno=_os_alarm_cycle(&alarmID, wakeUpCall, timeToDelay)) != 0)
	{
		printf("SeatBelt -- Error creating alarm\n");
		exit(errno);
	}

	printf("SeatBelt Process Started\n");

	
	while(carData->numberOfSeatIsOccupied > 0)
	{
		if((errno = _os_ev_wait(ev_id, &value, &sig, 1, 1)) != 0)
		{
			printf("Waiting on Event error\n");
			exit(errno);
		}

		for (count = 0; count < SEAT_NO; count++)
			if(carData->seatBeltFasten[count] == TRUE)
				countSeatBelt++;

		if (countSeatBelt < carData->numberOfSeatIsOccupied)
			_os_send(pidMem->childrenPID[3], 750);
		
		if (countSeatBelt == carData->numberOfSeatIsOccupied)
	 		_os_send(pidMem->childrenPID[6], 1750);

		sleepTime = 0;
		_os_sleep(&sleepTime, &signal);
		
		/*
		printf("Car door is still open\n");		
		_os_send Signal to Generate Alert
		*/ 

		if((errno = _os_ev_signal(ev_id, &value, 0)) != 0)
		{
			printf("Error : Signalling event error\n");
			exit(errno);
		}

		if((errno = _os_ev_unlink(ev_id)) != 0)
		{
			printf("Error : Event Unlink error\n");
			exit(0);
		}
		/*printf("SeatBelt - unlink event\n");		*/
	}
   /*	printf("Car door is closed\n");*/
   	_os_unlink(&mod_head);
}




