#ifndef _DS3231_H_
#define _DS3231_H_
enum {
	RTC_BUF_SIZE = 3,
	ALM_BUF_SIZE = 4,
};
void DS3231_GetTime(uint8_t *buf, uint8_t size);
void DS3231_SetTime(uint8_t *buf, uint8_t size);
void DS3231_GetTemp(int8_t *val, uint8_t *frac);
void DS3231_GetAlarm1(uint8_t *buf, uint8_t size);
void DS3231_SetAlarm1(uint8_t *buf, uint8_t size);
void DS3231_ReadReg(uint8_t Addr,uint8_t *buf, uint8_t size);
void DS3231_WriteReg(uint8_t Addr,uint8_t *buf, uint8_t size);


void DS3231_Init(void);

#endif
