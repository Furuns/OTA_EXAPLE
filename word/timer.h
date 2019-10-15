#ifndef __TIMER_H_
#define __TIMER_H_
#include "stm32f10x_tim.h"
void TIM2_Configuration(void);
void TIM2_NVIC_Configuration(void);	
void TIM3_Int_Init(u16 arr,u16 psc);
uint64_t get_sys_tick(void);
#endif
