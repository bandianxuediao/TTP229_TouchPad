#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
 

//ALIENTEK战舰STM32开发板实验22
//IIC 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
 				 	
//要写入到24c02的字符串数组

 int main(void)
 {	 
	u8 key;
	u16 i=0;

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
	KEY_Init();
 	LED_Init();			     //LED端口初始化		 	

 	while(AT24CXX_Check())//检测不到24c02
	{

		LED0=!LED0;//DS0闪烁
	}

									  

	while(1)
	{
		   
	}
}
