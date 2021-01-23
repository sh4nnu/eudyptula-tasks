/*
 * Hello World module.
 */
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	pr_debug("Hello World\n");
	return 0;
}

void cleanup_module(void)
{
	pr_debug("Module unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Hello World Module");
