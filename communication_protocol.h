/*
 * communication_protocol.h
 *
 *  Created on: July 7, 2021
 *  Author: Pavel Racovcen
 */

#ifndef COMMUNICATION_PROTOCOL_H_
#define COMMUNICATION_PROTOCOL_H_

#include <stdio.h> //this library contains variable types, functions and macros for performing input and output e.g. int fclose(FILE *stream) to close a stream
#include <stdlib.h> //this library defines variable types, functions and macros to perform general useful functions e.g. int atoi(const char * str) to convert a string to an integer
#include <string.h> //this library contains useful variable types, functions and a macro for manipulating strings e.g. char *(char * destination, char * source)
#include <ctype.h> //this library contains useful variable types, functions and macros to test and map characters e.g. int isalpha(int c) etc
#include <errno.h> //this library defines the integer variable errno, thus providing precise explanations for the ocurring errors during runtime
#include <time.h> //this library contains variable types,  functions and macros useful to manipulate date and time e.g. time_t time(time_t * timer)
#include "common_utilities.h" //this header contains all the functions needed here , but programmed internally
#include  "construct_dynamic_strings.h"


void process_answer(char * cmd);

#endif /* COMMUNICATION_PROTOCOL_H_ */
