#include "includes.h"


//��ʼ��IIC
void PAD_IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE );  //ʹ��GPIOBʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7); //PB6,PB7 �����

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_14; //�ж�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}



//����IIC��ʼ�ź�
void PAD_IIC_Start(void)
{
	PAD_SDA_OUT();     //sda�����
	PAD_IIC_SDA = 1;
	PAD_IIC_SCL = 1;
	delay_us(4);
	PAD_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
	delay_us(4);
	PAD_IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void PAD_IIC_Stop(void)
{
	PAD_SDA_OUT();//sda�����
	PAD_IIC_SCL = 0;
	PAD_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	delay_us(4);
	PAD_IIC_SCL = 1;
	PAD_IIC_SDA = 1; //����I2C���߽����ź�
	delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 PAD_IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	PAD_SDA_IN();      //SDA����Ϊ����
	PAD_IIC_SDA = 1;
	delay_us(1);
	PAD_IIC_SCL = 1;
	delay_us(1);

	while(PAD_READ_SDA)
	{
		ucErrTime++;

		if(ucErrTime > 250)
		{
			PAD_IIC_Stop();
			return 1;
		}
	}

	PAD_IIC_SCL = 0; //ʱ�����0
	return 0;
}
//����ACKӦ��
void PAD_IIC_Ack(void)
{
	PAD_IIC_SCL = 0;
	PAD_SDA_OUT();
	PAD_IIC_SDA = 0;
	delay_us(2);
	PAD_IIC_SCL = 1;
	delay_us(2);
	PAD_IIC_SCL = 0;
}
//������ACKӦ��
void PAD_IIC_NAck(void)
{
	PAD_IIC_SCL = 0;
	PAD_SDA_OUT();
	PAD_IIC_SDA = 1;
	delay_us(2);
	PAD_IIC_SCL = 1;
	delay_us(2);
	PAD_IIC_SCL = 0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void PAD_IIC_Send_Byte(u8 txd)
{
	u8 t;
	PAD_SDA_OUT();
	PAD_IIC_SCL = 0; //����ʱ�ӿ�ʼ���ݴ���

	for(t = 0; t < 8; t++)
	{
		PAD_IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		PAD_IIC_SCL = 1;
		delay_us(2);
		PAD_IIC_SCL = 0;
		delay_us(2);
	}
}
void PAD_IIC_Key_Send_Byte(u8 txd)
{
	u8 t;
	PAD_SDA_OUT();
	PAD_IIC_SCL = 0; //����ʱ�ӿ�ʼ���ݴ���

	for(t = 0; t < 8; t++)
	{
		PAD_IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		PAD_IIC_SCL = 1;
		delay_us(2);
		PAD_IIC_SCL = 0;
		delay_us(2);
	}
}

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 PAD_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	PAD_SDA_IN();//SDA����Ϊ����

	for(i = 0; i < 8; i++ )
	{
		PAD_IIC_SCL = 0;
		delay_us(2);
		PAD_IIC_SCL = 1;
		receive <<= 1;

		if(PAD_READ_SDA)receive++;

		delay_us(1);
	}

	//    if (!ack)
	//        PAD_IIC_NAck();//����nACK
	//    else
	//        IIC_Ack(); //����ACK
	return receive;
}



























