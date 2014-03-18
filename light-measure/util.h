/*
 * util.h
 *
 * Created: 12.12.2012 22:50:06
 *  Author: sunside
 */ 

#ifndef UTIL_H_
#define UTIL_H_

#include <limits.h>

// Because we can.
#include "system.h"

//! \def SUCCESS The return value for success
#define SUCCESS	0

//! \def VALUE_TO_STRING Helper macro to print the content of a define
#define VALUE_TO_STRING(x) #x

//! \def VALUE Macro to print the content of a define
#define VALUE(x) VALUE_TO_STRING(x)

//! \def VAR_NAME_VALUE macro to print the name and content of a define
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

//! \def MAX_VALUE Gets the maximum value of a data type
#define MAX_VALUE(a) (((unsigned long long)1 << (sizeof(a) * CHAR_BIT)) - 1)

#endif /* UTIL_H_ */