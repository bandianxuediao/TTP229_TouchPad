#include "includes.h"


#define HC595_PORT GPIOB
#define MOSIO_Pin14_DS_OUT PBout(14)
#define S_CLK_Pin13_SHCP_OUT PBout(13)
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

void write_smg(u8 temp)
{
	u8 i;

	for(i = 0; i < 8; i++)
	{
		S_CLK_Pin13_SHCP_OUT = 0;

		if((temp & 0x80) == 0x80)
		{
			MOSIO_Pin14_DS_OUT = 1; //�����������
		}
		else
		{
			MOSIO_Pin14_DS_OUT = 0;
		}

		S_CLK_Pin13_SHCP_OUT = 1; //��λ����ʱ�ӣ�����������
		temp <<= 1;
		delay_us(3);
		S_CLK_Pin13_SHCP_OUT = 0;
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
	u8 key_value = 0;
	/////main����

	u16 Valll = 1;
	delay_init();            //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);      //���ڳ�ʼ��Ϊ115200
	HC595_Init();
	PAD_IIC_Init();
	delay_ms(500);
	delay_ms(500);
	/*--Z QP��74HC595*/


	while(1)
	{
		//HC595SendData(Valll);
		//      delay_ms(500);
		//      delay_ms(500);
		//Valll<<=1;
		//      if(Valll==0)
		//      {
		//      Valll=1;
		//      }
		key_value = scan_key();

		if (key_value != 0)
		{
			HC595SendData(1 << (key_value - 1));
			printf ("����%02d���� \r\n", key_value);
		}
	}
}
