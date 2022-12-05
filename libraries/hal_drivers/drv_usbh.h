/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-25     ebaeab       the first version
 */
#ifndef __DRV_USBH_H_
#define __DRV_USBH_H_

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#define OTG_HS_PORT 1
int ch_usbh_register(void);

#endif /* __DRV_USBH_H_ */
