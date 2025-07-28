#ifndef __LOGGER_
#define __LOGGER_
#include <string.h>
#include "../inc/uart.h"
#include "../inc/rtc.h"

typedef enum 
{
    INFO,
    WARNING,
    ERROR,
    DEBUG,
}logLevel_enum;

void LoggerLevelToStr(logLevel_enum level, char *levelStr);
void LoggerInit(void);
void LoggerLogMsg(logLevel_enum level, char *msg);

#endif