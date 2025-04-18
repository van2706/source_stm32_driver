/*
 * spi_f407.h
 *
 *  Created on: Mar 3, 2025
 *      Author: ADMIN
 */

#ifndef INC_SPI_F407_H_
#define INC_SPI_F407_H_
#include "stm32f407.h"
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_Busconfig;
	uint8_t SPI_Sclkspeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;
typedef struct{
	SPI_RegDef_t *SPIx;
	SPI_Config_t SPIconfig;

	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t Txstate;
	uint8_t Rxstate;
}SPI_Handle_t;


// possibile SPI Application events
#define SPI_EVENT_TX_CMPLT 1
#define SPI_EVENT_RX_CMPLT 2
#define SPI_EVENT_OVR_ERR 3
/*
 SPI application states
 */
#define SPI_READY 0
#define SPI_BUSY_IN_RX 1
#define SPI_BUSY_IN_TX 2

// spi_deviceMode
#define SPI_DEVICE_MODE_SLAVE 0
#define SPI_DEVICE_MODE_MASTER 1

// spi_busconfig
#define SPI_BUSCONFIG_FD			 1
#define SPI_BUSCONFIG_HD			 2
#define SPI_BUSCONFIG_SIMPLEX_RXONLY 3

// spi_sclkspeed
#define SPI_SCLK_SPEED_DIV2		 	 0
#define SPI_SCLK_SPEED_DIV4		 	 1
#define SPI_SCLK_SPEED_DIV8		 	 2
#define SPI_SCLK_SPEED_DIV16		 3
#define SPI_SCLK_SPEED_DIV32		 4
#define SPI_SCLK_SPEED_DIV64		 5
#define SPI_SCLK_SPEED_DIV128		 6
#define SPI_SCLK_SPEED_DIV256		 7

// data frame
#define SPI_DFF_16BIT 0
#define SPI_DFF_8BIT 1

#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

#define SPI_CPHA_LOW 0
#define SPI_CPHA_HIGH 1

#define SPI_SSM_DI 0
#define SPI_SSM_EN 1


// vi tri thanh ghi
#define SPI_CR1_CPHA 0
#define SPI_CR1_CPOL 1
#define SPI_CR1_MSTR 2
#define SPI_CR1_BR 3
#define SPI_CR1_SPE 6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI 8
#define SPI_CR1_SSM 9
#define SPI_CR1_RXONLY 10
#define SPI_CR1_DFF 11
#define SPI_CR1_CRCNEXT 12
#define SPI_CR1_CRCEN 13
#define SPI_CR1_BIDIOE 14
#define SPI_CR1_BIDIMODE 15

#define SPI_CR2_RXDMAEN 0
#define SPI_CR2_TXDMAEN 1
#define SPI_CR2_SSOE 2
#define SPI_CR2_FEF 4
#define SPI_CR2_ERRIE 5
#define SPI_CR2_RXNEIE 6
#define SPI_CR2_TXEIE 7

#define SPI_SR_RXNE 0
#define SPI_SR_TXE 1
#define SPI_SR_CHSIDE 2
#define SPI_SR_UDR 3
#define SPI_SR_CRCERR 4
#define SPI_SR_MODF 5
#define SPI_SR_OVR 6
#define SPI_SR_BSY 7
#define SPI_SR_FRE 8

#define SPI_TX_FLAG (1<<SPI_SR_TXE)
#define SPI_RX_FLAG (1<<SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1<<SPI_SR_BSY)

#define IRQ_NO_SPI1 35
#define IRQ_NO_SPI2 36
#define IRQ_NO_SPI3 51


void SPI_Init(SPI_Handle_t *SPIHandle);
void SPI_Deinit(SPI_RegDef_t *SPIx);
void SPI_ClockControl(SPI_RegDef_t *SPIx, uint8_t EnorDi);
void SPI_SendData(SPI_RegDef_t *SPIx, uint8_t *TxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t *SPIx, uint8_t *RxBuffer, uint32_t len);
int8_t SPI_GetFlag(SPI_RegDef_t *SPIx, uint8_t number);

void SPI_PeriphrealControl(SPI_RegDef_t *SPIx, uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *SPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *SPIx, uint8_t EnorDi);

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *SPIHandle);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *TxBuffer, uint32_t len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *RxBuffer, uint32_t len);

void SPI_CloseTransmisson(SPI_Handle_t *SPIHandle);
void SPI_CloseReception(SPI_Handle_t *SPIHandle);
void SPI_ApplicationEventCallback(SPI_Handle_t *SPIHandle, uint8_t appEv);
#endif /* INC_SPI_F407_H_ */
