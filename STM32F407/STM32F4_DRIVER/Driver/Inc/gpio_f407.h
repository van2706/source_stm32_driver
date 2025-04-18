/*
 * gpio_f407.h
 *
 *  Created on: Mar 2, 2025
 *      Author: ADMIN
 */

#ifndef INC_GPIO_F407_H_
#define INC_GPIO_F407_H_

#include  "stm32f407.h"

typedef struct{
	uint8_t GPIO_Pinnumber;
	uint8_t GPIO_Pinmode;
	uint8_t GPIO_Pinspeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPtyple;
	uint8_t GPIO_PinnAltfunction;
}GPIO_Pinconfig_t;
typedef struct {
	GPIO_RegDef_t *GPIOx;
	GPIO_Pinconfig_t Pinconfig;
}GPIO_Handle_t;

#define GPIO_PIN_O 		0
#define GPIO_PIN_1 		1
#define GPIO_PIN_2 		2
#define GPIO_PIN_3 		3
#define GPIO_PIN_4 		4
#define GPIO_PIN_5 		5
#define GPIO_PIN_6 		6
#define GPIO_PIN_7 		7
#define GPIO_PIN_8 		8
#define GPIO_PIN_9 		9
#define GPIO_PIN_10 	10
#define GPIO_PIN_11		11
#define GPIO_PIN_12 	12
#define GPIO_PIN_13 	13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15

// PinMode
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALT 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODER_IT_FL 4
#define GPIO_MODER_IT_RT 5
#define GPIO_MODER_IT_FL_RT 6

#define GPIO_TYPE_PP 0
#define GPIO_TYPE_OD 1

#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_HIGH 2
#define GPIO_SPEED_VERYHIGH 3

#define NO_GPIO_PU_PD 0
#define GPIO_PULL_UP 1
#define GPIO_PULL_DOWN 2


void GPIO_SETUP1(GPIO_Handle_t GPIOHandle);
void GPIO_SETUP2(GPIO_Handle_t GPIOHandle);
void GPIO_Periodclockcontrol(GPIO_RegDef_t *GPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t *GPIOHandle);
void GPIO_Deinit(GPIO_RegDef_t *GPIOx);
void GPIO_WriteToPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToPort(GPIO_RegDef_t *GPIOx, uint16_t value);
int8_t GPIO_ReadToPin(GPIO_RegDef_t *GPIO,uint8_t PinNumber);
int16_t GPIO_ReadToPort(GPIO_RegDef_t *GPIO);
void GPIO_ToggleFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQInterruptPriority(uint8_t IRQNumber, uint32_t priority);
void IRQHandling(uint8_t PinNumber);
#define IRQ_NUM_EXTI0 6
#define IRQ_NUM_EXTI1 7
#define IRQ_NUM_EXTI2 8
#define IRQ_NUM_EXTI3 9
#define IRQ_NUM_EXTI4 10
#define IRQ_NUM_EXTI9_5 23
#define IRQ_NUM_EXTI15_10 40

#define GPIO_GENERAL_TO_CODE(x) ((x==GPIOA)?0 :(x==GPIOB)?1: (x==GPIOC)?2: (x==GPIOD)?3: (x==GPIOE)?4: (x==GPIOF)?5: (x==GPIOG)?6: (x==GPIOH)?7: (x==GPIOI)?8:0)
#endif /* INC_GPIO_F407_H_ */
