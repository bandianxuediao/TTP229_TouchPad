#include "includes.h"


#define HC595_PORT GPIOB
#define MOSIO_Pin14_DS_OUT PBout(14)
#define S_CLK_Pin11_SHCP_OUT PBout(11)
#define R_CLK_Pin12_STCP_OUT PBout(12)
/*--ZQP��74HC595�ĳ�ʼ��*/
void HC595_Init()
{
	GPIO_InitTypeDef GPIO_InitS;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitS.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitS.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitS.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC595_PORT, &GPIO_InitS);

	GPIO_SetBits(HC595_PORT, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}


void HC595SendData(unsigned int SendVal)
{
	uint8_t i;

	for (i = 0; i < 16; i++)
	{
		/*--step1�������������ţ���ν���о���ʹ������һ���ź����ϰ�˳��һλһλ�ش���*/
		if (((SendVal << i) & 0x8000) != 0 )
			MOSIO_Pin14_DS_OUT = 1;
		else
			MOSIO_Pin14_DS_OUT = 0;

		/*--step2��SHCP����һ�������ص�ʱ��74HC595�Ż��DS������ȡ�õ�ǰ������*/
		S_CLK_Pin11_SHCP_OUT = 0;
		delay_us(100);
		S_CLK_Pin11_SHCP_OUT = 1;
	}

	/*--step3������λ�Ĵ�����8λ����ȫ��������Ϻ�����һ��������ʱ�����ŵ������أ������͵�ƽ�����ߵ�ƽ��*/
	R_CLK_Pin12_STCP_OUT = 0;
	delay_us(100);
	R_CLK_Pin12_STCP_OUT = 1;
}

void write_smg(u8 temp)
{
	u8 i;

	for(i = 0; i < 8; i++)
	{
		S_CLK_Pin11_SHCP_OUT = 0;

		if((temp & 0x80) == 0x80)
		{
			MOSIO_Pin14_DS_OUT = 1; //�����������
		}
		else
		{
			MOSIO_Pin14_DS_OUT = 0;
		}

		S_CLK_Pin11_SHCP_OUT = 1; //��λ����ʱ�ӣ�����������
		temp <<= 1;
		delay_us(3);
		S_CLK_Pin11_SHCP_OUT = 0;
	}

	R_CLK_Pin12_STCP_OUT = 0; //�������ʱ��
	delay_us(3);
	R_CLK_Pin12_STCP_OUT = 1;
	delay_us(3);
	R_CLK_Pin12_STCP_OUT = 0;
}


int main(void)
{
	u8 key;
	u16 i = 0;
	uint8_t key_value;
	/////main����

	u16 Valll = 0XFFFF;
	delay_init();            //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);      //���ڳ�ʼ��Ϊ115200
	HC595_Init();

	/*--Z QP��74HC595*/


	while(Valll)
	{
		HC595SendData(0xff0f);
		delay_ms(500);
		delay_ms(500);


		key_value = scan_key();

		if ((key_value != 0xffff) && (key_value != 0x0000))
			printf ("Value: 0x%04x \r\n", key_value);

	}
}
