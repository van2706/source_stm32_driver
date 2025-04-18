/*
 * stm32f407.h
 *
 *  Created on: Mar 2, 2025
 *      Author: ADMIN
 */

#ifndef INC_STM32F407_H_
#define INC_STM32F407_H_
#include <stdint.h>

#define __vo volatile

// Bước 1 cấu hình base address
#define FLASH_BASEADDER 0x08000000U
#define SRAM1_BASEADDER 0x20000000U
#define SRAM2_BASEADDER 0x2001C000U
#define ROM_BASEADDER 	0x1FFF0000U
#define SRAM 			SRAM1_BASEADDER
// Bước 2 cấu hình peripheral

#define PERIPHERAL_BASEADDER 0x40000000U
#define APB1PERIPH_BASEADDER PERIPHERAL_BASEADDER
#define APB2PERIPH_BASEADDER 0x40007C00U
#define AHB1PERIPH_BASEADDER 0x40020000U
#define AHB1PERIPH_BASEADDER 0x40020000U
#define AHB2PERIPH_BASEADDER 0x50000000U


#define NVIC_ISER0 (uint32_t *)0xE000E100
#define NVIC_ISER1 (uint32_t *)0xE000E104
#define NVIC_ISER2 (uint32_t *)0xE000E108
#define NVIC_ISER3 (uint32_t *)0xE000E10C

#define NVIC_IPR0 (uint32_t *)0xE000E400


// Bước 3 cấu hình GPIO
// AHB1
#define GPIOA_BASEADDER (AHB1PERIPH_BASEADDER+ 0x0000U)
#define GPIOB_BASEADDER (AHB1PERIPH_BASEADDER+ 0x0400U)
#define GPIOC_BASEADDER (AHB1PERIPH_BASEADDER+ 0x0800U)
#define GPIOD_BASEADDER (AHB1PERIPH_BASEADDER+ 0x0C00U)
#define GPIOE_BASEADDER (AHB1PERIPH_BASEADDER+ 0x1000U)
#define GPIOF_BASEADDER (AHB1PERIPH_BASEADDER+ 0x1400U)
#define GPIOG_BASEADDER (AHB1PERIPH_BASEADDER+ 0x1800U)
#define GPIOH_BASEADDER (AHB1PERIPH_BASEADDER+ 0x1C00U)
#define GPIOI_BASEADDER (AHB1PERIPH_BASEADDER+ 0x2000U)
#define GPIOJ_BASEADDER (AHB1PERIPH_BASEADDER+ 0x2400U)
#define GPIOK_BASEADDER (AHB1PERIPH_BASEADDER+ 0x2800U)
#define RCC_BASEADDER   (AHB1PERIPH_BASEADDER+ 0x3800U)


// APB2
#define USART1_BASEADDER (APB2PERIPH_BASEADDER+0x1000U)
#define USART6_BASEADDER (APB2PERIPH_BASEADDER+0x1400U)

#define SPI1_BASEADDER 	 (APB2PERIPH_BASEADDER + 0x3000U)
#define SPI4_BASEADDER (APB2PERIPH_BASEADDER + 0x3400U)
#define SPI5_BASEADDER (APB2PERIPH_BASEADDER + 0x5000U)
#define SPI6_BASEADDER (APB2PERIPH_BASEADDER + 0x5400U)
#define EXTI_BASEADDER (APB2PERIPH_BASEADDER + 0x3C00U)

#define SYSCFG_BASEADDER (APB2PERIPH_BASEADDER + 0x3800U)
// APB1

#define SPI2_BASEADDER 	 (APB1PERIPH_BASEADDER + 0x3800U)
#define SPI3_BASEADDER 	 (APB1PERIPH_BASEADDER + 0x3C00U)

#define USART2_BASEADDER (APB1PERIPH_BASEADDER+0x4400U)
#define USART3_BASEADDER (APB1PERIPH_BASEADDER+0x4800U)
#define UART4_BASEADDER (APB1PERIPH_BASEADDER+0x4C00U)
#define UART5_BASEADDER (APB1PERIPH_BASEADDER+0x5000U)
#define USART7_BASEADDER (APB1PERIPH_BASEADDER+0x7800U)
#define USART8_BASEADDER (APB1PERIPH_BASEADDER+0x7C00U)

#define I2C1_BASEADDER (APB1PERIPH_BASEADDER+0x5400U)
#define I2C2_BASEADDER (APB1PERIPH_BASEADDER+0x5800U)
#define I2C3_BASEADDER (APB1PERIPH_BASEADDER+0x5C00U)

typedef struct{
	__vo uint32_t MODEL;			// address offset 0x00
	__vo uint32_t OTYPER;			// address offset 0x08
	__vo uint32_t OSPEEDR;			// address offset 0xC0
	__vo uint32_t PUPDR;			// address offset 0x0C
	__vo uint32_t IDR;			//address offset 0x10
	__vo uint32_t ODR;			// address offset 0x14
	__vo uint32_t BSRR;			// address offset 0x1C
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDER)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADDER)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDER)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDER)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADDER)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADDER)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADDER)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASEADDER)
#define GPIOI ((GPIO_RegDef_t *)GPIOI_BASEADDER)

