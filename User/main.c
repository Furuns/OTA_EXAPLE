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
	Systick_Init();/* ��ʼ��Systick����ʱ��*/ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	GPIO_Configuration();/* ����GPIO*/	
	USART1_Init(); /*��ʼ������ͨ��:115200@8-n-1*/
	printf("W5500 EVB initialization over.\r\n");
    WIZ_SPI_Init();/*��ʼ��SPI�ӿ�*/
	set_wiz_mode();//����W5500��ģʽ
    Reset_W5500();/*Ӳ����W5500*/
	set_default(); 	
	set_network();
	TIM3_Int_Init(9,7199);//10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms
	printf("W5500 Init Complete!\r\n");
	
	while(1)
	{	
	  ota_example_mqtt();
	  while(1);
	}
}
