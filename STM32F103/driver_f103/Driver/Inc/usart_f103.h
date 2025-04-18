/*
 * usart_f103.h
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */

#ifndef INC_USART_F103_H_
#define INC_USART_F103_H_

#include "stm32f103xxx.h"
#include "stddef.h"
typedef struct {
	uint8_t USART_Mode;
	uint8_t USART_Wordlenght;
	uint16_t Baudrate;
	uint8_t USART_Parity;
	uint8_t USART_Stop;
	uint8_t HWFlowControl;
}USART_Config_t;

typedef struct{
	USART_RegDef_t *USARTx;
	USART_Config_t USART_Config;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t lenTx;
	uint32_t lenRx;
	uint8_t TxBussystatus;
	uint8_t RxBussystatus;
}USART_Handle_t;

#define USART_MODE_TX 0
#define USART_MODE_RX 1
#define USART_MODE_TX_RX 2

#define USART_8BIT_DATA 0
#define USART_9BIT_DATA 1

#define USART_PARTY_DISABLE 0
#define USART_PARTY_EN_EVEN 1
#define USART_PARTY_EN_ODD 2

#define USART_STOP_1BIT 0
#define USART_STOP_0_5BIT 1
#define USART_STOP_2_BIT 2
#define USART_STOP_1_5BIT 3

#define USART_STD_BAUD_1200 1200
#define USART_STD_BAUD_2400 2400
#define USART_STD_BAUD_9600 9600
#define USART_STD_BAUD_19200 19200
#define USART_STD_BAUD_38400 38400
#define USART_STD_BAUD_57600 57600
#define USART_STD_BAUD_115200 115200
#define USART_STD_BAUD_230400 230400
#define USART_STD_BAUD_460800 460800
#define USART_STD_BAUD_921600 921600
#define USART_STD_BAUD_2M 2000000
#define USART_STD_BAUD_3M 3000000

#define USART_HW_FLOW_CTRL_NONE 0
#define USART_HW_FLOW_CTRL_CTS 	1
#define USART_HW_FLOW_CTRL_RTS 	2
#define USART_HW_FLOW_CTRL_CTS_RTS 	3

#define USART_SR_PE 0
#define USART_SR_FE 1
#define USART_SR_NE 2
#define USART_SR_ORE 3
#define USART_SR_IDLE 4
#define USART_SR_RXNE 5
#define USART_SR_TC 6
#define USART_SR_TXE 7
#define USART_SR_LBD 8
#define USART_SR_CTS 9

#define USART_BRR_DIVFRA 0
#define USART_BRR_DIV_MAN 4

#define USART_CR1_SBK 0
#define USART_CR1_RWU 1
#define USART_CR1_RE 2
#define USART_CR1_TE 3
#define USART_CR1_IDLEIE 4
#define USART_CR1_RXNEIE 5
#define USART_CR1_TCIE 6
#define USART_CR1_TXEIE 7
#define USART_CR1_PEIE 8
#define USART_CR1_PS 9
#define USART_CR1_PCE 10
#define USART_CR1_WAKE 11
#define USART_CR1_M 12
#define USART_CR1_UE 13
#define USART_CR1_OVER8 15

#define USART_CR2_ADD 0
#define USART_CR2_LBDL 5
#define USART_CR2_LBDIE 6
#define USART_CR2_LBCL 8
#define USART_CR2_CPHA 9
#define USART_CR2_CPOL 10
#define USART_CR2_CLKEN 11
#define USART_CR2_STOP 12
#define USART_CR2_LINEN 14

#define USART_CR3_EIE 0
#define USART_CR3_IREN 1
#define USART_CR3_IRLP 2
#define USART_CR3_HDSEL 3
#define USART_CR3_NACK 4
#define USART_CR3_SCEN 5
#define USART_CR3_DMAR 6
#define USART_CR3_DMAT 7
#define USART_CR3_RTSE 8
#define USART_CR3_CTSE 9
#define USART_CR3_CTSIE 10
#define USART_CR3_ONEBIT 11

#define USART_GTPR_PCS 0
#define USART_GTPR_GT 8

#define USART_FLAG_TX (1 << USART_SR_TC)
#define USART_FLAG_RX (1 <<USART_SR_RXNE)

#define USART_READY 0
#define USART_BUSSY_IN_TX 1
#define USART_BUSSY_IN_RX 2

#define USART_EVENT_TX_CMPLT 0
#define USART_EVENT_RX_CMPLT 1
#define USART_EVENT_IDLE 2
#define USART_EVENT_CTS 3
#define USART_ERR_PE 4
#define USART_ERR_FE 5
#define USART_ERR_NE 6
#define USART_ERR_ORE 7

void USART_PreriClockControl(USART_RegDef_t *USARTx, uint8_t EnorDi);
void USART_Init(USART_Handle_t *USART_Handle);
void USART_DeInit(USART_Handle_t *USART_Handle);
void USART_Baudrate(USART_Handle_t *USART_handle);
void USART_SendData(USART_Handle_t *pHandle_uart, uint8_t *pTxBuffer, uint32_t len);
void USART_ReceiveData(USART_Handle_t *pHandle_uart, uint8_t *pRxBuffer, uint32_t len);

void IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);

uint8_t USART_SendData_IT(USART_Handle_t *USARTHandle, uint8_t *pTxBuffer, uint32_t len);
uint8_t USART_ReceiveData_IT(USART_Handle_t *USARTHandle, uint8_t *pRxBuffer, uint32_t len);

uint8_t USART_GetFlag(USART_RegDef_t *USARTx, uint16_t FlagStatus);
void ApllicationEnventCallBack(USART_Handle_t *pUSARTx, uint8_t Envent);
#endif /* INC_USART_F103_H_ */
