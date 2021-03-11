/*
 * Debugfs module
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>

#define ID "028aba07e56d"
#define ID_LEN 13 /* ID length */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Debugfs module");

static DEFINE_SEMAPHORE(foo_sem);

static char foo_data[PAGE_SIZE];
static int foo_len;

static struct dentry *dfs;

static ssize_t my_read(struct file *file, char __user *buf, size_t count,
		loff_t *f_pos)
{
	return simple_read_from_buffer(buf, count, f_pos, ID, ID_LEN);
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count,
		loff_t *f_pos)
{
	char input[ID_LEN];
	int ret;

	if (count != ID_LEN)
		return -EINVAL;

	ret = simple_write_to_buffer(input, count, f_pos, buf, count);
	if (ret < 0)
		return ret;
	ret = strncmp(ID, input, count) ? count : -EINVAL;
	return ret;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = my_write,
	.read = my_read
};

static ssize_t foo_read(struct file *file, char __user *buff, size_t count,
		loff_t *ppos)
{
	int retval = -EINVAL;

	if (*ppos != 0)
		return 0;

	down(&foo_sem);

	if (!copy_to_user(buff, foo_data, foo_len)) {
		*ppos += count;
		retval = count;
	}

	up(&foo_sem);
	return retval;
}

static ssize_t foo_write(struct file *file, char const __user *buff,
			size_t count, loff_t *ppos)
{
	int retval = -EINVAL;

	if (count >= PAGE_SIZE)
		return -EINVAL;

	down(&foo_sem);

	if (copy_from_user(foo_data, buff, count)) {
		foo_len = 0;
	} else {
		foo_len = count;
		retval = count;
	}

	up(&foo_sem);
	return retval;
}

static const struct file_operations foo_fops = {
	.owner = THIS_MODULE,
	.read = foo_read,
	.write = foo_write
};

static int __init my_init(void)
{
	dfs = debugfs_create_dir("eudyptula", NULL);
	debugfs_create_file("id", 0666, dfs, NULL, &fops);
	debugfs_create_u32("jiffies", 0444, dfs, (u32*)&jiffies);
	debugfs_create_file("foo", 0644, dfs, NULL, &foo_fops);
	pr_debug("Debugfs module loaded.");
	return 0;
}

static void __exit my_exit(void)
{
	debugfs_remove_recursive(dfs);
	pr_debug("Debugfs module unloaded.\n");
}

module_init(my_init);
module_exit(my_exit);
