/*
 * main_usart.c
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */

#include "stm32f103xxx.h"
#include "usart_f103.h"
#include "gpio_f103.h"
#include <string.h>
USART_Handle_t USARTHandle1;
GPIO_Handle_t GPIOHandle1, GPIOHandle2;
char message[100] = "dinh van";
void DV_USART_Inits();
void DV_GPIO_Inits();
int main(){
	DV_GPIO_Inits();
	DV_USART_Inits();
	while(1){
		USART_SendData(&USARTHandle1, (uint8_t *)message , strlen(message));
	}
	return 0;
}

void DV_USART_Inits(){

	USARTHandle1.USARTx = USART1;
	USARTHandle1.USART_Config.USART_Mode = USART_MODE_TX_RX;
	USARTHandle1.USART_Config.USART_Parity = USART_PARTY_DISABLE;
	USARTHandle1.USART_Config.USART_Wordlenght = USART_8BIT_DATA;
	USARTHandle1.USART_Config.USART_Stop = USART_STOP_1BIT;
	USARTHandle1.USART_Config.HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	USARTHandle1.USART_Config.Baudrate = USART_STD_BAUD_115200;

}
void DV_GPIO_Inits(){
	// USART_TX PA9
	// USART_RX PA10
	GPIOHandle1.GPIOx =GPIOA;
	GPIOHandle1.GPIOConfig.GPIO_Mode = GPIO_MODE_ALT_PP;
	GPIOHandle1.GPIOConfig.GPIO_Pin_Number = GPIO_PIN_9;
	GPIOHandle1.GPIOConfig.GPIO_Speed = GPIO_OUT_SPEED_10MHZ;
	GPIOHandle1.GPIOConfig.GPIO_type = GPIO_NOPULL;

	GPIOHandle2.GPIOx =GPIOA;
	GPIOHandle2.GPIOConfig.GPIO_Mode = GPIO_MODE_ALT_PP;
	GPIOHandle2.GPIOConfig.GPIO_Pin_Number = GPIO_PIN_10;
	GPIOHandle2.GPIOConfig.GPIO_Speed = GPIO_OUT_SPEED_10MHZ;
	GPIOHandle2.GPIOConfig.GPIO_type = GPIO_NOPULL;
}
