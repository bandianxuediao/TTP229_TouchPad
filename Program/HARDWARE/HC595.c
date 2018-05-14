#include "includes.h"


/*--ZQP��74HC595�ĳ�ʼ��*/
void HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitS;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitS.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitS.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitS.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC595_PORT, &GPIO_InitS);

	GPIO_SetBits(HC595_PORT, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}


void HC595SendData(u16 SendVal)
{
	uint8_t i;
	S_CLK_Pin13_SHCP_OUT = 0;
	S_CLK_Pin13_SHCP_OUT = 0;

	for (i = 0; i < 16; i++)
	{
		/*--step1�������������ţ���ν���о���ʹ������һ���ź����ϰ�˳��һλһλ�ش���*/
		if (((SendVal << i) & 0x8000) != 0 )
			MOSIO_Pin14_DS_OUT = 1;
		else
			MOSIO_Pin14_DS_OUT = 0;

		/*--step2��SHCP����һ�������ص�ʱ��74HC595�Ż��DS������ȡ�õ�ǰ������*/
		S_CLK_Pin13_SHCP_OUT = 0;
		delay_us(10);
		S_CLK_Pin13_SHCP_OUT = 1;
	}

	/*--step3������λ�Ĵ�����8λ����ȫ��������Ϻ�����һ��������ʱ�����ŵ������أ������͵�ƽ�����ߵ�ƽ��*/
	R_CLK_Pin12_STCP_OUT = 0;
	delay_us(10);
	R_CLK_Pin12_STCP_OUT = 1;
	delay_us(10);
	S_CLK_Pin13_SHCP_OUT = 0;

	R_CLK_Pin12_STCP_OUT = 0;
	MOSIO_Pin14_DS_OUT = 0;
}
























