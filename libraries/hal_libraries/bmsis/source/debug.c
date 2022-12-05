/********************************** (C) COPYRIGHT  *******************************
* File Name          : debug.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : This file contains all the functions prototypes for UART
*                      Printf , Delay functions.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "debug.h"

void Delay_Us(uint32_t us)
{
    uint64_t start, now, delta, us_tick;
    start = SysTick->CNT;
    us_tick = SystemCoreClock / 1000000UL;
    do {
        now = SysTick->CNT;
        delta = now - start;
    } while(delta < us_tick * us);
}

/*********************************************************************
 * @fn      Delay_Ms
 *
 * @brief   Millisecond Delay Time.
 *
 * @param   n - Millisecond number.
 *
 * @return  None
 */
void Delay_Ms(uint32_t n)
{
    uint32_t i;
    for (i = 0; i < n; i++)
    {
        Delay_Us(1000);
    }
}



