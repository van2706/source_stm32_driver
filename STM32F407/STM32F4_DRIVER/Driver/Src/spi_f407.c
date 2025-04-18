/*
 * spi_f407.c
 *
 *  Created on: Mar 3, 2025
 *      Author: ADMIN
 */
#include "spi_f407.h"
#include "stddef.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *SPIHandle);
static void spi_rxe_interrupt_handle(SPI_Handle_t *SPIHandle);
static void spi_over_flag_interrupt_handle(SPI_Handle_t *SPIHandle);

void SPI_ClockControl(SPI_RegDef_t *SPIx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
		if(SPIx ==SPI1){
			SPI1_PCLK();
		}
		else if(SPIx ==SPI2){
			SPI2_PCLK();
		}
		else if(SPIx ==SPI3){
			SPI3_PCLK();
		}
	}
	else{

	}
}
void SPI_Init(SPI_Handle_t *SPIHandle){
	SPI_ClockControl(SPIHandle->SPIx, ENABLE);
	uint32_t  temp=0;
	// device
	temp |= SPIHandle->SPIconfig.SPI_DeviceMode << SPI_CR1_MSTR;

	if(SPIHandle->SPIconfig.SPI_Busconfig == SPI_BUSCONFIG_HD){
		temp |= (1 <<SPI_CR1_BIDIMODE);
	}
	else if(SPIHandle->SPIconfig.SPI_Busconfig ==SPI_BUSCONFIG_FD){
		temp &=~ (1 <<SPI_CR1_BIDIMODE);
	}
	else if(SPIHandle->SPIconfig.SPI_Busconfig ==SPI_BUSCONFIG_SIMPLEX_RXONLY){
		temp &=~ (1 <<SPI_CR1_BIDIMODE);
		temp |= (1 <<SPI_CR1_RXONLY);
	}
	temp |= (SPIHandle->SPIconfig.SPI_Sclkspeed <<(3*SPI_CR1_BR));
	temp |= (SPIHandle->SPIconfig.SPI_DFF <<SPI_CR1_DFF);

	temp |= (SPIHandle->SPIconfig.SPI_CPHA << SPI_CR1_CPHA);
	temp |= (SPIHandle->SPIconfig.SPI_CPOL <<SPI_CR1_CPOL);
	temp |= (SPIHandle->SPIconfig.SPI_SSM <<SPI_CR1_SSM);

	SPIHandle->SPIx->CR1 |=temp;
}
int8_t SPI_GetFlag(SPI_RegDef_t *SPIx, uint8_t number){
	if(SPIx->SR &number){
		return FLAG_SET;
	}
	return FLAG_RESET;
}
void SPI_SendData(SPI_RegDef_t *SPIx, uint8_t *TxBuffer, uint32_t len){
	while(len >0){
		while(SPI_GetFlag(SPIx, SPI_TX_FLAG)== FLAG_RESET);
		if(SPIx->CR1 &(1<<SPI_CR1_DFF)){
			// 16 bit
			SPIx->DR = *((uint16_t *)TxBuffer);
			len -=2;
			(uint16_t *)TxBuffer ++;
		}
		else{
			// 8 bit
			SPIx->DR = *TxBuffer;
			len --;
			TxBuffer++;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *SPIx, uint8_t *RxBuffer, uint32_t len){
	while(len>0){
		while (SPI_GetFlag(SPIx, SPI_RX_FLAG)==FLAG_RESET);
		if(SPIx->CR1 &(1<< SPI_CR1_DFF)){
			*(uint16_t *)RxBuffer = SPIx->DR;
			len -=2;
			RxBuffer +=2;
		}
		else{
			*RxBuffer =SPIx->DR;
			len --;
			RxBuffer ++;
		}
	}
}
void SPI_PeriphrealControl(SPI_RegDef_t *SPIx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
		SPIx->CR1 |= (1<< SPI_CR1_SPE);
	}
	else{
		SPIx->CR1 &=~ (1<< SPI_CR1_SPE);
	}
}
// truyen nhan ben trong MCU
void SPI_SSIConfig(SPI_RegDef_t *SPIx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
		SPIx->CR1 |= (1<< SPI_CR1_SSI);
	}
	else{
		SPIx->CR1 &=~ (1<< SPI_CR1_SSI);
	}
}
void SPI_SSOEConfig(SPI_RegDef_t *SPIx, uint8_t EnorDi){
	if(EnorDi ==ENABLE){
		SPIx->CR2 |= (1<< SPI_CR2_SSOE);
	}
	else{
		SPIx->CR2 &=~ (1<< SPI_CR2_SSOE);
	}
}


