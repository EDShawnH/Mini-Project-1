#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

typedef struct
{
	uint8_t Button_curr;
	uint8_t Button_last;
	uint8_t Button_filter;
	
	uint32_t time_debounce;
	uint32_t time_startPress;
	
	uint8_t is_debouncing;
	uint8_t is_holding;
	
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
	
} Button_Typedef;

void Button_init(Button_Typedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void Button_handle(Button_Typedef* ButtonX);

#endif 
