/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-25     ebaeab       the first version
 */
#include "drv_usbh.h"
#include "stdio.h"
#include "board.h"
#include "rtdef.h"

static rt_err_t drv_reset_port(rt_uint8_t port)
{
    return RT_EOK;
}

static int drv_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    return -1;
}

static rt_err_t drv_open_pipe(upipe_t pipe)
{
    return RT_EOK;
}

static rt_err_t drv_close_pipe(upipe_t pipe)
{
    return RT_EOK;
}

static struct uhcd_ops _uhcd_ops =
{
    drv_reset_port,
    drv_pipe_xfer,
    drv_open_pipe,
    drv_close_pipe,
};

static rt_err_t ch_hcd_init(rt_device_t device)
{
    USBHS_RCC_Init();
    USBHS_Host_Init(ENABLE);
    memset( &RootHubDev[ DEF_USBHS_PORT_INDEX ].bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBHS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
    return RT_EOK;
}

int ch_usbh_register(void)
{
    rt_err_t res = -RT_ERROR;
    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    if (uhcd == RT_NULL)
    {
        rt_kprintf("uhcd malloc failed\n");
        return res;
    }
    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));

    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = ch_hcd_init;
    uhcd->parent.user_data = NULL;

    uhcd->ops = &_uhcd_ops;
    uhcd->num_ports = OTG_HS_PORT;
    res = rt_device_register(&uhcd->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }
    rt_usb_host_init();

    return RT_EOK;
}

INIT_DEVICE_EXPORT(ch_usbh_register);
