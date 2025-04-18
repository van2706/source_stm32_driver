/*
 * gpio_f103.h
 *
 *  Created on: Mar 1, 2025
 *      Author: ADMIN
 */

#ifndef INC_GPIO_F103_H_
#define INC_GPIO_F103_H_

#include "stm32f103xxx.h"

typedef struct{
    uint32_t GPIO_Pin_Number;
    uint32_t GPIO_Mode;
    uint32_t GPIO_type;
    uint32_t GPIO_Speed;

}GPIO_Config_t;
typedef struct 
{
    /* data */
    GPIO_RegDef_t *GPIOx;
    GPIO_Config_t GPIOConfig;
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



#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT_PP 1
#define GPIO_MODE_OUTPUT_OD 2
#define  GPIO_MODE_ALT_PP 3
#define GPIO_MODE_ALT_OD 4
#define GPIO_MODE_ANALOG 5

#define GPIO_MODER_IT_FL 6
#define GPIO_MODER_IT_RT 7
#define GPIO_MODER_IT_FL_RT 8

#define GPIO_OUT_SPEED_10MHZ 1
#define GPIO_OUT_SPEED_2MHZ 2
#define GPIO_OUT_SPEED_50MHZ 3

#define GPIO_NOPULL 0
#define GPIO_PULLUP 1
#define GPIO_PULLDOWN 2


// gia tri can cho o nho CNF va Mode
#define GPIO_CR_CNF_ANALOG 0
#define GPIO_CR_CNF_FLOAT_INPUT 1
#define GPIO_CR_CNF_INPUT_PUPD 2

#define GPIO_CR_MODE_OUTPUT_PU 0
#define GPIO_CR_MODE_OUTPUT_OD 1
#define GPIO_CR_MODE_ALT_PU 2
#define GPIO_CR_MODE_ALT_OD 3

void ClockControl(GPIO_RegDef_t *GPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t *GPIO_Handle);
void GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WritePort(GPIO_RegDef_t *GPIOx, uint16_t value);
uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *GPIOx);
void GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber);
void GPIO_TogglePort(GPIO_RegDef_t *GPIOx);
uint8_t Generate_port(GPIO_RegDef_t *GPIOx);
void IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void IRQ_priority(uint8_t IRQNumber, uint8_t priority);
#define IRQ_NUM_EXTI0 6
#define IRQ_NUM_EXTI1 7
#define IRQ_NUM_EXTI2 8
#define IRQ_NUM_EXTI3 9
#define IRQ_NUM_EXTI4 10
#define IRQ_NUM_EXTI9_5 23
#define IRQ_NUM_EXTI15_10 40

__attribute__((weak)) void GPIO_InterruptCallBack(uint8_t PinNumber);
#endif /* INC_GPIO_F103_H_ */
