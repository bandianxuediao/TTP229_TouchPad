#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
 

//ALIENTEKս��STM32������ʵ��22
//IIC ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
 				 	
//Ҫд�뵽24c02���ַ�������

 int main(void)
 {	 
	u8 key;
	u16 i=0;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	KEY_Init();
 	LED_Init();			     //LED�˿ڳ�ʼ��		 	

 	while(AT24CXX_Check())//��ⲻ��24c02
	{

		LED0=!LED0;//DS0��˸
	}

									  

	while(1)
	{
		   
	}
}
