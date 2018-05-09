#ifndef __PAD_IIC_H
#define __PAD_IIC_H
#include "includes.h"

//IO��������

#define PAD_SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define PAD_SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define PAD_INT1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//��ȡ����TOUCH1
#define PAD_INT2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//��ȡ����TOUCH2

//IO��������
#define PAD_IIC_SCL    PBout(6) //SCL
#define PAD_IIC_SDA    PBout(7) //SDA    
#define PAD_READ_SDA   PBin(7)  //����SDA 

//IIC���в�������
void PAD_IIC_Init(void);                //��ʼ��IIC��IO��
void PAD_IIC_Start(void);               //����IIC��ʼ�ź�
void PAD_IIC_Stop(void);                //����IICֹͣ�ź�
void PAD_IIC_Send_Byte(u8 txd);         //IIC����һ���ֽ�
u8 PAD_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 PAD_IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void PAD_IIC_Ack(void);                 //IIC����ACK�ź�
void PAD_IIC_NAck(void);                //IIC������ACK�ź�
void PAD_IIC_Key_Send_Byte(u8 txd);

#endif
















