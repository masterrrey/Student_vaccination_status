/*
 * construct_dynamic_strings.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#include "construct_dynamic_strings.h"

/*char *construct_string_for_select_query_with_where(char *myDatabaseTable,char * myColumnNameToSelect, char *myColumnNameWHERE, int *myValueEqualTo)
{
	static char bucketSelect[200];
	//the returned value from snprinf() is the number of characters entered in the stream
	int output_length=snprintf(bucketSelect,200,"SELECT %s FROM %s WHERE %s=%d ", myColumnNameToSelect,myDatabaseTable,myColumnNameWHERE,myValueEqualTo);
	return bucketSelect;
}*/

char *construct_string_for_update_query(char *myDatabaseTable,char *myColumnNameToUpdate, char *myValueToUpdate)
{
	static char bucketUpdate[250];
	int output_length=snprintf(bucketUpdate,250,"UPDATE %s SET %s='%s' ; ",myDatabaseTable,myColumnNameToUpdate,myValueToUpdate);
	return bucketUpdate;
}

char *construct_string_for_update_query_with_where(char *myDatabaseTable, char *myColumnNameToUpdate, char *myValueToUpdate, char *myColumnNameWHERE, char *myValueEqualTo)
{
	static char bucketUpdate[250];
	int output_length=snprintf(bucketUpdate,100,"UPDATE %s SET %s='%s'  WHERE %s='%s'; ",myDatabaseTable,myColumnNameToUpdate,myValueToUpdate,myColumnNameWHERE,myValueEqualTo);
	return bucketUpdate;
}

char *construct_string_for_update_multiple_column_query(char *myDatabaseTable, char *myColumn1ToUpdate, char *myColumn2ToUpdate, char *myColumn3ToUpdate, char *myColumn4ToUpdate, char *myValue1ToUpdate, char *myValue2ToUpdate, char *myValue3ToUpdate, char *myValue4ToUpdate)
{
	static char bucketUpdate[250];
	int output_length=snprintf(bucketUpdate,250,"INSERT INTO %s (%s, %s, %s, %s) VALUES ('%s', '%s', '%s', '%s');",myDatabaseTable, myColumn1ToUpdate, myColumn2ToUpdate, myColumn3ToUpdate, myColumn4ToUpdate, myValue1ToUpdate, myValue2ToUpdate, myValue3ToUpdate, myValue4ToUpdate);
	return bucketUpdate;
}

char *construct_string_for_delete(char *myDatabaseTable,char *myColumnNameWHERE, char *myValueToDELETE)
{
	static char bucketUpdate[250];
	int output_length=snprintf(bucketUpdate,250,"DELETE FROM %s WHERE %s='%s' ; ",myDatabaseTable, myColumnNameWHERE ,myValueToDELETE);
	return bucketUpdate;
}

char *construct_string_to_show_all_kids(char *myDatabaseTable)
{
	static char bucketUpdate[250];
	int output_length=snprintf(bucketUpdate,250,"SELECT * FROM %s ; ",myDatabaseTable);
	return bucketUpdate;
}
