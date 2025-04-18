#include "rcc_f407.h"

uint32_t GetValuePlck1(void){
    uint16_t AHBPrescaler[9]={1,2,4,8,16,64,128,256,512};
    uint16_t AHB1Prescaler[4]={2,4,8,16};
    uint16_t AHBscaler,ABP1scaler;
    uint32_t clock, pclk;
    uint8_t slectionclock = ((RCC->CFGR >>2) & 0x3);

    if(slectionclock ==0){
        clock = 16000000;
    }
    else if(slectionclock==1){
        clock =8000000;
    }
    uint8_t AHBPrestatus = ((RCC->CFGR >>4)&0xf);
    if(AHBPrestatus  <8){
        AHBscaler = 1;
    }
    else if(AHBPrestatus  <8){
        AHBscaler = AHBPrescaler[AHBPrestatus-8];
    }
    uint8_t ABP1Prestatus = ((RCC->CFGR >> 10)&0x7);
    if(ABP1Prestatus < 4){
        ABP1scaler = 1;
    }
    else if(ABP1Prestatus > 4){
        ABP1scaler = AHB1Prescaler[ABP1Prestatus -4];
    }
    pclk = clock /AHBscaler/ABP1scaler;
    return pclk;
}

uint32_t GetValuePlck2(void){
    uint16_t AHBPrescaler[9]={1,2,4,8,16,64,128,256,512};
    uint16_t AHB2Prescaler[4]={2,4,8,16};
    uint32_t clock,pclk;
    uint16_t AHBscaler,ABP2scaler;
    uint8_t selectionclock = ((RCC->CFGR >>2)&0x3);

    if(selectionclock ==0){
        clock =16000000;
    }
    else if(selectionclock ==1){
        clock =8000000;
    }
    uint8_t AHBPrestatus = ((RCC->CFGR >>4)&0xf);
    if(AHBPrestatus  <8){
        AHBscaler = 1;
    }
    else if(AHBPrestatus  <8){
        AHBscaler = AHBPrescaler[AHBPrestatus-8];
    }
    uint8_t ABP2Prestatus = ((RCC->CFGR >> 13)&0x7);
    if(ABP2Prestatus < 4){
        ABP2scaler = 1;
    }
    else if(ABP2Prestatus > 4){
        ABP2scaler = AHB2Prescaler[ABP2Prestatus -4];
    }
    pclk = clock /AHBscaler/ABP2scaler;
    return pclk;
}
