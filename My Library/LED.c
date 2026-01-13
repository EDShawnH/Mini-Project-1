#include "LED.h"

#define BRIGHT_MIN  0
#define BRIGHT_MAX  100
#define STEP        20
#define PERIOD_MS		10000

void PWM_Set_DutyCycle(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t DT)
{
	uint32_t Duty;
	uint32_t ARR_counts = (uint32_t)(htim->Instance->ARR) + 1;
	if (DT > 100) Duty = 100;
	else Duty = DT;
	switch (Channel)
	{
		case TIM_CHANNEL_1:
			htim->Instance->CCR1 = (Duty * ARR_counts)/100 - 1;
			break;
		case TIM_CHANNEL_2:
			htim->Instance->CCR2 = (Duty * ARR_counts)/100 - 1;
			break;
		case TIM_CHANNEL_3:
			htim->Instance->CCR3 = (Duty * ARR_counts)/100 - 1;
			break;
		case TIM_CHANNEL_4:
			htim->Instance->CCR4 = (Duty * ARR_counts)/100 - 1;
			break;
	}
}

void LED_handle(LED_Typedef *LED)
{
	switch (LED->mode)
	{
		case LED_OFF:
			if (LED->state != 0) 
			{
				HAL_TIM_PWM_Stop(LED->htim, LED->Channel);
				LED->state = 0;
			}
			break;
		case LED_ON:
			if (LED->state != 1) 
			{
				LED->brightness = BRIGHT_MAX;
				PWM_Set_DutyCycle(LED->htim, LED->Channel, LED->brightness);
				HAL_TIM_PWM_Start(LED->htim, LED->Channel);
				LED->state = 1;
			}
			break;
		case LED_BREATH:
			if (HAL_GetTick() - LED->time_change >= PERIOD_MS/20)
			{
				if (LED->brightness >= BRIGHT_MAX) 
					LED->brightness_incr = 0;
				else if (LED->brightness <= BRIGHT_MIN)
					LED->brightness_incr = 1;
				
				if (LED->brightness_incr)
						LED->brightness += STEP;
				else
						LED->brightness -= STEP;
				
				PWM_Set_DutyCycle(LED->htim, LED->Channel, LED->brightness);
				LED->time_change = HAL_GetTick();
			}
			break;
	}
}

void LED_init(LED_Typedef *LED, TIM_HandleTypeDef *htim, uint32_t Channel)
{
	LED -> mode 						= LED_OFF;
	LED -> state 						= 0;
	LED -> brightness 			= BRIGHT_MAX;
	LED -> brightness_incr 	= 0;
	LED ->  htim = htim;
	LED -> Channel = Channel;
}
