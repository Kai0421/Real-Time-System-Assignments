#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <module.h>
#include <types.h>
#include <cglob.h>
#include "MemoryModule.h"

void signal_handler(signal_code sig)
{
	switch(sig)
	{
		case 600:
		    printf("I am P4 -- Signal Received !!\n");
		   break;
		default:
			printf("Incorrect Signal");
	}
	_os_rte();
}

main()
{
	u_int32 ticks;
	signal_code dummySig;
	u_int16 attr_rev, type_lang, mem_size;
	mh_com mod_head;
	u_int32 sleepTime;
	char *ptrMemName;
	int i;
	struct MemoryModule *pidData;
	
	
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);
	
	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
			exit(errno);

	ticks = 1000;
	_os_sleep(&ticks, &dummySig);

	
 	/*  ticks = 1500;
   	_os_sleep(&ticks, &dummySig);	
   	ptrMemName = MEMORY_MODULE;
   	if(errno = _os_link(&ptrMemName, (mh_com **) &mod_head, (void **)&pidData, &type_lang, &attr_rev) != 0)
   	{
   		fprintf(stderr, "%d: Couldn't link to data module!\n");
   		_os_exit(errno);
   	}
   	
   	printf("\n PID : %d", pidData->childrenPID[3]);
   _os_send(pidData->childrenPID[3], 600);    
	
   	_os_unlink(&mod_head);*/
											   
}