/*
 * systick_f103.h
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */

#ifndef INC_SYSTICK_F103_H_
#define INC_SYSTICK_F103_H_

#include <stdint.h>
#define TICK_HZ 1000U
#define HSI_CLOCK 8000000U
#define SYSTICK_TIM_CLK HSI_CLOCK

#define SYST_CSR (uint32_t *)0xE000E010
#define SYST_RVR (uint32_t *)0xE000E014
#define SYST_CVR (uint32_t *)0xE000E014



void Init_systick_time();
uint32_t millis(void);
void delay_ms(uint32_t ms);
#endif /* INC_SYSTICK_F103_H_ */
