/*
 * Task 05 - I used usb mouse for this task, as I couldn't get a usb keyboard.
 * I contacted little regarding this and got approval for using usb mouse.
 */
#include<linux/init.h>
#include<linux/module.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d Manikishan Ghantasala");

static int __init my_init(void)
{
	pr_debug("A USB Device was connected! - eudyptula-028aba07e56d");
	return 0;
}

static void __exit my_exit(void)
{
	pr_debug("A USB Device was disconnected! - eudyptula-028aba07e56d");
}

static struct usb_device_id usb_mouse_id_table[] = {
{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
	USB_INTERFACE_SUBCLASS_BOOT,
	USB_INTERFACE_PROTOCOL_MOUSE) },
{}
};

MODULE_DEVICE_TABLE(usb, usb_mouse_id_table);

module_init(my_init);
module_exit(my_exit);
