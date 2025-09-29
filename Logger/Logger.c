#include <time.h>
#include <stdio.h>
#include <string.h>

#include "Logger.h"

const char* logLevelToString(enum LogLevel level)
{
    switch (level) {
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        case INFO_G: return "INFO";
        default: return "UNKNOWN";
    }
}

const char* logSetLogColor(enum LogLevel level)
{
    switch (level) {
        case DEBUG: return "\033[36m";       
        case INFO: return "\033[37m";       
        case WARNING: return "\033[33m";     
        case ERROR: return "\033[31m";     
        case CRITICAL: return "\033[1;31;47m";
        case INFO_G:  return "\033[32m";

        default: return "\033[90m"; 
    }
}

void logMessage(enum LogLevel level, const char* message)
{

    printf("%s[%s] %s%s\n", 
           logSetLogColor(level), 
           logLevelToString(level), 
           message,
           STANDART_LOG_COLOR);
}