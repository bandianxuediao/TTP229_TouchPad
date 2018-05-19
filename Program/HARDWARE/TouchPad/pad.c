#include "includes.h"
u8 INPUT_DATA_NUM[10] ;
u8 INPUT_DATA_AMOUNT = 0;
	u16 receive;
const u8 PAD_1[2]   = {0xfd, 0xff};
const u8 PAD_2[2]   = {0xfb, 0xff};
const u8 PAD_3[2]   = {0xf7, 0xff};
const u8 PAD_4[2]   = {0xff, 0xdf};
const u8 PAD_5[2]   = {0xff, 0xbf};
const u8 PAD_6[2]   = {0xff, 0x7f};
const u8 PAD_7[2]   = {0xff, 0xef};
const u8 PAD_IN[2]  = {0xef, 0xff};
const u8 PAD_OUT[2] = {0xfe, 0xff};

const u8 PAD_8[2]        = {0xfb, 0xff};
const u8 PAD_9[2]    = {0xf7, 0xff};
const u8 PAD_0[2]    = {0xff, 0x7f};
const u8 PAD_SYS[2]  = {0xef, 0xff};
const u8 PAD_KEY[2]  = {0xfd, 0xff};
const u8 PAD_SURE[2] = {0xfe, 0xff};
const u8 PAD_BACK[2] = {0xff, 0xbf};

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
		return 1;   //TP0���£�������1
	}

	if(receive == 0x0080)
	{
		return 2;   //TP8���£�������2
	}

	if(receive == 0x4000)
	{
		return 3;   //TP1���£�������3
	}

	if(receive == 0x0040)
	{
		return 4;   //TP9���£�������4
	}

	if(receive == 0x2000)
	{
		return 5;   //TP2���£�������5
	}

	if(receive == 0x0020)
	{
		return 6;   //TP10���£�������6
	}

	if(receive == 0x1000)
	{
		return 7;   //TP3���£�������7
	}

	if(receive == 0x0010)
	{
		return 8;   //TP11���£�������8
	}

	if(receive == 0x0800)
	{
		return 9;   //TP4���£�������9
	}

	if(receive == 0x0008)
	{
		return 10;   //TP12���£�������10
	}

	if(receive == 0x0400)
	{
		return 11;   //TP5���£�������11
	}

	if(receive == 0x0004)
	{
		return 12;   //TP13���£�������12
	}

	if(receive == 0x0200)
	{
		return 13;   //TP6���£�������13
	}

	if(receive == 0x0002)
	{
		return 14;   //TP14���£�������14
	}

	if(receive == 0x0100)
	{
		return 15;   //TP7���£�������15
	}

	if(receive == 0x0001)
	{
		return 16;   //TP15���£�������16
	}


	//if((temp1=!0)&&(temp1!=0xffff))
	//{
	return 0;
	//}
	//  printf("%x %x\r\n",temp1[0],temp1[1]);
}







