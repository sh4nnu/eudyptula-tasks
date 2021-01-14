/*
 * hello.c - Hello World module.
 */
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_DEBUG "Hello World \n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_DEBUG "Module unloaded\n");
}

MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Hello World Module");
