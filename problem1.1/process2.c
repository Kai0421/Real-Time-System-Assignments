#include <stdio.h>
#include <types.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int i = 1;

 	if (argc <= 1)
		printf("Enter more than 1 parameter");
	
	for (i ; i < argc; i ++)
		printf("%s -- %d\n", argv[i], strlen(argv[i]));

}
