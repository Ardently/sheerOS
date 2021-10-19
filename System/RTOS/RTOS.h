#ifndef _RTOS_H
#define _RTOS_H

#include "stm32f10x.h"

/* ������ƿ� */
typedef struct TaskCtrBlock   
{
        u32 OSTCBStkPtr;          /* ����˽��ջջ�� */     
        u32 OSTCBDly;             /* ����������ʱ���� */

}TaskCtrBlock;

#define OS_TASKS  32        /* ���������� */
#define IdelTask_Prio 31   /* �����������ȼ� */

extern TaskCtrBlock TCB[OS_TASKS - 1];  /* ������ƿ鶨�� */
extern TaskCtrBlock *p_OSTCBCur;        /* ָ��ǰ������ƿ��ָ�� */
extern TaskCtrBlock *p_OSTCBHighRdy;    /* ָ��������ȼ�����������ƿ��ָ�� */
extern u8 OSPrioCur;                    /* ��ǰִ������ */
extern u8 OSPrioHighRdy;                /* ������ȼ� */
extern u8 OSRunning;                    /* ���������б�־ 0:δ����  1:�Ѿ����� */
extern u32 OSInterruptSum;              /* �����жϴ��� */
extern u32 OSTime;                      /* ϵͳʱ��(����ʱ���жϴ���) */
extern u32 OSRdyTb1;                    /* ���������, 0:����  1:���� */
extern u32 OSIntNesting;                /* ����ǰ���� */

void OSTimeDly(u32 ticks);              /* ����������ʱʱ�� */
void TicksInterrupt(void);              /* ��ʱ���ж϶�������ʱ������ */
void IdleTask(void *pdata);             /* ϵͳ�������� */
void OSSched(void);                     /* �����л� */
void OSStart(void);                     /* ���������� */
void  OSIntEnter (void);
void OSIntExit(void);                   /* �ж��˳��������жϼ�������� */

void OSTaskCreate(void (*Task)(void *parg), void *parg, u32 *p_Stack, u8 TaskID);   /* ���������� */
void OSTaskSuspend(u8 prio);            /* ����ָ������ */
void OSTaskResume(u8 prio);             /* �ָ������������ */

void OSTaskSwHook(void);                /* �պ��� */

/* in asm function */
void OS_EXIT_CRITICAL(void);      /* �˳��ٽ��� */
void OS_ENTER_CRITICAL(void);     /* �����ٽ��� */
void OSStartHighRdy(void);        /* ���ȵ�һ������ */
void OSCtxSw(void);               /* �����������л� */
void OSIntCtxSw(void);            /* �жϼ������л� */


#endif