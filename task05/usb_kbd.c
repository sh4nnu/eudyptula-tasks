/*
 * Task05- USB hotplugging module
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

static int hello_probe(struct usb_interface *interface,
		const struct usb_device_id *id)
{
	pr_alert("USB keyboard plugged in\n");
	return 0;
}

static void hello_disconnect(struct usb_interface *interface)
{
	pr_alert("USB keyboard disconnected.\n");
}


int init_module(void)
{
	pr_debug("Hello World\n");
	return 0;
}

void cleanup_module(void)
{
	pr_debug("Module unloaded\n");
}

static const struct usb_device_id usbkbd_id_table[] = {
    { .match_flags = USB_DEVICE_ID_MATCH_INT_CLASS,
        .bInterfaceClass = USB_INTERFACE_CLASS_HID },
{}
};

static struct usb_driver usbkbd_driver = {
	.name = "usb_kbd",
	.probe = hello_probe,
	.disconnect = hello_disconnect,
	.id_table = usbkbd_id_table,
};

MODULE_DEVICE_TABLE(usb, usbkbd_id_table);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Taske05- USB hotplugging");
