		/********************************************************************************/
		/*	Ren Kai Tam -- R00095982													*/
		/*	Problem 1.5	-- Self Driving Car			   									*/
		/*	      																		*/
		/*	      																		*/
		/*	Enter Process																*/
		/********************************************************************************/


#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <alarm.h>
#include <types.h>
#include <cglob.h>
#include "InfoModule.h"
#include "DataModule.h"

main()
{
  
	signal_code dummySig, signal, sig;
	u_int16 attr_rev, type_lang, mem_size;
	mh_com mod_head;
   	char *ptrMemName;
   	char *ptrMemName2;
	process_id nextTemp; 
	struct CarInfo *carData;
	struct MemoryModule *pidMem;
	event_id ev_id;
	u_int32 value;

	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);

	ptrMemName = INFO_MODULE;
	ptrMemName2 = MEMORY_MODULE;

   	if(errno = _os_link(&ptrMemName, (mh_com **) &mod_head, (void **)&carData, &type_lang, &attr_rev) != 0)
	{
		fprintf(stderr, "%d: Couldn't link to car Info data module!\n");
		_os_exit(errno);
	}

	if(errno = _os_link(&ptrMemName2, (mh_com **) &mod_head, (void **)&pidMem, &type_lang, &attr_rev) != 0)
	{
		fprintf(stderr, "%d: Couldn't link to PID data module!\n");
		_os_exit(errno);
	}

	if((errno = _os_ev_link(SEMA_EVENT, &ev_id)) != 0)
	{
		printf("Error : Fail to link SEMA_EVENT\n");
		exit(errno);
	}

	if((errno = _os_ev_wait(ev_id, &value, &sig, 1, 1)) != 0)
	{
		printf("Waiting on Event error\n");
		exit(errno);
	}
	
	printf("EnterValue Started\n");

	carData->carDoorClose = TRUE;

   	carData->handBrakeIsOff = FALSE;

 	carData->numberOfSeatIsOccupied = 3;

  	carData->seatBeltFasten[0] = TRUE;
	carData->seatBeltFasten[1] = TRUE;
	carData->seatBeltFasten[2] = TRUE;
	carData->seatBeltFasten[3] = FALSE;
	

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

	printf("Enter Value - unlink event\n")	;
	_os_unlink(&mod_head);

    _os_exit(0);
}

