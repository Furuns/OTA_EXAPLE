#include "device.h"
#include "my_config.h"
#include "socket.h"
#include "ult.h"
#include "w5500.h"
#include "24c16.h"
#include <stdio.h> 
#include <string.h>

CONFIG_MSG  ConfigMsg, RecvMsg;

uint8 txsize[MAX_SOCK_NUM] = {16};
uint8 rxsize[MAX_SOCK_NUM] = {16};
extern uint8 MAC[6];//public buffer for DHCP, DNS, HTTP
//public buffer for DHCP, DNS, HTTP
//uint8 pub_buf[1460];
 
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO , ENABLE);
  // Port A output
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2 |GPIO_Pin_3; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_ResetBits(GPIOA, GPIO_Pin_0);
  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
  GPIO_SetBits(GPIOA, GPIO_Pin_2); // led off
  GPIO_SetBits(GPIOA, GPIO_Pin_3); // led off
  // Port B output;
  GPIO_InitStructure.GPIO_Pin = WIZ_RESET; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(WIZ_RESET_PORT, &GPIO_InitStructure);
  GPIO_SetBits(WIZ_RESET_PORT, WIZ_RESET);
  // Port C input
  GPIO_InitStructure.GPIO_Pin = WIZ_INT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(WIZ_INT_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_12);//DHT11 DATA
  
  /*定义MODE引脚*/
    GPIO_InitStructure.GPIO_Pin = WIZ_PMODE0 | WIZ_PMODE1 | WIZ_PMODE2;						       /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     /*设置引脚速率为50MHz*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				     /*设置引脚模式为通用推挽模拟上拉输入*/
    GPIO_Init ( WIZ_PMODE_PORT, &GPIO_InitStructure );			 /*调用库函数，初始化GPIO*/
}
void set_wiz_mode ( void )
{
    //将模式设置为全功能，并启动自动协商
    GPIO_SetBits ( WIZ_PMODE_PORT, WIZ_PMODE0 | WIZ_PMODE1 | WIZ_PMODE2 );
    printf ( "设置W5500模式：全功能，自动协商" );
}
void Reset_W5500(void)
{
  GPIO_ResetBits(WIZ_RESET_PORT, WIZ_RESET);
  Delay_us(2);  
  GPIO_SetBits(WIZ_RESET_PORT, WIZ_RESET);
  Delay_ms(1600);
}
//reboot 
void reboot(void)
{
  pFunction Jump_To_Application;
  uint32 JumpAddress;
  JumpAddress = *(vu32*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}

void set_network(void)
{
  uint8 ip[4];
  setSHAR(ConfigMsg.mac);/*配置Mac地址*/
  setSUBR(ConfigMsg.sub);/*配置子网掩码*/
  setGAR(ConfigMsg.gw);/*配置默认网关*/
  setSIPR(ConfigMsg.lip);/*配置Ip地址*/

  //Init. TX & RX Memory size of w5500
  sysinit(txsize, rxsize); /*初始化8个socket*/
  
  setRTR(2000);/*设置溢出时间值*/
  setRCR(3);/*设置最大重新发送次数*/
  
  getSIPR (ip);
  printf(" IP : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  getSUBR(ip);
  printf(" SN : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  getGAR(ip);
  printf(" GW : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
 
}
#define ip_gateway	188
void set_default(void)
{
  
  uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0xff};
  uint8 lip[4]={192,168,ip_gateway,136};
  uint8 sub[4]={255,255,255,0};
  uint8 gw[4]={192,168,ip_gateway,1};
  uint8 dns[4]={192,168,ip_gateway,1};
  memcpy(ConfigMsg.lip, lip, 4);
  memcpy(ConfigMsg.sub, sub, 4);
  memcpy(ConfigMsg.gw,  gw, 4);
  memcpy(ConfigMsg.mac, mac,6);
  memcpy(ConfigMsg.dns,dns,4);

  ConfigMsg.dhcp=0;
  ConfigMsg.debug=1;
  ConfigMsg.fw_len=0;
  
  ConfigMsg.state=NORMAL_STATE;
  ConfigMsg.sw_ver[0]=FW_VER_HIGH;
  ConfigMsg.sw_ver[1]=FW_VER_LOW;
  
}
