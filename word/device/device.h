#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "stm32f10x.h"
#include"stdio.h"
#define DEVICE_ID "W5500"

#define FW_VER_HIGH  				1
#define FW_VER_LOW    			0
#define LED0  							GPIO_Pin_0	// out
#define LED1								GPIO_Pin_1	// out
#define LED2		    				GPIO_Pin_2	// 
#define LED3								GPIO_Pin_3	// 

#define WIZ_SCS			    		GPIO_Pin_12	// out
#define WIZ_SCLK						GPIO_Pin_13	// out
#define WIZ_MISO						GPIO_Pin_14	// in
#define WIZ_MOSI						GPIO_Pin_15	// out

#define WIZ_RESET		    		GPIO_Pin_9	// out
#define WIZ_INT			    		GPIO_Pin_6	// in
#define WIZ_RESET_PORT		    GPIOB
#define WIZ_INT_PORT		    GPIOC

#define WIZ_PMODE0          GPIO_Pin_8						 	    /* W5500的MODE0管脚         */
#define WIZ_PMODE0_PORT     GPIOB									 	    /*GPIO端口                      */
#define WIZ_PMODE0_CLK      RCC_APB2Periph_GPIOB	 	    /*GPIO端口时钟                  */

#define WIZ_PMODE1          GPIO_Pin_6						 	    /* W5500的MODE1管脚         */
#define WIZ_PMODE1_PORT     GPIOB									 	    /*GPIO端口                      */
#define WIZ_PMODE1_CLK      RCC_APB2Periph_GPIOB	 	    /*GPIO端口时钟                  */

#define WIZ_PMODE2          GPIO_Pin_5						 	    /* W5500的MODE2管脚         */
#define WIZ_PMODE2_PORT     GPIOB									 	    /*GPIO端口                      */
#define WIZ_PMODE2_CLK      RCC_APB2Periph_GPIOB	 	    /*GPIO端口时钟                  */

#define WIZ_PMODE_PORT     GPIOB									 	    /*GPIO端口                      */

typedef  void (*pFunction)(void);
void GPIO_Configuration(void);
void set_network(void);
void write_config_to_eeprom(void);
void set_default(void);
void set_wiz_mode ( void );
void Reset_W5500(void);
void reboot(void);
void get_config(void);
#endif

