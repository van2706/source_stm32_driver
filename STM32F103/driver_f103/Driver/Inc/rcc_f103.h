/*
 * rcc_f103.h
 *
 *  Created on: Mar 28, 2025
 *      Author: ADMIN
 */

#ifndef INC_RCC_F103_H_
#define INC_RCC_F103_H_
#include "stm32f103xxx.h"
typedef struct{
	uint32_t SYSCLKSource;
	uint32_t AHBCLKDivider;
	uint32_t APB1CLKDivider;
	uint32_t APB2CLKDivider;

}RCC_config_t;
typedef struct{
	RCC_config_t RCCConfig;
	RCC_RegDef_t *RCCx;
}RCC_Handle_t;

#define SYSCLK_SOURCE_HSI 0
#define SYSCLK_SOURCE_HSE 1
#define SYSCLK_SOURCE_PLL 2

#define AHBCLK_DIVIDER_1 1
#define AHBCLK_DIVIDER_2 8
#define AHBCLK_DIVIDER_4 9
#define AHBCLK_DIVIDER_8 10
#define AHBCLK_DIVIDER_16 11
#define AHBCLK_DIVIDER_64 12
#define AHBCLK_DIVIDER_128 13
#define AHBCLK_DIVIDER_256 14
#define AHBCLK_DIVIDER_512 15

#define APB1CLK_DIVIDER_1 1
#define APB1CLK_DIVIDER_2 4
#define APB1CLK_DIVIDER_4 5
#define APB1CLK_DIVIDER_8 5
#define APB1CLK_DIVIDER_16 6

#define APB2CLK_DIVIDER_1 1
#define APB2CLK_DIVIDER_2 4
#define APB2CLK_DIVIDER_4 5
#define APB2CLK_DIVIDER_8 5
#define APB2CLK_DIVIDER_16 6

void RCC_ConfigurationClock(RCC_Handle_t *RCCHandle);
void RCC_GET_CLOCK_BUS_APB1(void);
void RCC_GET_CLOCK_BUS_APB2(void);

#endif /* INC_RCC_F103_H_ */
