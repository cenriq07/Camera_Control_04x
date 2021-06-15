/*
 * utilities.h
 *
 *  Created on: 07/05/2021
 *      Author: Enrique
 */

#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "sys_core.h"

void ftoa(float n, char *res, int afterpoint);
static void reverse(char *, size_t);
size_t  sltoa(char *s, long int n);

#endif /* INCLUDE_UTILITIES_H_ */
