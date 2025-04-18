/*
 * main_gpio_it.c
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */
#include "stm32f103xxx.h"
#include "gpio_f103.h"
#include "systick_f103.h"

void DV_GPIO_Inits(void);
int main(void)
{
	DV_GPIO_Inits();
	Init_systick_time();
	 IRQInterruptConfig(IRQ_NUM_EXTI1, ENABLE);
	 IRQ_priority(IRQ_NUM_EXTI1, 8);
    /* Loop forever */
	while (1){
		GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
		delay_ms(1000);
	}
	return 0;
}
void DV_GPIO_Inits(void){
	GPIO_Handle_t GPIO_Handle;
	GPIO_Handle.GPIOx = GPIOA;
	GPIO_Handle.GPIOConfig.GPIO_Mode = GPIO_MODER_IT_RT;
	GPIO_Handle.GPIOConfig.GPIO_Pin_Number = GPIO_PIN_1;
	GPIO_Handle.GPIOConfig.GPIO_Speed = GPIO_OUT_SPEED_10MHZ;
	GPIO_Handle.GPIOConfig.GPIO_type = GPIO_NOPULL;
	GPIO_Init(&GPIO_Handle);
}

void EXTI1_IRQHandler(){
	IRQ_Handling(GPIO_PIN_1);
}
void GPIO_InterruptCallBack(uint8_t pinNumber){
	if(pinNumber==GPIO_PIN_1){
		GPIO_TogglePin(GPIOA, GPIO_PIN_1);
	}
}
