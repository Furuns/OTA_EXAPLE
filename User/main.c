#include "usart.h"
#include "my_config.h"
#include "device.h"
#include "spi2.h"
#include "socket.h"
#include "w5500.h"
#include "24c16.h"
#include "ult.h"
#include "md5.h"
#include "string.h"
#include "ntp.h"
#include <stdio.h>
#include "tcp_client.h"
#include "timer.h"
#include "usart.h"
#include "dns.h"
#include "malloc.h"
extern tstamp Total_Seconds;
extern int ota_example_mqtt(void);
int main()
{
	Systick_Init();/* 初始化Systick工作时钟*/ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	GPIO_Configuration();/* 配置GPIO*/	
	USART1_Init(); /*初始化串口通信:115200@8-n-1*/
	printf("W5500 EVB initialization over.\r\n");
    WIZ_SPI_Init();/*初始化SPI接口*/
	set_wiz_mode();//设置W5500的模式
    Reset_W5500();/*硬重启W5500*/
	set_default(); 	
	set_network();
	TIM3_Int_Init(9,7199);//10Khz的计数频率，计数到10为1ms
	printf("W5500 Init Complete!\r\n");
	
	while(1)
	{	
	  ota_example_mqtt();
	  while(1);
	}
}
