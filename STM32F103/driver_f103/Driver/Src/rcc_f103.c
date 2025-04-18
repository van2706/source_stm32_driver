/*
 * rcc_f103.c
 *
 *  Created on: Mar 28, 2025
 *      Author: ADMIN
 */
#include "rcc_f103.h"
void RCC_ConfigurationClock(RCC_Handle_t *RCCHandle){
	// write clock
	RCCHandle->RCCx->CFGR &=~ (0x3 << 0);
	RCCHandle->RCCx->CFGR &=~ (RCCHandle->RCCConfig.SYSCLKSource << 0);
	// write to AHB prescaler
	RCCHandle->RCCx->CFGR &=~ (0xF <<4);
	RCCHandle->RCCx->CFGR |= (RCCHandle->RCCConfig.AHBCLKDivider << 4);
	// write to APB1
	RCCHandle->RCCx->CFGR &=~ (0x3<<8);
	RCCHandle->RCCx->CFGR |=(RCCHandle->RCCConfig.APB1CLKDivider <<8);
	// write to APB1
	RCCHandle->RCCx->CFGR &=~ (0x3<<11);
	RCCHandle->RCCx->CFGR |=(RCCHandle->RCCConfig.APB2CLKDivider <<11);
}
void RCC_GET_CLOCK_BUS_APB1(void){
	uint16_t AHBPrescaler[9] ={1,2,4,8,16,64,128,256,512};
	uint8_t APB1Prescaler[5] = {1,2,4,8,16};
	uint8_t temp;
	temp = (RCC->)

}
