#include "tcp_client.h"
#include "device.h"
#include "spi2.h"
#include "ult.h"
#include "socket.h"
#include "w5500.h"
#include "24c16.h"
#include "md5.h"
#include <string.h>
#include <stdio.h>
#include "mqtt_fun.h"
#include "MQTTPacket.h"
//#include "cJSON.h"
#include "msg_command.h"
#include "timer.h"

uint8_t mqtt_connedted = 0;
 uint8 server_ip[4] = {139,196,135,135};//extern uint8 server_ip[4];			// 配置远程服务器IP地址
	uint16 server_port=1883;								// 配置远程服务器端口
  uint16 local_port=6000;									// 初始化一个本地端口
  uint16 len=0;
//	uint8  msgbuf[1024];
//	extern uint8 buffer[2048];
	uint8 CONNECT_FLAG=1;
	uint8 SUB_FLAG = 1;
	uint8 PUB_FLAG = 1;
	char ser_cmd[240];
/**************************/
	
//	unsigned char dup;
//	int qos;
//	unsigned char retained;
//	unsigned short mssageid;
//	int payloadlen_in;
//	unsigned char* payload_in;
//	MQTTString receivedTopic;
//	char topic[100]={"/a1TYwrkFQNN/cancan/user/led"};//设置发布订阅主题
//	char new_topic[100];
//	int count=0;
//	char rebuf[1024];
//	void hamacsha1(void);

