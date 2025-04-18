/*
 * gpio_f103.c
 *
 *  Created on: Mar 1, 2025
 *      Author: ADMIN
 */
#include "gpio_f103.h"

void ClockControl(GPIO_RegDef_t *GPIOx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
	    if(GPIOx == GPIOA){
	        GPIOA_PCLK();
	    }
	    else  if(GPIOx == GPIOB){
	        GPIOB_PCLK();
	    }
	    else  if(GPIOx == GPIOC){
	        GPIOC_PCLK();
	    }
	    else  if(GPIOx == GPIOD){
	        GPIOD_PCLK();
	    }
	    else  if(GPIOx == GPIOE){
	        GPIOE_PCLK();
	    }
	}


}
uint8_t Generate_port(GPIO_RegDef_t *GPIOx){
	uint8_t value;
    if(GPIOx ==GPIOA){
        value = 0;
    }
    else if(GPIOx == GPIOB){
    	value = 1;
    }
    else if(GPIOx == GPIOC){
    	value = 2;
    }
    else if(GPIOx == GPIOD){
    	value = 3;
    }
    else if(GPIOx == GPIOE){
    	value = 4;
    }
    else if(GPIOx == GPIOF){
    	value = 5;
    }
    else if(GPIOx == GPIOG){
    	value = 6;
    }
    return value;
}
void GPIO_Init(GPIO_Handle_t *GPIO_Handle){
	uint32_t position=0;
    uint32_t config= 0;

    if(GPIO_Handle->GPIOConfig.GPIO_Mode == GPIO_MODE_INPUT){
        if(GPIO_Handle->GPIOConfig.GPIO_type== GPIO_NOPULL){
            config |= GPIO_Handle->GPIOConfig.GPIO_Mode + GPIO_CR_CNF_FLOAT_INPUT;
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_type ==GPIO_PULLUP){
            config |= GPIO_Handle->GPIOConfig.GPIO_Mode + GPIO_CR_CNF_INPUT_PUPD;
        }
    }
    else if((GPIO_Handle->GPIOConfig.GPIO_Mode > GPIO_MODE_INPUT) && (GPIO_Handle->GPIOConfig.GPIO_Mode < GPIO_MODER_IT_FL)){
        if(GPIO_Handle->GPIOConfig.GPIO_Mode== GPIO_MODE_OUTPUT_PP){
            config |= GPIO_Handle->GPIOConfig.GPIO_Speed + GPIO_CR_MODE_OUTPUT_PU;
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_Mode== GPIO_MODE_OUTPUT_OD){
            config |= GPIO_Handle->GPIOConfig.GPIO_Speed + GPIO_CR_MODE_OUTPUT_OD;
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_Mode== GPIO_MODE_ALT_PP){
            config |= GPIO_Handle->GPIOConfig.GPIO_Speed + GPIO_CR_MODE_ALT_PU;
            AFIO->MAPR &=~ (0xffffffff); // dua cac chan alt về mac dinh
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_Mode == GPIO_MODE_ALT_OD){
            config |= GPIO_Handle->GPIOConfig.GPIO_Speed + GPIO_CR_MODE_ALT_OD;
            AFIO->MAPR &=~ (0xffffffff); // dua cac chan alt về mac dinh
        }
    }
    else if(GPIO_Handle->GPIOConfig.GPIO_Mode >= GPIO_MODER_IT_FL){

    	AFIO_PCLK();
        if(GPIO_Handle->GPIOConfig.GPIO_Mode == GPIO_MODER_IT_FL){
            EXTI->RTSR &=~(0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
            EXTI->FTSR |= (0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_Mode == GPIO_MODER_IT_RT){
            EXTI->RTSR |= (0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
            EXTI->FTSR &=~ (0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
        }
        else if(GPIO_Handle->GPIOConfig.GPIO_Mode == GPIO_MODER_IT_FL_RT){
            EXTI->RTSR |= (0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
            EXTI->FTSR |= (0x1<< GPIO_Handle->GPIOConfig.GPIO_Pin_Number);
        }

        uint8_t temp1 = GPIO_Handle->GPIOConfig.GPIO_Pin_Number/4;
        uint8_t temp2 = GPIO_Handle->GPIOConfig.GPIO_Pin_Number%4;
        uint8_t value = Generate_port(GPIO_Handle->GPIOx);
        AFIO->EXTICR[temp1] &=~ (0XF <<(temp2 *4));
        AFIO->EXTICR[temp1] |= (value <<(temp2 *4));
        EXTI->IMR |= (0x1 <<GPIO_Handle->GPIOConfig.GPIO_Pin_Number);

    }
    if(GPIO_Handle->GPIOConfig.GPIO_Pin_Number < 8){
        position = GPIO_Handle->GPIOConfig.GPIO_Pin_Number;
        GPIO_Handle->GPIOx->CRL &=~ (0XF << (4*position));
        GPIO_Handle->GPIOx->CRL |= (config << (4*position));
    }
    else{
        position = GPIO_Handle->GPIOConfig.GPIO_Pin_Number- 8;
        GPIO_Handle->GPIOx->CRH &=~ (0XF << (4*position));
        GPIO_Handle->GPIOx->CRH |= (config << (4*position));
    }
}


void GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t value){
    if(value ==GPIO_PIN_SET){
        GPIOx->ODR |= value << PinNumber;
    }
    else{
        GPIOx->ODR &=~ (value << PinNumber);
    }

}
void GPIO_WritePort(GPIO_RegDef_t *GPIOx, uint16_t value){
    GPIOx->ODR = value;
}
uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t)(GPIOx->IDR >> PinNumber);
    return value;
}
uint16_t GPIO_ReadPort(GPIO_RegDef_t *GPIOx){
    uint16_t value;
    value = GPIOx->IDR;
    return  value;
}
void GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber){
    GPIOx->ODR ^= (1<<PinNumber);
}
void GPIO_TogglePort(GPIO_RegDef_t *GPIOx){
    GPIOx->ODR ^= 0xffff;
}
void IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        if(IRQNumber < 31){
            *(NVIC_ISER0)|= (0x1<<IRQNumber);
        }
        else if(IRQNumber >31 && IRQNumber <64){
            *(NVIC_ISER1)|= (0x1<<(IRQNumber - 32));
        }
        else if(IRQNumber >=64 && IRQNumber <96){
            *(NVIC_ISER2)|= (0x1<<(IRQNumber - 64));
        }
    }
}
void IRQ_priority(uint8_t IRQNumber, uint8_t priority){
    uint8_t temp1 = IRQNumber /8;
    uint8_t temp2 = IRQNumber %8;
    *(NIVC_IPR0+temp1) = (0x1 <<((8*temp2)+4));
}
void IRQ_Handling(uint8_t pinNumber){
    if(EXTI->PR &(1<<pinNumber)){
        EXTI->PR|= (1<<pinNumber);
    }
    GPIO_InterruptCallBack(pinNumber);
}
__attribute__((weak)) void GPIO_InterruptCallBack(uint8_t PinNumber){

}
