#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "RTOS.h"

#define task0_Prio 3   
#define task1_Prio 4
u32 TASK0TASK_STK[30];
u32 TASK1TASK_STK[30];

void Task0Task(void *pdata);
void Task1Task(void *pdata);

void TIM3_Int_Init(u16 arr,u16 psc);

 int main(void)
 {	  
   delay_init();
   uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
  // TIM3_Int_Init(10 - 1,7200 - 1);
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   
   OSTaskCreate(Task0Task, (void*)0, (u32*)&TASK0TASK_STK[30], task0_Prio);
   OSTaskCreate(Task1Task, (void*)0, (u32*)&TASK1TASK_STK[30], task1_Prio);
   OSStart();
 }
 
 /* ϵͳ�������� */
void Task0Task(void *pdata)
{
    while (1)
    {
        printf("����1����\r\n ");
        OSTimeDly(100);
    }
}

  /* ϵͳ�������� */
void Task1Task(void *pdata)
{
    while (1)
    {
        printf("����2����\r\n ");
        OSTimeDly(200);
    }
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{   
    OS_ENTER_CRITICAL();
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
        TicksInterrupt();
	}
    OS_EXIT_CRITICAL();    
}




 