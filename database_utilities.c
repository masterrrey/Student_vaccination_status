/*
 * database_utilities.c
 *
 *  Created on: Jun 10, 2021
 *  Author: Pavel Racovcen
 */
#include "database_utilities.h"

void print_sqlite_library_version()
{
	    puts("***********************************************************");
		printf("The version of SQLite Library running on this system is %s.\n", sqlite3_libversion());

}

void print_sqlite_library_version_using_SQL_query()
{
	sqlite3 *my_database;  //declares a database handle
	sqlite3_stmt *statement; //declares the handle of the SQL statement

	/*
	 * The sqlite3_open() functions opens a new database connection.
	 * The parameters of the sqlite3_open() function are: database name and the database handle.
	 * The ":memory: " database name is a special database which causes opening an in-memory database
	 * The return code indicates whether the database has been successfully opened. If successfully opened, the return code is SQLITE_OK and the connection is established
	 */
	int return_code=sqlite3_open(":memory:", &my_database);

	if (return_code!=SQLITE_OK)
	{
		perror("sqlite_open"); //prints a descriptive error message to stderr
		/*
		 * #include <stdio.h>
		 * fprintf() function sends formatted output to a stream
		 * int fprintf(FILE *stream, const char *format,...)
		 */
		fprintf(stderr,"Oops, I can not open the database \"%s\".\n", sqlite3_errmsg(my_database));
		sqlite3_close(my_database); //the resources associated with the database connection handle are released
	}

	/*
	 * Before a SQL Statement is executed , this statement has to be compiled in byte-code.
	 * The compilation into byte-code is done using one of the sqlite3_prepare??  functions. The use of the sqlite3_prepare() function is deprecated.
	 * The sqlite3_prepare_v2() function takes 5 parameters.
	 * 1st parameter is the handle of the database
	 * 2nd parameter is the SQL Statement to be compiled
	 * 3rd parameter is the maximum length of the SQL statement measured in bytes. If passed -1, it means that the SQL Statement is read up to the first \0 character which is the end of the string. Gain performance advantage by using the exact size in bytes of the SQL Statement string.
	 * 4th parameter is the handle of the statement. It will point to the precompiled SQL Statement in byte code if the command runs properly
	 * 5th parameter is a pointer to the unused portion of the SQL Statement. Only the 1st statement of the SQL String is compiled, so this parameter points to what is left uncompiled.
	 * On success, sqlite3_prepare_v2() returns SQLITE_OK; if it fails it returns an error code.
	 */
	  return_code=sqlite3_prepare_v2(my_database,"SELECT SQLITE_VERSION()",-1,&statement,0);

	  if (return_code!=SQLITE_OK)
	  {
		  perror("sqlite3_prepare_v2");
		  fprintf(stderr,"Failed to compile the SQL Statement in byte code : %s.\n", sqlite3_errmsg(my_database));
		  sqlite3_close(my_database);
	  }

	  /*
	   * Next, we run the SQL Statement as at this point the SQL Statement was prepared and is precompiled in byte code
	   * We use function sqlite3_step(handler_of_the_statement)
	   * When the return code from the sqlite3_step() is SQLITE_ROW it means there is another row ready. In this case there is only one Row to be returned , hence we run this only once, and not in a loop.
	   */
	  return_code=sqlite3_step(statement);

	  if(return_code==SQLITE_ROW)
	  {
		  printf("%s\n", sqlite3_column_text(statement, 0)); //column_text(handler, column_index))
	  }

	  //sqlite3_finalize(handler_statement) function destroys the statement pointer
	  sqlite3_finalize(statement);

	  //close the database connection
     sqlite3_close(my_database);
}

