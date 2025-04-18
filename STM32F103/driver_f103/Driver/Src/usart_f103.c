/*
 * usart_f103.c
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */
#include "stm32f103xxx.h"
#include "usart_f103.h"

void USART_PreriClockControl(USART_RegDef_t *USARTx, uint8_t EnorDi){
	if(EnorDi==ENABLE){
		if(USARTx == USART1){
			USART1_PCLK();
		}else if(USARTx ==USART2){
			USART2_PCLK();
		}else if(USARTx == USART3){
			USART3_PCLK();
		}
	}
	else{

	}
}
void USART_Init(USART_Handle_t *USART_Handle){
	uint32_t config = 0;
	USART_PreriClockControl(USART_Handle->USARTx, ENABLE);
	// register CR1
	config |= (0x1 << USART_CR1_UE);
	config |= (USART_Handle->USART_Config.USART_Wordlenght << USART_CR1_M);
	if(USART_Handle->USART_Config.USART_Mode == USART_MODE_TX){
		config &=~ (0x1<< USART_CR1_RE);
		config |= (0x1<< USART_CR1_TE);
	}
	else if(USART_Handle->USART_Config.USART_Mode == USART_MODE_RX){
		config &=~ (0x1<< USART_CR1_TE);
		config |= (0x1<< USART_CR1_RE);
	}
	else {
		config |= (0x1<< USART_CR1_RE);
		config |= (0x1<< USART_CR1_TE);
	}
	if(USART_Handle->USART_Config.USART_Parity == USART_PARTY_EN_EVEN){
		config |= (0x1 << USART_CR1_PCE);
	}
	else if(USART_Handle->USART_Config.USART_Parity == USART_PARTY_EN_ODD){
		config |= (0x1 << USART_CR1_PS);
	}
	USART_Handle->USARTx->CR1= config;
	// register CR2;
	config =0;
	config |= (USART_Handle->USART_Config.USART_Stop << USART_CR2_STOP);
	USART_Handle->USARTx->CR2 = config;
	// register CR3
	config =0;
	if(USART_Handle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_NONE){
		config &=~ (0x1 << USART_CR3_CTSE);
		config &=~ (0x1 << USART_CR3_RTSE);
	}
	else if(USART_Handle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_CTS){
		config |= (0x1 << USART_CR3_CTSE);
		config &=~ (0x1 << USART_CR3_RTSE);
	}
	else if(USART_Handle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_RTS){
		config &=~ (0x1 << USART_CR3_CTSE);
		config |= (0x1 << USART_CR3_RTSE);
	}
	else if(USART_Handle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS){
		config |= (0x1 << USART_CR3_CTSE);
		config |= (0x1 << USART_CR3_RTSE);
	}
	USART_Handle->USARTx->CR3 = config;
}
uint8_t USART_GetFlag(USART_RegDef_t *USARTx, uint16_t FlagStatus){
	uint8_t flag = FLAG_RESET;
	if(USARTx->SR & FlagStatus){
		flag = FLAG_SET;
	}
	return flag;
}
void USART_SendData(USART_Handle_t *pHandle_uart, uint8_t *pTxBuffer, uint32_t len){
	uint16_t *data;
	for (uint32_t i=0;i< len ;i++){
		while (USART_GetFlag(pHandle_uart->USARTx, USART_FLAG_TX) != FLAG_SET);
		if(pHandle_uart->USART_Config.USART_Wordlenght == USART_9BIT_DATA){
			data = (uint16_t *)pTxBuffer;
			pHandle_uart->USARTx->DR = ((*data)&(uint16_t)0x1FF);
			if(pHandle_uart->USART_Config.USART_Parity == USART_PARTY_DISABLE){
				pTxBuffer+=2;
			}
			else{
				pTxBuffer++;
			}
		}
		else {

			pHandle_uart->USARTx->DR = *pTxBuffer;
			pTxBuffer++;
		}
	}

}
void USART_ReceiveData(USART_Handle_t *pHandle_uart, uint8_t *pRxBuffer, uint32_t len){
	for(uint32_t i=0;i<len ;i++){
		while(USART_GetFlag(pHandle_uart->USARTx, USART_FLAG_RX)!= FLAG_SET);
		if(pHandle_uart->USART_Config.USART_Wordlenght == USART_9BIT_DATA){
			*(uint16_t *)pRxBuffer = (pHandle_uart->USARTx->DR)&(0x1ff);
		if(pHandle_uart->USART_Config.USART_Parity == USART_PARTY_DISABLE){
			pRxBuffer+=2;
		}
		else{
			pRxBuffer++;
		}
		}
		else {
			*pRxBuffer = pHandle_uart->USARTx->DR &(0xff);
		}
	}
}

