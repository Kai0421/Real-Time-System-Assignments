#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <module.h>
#include <types.h>
#include <cglob.h>
#include "MemoryModule.h"
process_id temp1;
process_id temp2;
process_id temp3;


void signal_handler(signal_code sig)
{

	int i = 0;
	switch(sig)
	{
		case 600:   
			printf("I am P2 -- Signal Received !! -- %d\nSending signal to the next process\n", sig);
			_os_send(temp1, 600);
		    _os_send(temp2, 600); 
		  	_os_send(temp3, 600);		
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
	
   
   /*	ticks = 2000;
	_os_sleep(&ticks, &dummySig);		
	printf("\nStaring P2\n");
								  */
  
   	ptrMemName = MEMORY_MODULE;

	ticks = 100;
	_os_sleep(&ticks, &dummySig);
		
	if(errno = _os_link(&ptrMemName, (mh_com **) &mod_head, (void **)&pidData, &type_lang, &attr_rev) != 0)
	{
	 	fprintf(stderr, "%d: Couldn't link to data module!\n");
	 	_os_exit(errno);
	}
	
	temp1 = pidData->childrenPID[3];
   	temp2 = pidData->childrenPID[4]; 
  	temp3 = pidData->childrenPID[5]; 	   
		 

	ticks = 1000 ;
	_os_sleep(&ticks, &dummySig);


	_os_unlink(&mod_head);

}	