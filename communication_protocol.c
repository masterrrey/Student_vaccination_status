/*
 * communication_protocol.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#include "communication_protocol.h"

void process_answer(char *cmd)
{

	char update_name[12]="";
	strncpy(update_name, cmd, 11);

	char update_surname[15]="";
	strncpy(update_surname, cmd, 14);

	char update_age[11]="";
	strncpy(update_age, cmd, 10);

	char update_vaccine_status[26]="";
	strncpy(update_vaccine_status, cmd, 25);

	char add_one_new_kid[8]="";
	strncpy(add_one_new_kid, cmd, 7);

	char delete_one_kid[11]="";
	strncpy(delete_one_kid, cmd, 10);


	if (cmd==NULL || strlen(cmd)<1)
	{
		printf("0 -INVALID CMD\n");
		return;
	}

	if(strcasecmp("UPDATE NAME", update_name)==0)
	{
		char *new_kid_name;
		char *get_record_id;
		char temporary_string[100];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;

		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		new_kid_name = token;
		token = strtok(NULL, delims);
		get_record_id = token;

		static char *reply_server;
		printf("You have passed this new name from the terminal: /t '%s' .\n", new_kid_name);
		reply_server= set_kid_name(new_kid_name, get_record_id);

	}

	else if(strcasecmp("UPDATE SURNAME", update_surname)==0)
	{
		char *new_kid_surname;
		char *get_record_id;
		char temporary_string[100];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;
		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		new_kid_surname = token;
		token = strtok(NULL, delims);
		get_record_id = token;

		static char *reply_server;

		printf("You have passed this new surname from the terminal: \t '%s' .\n", new_kid_surname);
		reply_server= set_kid_surname(new_kid_surname, get_record_id);

	}

	else if(strcasecmp("UPDATE AGE", update_age)==0)
	{
		char *new_kid_age;
		char *get_record_id;
		char temporary_string[100];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;
		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		new_kid_age = token;
		token = strtok(NULL, delims);
		get_record_id = token;

		static char *reply_server;

		printf("You have passed this new age from the terminal: \t '%s' .\n", new_kid_age);
		reply_server= set_kid_age(new_kid_age, get_record_id);

	}

	else if(strcasecmp("UPDATE VACCINATION STATUS", update_vaccine_status)==0)
	{
		printf("\n1\n");
		char *new_vaccine_status;
		char *get_record_id;
		char temporary_string[100];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;

		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		new_vaccine_status = token;
		token = strtok(NULL, delims);
		get_record_id = token;

		static char *reply_server;

		printf("You have passed this new name from the terminal: /t '%s' .\n", new_vaccine_status);
		reply_server= set_kid_vaccine_status(new_vaccine_status, get_record_id);

	}

	else if(strcasecmp("SHOW ALL KIDS", cmd)==0)
		{
			static char *reply_server;

			printf("This are all kids from the database.\n");
			reply_server= show_all_kids();

		}


	else if(strcasecmp("ADD KID", add_one_new_kid)==0)
	{
		char *add_name;
		char *add_surname;
		char *add_age;
		char *add_vaccine_status;
		char temporary_string[100];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;
		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		add_name = token;
		token = strtok(NULL, delims);
		add_surname = token;
		token = strtok(NULL, delims);
		add_age = token;
		token = strtok(NULL, delims);
		add_vaccine_status = token;

		static char *reply_server;


		printf("You have passed the Name, Surname, Age and Vaccine status from the terminal for the new kid:./n");
		reply_server=add_new_kid(add_name, add_surname, add_age, add_vaccine_status);

	}

	else if(strcasecmp("DELETE KID", delete_one_kid)==0)
	{
		char *get_record_id;
		char temporary_string[13];
		strcpy(temporary_string, cmd);
		char delims[] = " ";
		char *token;

		token = strtok(temporary_string, delims);
		token = strtok(NULL, delims);
		token = strtok(NULL, delims);
		get_record_id = token;

		static char *reply_server;

		reply_server= delete_kid(get_record_id);

	}

}
