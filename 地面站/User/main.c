#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Serial2.h"

uint8_t Ele = 0, Ele_local = 1, Ele_flag = 0;
uint8_t Tig = 0, Tig_local = 7, Tig_flag = 0;
uint8_t Wol = 0, Wol_local = 13, Wol_flag = 0;
uint8_t Mon = 0, Mon_local = 19, Mon_flag = 0;
uint8_t Pea = 0, Pea_local = 25, Pea_flag = 0;
uint8_t Ele_Pevrlocal[5][2];
uint8_t Tig_Pevrlocal[5][2];
uint8_t Wol_Pevrlocal[5][2];
uint8_t Mon_Pevrlocal[5][2];
uint8_t Pea_Pevrlocal[5][2];
uint8_t Ele_Pevrlocal_local = 0;
uint8_t Tig_Pevrlocal_local = 0;
uint8_t Wol_Pevrlocal_local = 0;
uint8_t Mon_Pevrlocal_local = 0;
uint8_t Pea_Pevrlocal_local = 0;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Serial_Init();		//串口初始化
	Serial2_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//配置NVIC为分组2
	
	while (1)
	{
		OLED_ShowHexNum(1, 1, x_local, 4);
		OLED_ShowHexNum(4, 1, y_local, 4);
		if(Serial_RxPacket[4])
		{
			for(int i = 0; i < 5; i++)
			{
				if(Serial_RxPacket[9] == Ele_Pevrlocal[i][0] && Serial_RxPacket[10] == Ele_Pevrlocal[i][1])
				{
					Ele_flag = 1;
					Serial_RxPacket[4] = 0;
					break;
				}
				else
				{
					Ele_flag = 0;
				}
			}
			if(Ele_flag != 1)
			{
				Ele += Serial_RxPacket[4];
				Serial2_Printf("page2.n31.val=%d\xff\xff\xff", Ele);
				Serial2_Printf("page1.n0.val=%d\xff\xff\xff", Serial_RxPacket[4]);
				Serial2_Printf("page2.n%d.val=%d\xff\xff\xff", Ele_local - 1, Serial_RxPacket[4]);
				Serial_RxPacket[4] = 0;
				Serial2_Printf("page2.t%d.txt=\"A%dB%d\"\xff\xff\xff", Ele_local, Serial_RxPacket[9], Serial_RxPacket[10]);
				Ele_Pevrlocal[Ele_Pevrlocal_local][0] = Serial_RxPacket[9];
				Ele_Pevrlocal[Ele_Pevrlocal_local][1] = Serial_RxPacket[10];
				Ele_local ++;
				Ele_Pevrlocal_local ++;
				if(Ele_local >= 6)
				{
					Ele_local = 6;
				}
			}
		}
		if(Serial_RxPacket[5])
		{
			for(int i = 0; i < 5; i++)
			{
				if(Serial_RxPacket[11] == Tig_Pevrlocal[i][0] && Serial_RxPacket[12] == Tig_Pevrlocal[i][1])
				{
					Tig_flag = 1;
					Serial_RxPacket[5] = 0;
					break;
				}
				else
				{
					Tig_flag = 0;
				}
			}
			if(Tig_flag != 1)
			{
				Tig += Serial_RxPacket[5];
				Serial2_Printf("page1.n1.val=%d\xff\xff\xff", Serial_RxPacket[5]);
				Serial2_Printf("page2.n%d.val=%d\xff\xff\xff",Tig_local - 1, Serial_RxPacket[5]);
				Serial2_Printf("page2.n11.val=%d\xff\xff\xff", Tig);
				Serial_RxPacket[5] = 0;
				Serial2_Printf("page2.t%d.txt=\"A%dB%d\"\xff\xff\xff", Tig_local, Serial_RxPacket[11], Serial_RxPacket[12]);
				Tig_Pevrlocal[Tig_Pevrlocal_local][0] = Serial_RxPacket[11];
				Tig_Pevrlocal[Tig_Pevrlocal_local][1] = Serial_RxPacket[12];
				Tig_local ++;
				Tig_Pevrlocal_local ++;
				if(Tig_local >= 12)
				{
					Tig_local = 12;
				}
			}
		}
		if(Serial_RxPacket[6])
		{
			for(int i = 0; i < 25; i++)
			{
				if(Serial_RxPacket[13] == Wol_Pevrlocal[i][0] && Serial_RxPacket[14] == Wol_Pevrlocal[i][1])
				{
					Wol_flag = 1;
					Serial_RxPacket[6] = 0;
					break;
				}
				else
				{
					Wol_flag = 0;
				}
			}
			if(Wol_flag != 1)
			{
				Wol += Serial_RxPacket[6];
				Serial2_Printf("page1.n2.val=%d\xff\xff\xff", Serial_RxPacket[6]);
				Serial2_Printf("page2.n%d.val=%d\xff\xff\xff",Wol_local - 1, Serial_RxPacket[6]);
				Serial2_Printf("page2.n17.val=%d\xff\xff\xff", Wol);
				Serial_RxPacket[6] = 0;
				Serial2_Printf("page2.t%d.txt=\"A%dB%d\"\xff\xff\xff", Wol_local, Serial_RxPacket[13], Serial_RxPacket[14]);
				Wol_Pevrlocal[Wol_Pevrlocal_local][0] = Serial_RxPacket[13];
				Wol_Pevrlocal[Wol_Pevrlocal_local][1] = Serial_RxPacket[14];
				Wol_local ++;
				Wol_Pevrlocal_local ++;
				if(Wol_local >= 18)
				{
					Wol_local = 18;
				}
			}
		}
		if(Serial_RxPacket[7])
		{
			for(int i = 0; i < 25; i++)
			{
				if(Serial_RxPacket[15] == Mon_Pevrlocal[i][0] && Serial_RxPacket[16] == Mon_Pevrlocal[i][1])
				{
					Mon_flag = 1;
					Serial_RxPacket[7] = 0;
					break;
				}
				else
				{
					Mon_flag = 0;
				}
			}
			if(Mon_flag != 1)
			{
				Mon += Serial_RxPacket[7];
				Serial2_Printf("page1.n3.val=%d\xff\xff\xff", Serial_RxPacket[7]);
				Serial2_Printf("page2.n%d.val=%d\xff\xff\xff",Mon_local - 1, Serial_RxPacket[7]);
				Serial2_Printf("page2.n23.val=%d\xff\xff\xff", Mon);
				Serial_RxPacket[7] = 0;
				Serial2_Printf("page2.t%d.txt=\"A%dB%d\"\xff\xff\xff", Mon_local, Serial_RxPacket[15], Serial_RxPacket[16]);
				Mon_Pevrlocal[Mon_Pevrlocal_local][0] = Serial_RxPacket[15];
				Mon_Pevrlocal[Mon_Pevrlocal_local][1] = Serial_RxPacket[16];
				Mon_local ++;
				Mon_Pevrlocal_local ++;
				if(Mon_local >= 24)
				{
					Mon_local = 24;
				}
			}
		}
		if(Serial_RxPacket[8])
		{
			for(int i = 0; i < 25; i++)
			{
				if(Serial_RxPacket[17] == Pea_Pevrlocal[i][0] && Serial_RxPacket[18] == Pea_Pevrlocal[i][1])
				{
					Pea_flag = 1;
					Serial_RxPacket[8] = 0;
					break;
				}
				else
				{
					Pea_flag = 0;
				}
			}
			if(Pea_flag != 1)
			{
				Pea += Serial_RxPacket[8];
				Serial2_Printf("page1.n4.val=%d\xff\xff\xff", Serial_RxPacket[8]);
				Serial2_Printf("page2.n%d.val=%d\xff\xff\xff",Pea_local - 1, Serial_RxPacket[8]);
				Serial2_Printf("page2.n29.val=%d\xff\xff\xff", Pea);
				Serial_RxPacket[8] = 0;
				Serial2_Printf("page2.t%d.txt=\"A%dB%d\"\xff\xff\xff", Pea_local, Serial_RxPacket[17], Serial_RxPacket[18]);
				Pea_Pevrlocal[Pea_Pevrlocal_local][0] = Serial_RxPacket[17];
				Pea_Pevrlocal[Pea_Pevrlocal_local][1] = Serial_RxPacket[18];
				Pea_local ++;
				Pea_Pevrlocal_local ++;
			}
		}
	}
}
