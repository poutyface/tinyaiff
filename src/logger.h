#ifndef _logger_h
#define _logger_h

#include <stdio.h>

#if defined(LOGGER_TRACE)
#define log_trace()       printf("TRACE: [%s:%d] %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define log_debug(M, ...) printf("DEBUG: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define log_info(M, ...)  printf("INFO: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define log_error(M, ...) printf("ERROR: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOGGER_DEBUG)
#define log_trace()      
#define log_debug(M, ...) printf("DEBUG: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define log_info(M, ...)  printf("INFO: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define log_error(M, ...) printf("ERROR: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOGGER_INFO)
#define log_trace()       
#define log_debug(M, ...) 
#define log_info(M, ...)  printf("INFO: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define log_error(M, ...) printf("ERROR: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOGGER_ERROR)
#define log_trace()
#define log_debug(M, ...) 
#define log_info(M, ...) 
#define log_error(M, ...) printf("ERROR: [%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#else
#define log_trace()
#define log_debug(M, ...) 
#define log_info(M, ...) 
#define log_error(M, ...)
#endif

#endif
