#ifndef LED_H
#define LED_H

#include "main.h"

typedef enum
{
	
	LED_ON,
	LED_OFF,
	LED_BREATH,
	
} LED_mode;

typedef struct
{
	
	LED_mode mode;
	uint8_t state;
	uint8_t brightness;
	uint8_t brightness_incr;
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint32_t time_change;
	uint8_t LED_change;
	
} LED_Typedef;

void PWM_Set_DutyCycle(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t DT);
void LED_handle(LED_Typedef *LED);
void LED_init(LED_Typedef *LED, TIM_HandleTypeDef *htim, uint32_t Channel);

#endif 
