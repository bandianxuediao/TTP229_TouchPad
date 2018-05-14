#ifndef __HC595_H
#define __HC595_H


#define HC595_PORT GPIOB
#define MOSIO_Pin14_DS_OUT PBout(14)
#define S_CLK_Pin13_SHCP_OUT PBout(13)
#define R_CLK_Pin12_STCP_OUT PBout(12)
/*--ZQP��74HC595�ĳ�ʼ��*/
void HC595_Init(void);
void HC595SendData(u16 SendVal);
#endif
