void insert_data_in_sqlite_database(char *myDatabaseName, char *mySQLStatement)
{
	sqlite3 *my_database;
	char return_code;
	char *error_message;

	return_code=sqlite3_open(myDatabaseName,&my_database); //Note: if the database does not exit, it will be constructed

	if(return_code!=SQLITE_OK)
	{
		perror("sqlite3_open()");
		fprintf(stderr,"Ooops, I got an error when opening the database %s.\n",sqlite3_errmsg(my_database));
		sqlite3_close(my_database);
	}

	/*
	 * the sqlite3_exec() function is a wrapper around sqlite_prepare_v2() + sqlite3_step() + sqlite3_finalize()
	 * sqlite3_exec() function uses 5 arguments:
	 * 1st argument is the name of the database handler
	 * 2nd argument is the statement string to execute
	 * 3rd argument is the callback function invoked for each result row coming out of the evaluated SQL statement. If you do not need it, place 0
	 * 4th argument is the first parameter to the callback function.If you do not need it, place 0
	 * 5th argument is a pointer to the error message
	 * If an error occurs out of the invoking the sqlite3_exec() function, then the last parameter points to the allocated error message
	 */

	return_code=sqlite3_exec(my_database,mySQLStatement,0,0,&error_message);

	if(return_code!=SQLITE_OK)
	{
		perror("sqlite3_exec()");
		fprintf(stderr,"Ooops, I got an error while executing sqlite3_exec() %s.\n", sqlite3_errmsg(my_database));

		//the allocated error message has to be freed using the sqlite3_free() function call
		sqlite3_free(error_message);

		sqlite3_close(my_database);
	}
	else
	{
		puts("Operation of INSERT in the database has performed successfully.");
		sqlite3_close(my_database);
	}
}

int insert_data_and_get_last_inserted_id_in_sqlite_database(char *myDatabaseName, char *mySQLStatement)
{
	sqlite3  *myDatabaseHandler;
	char *errorMessage=0;

	int returned_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

	if(returned_character!=SQLITE_OK)
	{
		perror("sqlite3_open()");
		fprintf(stderr,"Oops..I could not open the database. %s\n",sqlite3_errmsg(myDatabaseHandler));
		sqlite3_close(myDatabaseHandler);
		return -1;
	}

	returned_character=sqlite3_exec(myDatabaseHandler,mySQLStatement,0,0,&errorMessage);

	if(returned_character!=SQLITE_OK)
	{
		perror("sqlite3_exec");
		fprintf(stderr,"Oops...error when executing the SQL Statement \"%s\": %s.\n",mySQLStatement,errorMessage);

		sqlite3_free(errorMessage);
		sqlite3_close(myDatabaseHandler);
		return -1;
	}
	else
	{
		fprintf(stdout,"Data inserted correctly in the database \"%s\".\n",myDatabaseName);
		/* *****
		 * sqlite3_last_insert_rowid() function returns the value of the last inserted ROWID.
		 * If no rows have been inserted since the database connection was opened, then this function will return 0.
		 */
		int lastRecordID=sqlite3_last_insert_rowid(myDatabaseHandler);

		printf("The last ID of the a row inserted in the database table is %d.\n",lastRecordID);

		sqlite3_close(myDatabaseHandler);

		return lastRecordID;
	}
}

