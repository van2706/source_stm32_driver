/*
 * master_slave.c
 *
 *  Created on: Mar 4, 2025
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
void SPI_GPIO(void);
void SPI_Inits(void);


int main(){
	char data[]="hello";
	SPI_GPIO();
	SPI_Inits();
	SPI_SSIConfig(SPI2, ENABLE);
	SPI_PeriphrealControl(SPI2, ENABLE);
	SPI_SendData(SPI2, (uint8_t*)data, strlen(data));
	while(1){

	}
	return 0;
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
	SPI_Handle_t SPI2handle;
	SPI2handle.SPIx = SPI2;
	SPI2handle.SPIconfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIconfig.SPI_Busconfig = SPI_BUSCONFIG_FD;
	SPI2handle.SPIconfig.SPI_Sclkspeed = SPI_SCLK_SPEED_DIV8; // generates sclk of 2MHz
	SPI2handle.SPIconfig.SPI_DFF = SPI_DFF_8BIT;
	SPI2handle.SPIconfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIconfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIconfig.SPI_SSM = SPI_SSM_DI;
	SPI_Init(&SPI2handle);
}

