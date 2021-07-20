/*
 ============================================================================
 Name        : Student_vaccination_status.c
 Author      : Pavel Racovcen
 Version     :
 Copyright   : Your copyright notice
 Description : Application which can be used in school to create a database 
               with vaccinated and not vaccinated children
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "common_utilities.h"
#include "communication_protocol.h"
#include "construct_dynamic_strings.h"
#include "database_utilities.h"

int main(int argc, char** argv)
{
	printf("Running Application.....\n");


	while(1)
	{
		printf("\nHello, please choose one of the following command:\n");
		printf("SHOW ALL KIDS\n");
		printf("UPDATE NAME <new name> <record_id>\n");
		printf("UPDATE SURNAME <new surname> <record_id>\n");
		printf("UPDATE AGE <new age> <record_id>\n");
		printf("UPDATE VACCINATION STATUS <new status> <record_id>\n");
		printf("ADD KID <name> <surname> <age> <vaccination status>\n");
		printf("DELETE KID <record_id>\n");

		char my_command[200];
		fgets(my_command, sizeof(my_command), stdin); //scanf() takes until the first break, there are commands that include multiple parameters so there is need for fgets()
		my_command[strcspn(my_command,"\n")]=0; //get rid of the \n which is taken by default with fgets() ; strcspn() returns the number of characters before the 1st occurrence of character present in both strings

		printf("You have entered the following command from the terminal line: \t '%s'.\n", my_command);
		if(strcmp(my_command, "out")==0)
		{
			puts("I shall cease the execution of the program now. Bye , bye!");
		}

		process_answer(my_command);
		fflush(stdin);


	}
	return 0;
}
