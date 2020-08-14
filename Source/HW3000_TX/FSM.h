#ifndef __FSM__H
#define __FSM__H
#include "stm8l10x.h"
typedef struct 
{
    int event;
	int CurState;
	void (*eventActFun)();
	int NextState;
}FsmTable_t;

typedef struct FSM_s
{
    FsmTable_t *FsmTable;         /* ״̬Ǩ�Ʊ� */
    uint8_t curState;             /* ״̬����ǰ״̬ */
	uint8_t stuMaxNum;              /* ״̬������*/
}FSM_t;
void FSM_Init(FSM_t *pFsm, FsmTable_t *pTable, uint8_t stuMaxNum,uint8_t curState);
void FSM_EventHandle(FSM_t* pFsm, int event);

#endif
