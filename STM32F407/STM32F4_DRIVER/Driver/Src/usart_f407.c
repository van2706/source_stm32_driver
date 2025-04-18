#include "rcc_f407.h"
#include "uart_f407.h"
void USART_PreriControlClock(USART_RegDef_t *USARTx, uint8_t EnorDi){
    if(EnorDi ==ENABLE){
        if(USARTx ==USART1){
            USART1_PCLK();
        }
        else if(USARTx ==USART2){
            USART2_PCLK();
        }
        else if(USARTx ==USART3){
            USART3_PCLK();
        }
        else if(USARTx ==UART4){
            UART4_PCLK();
        }
        else if(USARTx ==UART5){
            UART5_PCLK();
        }
        else if(USARTx ==USART6){
            USART6_PCLK();
        }
    }
    else{
    }
}

void USART_Baurdrate(USART_RegDef_t *pUSART, uint16_t Baudrate){
    uint32_t pclk;
    uint32_t USARTdiv;
    uint16_t M_part;
    uint16_t F_part;
    uint32_t temp=0;
    if(pUSART ==USART1 ||pUSART ==USART6){
        pclk = GetValuePlck2();
    }
    else{
        pclk = GetValuePlck1();
    }
    if(pUSART->CR1 &(1<<USART_CR1_OVER8)){
        // over8 =1
        USARTdiv = (25* pclk)/(2* Baudrate);
    }
    else{
        // over16 =0
        USARTdiv = (25* pclk)/(4* Baudrate);
    }
    M_part = USARTdiv/100;
    temp |= M_part << 4;
    F_part = USARTdiv - M_part*100;
    if(pUSART->CR1 & (1<< USART_CR1_OVER8)){
		// La oversample OVER8 =1
		F_part  = ((((F_part *8)+50)/100) & 0x07);
	}
	else {
		// la 16
		F_part  = ((((F_part *16)+50)/100) & 0x07);
	}
	temp |= F_part;
    pUSART->BRR |= temp;
}

void USART_Init(USART_Handle_t *pUSARTHandle){
    USART_PreriControlClock(pUSARTHandle->USARTx, ENABLE);
    uint32_t temp=0;
    if(pUSARTHandle->USART_Config.UART_Mode== USART_Mode_Rx){
        temp |= (1<< USART_CR1_RE);
        temp &=~ (1<< USART_CR1_TE);
    }
    else    if(pUSARTHandle->USART_Config.UART_Mode== USART_Mode_Tx){
        temp |= (1<< USART_CR1_TE);
        temp &=~ (1<< USART_CR1_RE);
    }
    else {
        temp |= (1<< USART_CR1_TE);
        temp |= (1<< USART_CR1_RE);
    }
    
    
    temp |= (pUSARTHandle->USART_Config.UART_WordLength << USART_CR1_M);
    if(pUSARTHandle->USART_Config.UART_ParityControl == USART_PARTY_EN_EVEN){
        temp |= (1<< USART_CR1_PCE);
    }
    else if(pUSARTHandle->USART_Config.UART_ParityControl == USART_PARTY_EN_ODD){
        temp |= (1<< USART_CR1_PS);
    }
    pUSARTHandle->USARTx->CR1 |= temp;
    temp =0;

    temp |= (pUSARTHandle->USART_Config.UART_NoStopBits << USART_CR2_STOP);
    pUSARTHandle->USARTx->CR2 |= temp;
    temp =0;
    if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_NONE){
        temp &=~ (1<< USART_CR3_CTSE);
        temp &=~ (1<< USART_CR3_RTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS){
        temp |= (1<< USART_CR3_CTSE);
        temp &=~ (1<< USART_CR3_RTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS){
        temp |= (1<< USART_CR3_RTSE);
        temp &=~ (1<< USART_CR3_CTSE);
    }
    else {
        temp |= (1<< USART_CR3_CTSE);
        temp |= (1<< USART_CR3_RTSE);
    }
    pUSARTHandle->USARTx->CR3 |= temp;
    temp =0;
}
void USART_DeInit(USART_RegDef_t *USARTx){

}

uint8_t USART_GetFlag(USART_RegDef_t *USARTx, uint8_t StatusFLAG){
    uint8_t flag = FLAG_RESET;
    while(USARTx->SR & StatusFLAG){
        flag = FLAG_SET;
    }
    return flag;
    
}
void USART_Sendata(USART_Handle_t *pHandle_uart, uint8_t *pTxbuffer, uint8_t len){
    uint16_t *pdata;
    for(uint32_t i =0;i<len ;i++){
        while (USART_GetFlag(pHandle_uart->USARTx, USART_FLAG_TX));
        if(pHandle_uart->USART_Config.UART_WordLength== USART_WORDLENGTH_9BIT){
            pdata = (uint16_t*)pTxbuffer;
            pHandle_uart->USARTx->DR |=(*pdata &(uint16_t)0x1FF);
            if(pHandle_uart->USART_Config.UART_ParityControl == USART_PARTY_DISABLE){
                pTxbuffer +=2;
            }
            else {
                pTxbuffer ++;
            }
        }
        else{
            pHandle_uart->USARTx->DR |= *pTxbuffer;
            pTxbuffer++;
        }

    }
}
void USART_Receivedata(USART_Handle_t *pHandle_uart, uint8_t *pRxbuffer, uint8_t len){
    for(uint32_t i =0; i<len ;i++){
        while(pHandle_uart->USARTx->DR , USART_FLAG_RX);
        if(pHandle_uart->USART_Config.UART_WordLength == USART_WORDLENGTH_9BIT){
            if(pHandle_uart->USART_Config.UART_ParityControl == USART_PARTY_DISABLE){
                *(uint16_t*)pRxbuffer = (pHandle_uart->USARTx->DR &(uint16_t)0x1ff);
                pRxbuffer ++;
                pRxbuffer++;
            }
            else{
                *pRxbuffer =(pHandle_uart->USARTx->DR & (uint16_t)0x1ff);
                pRxbuffer++;
            }
        }
        else{
            *pRxbuffer =(pHandle_uart->USARTx->DR & (uint16_t)0xff);
            pRxbuffer++;
        }
    }
}
