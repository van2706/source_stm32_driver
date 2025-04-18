/*
 * stm32f103xxx.h
 *
 *  Created on: Mar 1, 2025
 *      Author: ADMIN
 */

#ifndef STM32F103XXX_H
#define STM32F103XXX_H
/*
#ifndef INC_STM32F103XXX_H_
#define INC_STM32F103XXX_H_
 */
#include <stdint.h>
#define _vo volatile

// Bước 1 cấu hình base address
#define FLASH_BASEADDER 0x08000000U
#define SRAM_BASEADDER 0x20000000U
// Bước 2 cấu hình
#define PERIPHERAL_BASEADDER 0x40000000U
#define APB1_BASEADDER PERIPHERAL_BASEADDER
#define APB2_BASEADDER 0x40010000U
#define AHB1_BASEADDER 0x40018000U
//#define AHB2_BASEADDER 0x50000000U

#define NVIC_ISER0 (uint32_t *)0xE000E100
#define NVIC_ISER1 (uint32_t *)0xE000E104
#define NVIC_ISER2 (uint32_t *)0xE000E108
#define NVIC_ISER3 (uint32_t *)0xE000E10C

#define NIVC_IPR0 (uint32_t *)0xE000E400

#define SPI2_BASEADDER  (APB1_BASEADDER+0x3800U)
#define SPI3_BASEADDER  (APB1_BASEADDER+0x3C00U)
#define USART2_BASEADDER (APB1_BASEADDER+0x4400U)
#define USART3_BASEADDER (APB1_BASEADDER+0x4800U)
#define UART4_BASEADDER (APB1_BASEADDER+0x4C00U)
#define UART5_BASEADDER (APB1_BASEADDER+0x5000U)
#define I2C1_BASEADDER  (APB1_BASEADDER+0x5400U)
#define I2C2_BASEADDER  (APB1_BASEADDER+0x5800U)

#define AFIO_BASEADDER  (APB2_BASEADDER+0x0000U)
#define EXTI_BASEADDER  (APB2_BASEADDER+0x0400U)
#define GPIOA_BASEADDER (APB2_BASEADDER+0x0800U)
#define GPIOB_BASEADDER (APB2_BASEADDER+0x0C00U)
#define GPIOC_BASEADDER (APB2_BASEADDER+0x1000U)
#define GPIOD_BASEADDER (APB2_BASEADDER+0x1400U)
#define GPIOE_BASEADDER (APB2_BASEADDER+0x1800U)
#define GPIOF_BASEADDER (APB2_BASEADDER+0x1C00U)
#define GPIOG_BASEADDER (APB2_BASEADDER+0x2000U)
#define SPI1_BASEADDER (APB2_BASEADDER+0x3000U)
#define USART1_BASEADDER (APB2_BASEADDER+0x3800U)

#define RCC_BASEADDER  	(AHB1_BASEADDER+0x1000U)

typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_RegDef_t;
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDER)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADDER)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDER)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDER)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADDER)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADDER)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADDER)

typedef struct {
	uint32_t EVCR;
	uint32_t MAPR;
	uint32_t EXTICR[4];
	uint32_t RESERVED0;
	uint32_t MAPR2;
}AFIO_RegDef_t;
#define AFIO ((AFIO_RegDef_t *)AFIO_BASEADDER)

typedef struct {
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t PR;

}EXTI_RegDef_t;
#define EXTI ((EXTI_RegDef_t *)EXTI_BASEADDER)

typedef struct {
	_vo uint32_t CR;
	_vo uint32_t CFGR;
	_vo uint32_t CIR;
	_vo uint32_t APB2RSTR;
	_vo uint32_t APB1RSTR;
	_vo uint32_t AHBENR;
	_vo uint32_t APB2ENR;
	_vo uint32_t APB1ENR;
	_vo uint32_t BDCR;
	_vo uint32_t CSR;
	_vo uint32_t AHBRSTR;
	_vo uint32_t CFGR2;
}RCC_RegDef_t;

#define RCC ((RCC_RegDef_t *)RCC_BASEADDER)
typedef struct{
		uint32_t SR;
		uint32_t DR;
		uint32_t BRR;
		uint32_t CR1;
		uint32_t CR2;
		uint32_t CR3;
		uint32_t GPTR;
}USART_RegDef_t;
#define USART1 ((USART_RegDef_t *)USART1_BASEADDER)
#define USART2 ((USART_RegDef_t *)USART2_BASEADDER)
#define USART3 ((USART_RegDef_t *)USART3_BASEADDER)
#define UART4  ((USART_RegDef_t *)UART4_BASEADDER)
#define UART5  ((USART_RegDef_t *)UART5_BASEADDER)

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t OAR1;
	uint32_t OAR2;
	uint32_t DR;
	uint32_t SR1;
	uint32_t SR2;
	uint32_t CCR;
	uint32_t TRISE;
}I2C_RegDef_t;
#define I2C1 ((I2C_RegDef_t *)I2C1_BASEADDER)
#define I2C2 ((I2C_RegDef_t *)I2C2_BASEADDER)
#define I2C3 ((I2C_RegDef_t *)I2C3_BASEADDER)

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SR;
	uint32_t DR;
	uint32_t CRCPR;
	uint32_t RXCRCR;
	uint32_t I2SCFGR;
	uint32_t I2SPR;
}SPI_RegDef_t;
#define SPI1 ((SPI_RegDef_t)SPI1_BASEADDER)
#define SPI2 ((SPI_RegDef_t)SPI2_BASEADDER)
#define SPI3 ((SPI_RegDef_t)SPI3_BASEADDER)

