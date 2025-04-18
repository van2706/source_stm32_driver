/*
 * main_master_slave_IT.c
 *
 *  Created on: Mar 5, 2025
 *      Author: ADMIN
 */


#include "spi_f407.h"
#include "gpio_f407.h"
#include "string.h"
/*
 PB14 -> MISO
 PB15 -> MOSI
 PB13 ->CLK
 PB12 -> SPI2 SS
 alt funciton 5
 */
SPI_Handle_t SPI2handle;
void SPI_GPIO(void);
void SPI_Inits(void);
#define MAX_LEN 500
char RvBuffer[500];
uint8_t ReadByte;

int main(){
	char data[]="hello";
	SPI_GPIO();
	SPI_Inits();
	SPI_SSOEConfig(SPI2, ENABLE);

	SPI_IRQInterruptConfig(IRQ_NO_SPI2, ENABLE);
	while(1){
		SPI_PeriphrealControl(SPI2, ENABLE);

		// fetch the data from the SPI peripheral byte by byte in interrupt
		while(SPI_ReceiveDataIT(&SPI2handle, &ReadByte, 1)==SPI_BUSY_IN_RX);

		// confirm SPI is not busy
		while(SPI_GetFlag(SPI2, SPI_BUSY_FLAG));
		SPI_PeriphrealControl(SPI2, DISABLE);
	}
	return 0;
}

void SPI2_IRQHandler(){
	SPI_IRQHandling(&SPI2handle);
}
void SPI_ApplicationEventCallback(SPI_Handle_t *SPIHandle, uint8_t appEv){
	uint32_t i=0;
	// In the Rx complete
	if(appEv== SPI_EVENT_RX_CMPLT){
		RvBuffer[i++]=ReadByte;
		if(ReadByte =='\0'|| i == MAX_LEN){
			RvBuffer[i-1]='\0';
			i=0;
		}
	}
}
void SPI_GPIO(void){
	GPIO_Handle_t SPIPins;
	SPIPins.GPIOx =GPIOB;
	SPIPins.Pinconfig.GPIO_Pinmode =GPIO_MODE_ALT;
	SPIPins.Pinconfig.GPIO_PinOPtyple =GPIO_TYPE_PP;
	SPIPins.Pinconfig.GPIO_PinPuPdControl = NO_GPIO_PU_PD;
	SPIPins.Pinconfig.GPIO_Pinspeed =GPIO_SPEED_HIGH;
	SPIPins.Pinconfig.GPIO_PinnAltfunction =5;
	// SCK
	SPIPins.Pinconfig.GPIO_Pinnumber = GPIO_PIN_13;
	GPIO_Init(&SPIPins);
	// MOSI
	SPIPins.Pinconfig.GPIO_Pinnumber = GPIO_PIN_15;
	GPIO_Init(&SPIPins);
	// MISO
	SPIPins.Pinconfig.GPIO_Pinnumber = GPIO_PIN_14;
	GPIO_Init(&SPIPins);
	// nss
	SPIPins.Pinconfig.GPIO_Pinnumber = GPIO_PIN_12;
	GPIO_Init(&SPIPins);
}
void SPI_Inits(void){
	SPI2handle.SPIx = SPI2;
	SPI2handle.SPIconfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIconfig.SPI_Busconfig = SPI_BUSCONFIG_FD;
	SPI2handle.SPIconfig.SPI_Sclkspeed = SPI_SCLK_SPEED_DIV32; // generates sclk of 2MHz
	SPI2handle.SPIconfig.SPI_DFF = SPI_DFF_8BIT;
	SPI2handle.SPIconfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIconfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIconfig.SPI_SSM = SPI_SSM_DI;
	SPI_Init(&SPI2handle);
}


