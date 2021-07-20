/*
 * common_utilities.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Pavel Racovcen
 */

#ifndef COMMON_UTILITIES_H_
#define COMMON_UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <linux/if.h>
#include <errno.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "construct_dynamic_strings.h"
#include "database_utilities.h"

/*Function to get properties*/
char *extract_kid_info();

/*Funtion to set properties*/
char *set_kid_name();
char *set_kid_surname();
char *set_kid_age();
char *set_kid_vaccine_status();
char *add_new_kid();
char *delete_kid();
char *show_all_kids();

#endif /* COMMON_UTILITIES_H_ */