// enable clock
#define AFIO_PCLK()  (RCC ->APB2ENR |= (0x1 <<0))
#define GPIOA_PCLK() (RCC ->APB2ENR |= (0x1 <<2))
#define GPIOB_PCLK() (RCC ->APB2ENR |= (0x1 <<3))
#define GPIOC_PCLK() (RCC ->APB2ENR |= (0x1 <<4))
#define GPIOD_PCLK() (RCC ->APB2ENR |= (0x1 <<5))
#define GPIOE_PCLK() (RCC ->APB2ENR |= (0x1 <<6))

#define ADC1_PCLK() (RCC->APB2ENR |= (0x1 <<9))
#define ADC2_PCLK() (RCC->APB2ENR |= (0x1 <<10))
#define TIM1_PCLK() (RCC->APB2ENR |= (0X1 <<11))
#define SPI1_PCLK() (RCC->APB2ENR |= (0X1 <<12))
#define USART1_PCLK() (RCC->APB2ENR |= (0x1 <<14))

#define TIM2_PCLK() (RCC->APB1ENR |= (0x1 << 0))
#define TIM3_PCLK() (RCC->APB1ENR |= (0x1 << 1))
#define TIM3_PCLK() (RCC->APB1ENR |= (0x1 << 1))
#define TIM4_PCLK() (RCC->APB1ENR |= (0x1 << 2))
#define TIM5_PCLK() (RCC->APB1ENR |= (0x1 << 3))
#define TIM6_PCLK() (RCC->APB1ENR |= (0x1 << 4))
#define TIM7_PCLK() (RCC->APB1ENR |= (0x1 << 5))
#define SPI2_PCLK() (RCC->APB1ENR |= (0x1 << 14))
#define SPI3_PCLK() (RCC->APB1ENR |= (0x1 << 15))
#define USART2_PCLK() (RCC->APB1ENR |= (0x1 << 17))
#define USART3_PCLK() (RCC->APB1ENR |= (0x1 << 18))
#define UART4_PCLK() (RCC->APB1ENR |= (0x1 << 19))
#define UART5_PCLK() (RCC->APB1ENR |= (0x1 << 20))
#define I2C1_PCLK() (RCC-> APB1ENR |= (0x1 << 21))
#define I2C2_PCLK() (RCC-> APB1ENR |= (0x1 << 22))

#define CAN1_PCLK() (RCC->APB1ENR |= (0x1 << 25))
#define CAN2_PCLK() (RCC->APB1ENR |= (0x1 << 26))
#define DAC_PCLK() (RCC-> APB1ENR |= (0x1 <<29))

#define AFIO_PCLK_DI()  (RCC ->APB2ENR &=~ (0x1 <<0))
#define GPIOA_PCLK_DI() (RCC ->APB2ENR &=~ (0x1 <<2))
#define GPIOB_PCLK_DI() (RCC ->APB2ENR &=~ (0x1 <<3))
#define GPIOC_PCLK_DI() (RCC ->APB2ENR &=~ (0x1 <<4))
#define GPIOD_PCLK_DI() (RCC ->APB2ENR &=~ (0x1 <<5))
#define GPIOE_PCLK_DI() (RCC ->APB2ENR &=~ (0x1 <<6))

#define ADC1_PCLK_DI() (RCC->APB2ENR &=~ (0x1 <<9))
#define ADC2_PCLK_DI() (RCC->APB2ENR &=~ (0x1 <<10))
#define TIM1_PCLK_DI() (RCC->APB2ENR &=~ (0X1 <<11))
#define SPI1_PCLK_DI() (RCC->APB2ENR &=~ (0X1 <<12))
#define USART1_PCLK_DI() (RCC->APB2ENR &=~ (0x1 <<14))

#define TIM2_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 0))
#define TIM3_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 1))
#define TIM4_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 2))
#define TIM5_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 3))
#define TIM6_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 4))
#define TIM7_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 5))
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 15))
#define USART2_PCLK_DI() (RCC->APB1ENR &=~(0x1 << 17))
#define USART3_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 18))
#define UART4_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 19))
#define UART5_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 20))
#define I2C1_PCLK_DI() (RCC-> APB1ENR &=~ (0x1 << 21))
#define I2C2_PCLK_DI() (RCC-> APB1ENR &=~ (0x1 << 22))

#define CAN1_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 25))
#define CAN2_PCLK_DI() (RCC->APB1ENR &=~ (0x1 << 26))
#define DAC_PCLK_DI() (RCC-> APB1ENR &=~ (0x1 <<29))

#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET ENABLE
#define GPIO_PIN_RESET DISABLE
#define FLAG_SET ENABLE
#define FLAG_RESET DISABLE


#endif /* INC_STM32F103XXX_H_ */