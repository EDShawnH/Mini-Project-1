#include "Button.h"

__weak void Button_pressing_callback()
{

}

__weak void Button_release_callback()
{

}

__weak void Button_short_pressing_callback()
{

}

__weak void Button_hold_pressing_callback()
{

}

void Button_handle(Button_Typedef* ButtonX)
{
	//-----loc nhieu-----
	uint8_t state = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if (state != ButtonX->Button_filter)
	{
		ButtonX->Button_filter = state;
		ButtonX->is_debouncing = 1;
		ButtonX->time_debounce = HAL_GetTick();
	}
	//-----xac lap-------
	if (ButtonX->is_debouncing && (HAL_GetTick() - ButtonX->time_debounce >= 15))
	{
		ButtonX->Button_curr = ButtonX->Button_filter;
		ButtonX->is_debouncing = 0;
	}
	//------xu li--------
	if (ButtonX->Button_curr != ButtonX->Button_last)
	{
		if (ButtonX->Button_curr == 1)
		{
			ButtonX->is_holding = 1;
			Button_pressing_callback();
			ButtonX->time_startPress = HAL_GetTick();
		}
		else
		{
			if (HAL_GetTick() - ButtonX->time_startPress <= 500) 
			{
				Button_short_pressing_callback();
			}
			Button_release_callback();
			ButtonX->is_holding = 0;
		}
		
		ButtonX->Button_last = ButtonX->Button_curr;
	}
	if (ButtonX->is_holding && HAL_GetTick() - ButtonX->time_startPress >= 1000)
	{
		Button_hold_pressing_callback();
		ButtonX->is_holding = 0;
	}
}

void Button_init(Button_Typedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->Button_curr = 0;
	ButtonX->Button_last = 0;
	ButtonX->Button_filter = 0;
	ButtonX->is_holding = 0;
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}
