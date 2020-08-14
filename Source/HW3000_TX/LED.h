#ifndef __LED_H__
#define __LED_H__
typedef struct{
    unsigned char one;
	unsigned char two;
	unsigned char three;
	unsigned char four;
}LED_SHOW_POS;
typedef enum{
    REQ_START_BLINK,
	REQ_STOP_BLINK,
}LED_BLINK_REQ;
void LED_Init(void);
void LED_Show(void);
void LED_SetBlink(LED_BLINK_REQ Status);
#endif
