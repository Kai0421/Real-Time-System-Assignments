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
		    printf("I am P3 -- Signal Received !!\n");
		   break;
		default:
			printf("Incorrect Signal - P3\n");
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
	
	if((errno=_os_intercept(signal_handler, _glob_data)) != 0)
		exit(errno);
	
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);
	
  		
    ticks = 500;
	_os_sleep(&ticks, &dummySig);
  
}											