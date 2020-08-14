#include "FSM.h"
/*״̬��ע��*/
void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable)
{
    pFsm->FsmTable = pTable;
}

/*״̬Ǩ��*/
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
    pFsm->curState = state;
}

/*�¼�����*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
    FsmTable_t* pActTable = pFsm->FsmTable;
    void (*eventActFun)() = 0;  //����ָ���ʼ��Ϊ��
    int NextState;
    int CurState = pFsm->curState;
    int flag = 0; //��ʶ�Ƿ���������
	int SumItem = pFsm->stuMaxNum;
    int i;
 
    /*��ȡ��ǰ��������*/
    for (i = 0; i<SumItem; i++)
    {
        if (event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }
 
 
    if (flag) //�������������
    {
        /*����ִ��*/
        if (eventActFun)
        {
            eventActFun();
        }
 
        //��ת����һ��״̬
        FSM_StateTransfer(pFsm, NextState);
    }
    else
    {
        // do nothing
    }
}

/*==================================================================
* Function  : FSM_Init
* Description : ״̬����ʼ��
* Input Para  : pFsm״̬������pTable״̬Ǩ�Ʊ�stuMaxNumǨ�Ʊ�����
*               curState��ǰ״̬
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_Init(FSM_t *pFsm, FsmTable_t *pTable, uint8_t stuMaxNum,uint8_t curState)
{
    pFsm->FsmTable = pTable;
    pFsm->curState = curState;
	pFsm->stuMaxNum  = stuMaxNum;
}
