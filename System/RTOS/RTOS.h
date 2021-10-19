#ifndef _RTOS_H
#define _RTOS_H

#include "stm32f10x.h"

/* 任务控制块 */
typedef struct TaskCtrBlock   
{
        u32 OSTCBStkPtr;          /* 保存私有栈栈顶 */     
        u32 OSTCBDly;             /* 保存任务延时节拍 */

}TaskCtrBlock;

#define OS_TASKS  32        /* 总任务数量 */
#define IdelTask_Prio 31   /* 空闲任务优先级 */

extern TaskCtrBlock TCB[OS_TASKS - 1];  /* 任务控制块定义 */
extern TaskCtrBlock *p_OSTCBCur;        /* 指向当前任务控制块的指针 */
extern TaskCtrBlock *p_OSTCBHighRdy;    /* 指向最高优先级就绪任务控制块的指针 */
extern u8 OSPrioCur;                    /* 当前执行任务 */
extern u8 OSPrioHighRdy;                /* 最高优先级 */
extern u8 OSRunning;                    /* 多任务运行标志 0:未运行  1:已经运行 */
extern u32 OSInterruptSum;              /* 进入中断次数 */
extern u32 OSTime;                      /* 系统时间(进入时钟中断次数) */
extern u32 OSRdyTb1;                    /* 任务就绪表, 0:挂起  1:就绪 */
extern u32 OSIntNesting;                /* 任务前套数 */

void OSTimeDly(u32 ticks);              /* 设置任务延时时间 */
void TicksInterrupt(void);              /* 定时器中断对任务延时处理函数 */
void IdleTask(void *pdata);             /* 系统空闲任务 */
void OSSched(void);                     /* 任务切换 */
void OSStart(void);                     /* 开启多任务 */
void  OSIntEnter (void);
void OSIntExit(void);                   /* 中断退出函数，中断级任务调度 */

void OSTaskCreate(void (*Task)(void *parg), void *parg, u32 *p_Stack, u8 TaskID);   /* 创建任务函数 */
void OSTaskSuspend(u8 prio);            /* 挂起指定任务 */
void OSTaskResume(u8 prio);             /* 恢复被挂起的任务 */

void OSTaskSwHook(void);                /* 空函数 */

/* in asm function */
void OS_EXIT_CRITICAL(void);      /* 退出临界区 */
void OS_ENTER_CRITICAL(void);     /* 进入临界区 */
void OSStartHighRdy(void);        /* 调度第一个任务 */
void OSCtxSw(void);               /* 函数级任务切换 */
void OSIntCtxSw(void);            /* 中断级任务切换 */


#endif