void USART_CleanFlag(USART_RegDef_t *USARTx, uint8_t FlagName){
	USARTx->SR &=~(FlagName);
}

uint8_t USART_SendData_IT(USART_Handle_t *USARTHandle, uint8_t *pTxBuffer, uint32_t len){
	uint8_t status = USARTHandle->TxBussystatus;
	if(status != USART_BUSSY_IN_TX){
		USARTHandle->pTxBuffer = pTxBuffer;
		USARTHandle->lenTx = len;
		USARTHandle->TxBussystatus = USART_BUSSY_IN_TX;
		USARTHandle->USARTx->CR1|= (0x1<<USART_CR1_TXEIE);
		USARTHandle->USARTx->CR1 |= (0x1 << USART_CR1_TCIE);
	}
	return status;
}
uint8_t USART_ReceiveData_IT(USART_Handle_t *USARTHandle, uint8_t *pRxBuffer, uint32_t len){
	uint8_t status = USARTHandle->RxBussystatus;
	if(status != USART_BUSSY_IN_RX){
		USARTHandle->pRxBuffer = pRxBuffer;
		USARTHandle->lenRx = len;
		USARTHandle->RxBussystatus = USART_BUSSY_IN_RX;
		USARTHandle->USARTx->CR1 |= (0x1 <<USART_CR1_RXNEIE);

	}
	return status;
}

