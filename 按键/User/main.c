#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "Timer.h"
#include "Serial.h"

uint8_t KeyNum;
uint8_t LED1Mode;
uint8_t LED2Mode;

uint16_t i;

int main(void)
{
	Key_Init();
	LED_Init();
	Buzzer_Init();
	Timer_Init();
	Serial_Init();
	
	
	while (1)
	{
		KeyNum = Key_GetNum();
		
//		if (KeyNum == 1)
//		{
//			Serial_SendByte(0x01);
//		}
//		if (KeyNum == 2)
//		{
//			Serial_SendByte(0x02);
//		}
//		if (KeyNum == 3)
//		{
//			Serial_SendByte(0x03);
//		}
        if(Serial_RxPacket[0] == 0x01 && Serial_RxPacket [1] == 0x01 && Serial_RxFlag)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			Serial_RxPacket[0] = 0;
			Serial_RxPacket [1] = 0;
			Serial_RxFlag = 0;
			Delay_ms(500);
		}
		else if(Serial_RxPacket[0] == 0x01 && Serial_RxPacket [1] == 0x00 && Serial_RxFlag)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			Serial_RxPacket[0] = 0;
			Serial_RxFlag = 0;
			Delay_ms(300);
		}
		
		if(Serial_RxPacket[0] == 0x00 && Serial_RxPacket[1] == 0x01 && Serial_RxFlag)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			Serial_RxPacket[1] = 0;
			Serial_RxFlag = 0;
			Delay_ms(100);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			Delay_ms(100);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			Delay_ms(100);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			Delay_ms(100);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			Delay_ms(100);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			Delay_ms(100);
			
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
		}
//		OLED_ShowNum(1, 3, i ++, 5);
//		OLED_ShowNum(2, 10, LED1Mode, 1);
//		OLED_ShowNum(3, 10, LED2Mode, 1);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Key_Tick();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
