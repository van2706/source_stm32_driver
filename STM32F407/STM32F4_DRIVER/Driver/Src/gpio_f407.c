/*
 * gpio_f407.c
 *
 *  Created on: Mar 2, 2025
 *      Author: ADMIN
 */

#include "gpio_f407.h"
void GPIO_Periodclockcontrol(GPIO_RegDef_t *GPIOx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
			if(GPIOx ==GPIOA){
				GPIOA_PCLK();
			}
			else if(GPIOx ==GPIOB){
				GPIOB_PCLK();
			}
			else if(GPIOx ==GPIOC){
				GPIOC_PCLK();
			}
			else if(GPIOx ==GPIOD){
				GPIOD_PCLK();
			}
			else if(GPIOx ==GPIOE){
				GPIOE_PCLK();
			}
			else if(GPIOx ==GPIOF){
				GPIOF_PCLK();
			}
			else if(GPIOx ==GPIOG){
				GPIOG_PCLK();
			}
			else if(GPIOx ==GPIOH){
				GPIOH_PCLK();
			}
			else if(GPIOx ==GPIOI){
				GPIOI_PCLK();
			}
	}
	else{
			if(GPIOx ==GPIOA){
				GPIOA_PCLK();
			}
			else if(GPIOx ==GPIOB){
				GPIOB_PCLK_DI();

			}
			else if(GPIOx ==GPIOC){
				GPIOC_PCLK_DI();
			}
			else if(GPIOx ==GPIOD){
				GPIOD_PCLK_DI();
			}
			else if(GPIOx ==GPIOE){
				GPIOE_PCLK_DI();
			}
			else if(GPIOx ==GPIOF){
				GPIOF_PCLK_DI();
			}
			else if(GPIOx ==GPIOG){
				GPIOG_PCLK_DI();
			}
			else if(GPIOx ==GPIOH){
				GPIOH_PCLK_DI();
			}
			else if(GPIOx ==GPIOI){
				GPIOI_PCLK_DI();
			}
	}
}
void GPIO_Init(GPIO_Handle_t *GPIOHandle){
	if(GPIOHandle->Pinconfig.GPIO_Pinmode <=4){
		GPIOHandle->GPIOx->MODEL &=~ (0x3 << (2*(GPIOHandle->Pinconfig.GPIO_Pinnumber)));
		GPIOHandle->GPIOx->MODEL |= (GPIOHandle->Pinconfig.GPIO_Pinmode << (2*(GPIOHandle->Pinconfig.GPIO_Pinnumber)));
	}else{
		// thuoc ve ngat
		if(GPIOHandle->Pinconfig.GPIO_Pinmode ==GPIO_MODER_IT_FL){
			EXTI->RTSR &=~ (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
			EXTI->FTSR |= (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
		}
		else if(GPIOHandle->Pinconfig.GPIO_Pinmode ==GPIO_MODER_IT_RT){
			EXTI->FTSR &=~ (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
			EXTI->RTSR |= (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
		}
		else if(GPIOHandle->Pinconfig.GPIO_Pinmode ==GPIO_MODER_IT_FL_RT){
			EXTI->FTSR |= (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
			EXTI->RTSR |= (1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
		}
		uint8_t temp1 = GPIOHandle->Pinconfig.GPIO_Pinnumber /4;
		uint8_t temp2 = GPIOHandle->Pinconfig.GPIO_Pinnumber %4;
		SYSCFG->EXTICR[temp1] |= GPIO_GENERAL_TO_CODE(GPIOHandle->GPIOx)<<(4*temp2);
		EXTI->IMR |= (1 <<GPIOHandle->Pinconfig.GPIO_Pinnumber);

	}
		GPIOHandle->GPIOx->OTYPER &=~ (0x1 << GPIOHandle->Pinconfig.GPIO_Pinnumber);
		GPIOHandle->GPIOx->OTYPER |= (GPIOHandle->Pinconfig.GPIO_PinOPtyple << GPIOHandle->Pinconfig.GPIO_Pinnumber);

		GPIOHandle->GPIOx->OSPEEDR &=~(0x3 <<(2*GPIOHandle->Pinconfig.GPIO_Pinnumber));
		GPIOHandle->GPIOx->OSPEEDR |= (GPIOHandle->Pinconfig.GPIO_Pinspeed <<(2*GPIOHandle->Pinconfig.GPIO_Pinnumber));

		GPIOHandle->GPIOx->PUPDR &=~ (0x3 <<(2*GPIOHandle->Pinconfig.GPIO_Pinnumber));
		GPIOHandle->GPIOx->PUPDR |= (GPIOHandle->Pinconfig.GPIO_PinPuPdControl <<(2*GPIOHandle->Pinconfig.GPIO_Pinnumber));

		uint8_t temp1, temp2;
		temp1 = GPIOHandle->Pinconfig.GPIO_Pinnumber /8;
		temp2 = GPIOHandle->Pinconfig.GPIO_Pinnumber%8;
		GPIOHandle->GPIOx->AFR[temp1] &=~(0xff << (4*temp2));
		GPIOHandle->GPIOx->AFR[temp1] |= (GPIOHandle->Pinconfig.GPIO_PinnAltfunction <<(4*temp2));
}
void GPIO_Deinit(GPIO_RegDef_t *GPIOx){
	uint8_t temp;
	if(GPIOx == GPIOA){temp =0;}
	else if(GPIOx == GPIOB){temp =1;}
	else if(GPIOx == GPIOC){temp =2;}
	else if(GPIOx == GPIOD){temp =3;}
	else if(GPIOx == GPIOE){temp =4;}
	else if(GPIOx == GPIOF){temp =5;}
	else if(GPIOx == GPIOG){temp =6;}
	else if(GPIOx == GPIOH){temp =7;}
	else if(GPIOx == GPIOI){temp =8;}
	RCC->AHB1RSTR |= (1 <<temp);
	RCC->AHB1RSTR &=~ (1 <<temp);
}
void GPIO_WriteToPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t value){
	GPIOx->ODR |= value <<PinNumber;
}
void GPIO_WriteToPort(GPIO_RegDef_t *GPIOx, uint16_t value){
		GPIOx->ODR |= (uint16_t)value;
}
int8_t GPIO_ReadToPin(GPIO_RegDef_t *GPIO,uint8_t PinNumber){
		uint8_t value;
		value = (uint8_t)((GPIO->IDR >> PinNumber)&(0x00000001));
		return value;
}
int16_t GPIO_ReadToPort(GPIO_RegDef_t *GPIO){
	uint16_t value;
	value = ((GPIO->IDR)&(0x00000001));
	return value;

}
void GPIO_ToggleFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1<< PinNumber);
}
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
		if(IRQNumber <=31){
			*(NVIC_ISER0) |= (1 <<IRQNumber);
		}
		else if(IRQNumber >31 &&IRQNumber <=64){
			*(NVIC_ISER1) |= (1 <<IRQNumber%32);
		}
		else if(IRQNumber <64 &&IRQNumber <=96){
			*(NVIC_ISER1) |= (1 <<IRQNumber%64);
		}
	}
	else{
		if(IRQNumber <=31){
			*(NVIC_ISER0) &=~ (1 <<IRQNumber);
		}
		else if(IRQNumber >31 &&IRQNumber <=64){
			*(NVIC_ISER1) &=~ (1 <<IRQNumber%32);
		}
		else if(IRQNumber <64 &&IRQNumber <=96){
			*(NVIC_ISER1) &=~ (1 <<IRQNumber%64);
		}
	}
}

void GPIO_IRQInterruptPriority(uint8_t IRQNumber, uint32_t priority){
	uint8_t temp1 = IRQNumber /8;
	uint8_t temp2 = IRQNumber %8;

	*(NVIC_IPR0 + temp1) |=( priority <<(8*temp2 +4));

}
void IRQHandling(uint8_t PinNumber){
	if(EXTI->PR &(1<<PinNumber)){
		EXTI->PR |= (1<<PinNumber);
	}
}
