#include "rcc.h"

void SystemClock_Config(void) {
		RCC->CR |= RCC_CR_HSEON; // HSE ON
		while(!(RCC->CR & RCC_CR_HSERDY)); // 안정화 대기
		
		FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
		RCC->CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);
		
		RCC->CR |= RCC_CR_PLLON; // PLL ON
		while(!(RCC->CR & RCC_CR_PLLRDY)); // 안정화 대기
		
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}