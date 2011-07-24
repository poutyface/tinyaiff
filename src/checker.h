#ifndef _checker_h
#define _checker_h

#include "logger.h"

#define check(C, M, ...) if(!(C)){ log_error(M, ##__VA_ARGS__); goto error; }

#endif
