//
// logger.h
//

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "string.h"

#define STANDART_LOG_COLOR "\033[0m"

#define DEBUG_LOG(msg) logMessage(DEBUG, msg);
#define INFO_LOG(msg) logMessage(INFO, msg);
#define WARNING_LOG(msg) logMessage(WARNING, msg);
#define ERROR_LOG(msg) logMessage(ERROR, msg);
#define CRITICAL_LOG(msg) logMessage(CRITICAL, msg);

#define INFOG_LOG(msg) logMessage(INFO_G, msg);

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL, INFO_G };

const char* logLevelToString(enum LogLevel level);
const char* logSetLogColor(enum LogLevel level);
void logMessage(enum LogLevel level, const char* message);

#endif // _LOGGER_H_