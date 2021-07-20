/*
 * common_utilities.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#include "common_utilities.h"

/*char *extract_kid_info()
{
	static char *kid_info;
	char *SQLQuery=construct_string_for_select_query("lista_copii", "*", "record_id");
	read_from_database=return_string_from_sqlite_database("my_dtb.db", SQLQuery);
	return kid_info;
}*/

char *set_kid_name(char *new_kid_name, char *get_record_id)
{
	char *SQLQuery=construct_string_for_update_query_with_where("lista_copii", "name", new_kid_name, "record_id", get_record_id);
	update_data_in_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

char *set_kid_surname(char *new_kid_surname, char *get_record_id)
{
	char *SQLQuery=construct_string_for_update_query_with_where("lista_copii", "surname", new_kid_surname, "record_id", get_record_id);
	update_data_in_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

char *set_kid_age(char *new_kid_age, char *get_record_id)
{
	char *SQLQuery=construct_string_for_update_query_with_where("lista_copii", "age", new_kid_age, "record_id", get_record_id);
	update_data_in_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

char *set_kid_vaccine_status(char *new_vaccine_status, char *get_record_id)
{
	char *SQLQuery=construct_string_for_update_query_with_where("lista_copii", "vaccination_status", new_vaccine_status, "record_id", get_record_id);
	update_data_in_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

char *show_all_kids()
{
	char *SQLQuery=construct_string_to_show_all_kids("lista_copii");
	select_data_from_sqlite_database("my_dtb.db", SQLQuery);
	return (" ;");
}

char *add_new_kid(char *add_name, char *add_surname, char *add_age, char *add_vaccination_status)
{
	char *SQLQuery=construct_string_for_update_multiple_column_query("lista_copii", "name", "surname", "age", "vaccination_status", add_name, add_surname, add_age, add_vaccination_status);
	printf("\n\n%s\n\n",SQLQuery);
	insert_data_in_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

char *delete_kid(char *get_record_id)
{
	char *SQLQuery=construct_string_for_delete("lista_copii", "record_id", get_record_id);
	delete_data_from_sqlite_database("my_dtb.db", SQLQuery);
	return (";");
}

