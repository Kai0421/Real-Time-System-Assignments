#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <module.h>
#include <types.h>
#include <cglob.h>
#include "MemoryModule.h"
process_id nextTemp;

void signal_handler(signal_code sig)
{
	switch(sig)
	{
		case 600:
		  	 printf("I am P1 -- Signal Received!! -- %d\nSending signal to the next process\n", sig);
			 break;
		default:
			printf("Incorrect Signal - P1\n");
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
	int i, trueOrFalse = 0;
	process_id nextTemp;
   	struct MemoryModule *pidData;
	
	
	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
			exit(errno);
	
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);
	
   	/*ticks = 1000;
	_os_sleep(&ticks, &dummySig); */
	ptrMemName = MEMORY_MODULE;

	ticks = 200;
	_os_sleep(&ticks, &dummySig);


   	if(errno = _os_link(&ptrMemName, (mh_com **) &mod_head, (void **)&pidData, &type_lang, &attr_rev) != 0)
	{
		fprintf(stderr, "%d: Couldn't link to data module!\n");
		_os_exit(errno);
	}
	
	printf("P1 Started\n");  
	if(trueOrFalse == 0) 
	{
		_os_send(pidData->childrenPID[2], 600);
		trueOrFalse = 1; 
	}

	ticks = 4000;
	_os_sleep(&ticks, &dummySig);
	
	_os_unlink(&mod_head); 

}