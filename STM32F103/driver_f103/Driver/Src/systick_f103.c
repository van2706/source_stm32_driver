/*
 * systick_f103.c
 *
 *  Created on: Mar 27, 2025
 *      Author: ADMIN
 */
#include <systick_f103.h>
void Init_systick_time(){
	// reload value
	uint32_t count_value = (SYSTICK_TIM_CLK / TICK_HZ ) - 1;

	// xoa syst rvr
	*SYST_RVR &=~ (0x00FFFFFF);
	/// Ghi reload value
	*SYST_RVR |= count_value;
	// set gia tri dem dau tien
	*SYST_CVR |= 0;
	// enable systic exception requesst
	*SYST_CSR |= (0x1<<1);
	// enable clock source
	*SYST_CSR |=(0x1 << 2);
	// enable count
	*SYST_CSR |= (0x1 <<0);
}
uint32_t tick =0;
void SysTick_Handler(){
	tick ++;
}
uint32_t millis(void){
	return tick;
}
void delay_ms(uint32_t ms){
	uint32_t start = millis();
	while((millis()-start)< ms);
}