//void MQTT_CON_ALI(void)
//{
//#if 1
//	int len;
//	int type;
//   switch(getSn_SR(0))										// 获取socket0的状态
//   {
//	  case SOCK_INIT:			                  // Socket处于初始化完成(打开)状态
//		 connect(0, server_ip,server_port);		// 配置Sn_CR为CONNECT，并向TCP服务器发出连接请求
//		 
//		 break;
//	  case SOCK_ESTABLISHED:								// Socket处于连接建立状态
//		if(getSn_IR(0) & Sn_IR_CON)   					
//		{
//			setSn_IR(0, Sn_IR_CON);				// Sn_IR的CON位置1，通知W5500连接已建立
//		}	
////		memset(msgbuf,0,sizeof(msgbuf));
//		mqtt_connedted = 1;
////        if((len=getSn_RX_RSR(0))==0)
////        {					
////			if(1==CONNECT_FLAG)
////		    {		
////                printf("send connect\r\n");	
////					
////				/*MQTT拼接连接报文
////				*根据阿里云平台MQTT设备接入手册配置
////				*/
////				
////				//void make_con_msg(char* clientID,int keepalive, uint8 cleansession,char*username,char* password,unsigned char*buf,int buflen)
////				make_con_msg("192.168.1.16|securemode=3,signmethod=hmacsha1,timestamp=10|",180, 1,
////				"cancan&a1TYwrkFQNN","564E85B1B12B24EA47514AFC3A8CC71297653B91",msgbuf,sizeof(msgbuf));
////				//hamacsha1();//hamacsha1字符串连接
////				//passwor = hamacsha1("secret","clientId192.168.207.115deviceNameMQTT1productKeyTKKMt4nMF8Utimestap789");
////				//printf(" server_ip: %d.%d.%d.%d\r\n", server_ip[0],server_ip[1],server_ip[2],server_ip[3]);
////				//printf("connect ALY\r\n");
////				CONNECT_FLAG = 0;
////				send(0,msgbuf,sizeof(msgbuf));
////				Delay_s(2);	
////				while((len=getSn_RX_RSR(0))==0)
////				{
////				 Delay_s(2);	
////				 send(0,msgbuf,sizeof(msgbuf));
////				};
////				 recv(0,msgbuf,len);
////				while(mqtt_decode_msg(msgbuf)!=CONNACK)//判断是不是CONNACK
////				{
////				  printf("wait ack\r\n");
////				}
////			}else if(SUB_FLAG == 1)
////            {	
////                memset(msgbuf,0,sizeof(msgbuf));					 
////		        make_sub_msg(topic,msgbuf,sizeof(msgbuf));
////				// make_pub_msg(topic,msgbuf,sizeof(msgbuf),"hello");
////				send(0,msgbuf,sizeof(msgbuf));// 接收到数据后再回给服务器，完成数据回环
////				SUB_FLAG = 0;
////				Delay_s(2);
////				while((len=getSn_RX_RSR(0))==0)
////				{
////					Delay_s(2);	
////					send(0,msgbuf,sizeof(msgbuf));
////				};
////				recv(0,msgbuf,len);
////				while(mqtt_decode_msg(msgbuf)!=SUBACK)//判断是不是SUBACK
////				{
////				    printf("wait suback\r\n");
////				}
////				TIM_Cmd(TIM2, ENABLE);
////				printf("send sub\r\n");						
////			}
////			#if 1
////			else
////			{
////				
//////				//count++;
//////				// Delay_s(2);
//////				if(count>10000)
//////				{
//////		             count = 0;						
//////				     make_ping_msg(msgbuf,sizeof(msgbuf));
//////				     send(0,msgbuf,sizeof(msgbuf));	
////// 
//////					 while((len=getSn_RX_RSR(0))==0)
//////					 {
//////						  //Delay_s(2);	
//////						  //send(0,msgbuf,sizeof(msgbuf));
//////						 printf("wait pingresponse");
//////						
//////					  };
//////					  recv(0,msgbuf,len);
//////					  printf("ping len : %d\r\n",len);
//////					  if(len>2)
//////					  {
//////						  if(PUBLISH==mqtt_decode_msg(msgbuf+2))
//////						  {
//////						      printf("publish\r\n");
//////							  MQTTDeserialize_publish(&dup, &qos, &retained, &mssageid, &receivedTopic,&payload_in, &payloadlen_in, msgbuf+2, len-2);
//////						  // printf("message arrived %d: %s\n\r", payloadlen_in, payload_in);
//////							  memset(topic,0,sizeof(topic));
//////							  memset(ser_cmd,0,sizeof(ser_cmd));
//////						      memcpy(topic,receivedTopic.lenstring.data,receivedTopic.lenstring.len);
//////							  replace_string(new_topic,topic , "request","response");
//////							  printf("topic:%s\r\n",topic);
//////					          strcpy(ser_cmd,(const char *)payload_in);
//////						      //parse_topic(ser_cmd);
//////					          // printf("message is %s\r\n",ser_cmd);
//////							  memset(msgbuf,0,sizeof(msgbuf));
//////							  make_pub_msg(new_topic,msgbuf,sizeof(msgbuf),"hello");
//////							  send(0,msgbuf,sizeof(msgbuf));	
//////						  }
//////					  }
//////				 }
////			 }
////		     #endif
////				 #if 0
////				  if(PUB_FLAG==1)
////				 {
////				    memset(msgbuf,0,sizeof(msgbuf));					 
////		       // make_sub_msg(topic,msgbuf,sizeof(msgbuf));
////					 make_pub_msg(topic,msgbuf,sizeof(msgbuf),"hello");
////					 if(count == 10000)
////					 {	 
////						 PUB:				 
////					 send(0,msgbuf,sizeof(msgbuf));	// 接收到数据后再回给服务器，完成数据回环
////					
////					  Delay_s(2);
////					// while((len=getSn_RX_RSR(0))==0)
////					//  {
////					// Delay_s(2);	
////					//send(0,msgbuf,sizeof(msgbuf));
////					//		printf("puback\r\n");
////					//  };
////					// recv(0,msgbuf,len);
////				  //	if(mqtt_decode_msg(msgbuf)!=PUBACK)//判断是不是SUBACK
////					//  {
////					//			goto PUB;
////					//	    printf("wait Puback\r\n");
////					//	}
////					  printf("send Pub\r\n");	
////				  }
////				 }	
////#endif				 
////			 } 
//			 #if 0//===========
//			 if((len=getSn_RX_RSR(0))>0)
//				{
//				     recv(0,msgbuf,len);
//					 if(PUBLISH== mqtt_decode_msg(msgbuf))
//					 {	 
//						printf("publish\r\n");
//					    MQTTDeserialize_publish(&dup, &qos, &retained, &mssageid, &receivedTopic,&payload_in, &payloadlen_in, msgbuf, len);
//					  // printf("message arrived %d: %s\n\r", payloadlen_in, payload_in);
//						memset(topic,0,sizeof(topic));
//					    memcpy(topic,receivedTopic.lenstring.data,receivedTopic.lenstring.len);
//						replace_string(new_topic,topic , "request","response");
//						 
//						 printf("topic:%s\r\n",topic);
//						 
//						 memset(ser_cmd,0,sizeof(ser_cmd));
//				         memcpy(ser_cmd,(const char *)payload_in,strlen((char*)payload_in));
//						 memset(msgbuf,0,sizeof(msgbuf));
//						 make_pub_msg(new_topic,msgbuf,sizeof(msgbuf),rebuf);
//						 send(0,msgbuf,sizeof(msgbuf));	
//					 //printf("%s\n",msgbuf);
//					 }else if(PINGRESP== mqtt_decode_msg(msgbuf))
//					 {	 	  
//						 if(len>2)
//						 {
//							 if(PUBLISH==mqtt_decode_msg(msgbuf+2))
//							 {
//							  printf("publish\r\n");
//							  MQTTDeserialize_publish(&dup, &qos, &retained, &mssageid, &receivedTopic,&payload_in, &payloadlen_in, msgbuf+2, len-2);
//							  // printf("message arrived %d: %s\n\r", payloadlen_in, payload_in);
//							  memset(topic,0,sizeof(topic));
//							  memcpy(topic,receivedTopic.lenstring.data,receivedTopic.lenstring.len);
//							  replace_string(new_topic,topic,"request","response");
//							  printf("topic:%s\r\n",topic);
//							  memset(ser_cmd,0,sizeof(ser_cmd));
//							  strcpy(ser_cmd,(const char *)payload_in);
//							  // printf("message is %s\r\n",ser_cmd);
//							  //parse_topic(ser_cmd);
//							  memset(msgbuf,0,sizeof(msgbuf));
//							  make_pub_msg(new_topic,msgbuf,sizeof(msgbuf),"hello");
//							  send(0,msgbuf,sizeof(msgbuf));	
//							 }
//						 } 
//					 }else
//					 {
//					     printf("wait publish\r\n");
//					 }
//				}
//			//	printf("send ping\r\n");
//			  
//			 #endif	
//			break;
//			case SOCK_CLOSE_WAIT:												// Socket处于等待关闭状态
//					close(0);																// 关闭Socket0
//			break;
//			case SOCK_CLOSED:														// Socket处于关闭状态
//					socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);// 打开Socket0，并配置为TCP无延时模式，打开一个本地端口
//			break;
//		}
//#else
//    uint8_t rc;
//    rc = socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);// 打开Socket0，并配置为TCP无延时模式，打开一个本地端口
//    if(1!=rc)
//	{
//		mqtt_connedted = 0;
//		close(0);
//	    printf("socket 0 open error \r\n");
//	}
//	else
//	{
//		connect(0, server_ip,server_port);		// 配置Sn_CR为CONNECT，并向TCP服务器发出连接请求
//		if(1!=rc)
//		{
//			mqtt_connedted = 0;
//			close(0);
//			printf("socket 0 connect error \r\n");
//		}
//		else
//		{
//		    mqtt_connedted = 1;
//		}
//    }
//#endif
//}