typedef struct{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	//__vo uint32_t CFGR2;
}RCC_RegDef_t;
#define RCC ((RCC_RegDef_t*)RCC_BASEADDER)

typedef struct {
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;
#define EXTI ((EXTI_RegDef_t *)EXTI_BASEADDER)

typedef struct{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	__vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
	__vo uint32_t CFGB;
}SYSCFG_RegDef_t;
#define SYSCFG ((SYSCFG_RegDef_t *)SYSCFG_BASEADDER)

typedef struct {
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t BRR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;
}USART_RegDef_t;
#define USART1 ((USART_RegDef_t *)USART1_BASEADDER)
#define USART2 ((USART_RegDef_t *)USART2_BASEADDER)
#define USART3 ((USART_RegDef_t *)USART3_BASEADDER)
#define UART4 ((USART_RegDef_t *)UART4_BASEADDER)
#define UART5 ((USART_RegDef_t *)UART5_BASEADDER)
#define USART6 ((USART_RegDef_t *)USART6_BASEADDER)
#define USART7 ((USART_RegDef_t *)USART7_BASEADDER)
#define USART8 ((USART_RegDef_t *)USART8_BASEADDER)

// I2C
typedef struct {
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
}I2C_RegDef_t;
#define I2C1 ((I2C_RegDef_t *)I2C1_BASEADDER)
#define I2C2 ((I2C_RegDef_t *)I2C2_BASEADDER)
#define I2C3 ((I2C_RegDef_t *)I2C3_BASEADDER)

typedef struct {
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
}SPI_RegDef_t;
#define SPI1 ((SPI_RegDef_t *)SPI1_BASEADDER)
#define SPI2 ((SPI_RegDef_t *)SPI2_BASEADDER)
#define SPI3 ((SPI_RegDef_t *)SPI3_BASEADDER)
#define SPI4 ((SPI_RegDef_t *)SPI4_BASEADDER)
#define SPI5 ((SPI_RegDef_t *)SPI5_BASEADDER)
#define SPI6 ((SPI_RegDef_t *)SPI6_BASEADDER)

#define GPIOA_PCLK() (RCC->AHB1ENR |= 0x1 <<0)
#define GPIOB_PCLK() (RCC->AHB1ENR |= 0x1 <<1)
#define GPIOC_PCLK() (RCC->AHB1ENR |= 0x1 <<2)
#define GPIOD_PCLK() (RCC->AHB1ENR |= 0x1 <<3)
#define GPIOE_PCLK() (RCC->AHB1ENR |= 0x1 <<4)
#define GPIOF_PCLK() (RCC->AHB1ENR |= 0x1 <<5)
#define GPIOG_PCLK() (RCC->AHB1ENR |= 0x1 <<6)
#define GPIOH_PCLK() (RCC->AHB1ENR |= 0x1 <<7)
#define GPIOI_PCLK() (RCC->AHB1ENR |= 0x1 <<8)

#define I2C1_PCLK() (RCC ->APB1ENR |= 0x1 << 21)
#define I2C2_PCLK() (RCC ->APB1ENR |= 0x1 << 22)
#define I2C3_PCLK() (RCC ->APB1ENR |= 0x1 << 23)

#define SPI2_PCLK() (RCC ->APB1ENR |= 0x1 << 14)
#define SPI3_PCLK() (RCC ->APB1ENR |= 0x1 << 15)

#define USART2_PCLK() (RCC ->APB1ENR |= 0x1 << 17)
#define USART3_PCLK() (RCC ->APB1ENR |= 0x1 << 18)
#define UART4_PCLK() (RCC ->APB1ENR |= 0x1 << 19)
#define UART5_PCLK() (RCC ->APB1ENR |= 0x1 << 20)

#define USART1_PCLK() (RCC ->APB2ENR |= 0x1 << 4)
#define USART6_PCLK() (RCC ->APB2ENR |= 0x1 << 5)
#define SPI1_PCLK() (RCC ->APB2ENR |= 0x1 << 12)

// Disable xung clock cho GPIO
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &=~ (1<<0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &=~ (1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &=~ (1<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &=~ (1<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &=~ (1<<4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &=~ (1<<5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &=~ (1<<6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &=~ (1<<7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &=~ (1<<8))

#define I2C1_PCLK_DI() (RCC->APB1ENR &=~ (1<<21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &=~ (1<<22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &=~ (1<<23))

#define SPI1_PCLK_DI() (RCC->APB2ENR &=~ (1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~ (1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~ (1<<15))

#define USART1_PCLK_DI() (RCC->APB2ENR &=~ (1<<4))
#define USART2_PCLK_DI() (RCC->APB1ENR &=~ (1<<17))
#define USART3_PCLK_DI() (RCC->APB1ENR &=~ (1<<18))
#define UART4_PCLK_DI() (RCC->APB1ENR &=~ (1<<19))
#define UART5_PCLK_DI() (RCC->APB1ENR &=~ (1<<20))
#define USART6_PCLK_DI() (RCC->APB2ENR &=~ (1<<5))

#define DISABLE 0
#define ENABLE 1
#define GPIO_PIN_SET ENABLE
#define GPIO_PIN_RESET DISABLE
#define FLAG_SET ENABLE
#define FLAG_RESET DISABLE
#define SET 1
#define RESET 0


#endif /* INC_STM32F407_H_ */
