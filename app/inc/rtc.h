#ifndef _RTC_
#define _RTC_
#include <stdint.h>

void RtcInit(uint32_t presetCounterVal);
void RtcSetCounter(uint32_t counterValue);
void RtcGetTimeStr(char *time);
uint32_t RtcGetTime(void);
#endif