#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
   	int a, b, answer;
	char *operationString;
	char operation;	
	  	
   	if (argc != 4)	
		printf("Not Enough Parameter -- require 4 parameters\n");  
	else
	{	

		a = atoi(argv[1]);
		b = atoi(argv[3]);

		operationString = argv[2];
		operation = operationString[0];
		switch (operation)
		{
			case '+':
			   answer = a + b;
			   break;	
			   
			case '-':
			   answer = a - b;
			   break;

			case '*':
			   answer = a * b;
			   break;

			case '/':
			   answer = a / b;
			   break;

			default:
				printf("Only allow symbols + - * / \n");
				break;
		}

		printf("%s %s %s = %d\n", argv[1], argv[2], argv[3], answer);
	 }
}