/********字符串替换********/
//void replace_string(char *result, char *source, char* s1, char *s2)
//{
//	char *q=NULL;
//	char *p=NULL;
//	p=source;
//	while((q=strstr(p, s1))!=NULL)
//	{
//		strncpy(result, p, q-p);
//		result[q-p]= '\0';//very important, must attention!
//		strcat(result, s2);
//		strcat(result, q+strlen(s1));
//		strcpy(p,result);
//	}
//	strcpy(result, p);
//}
uint8_t OpenClientConnection(SOCKET fd, uint8_t type, const char* name, uint8_t* s_ip, uint16_t s_port, uint16_t l_port)
{
	uint8_t count=0;
	uint8_t errflag = 1;
	uint64_t timeout_tick;
	
	if((type != Sn_MR_UDP)&&(type != Sn_MR_TCP))
	{
	    printf("SOCKET error type:%d",type);
		return errflag;
	}
//------
  //check if this socket id is occupied
  //!!if use multi-connection, it will have problem here - TODO
  //this code need change to support multi-connection - TODO
  if(getSn_SR(fd)!=SOCK_CLOSED)
  {
    count=0;
    do
    {
      close(fd);
      count++;
    }while((getSn_SR(fd)!=SOCK_CLOSED) && count<3);
  }
//------
	do
	{
		if(errflag)
		{
		    timeout_tick = get_sys_tick();
		}
		switch(getSn_SR(fd))										// 获取socket0的状态
		{
			case SOCK_INIT:			                  // Socket处于初始化完成(打开)状态
				connect(fd, s_ip,s_port);		// 配置Sn_CR为CONNECT，并向TCP服务器发出连接请求

				break;
			case SOCK_ESTABLISHED:								// Socket处于连接建立状态
				if(getSn_IR(fd) & Sn_IR_CON)   					
				{
					setSn_IR(fd, Sn_IR_CON);				// Sn_IR的CON位置1，通知W5500连接已建立
				}	
				errflag = 0;

				break;
			case SOCK_CLOSE_WAIT:												// Socket处于等待关闭状态
				close(fd);																// 关闭Socket0
				break;
			case SOCK_CLOSED:														// Socket处于关闭状态
				socket(fd,type,l_port,Sn_MR_ND);// 打开Socket0，并配置为TCP无延时模式，打开一个本地端口
				break;
		}
	}while((get_sys_tick()-timeout_tick) < 5000);
	return errflag;
}