void USART_IRQHandling(USART_Handle_t *USARTHandle){
	uint32_t temp1, temp2;
	uint16_t *pdata;
	// TC flag
	temp1 = (USARTHandle->USARTx->SR)& (0x1 << USART_SR_TC);
	temp2 = (USARTHandle->USARTx->CR1) &(0x1 << USART_CR1_TCIE);
	if(temp1 && temp2){
		// interrupt is because TC
		// if TXLen is zero close transmit and call application
		if(USARTHandle->TxBussystatus == USART_BUSSY_IN_TX){
			if(!USARTHandle->lenTx){
				// clean flag TC
				USARTHandle->USARTx->SR &=~ (0x1 << USART_SR_TC);
				USARTHandle->USARTx->CR1 &=~ (0x1 << USART_CR1_TCIE);
				USARTHandle->RxBussystatus = USART_READY;
				USARTHandle->pTxBuffer =NULL;
				USARTHandle->lenTx =0;
				// call application
				ApllicationEnventCallBack(USARTHandle, USART_EVENT_TX_CMPLT);
			}
		}
	}
	temp1=0; temp2 =0;
	temp1 = (USARTHandle->USARTx->SR)& (0x1 << USART_SR_TXE);
	temp2 = (USARTHandle->USARTx->CR1) &(0x1 << USART_CR1_TXEIE);
	if(temp1 && temp2){
		if(USARTHandle->TxBussystatus == USART_BUSSY_IN_TX){
			if(USARTHandle->lenTx >0){
				if(USARTHandle->USART_Config.USART_Wordlenght == USART_9BIT_DATA){
					// transmit 9 bit
					pdata = (uint16_t *)(USARTHandle->pTxBuffer);
					USARTHandle->USARTx->DR = (*pdata & (uint16_t )0x01FF);
					if(USARTHandle->USART_Config.USART_Parity == USART_PARTY_DISABLE){
						USARTHandle->pTxBuffer ++;
						USARTHandle->pTxBuffer ++;
						USARTHandle->lenTx -=2;
					}
					else{
						USARTHandle->pTxBuffer ++;
						USARTHandle->lenTx --;
					}
				}
				else {
					// transmit 8 bit
					USARTHandle->USARTx->DR = (*USARTHandle->pTxBuffer& (uint8_t)0xFF);
					USARTHandle->pTxBuffer ++;
					USARTHandle->lenTx --;
				}
			}
			else if(!USARTHandle->lenTx){
				(USARTHandle->USARTx->SR)&=~ (0x1 << USART_SR_TXE);
				(USARTHandle->USARTx->CR1) &=~ (0x1 << USART_CR1_TXEIE);
				USARTHandle->TxBussystatus = USART_READY;
				USARTHandle->pTxBuffer =NULL;
				USARTHandle->lenTx =0;
				// call application
				ApllicationEnventCallBack(USARTHandle, USART_EVENT_TX_CMPLT);
			}
		}
	}
	temp1=0, temp2=0;
	temp1 = (USARTHandle->USARTx->SR) &(0x1 << USART_SR_RXNE);
	temp2 = (USARTHandle->USARTx->CR1)& (0x1<< USART_CR1_RXNEIE);
	if(temp1 && temp2){
		if(USARTHandle->lenRx >0){
			if(USARTHandle->USART_Config.USART_Wordlenght== USART_9BIT_DATA){
				*((uint16_t *)USARTHandle->pRxBuffer) = ((USARTHandle->USARTx->DR)&(uint16_t)0x1FF);
				if(USARTHandle->USART_Config.USART_Parity == USART_PARTY_DISABLE){
					USARTHandle->pRxBuffer ++;
					USARTHandle->pRxBuffer ++;
					USARTHandle->lenRx -=2;
				}
				else{
					USARTHandle->pRxBuffer ++;
					USARTHandle->lenRx --;
				}
			}
			else{
				// transmnit 8 bit
				if(USARTHandle->USART_Config.USART_Parity == USART_PARTY_DISABLE){
					*USARTHandle->pRxBuffer = (uint8_t)((USARTHandle->USARTx->DR) & (uint8_t)0xFF);
				}
				else{
					*USARTHandle->pRxBuffer = (uint8_t)((USARTHandle->USARTx->DR) & (uint8_t)0x7F);
				}
				USARTHandle->pRxBuffer ++;
				USARTHandle->lenRx --;
			}
		}
		else if(!USARTHandle->lenRx){
			(USARTHandle->USARTx->SR) &=~(0x1 << USART_SR_RXNE);
			(USARTHandle->USARTx->CR1)&=~ (0x1<< USART_CR1_RXNEIE);
			(USARTHandle->USARTx->CR1) &=~ (0x1 << USART_CR1_TXEIE);
			USARTHandle->RxBussystatus = USART_READY;
			USARTHandle->pRxBuffer =NULL;
			USARTHandle->lenRx =0;
			// call application
			ApllicationEnventCallBack(USARTHandle, USART_EVENT_RX_CMPLT);
		}
	}
	// CTS flag
	temp1 = USARTHandle->USARTx->SR & (0x1 << USART_SR_CTS);
	temp2 = USARTHandle->USARTx->CR3 & (0X1 << USART_CR3_CTSE);
	if(temp1 && temp2){
		USARTHandle->USARTx->SR &=~ (0x1 << USART_SR_CTS);
		ApllicationEnventCallBack(USARTHandle, USART_EVENT_CTS);
	}
	// IDLE detection flag
	temp1 = USARTHandle->USARTx->SR & (0x1 << USART_SR_IDLE);
	temp2 = USARTHandle->USARTx->CR1 & (0X1 << USART_CR1_IDLEIE);
	if(temp1 && temp2){
		USARTHandle->USARTx->SR &=~ (0x1 << USART_SR_IDLE);
		ApllicationEnventCallBack(USARTHandle, USART_EVENT_IDLE);
	}
	// Over detection flag
	temp1 = USARTHandle->USARTx->SR &(0x1 <<USART_SR_ORE);
	temp2 = (USARTHandle->USARTx->CR1)& (0x1<< USART_CR1_RXNEIE);
	if(temp1 && temp2){
		ApllicationEnventCallBack(USARTHandle, USART_ERR_ORE);
	}
	// ERROR flag
	temp2 = USARTHandle->USARTx->CR3 &(0x1 << USART_CR3_EIE);
	if(temp2){
		temp1 = USARTHandle->USARTx->SR ;
		if(temp1 &(0x1 << USART_SR_FE)){
			ApllicationEnventCallBack(USARTHandle, USART_ERR_FE);
		}
		if(temp1 &(0x1 << USART_SR_NE)){
			ApllicationEnventCallBack(USARTHandle, USART_ERR_NE);
		}
		if(temp1 &(0x1 << USART_SR_ORE)){
			ApllicationEnventCallBack(USARTHandle, USART_ERR_ORE);
		}

	}


}
__attribute__((weak)) void ApllicationEnventCallBack(USART_Handle_t *pUSARTx, uint8_t Envent){

}