void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi==ENABLE){
			if(IRQNumber <=31){
				*NVIC_ISER0 |= (1<<IRQNumber);
			}
			else if(IRQNumber >31&& IRQNumber <=64){
					*NVIC_ISER1 |= 1<<(IRQNumber%32);
				}
			else if(IRQNumber >64 && IRQNumber <96){
					*NVIC_ISER2 |= 1<<(IRQNumber%64);
				}
		}
		else{

		}

}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t temp1 = IRQNumber /4;
		uint8_t temp2 =IRQNumber%4;

		*(NVIC_IPR0 + temp1) |= IRQPriority << (8*temp2 + 4);
}
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *TxBuffer, uint32_t len){
	uint8_t state= pSPIHandle->Txstate;
	if(state != SPI_BUSY_IN_TX){
		 // 1 save the Tx buffer address and len information in some global variables
		pSPIHandle->pTxBuffer = TxBuffer;
		pSPIHandle->TxLen = len;
		 // 2. Mark the SPI states as busy in transmission so that
		pSPIHandle->Txstate = SPI_BUSY_IN_TX;
		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->SPIx->CR2 |= (1<<SPI_CR2_TXEIE);
		// When transmit will be handled at ISR code
	}
	return state;
}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *RxBuffer, uint32_t len){
	uint8_t state= pSPIHandle->Rxstate;
	if(state != SPI_BUSY_IN_RX){
		 // 1 save the Tx buffer address and len information in some global variables
		pSPIHandle->pRxBuffer = RxBuffer;
		pSPIHandle->RxLen = len;
		 // 2. Mark the SPI states as busy in transmission so that
		pSPIHandle->Rxstate = SPI_BUSY_IN_RX;
		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->SPIx->CR2 |= (1<<SPI_CR2_RXNEIE);
		// When transmit will be handled at ISR code
	}
	return state;
}
void SPI_IRQHandling(SPI_Handle_t *SPIHandle){
	uint8_t temp1, temp2;
	temp1 = SPIHandle->SPIx->SR &(1<<SPI_SR_TXE);
	temp2 =SPIHandle->SPIx->CR2 &(1<<SPI_CR2_TXEIE);
	if(temp1 && temp2){
		// handle TXE
		spi_txe_interrupt_handle(SPIHandle);
	}
	temp1 = SPIHandle->SPIx->SR &(1<<SPI_SR_RXNE);
	temp2 =SPIHandle->SPIx->CR2 &(1<< SPI_CR2_RXNEIE);
	if(temp1 &&temp2){
		// handled RXE
		spi_rxe_interrupt_handle(SPIHandle);
	}
	// over flag
	temp1 = SPIHandle->SPIx->SR &(1<<SPI_SR_OVR);
	temp2 =SPIHandle->SPIx->CR2 &(1<< SPI_CR2_ERRIE);
	if(temp1 &&temp2){
		// over error
		spi_over_flag_interrupt_handle(SPIHandle);
	}
}
static void spi_txe_interrupt_handle(SPI_Handle_t *SPIHandle){
	if(SPIHandle->SPIx->CR1 &(1<<SPI_CR1_DFF)){
			// 16 bit
			SPIHandle->SPIx->DR = *((uint16_t *)SPIHandle->pTxBuffer);
			SPIHandle->TxLen -=2;
			(uint16_t *)SPIHandle->pTxBuffer ++;
		}
	else{
			// 8 bit
			SPIHandle->SPIx->DR = *SPIHandle->pTxBuffer;
			SPIHandle->TxLen --;
			SPIHandle->pTxBuffer ++;
		}
	if(!SPIHandle->TxLen){
		// txLen is zẻo, so close the spi tranmission and inform the application that
		// Tx is over
		SPI_CloseTransmisson(SPIHandle);
		SPI_ApplicationEventCallback(SPIHandle, SPI_EVENT_TX_CMPLT);
	}
}
void SPI_CloseTransmisson(SPI_Handle_t *SPIHandle){
	SPIHandle->SPIx->CR2 &=~ (1<<SPI_CR2_TXEIE);
	SPIHandle->pTxBuffer = 0;
	SPIHandle->TxLen =0;
	SPIHandle->Txstate = SPI_READY;
}

static void spi_rxe_interrupt_handle(SPI_Handle_t *SPIHandle){
		if(SPIHandle->SPIx->CR1 &(1<< SPI_CR1_DFF)){
			*(uint16_t *)SPIHandle->pRxBuffer = SPIHandle->SPIx->DR;
			SPIHandle->RxLen -=2;
			SPIHandle->pRxBuffer +=2;
		}
		else{
			*SPIHandle->pRxBuffer =SPIHandle->SPIx->DR;
			SPIHandle->RxLen --;
			SPIHandle->pRxBuffer ++;
		}
		if(!SPIHandle->RxLen){
			// txLen is zẻo, so close the spi tranmission and inform the application that
			// Tx is over
			SPI_CloseReception(SPIHandle);
			SPI_ApplicationEventCallback(SPIHandle, SPI_EVENT_RX_CMPLT);
		}
}
void SPI_CloseReception(SPI_Handle_t *SPIHandle){
	SPIHandle->SPIx->CR2 &=~ (1<<SPI_CR2_RXNEIE);
	SPIHandle->pRxBuffer = 0;
	SPIHandle->RxLen =0;
	SPIHandle->Rxstate = SPI_READY;
}
static void spi_over_flag_interrupt_handle(SPI_Handle_t *SPIHandle){
	uint8_t temp;
	// clear the ovr flag
	if(SPIHandle ->Txstate != SPI_BUSY_IN_TX){
		temp = SPIHandle->SPIx->DR;
		temp = SPIHandle->SPIx->SR;
	}
	(void)temp;
	//2 inform the application
	SPI_ApplicationEventCallback(SPIHandle, SPI_EVENT_OVR_ERR);
}
void SPI_ClearOVERFlag(SPI_RegDef_t *pSPIx){
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}
 __attribute__((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *SPIHandle, uint8_t appEv){

}
