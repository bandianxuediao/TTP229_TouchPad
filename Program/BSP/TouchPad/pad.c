#include "includes.h"
u8 INPUT_DATA_NUM[10] ;
u8 INPUT_DATA_AMOUNT = 0;
u16 receive;

u16 scan_key(void)
{

	PAD_IIC_Start();
	PAD_IIC_Key_Send_Byte(0xAF);
	PAD_IIC_Ack();//����nACK
	receive = PAD_IIC_Read_Byte(0);
	PAD_IIC_Ack();//����nACK

	receive = (receive << 8) + PAD_IIC_Read_Byte(0);
	PAD_IIC_NAck();//����nACK
	PAD_IIC_Stop();//����һ��ֹͣ����

	if(receive == 0x8000)
	{
		return 10;   //TP0���£�������1
	}

	if(receive == 0x0080)
	{
		return 1;   //TP8���£�������2
	}

	if(receive == 0x4000)
	{
		return 11;   //TP1���£�������3
	}

	if(receive == 0x0040)
	{
		return 2;   //TP9���£�������4
	}

	if(receive == 0x2000)
	{
		return 12;   //TP2���£�������5
	}

	if(receive == 0x0020)
	{
		return 3;   //TP10���£�������6
	}

	if(receive == 0x1000)
	{
		return 9;   //TP3���£�������7
	}

	if(receive == 0x0010)
	{
		return 4;   //TP11���£�������8
	}

	if(receive == 0x0800)
	{
		return 13;   //TP4���£�������9
	}

	if(receive == 0x0008)
	{
		return 5;   //TP12���£�������10
	}

	if(receive == 0x0400)
	{
		return 14;   //TP5���£�������11
	}

	if(receive == 0x0004)
	{
		return 6;   //TP13���£�������12
	}

	if(receive == 0x0200)
	{
		return 15;   //TP6���£�������13
	}

	if(receive == 0x0002)
	{
		return 8;   //TP14���£�������14
	}

	if(receive == 0x0100)
	{
		return 16;   //TP7���£�������15
	}

	if(receive == 0x0001)
	{
		return 7;   //TP15���£�������16
	}


	//if((temp1=!0)&&(temp1!=0xffff))
	//{
	return 0;
	//}
	//  printf("%x %x\r\n",temp1[0],temp1[1]);
}







