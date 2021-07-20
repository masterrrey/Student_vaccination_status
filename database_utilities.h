/*
 * database_utilities.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#ifndef DATABASE_UTILITIES_H_
#define DATABASE_UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

//void print_sqlite_library_version();
void print_sqlite_library_version_using_SQL_query();
void insert_data_in_sqlite_database(char *myDatabaseName, char *mySQLStatement);
int insert_data_and_get_last_inserted_id_in_sqlite_database(char *myDatabaseName, char *mySQLStatement);

/*
 * The callback function is executed within the querying function and needed for the SELECT query
 * *******************************************************
 * The first parameter of the callback function and it is often not used
 * The second parameter of the callback function is the number of columns in the result
 * The third parameter of the callback function is an array of strings representing fields in the row
 * The fourth parameter of the callback function is an array of strings representing columns names
 */
int myCallbackFunction_for_Select(void *, int argc, char **, char **);
void select_data_from_sqlite_database(char *myDatabaseName, char *mySQLStatement);

int myCallback_Function_For_Update(void *, int argc, char **, char **);
void update_data_in_sqlite_database(char *myDatabaseName, char *mySQLStatement);

void delete_data_from_sqlite_database(char *myDatabaseName, char *mySQLStatement);
void check_autocommit_mode_in_sqlite_database(char *myDatabaseName);
char * return_string_from_sqlite_database(char* myDatabaseName, char *mySQLStatement);

#endif /* DATABASE_UTILITIES_H_ */