int myCallbackFunction_for_Select(void *notUsed, int argc, char ** argv, char ** argColumnNames)
{
	puts("Executing callback function...");
	notUsed=0;

	for(int i=0;i<argc;i++)
	{
		printf("%s = %s\n", argColumnNames[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
}

void select_data_from_sqlite_database(char *myDatabaseName, char *mySQLStatement)
{
	    //Any function that is passed as an argument to other function otherfunction() is a callback function, and the callback function  is called and executed inside the otherfunction()

	    sqlite3 *myDatabaseHandler;
	    char *error_message=0;
	    sqlite3_stmt *myTransactionHandler;

	    int returned_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

	    if(returned_character!=SQLITE_OK)
	    {
	    	perror("sqlite3_open()");
	    	fprintf(stderr,"Ooops...I got an error when opening the database \"%s\" : %s.\n",myDatabaseName,sqlite3_errmsg(myDatabaseHandler));
	    	sqlite3_close(myDatabaseHandler);
	    }

	   returned_character=sqlite3_prepare_v2(myDatabaseHandler,mySQLStatement,-1,&myTransactionHandler,0);

	    if(returned_character!=SQLITE_OK)
	    {
	    	perror("sqlite3_exec()");
	    	fprintf(stderr,"Oops..Failed to select data from database \"%s\".\n",myDatabaseName);
	    	fprintf(stderr,"SQL Error is %s. \n",error_message);

	    	sqlite3_free(error_message);
	    	sqlite3_close(myDatabaseHandler);
	    }
	    else
	    {
	    	//puts("Operation of SELECT from database has performed successfully.");
            while(sqlite3_step(myTransactionHandler)==SQLITE_ROW)
            {
            	printf("%s  %s \t%s \t%s \t%s\n",
            			 sqlite3_column_text(myTransactionHandler,0),
						 sqlite3_column_text(myTransactionHandler,1),
						 sqlite3_column_text(myTransactionHandler,2),
						 sqlite3_column_text(myTransactionHandler,3),
						 sqlite3_column_text(myTransactionHandler,4));

            }

            sqlite3_finalize(myTransactionHandler);
            sqlite3_close(myDatabaseHandler);
	    }
}

/*
 * The first parameter of the callback function and it is often not used
 * The second parameter of the callback function is the number of columns in the result
 * The third parameter of the callback function is an array of strings representing fields in the row
 * The fourth parameter of the callback function is an array of strings representing columns names
 */

void update_data_in_sqlite_database(char *myDatabaseName, char *mySQLStatement)
{
	sqlite3 *myDatabaseHandler;
	char *errorMessage=0;

	int return_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

	if(return_character!=SQLITE_OK)
	{
		perror("sqlite3_open()");
		fprintf(stderr,"Oops..I got an error when opening the database \"%s\" : %s.\n", myDatabaseName, sqlite3_errmsg(myDatabaseHandler));
		sqlite3_close(myDatabaseHandler);
	}

	/* *** Example of SQL Update statement
	 * UPDATE table_name
	 * SET column1=value1, column2=value2...columnN=valueN
	 * WHERE [condition]
	 */

	return_character=sqlite3_exec(myDatabaseHandler, mySQLStatement,myCallback_Function_For_Update, 0, &errorMessage);

	if(return_character !=SQLITE_OK)
		{
			perror("sqlite3_exec()");
			fprintf(stderr,"Oops..error while sqlite3_exec() of this SQL Statement \t \"%s\" : %s. \n ",mySQLStatement,errorMessage);

			sqlite3_free(errorMessage);
			sqlite3_close(myDatabaseHandler);
		}
	else
	{
		//fprintf(stdout,"Operation of UPDATE in the database has been performed successfully.\n");
		sqlite3_close(myDatabaseHandler);
	}
}

/*
 * The first parameter of the callback function and it is often not used
 * The second parameter of the callback function is the number of columns in the result
 * The third parameter of the callback function is an array of strings representing fields in the row
 * The fourth parameter of the callback function is an array of strings representing columns names
 */
int myCallback_Function_For_Update(void *notUsed, int argc, char ** argv, char ** argColumnNames)
{
	notUsed=0;

	for(int i=0;i<argc;i++)
	{
		printf("%s = %s\n", argColumnNames[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
}

void delete_data_from_sqlite_database(char *myDatabaseName, char *mySQLStatement)
{
	sqlite3 *myDatabaseHandler;
	char *errorMessage=0;

	int return_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

	if(return_character!=SQLITE_OK)
	{
		perror("sqlite3_open()");
		fprintf(stderr,"Oops..I got an error when opening the database \"%s\" : %s.\n", myDatabaseName, sqlite3_errmsg(myDatabaseHandler));
		sqlite3_close(myDatabaseHandler);
	}

	/* *** Example of SQL Statement DELETE from Cars *** */

	return_character=sqlite3_exec(myDatabaseHandler,mySQLStatement,0,0,&errorMessage);

	if(return_character !=SQLITE_OK)
	{
		perror("sqlite3_exec()");
		fprintf(stderr,"Oops..error while sqlite3_exec() of this SQL Statement \t \"%s\" : %s. \n ",mySQLStatement,errorMessage);

		sqlite3_free(errorMessage);
		sqlite3_close(myDatabaseHandler);
	}
	else
	{
		printf("The records have been deleted successfully from the database");
		sqlite3_close(myDatabaseHandler);
	}
}

void check_autocommit_mode_in_sqlite_database(char *myDatabaseName)
{
    /*
     * A transaction is an atomic unit of database operations against the data in one or more databases.
     * The effects of all the SQL statements in a transaction can be either all committed to the database or rolled back.
     * ****************************************
     * Autocommit
     * ****************************************
     *  In autocommit mode, all changes to the database are committed as soon as all the operations associated with the current database connection complete.
     *  Autocommit mode is disabled by a BEGIN statement and re-enabled by a COMMIT or ROLLBACK
     */
	  sqlite3 *myDatabaseHandler;

	  int return_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

	  if (return_character!=SQLITE_OK)
	  {
		  perror("sqlite3_open()");
		  fprintf(stderr,"Oops...error while opening the database \"%s\" : %s.\n",myDatabaseName,sqlite3_errmsg(myDatabaseHandler));
		  sqlite3_close(myDatabaseHandler);
	  }
	  else
	  {
		  /*
		   * The function sqlite3_get_autocommit() returns 0 if the database is not in 'autocommit' mode
			* sqlite3_get_autocommit() returns non-0 if it is in 'autommit' mode
			 */

		 printf("The autocommit mode for this database \"%s\" is set to  %d.\n", myDatabaseName, sqlite3_get_autocommit(myDatabaseHandler));
		 sqlite3_close(myDatabaseHandler);

	  }
}

char * return_string_from_sqlite_database(char* myDatabaseName, char *mySQLStatement)
{
	 static char return_string_from_database[30];  //in case that the entered password does not correspond to an access level in the db table, it returns the "-1"

	sqlite3 *myDatabaseHandler;
     char *error_message=0;
	 sqlite3_stmt *myTransactionHandler;

     int returned_character=sqlite3_open(myDatabaseName,&myDatabaseHandler);

     if(returned_character!=SQLITE_OK)
		    {
		    	perror("sqlite3_open()");
		    	fprintf(stderr,"Ooops...I got an error when opening the database \"%s\" : %s.\n",myDatabaseName,sqlite3_errmsg(myDatabaseHandler));
		    	sqlite3_close(myDatabaseHandler);
		    }

		   returned_character=sqlite3_prepare_v2(myDatabaseHandler,mySQLStatement,-1,&myTransactionHandler,0);

		    if(returned_character!=SQLITE_OK)
		    {
		    	perror("sqlite3_exec()");
		    	fprintf(stderr,"Oops..Failed to select data from database \"%s\".\n",myDatabaseName);
		    	fprintf(stderr,"SQL Error is %s. \n",error_message);

		    	sqlite3_free(error_message);
		    	sqlite3_close(myDatabaseHandler);
		    }
		    else
		    {
		    	strcpy(return_string_from_database,"-1");
		    	while(sqlite3_step(myTransactionHandler)==SQLITE_ROW)
		    	{
		    		strcpy(return_string_from_database,sqlite3_column_text(myTransactionHandler,0));
		    	}
		    	sqlite3_finalize(myTransactionHandler);
		    	sqlite3_close(myDatabaseHandler);
		    }
		    return return_string_from_database;

}

