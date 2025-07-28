#include "../inc/logger.h"
#include <libopencm3/stm32/usart.h>
#include <stdio.h>

static uart_handle_t uart_handle;
void LoggerLevelToStr(logLevel_enum level, char *levelStr)
{
    switch (level)
    {
    case INFO:
        strcpy(levelStr, "INFO");
        break;
    case WARNING:
        strcpy(levelStr, "WARNING");
        break;
    case ERROR:
        strcpy(levelStr, "ERROR");
        break;
    case DEBUG:
        strcpy(levelStr, "DEBUG");
        break;
    default:
        strcpy(levelStr, "DEBUG");
        break;
    }
}
void LoggerInit(void)
{
    // initalize rtc;
    RtcInit(0);
    // initalize uart 
    UartInit(USART2, &uart_handle);
}
void LoggerLogMsg(logLevel_enum level, char *msg)
{
    char buffer[LOGGER_BUFFER_SIZE];
    char time[20];
    char levelStr[15];

    LoggerLevelToStr(level, levelStr);
    #ifdef _USE_RTC
        RtcGetTimeStr(time);
        sprintf(buffer, "%s:\t %s : %s", time, levelStr, msg);
    #else
        sprintf(buffer, "%s : %s",levelStr, msg);
    #endif

    UartPrintLn(&uart_handle, buffer);
}
