/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "ch32v30x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"
#include <board.h>
#include"cpuusage.h"
/* Global typedef */

/* Global define */


#define LED0_PIN  35   //PC3

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    rt_kprintf("MCU: CH32V307\n");
	rt_kprintf("SysClk: %dMHz\n",SystemCoreClock/1048576);
    rt_kprintf("www.wch.cn\n");
	LED1_BLINK_INIT();
    cpu_usage_init();

	while(1)
	{
	    rt_thread_mdelay(2);
	}
}


/*********************************************************************
 * @fn      led
 *
 * @brief   gpio operation by pins driver.
 *
 * @return  none
 */
int led(void)
{
    rt_uint8_t count;

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_kprintf("led_SP:%08x\r\n",__get_SP());
    for(count = 0 ; count < 10 ;count++)
    {
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_kprintf("led on, count : %d\r\n", count);
        rt_thread_mdelay(500);

        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_kprintf("led off\r\n");
        rt_thread_mdelay(500);
    }
    return 0;
}

MSH_CMD_EXPORT(led,  led sample by using I/O drivers);


int cpustat(void)
{
    rt_uint8_t major, minor;

    for(int count = 0 ; count < 10 ;count++)
    {
        cpu_usage_get(&major, &minor);
		rt_kprintf("CPU 利用率：%d.%d %\r\n", major, minor);
	    rt_thread_mdelay(500);
    }
    return 0;
}

MSH_CMD_EXPORT(cpustat,  cpustat);
