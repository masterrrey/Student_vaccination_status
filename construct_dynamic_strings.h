/*
 * construct_dynamic_strings.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#ifndef CONSTRUCT_DYNAMIC_STRINGS_H_
#define CONSTRUCT_DYNAMIC_STRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//Funtions to build strings for SQL Queries
char *construct_string_for_select_query_with_where(char *myDatabaseTable,char * myColumnNameToSelect, char *myColumnNameWHERE, char *myValueEqualTo);
char *construct_string_for_update_query(char *myDatabaseTable,char *myColumnNameToUpdate, char *myValueToUpdate);
char *construct_string_for_update_query_with_where(char *myDatabaseTable, char *myColumnNameToUpdate, char *myValueToUpdate, char *myColumnNameWHERE, char *myValueEqualTo);
char *construct_string_for_update_multiple_column_query(char *myDatabaseTable, char *myColumn1ToUpdate, char *myColumn2ToUpdate, char *myColumn3ToUpdate, char *myColumn4ToUpdate, char *myValue1ToUpdate, char *myValue2ToUpdate, char *myValue3ToUpdate, char *myValue4ToUpdate);
char *construct_string_for_delete(char *myDatabaseTable,char *myColumnNameWHERE, char *myValueToDELETE);
char *construct_string_to_show_all_kids(char *myDatabaseTable);

//Functions to fulfill various utility usage on strings
//char *get_substring_of_a_string(char *this_string, int index_to_start_from, int how_many_characters);

#endif /* CONSTRUCT_DYNAMIC_STRINGS_H_ */
