/*
 * Simple misc char driver.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define ID "028aba07e56d"
#define ID_LEN 13 /* ID length */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Misc char device driver");

static ssize_t my_read(struct file *file, char __user *buf,
		size_t count, loff_t *f_pos)
{
	return simple_read_from_buffer(buf, count, f_pos, ID, ID_LEN);
}

static ssize_t my_write(struct file *file, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	char input[ID_LEN];
	int ret;

	if (count != ID_LEN)
		return -EINVAL;

	ret = simple_write_to_buffer(input, count, f_pos, buf, count);
	if (ret < 0)
		return ret;

	ret = strncmp(ID, input, ID_LEN-1) ? count : -EINVAL;
	return ret;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = my_write,
	.read = my_read
};

struct miscdevice eudyptula = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "eudyptula",
	.fops = &fops
};

static int __init my_init(void)
{
	int ret;

	ret = misc_register(&eudyptula);
	pr_debug("Hello World\n");
	return ret;
}

static void __exit my_exit(void)
{
	misc_deregister(&eudyptula);
	pr_debug("Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
