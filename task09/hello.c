/*
 * Task 09 - Sysfs
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/jiffies.h>
#include <linux/semaphore.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/sysfs.h>

#define ID "028aba07e56d"
#define ID_LEN 13

MODULE_LICENSE("GPL");
MODULE_AUTHOR("028aba07e56d");
MODULE_DESCRIPTION("Sysfs module");

static DEFINE_SEMAPHORE(foo_sem);

static char foo_data[PAGE_SIZE];
static int foo_len;

static struct kobject *eudypt_kobj;

static ssize_t id_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	return sysfs_emit(buf, ID, ID_LEN);
}

static ssize_t id_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	if ((count != ID_LEN) || (strncmp(ID, buf, ID_LEN-1)))
		return -EINVAL;
	else
		return ID_LEN;
}

static ssize_t jiffies_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	return sprintf(buf, "%lu\n", jiffies);
}

static ssize_t jiffies_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	return -EINVAL;
}

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	down(&foo_sem);
	strncpy(buf, foo_data, foo_len);
	up(&foo_sem);

	return foo_len;
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	if (count > PAGE_SIZE)
		return -EINVAL;

	down(&foo_sem);
	strncpy(foo_data, buf, count);
	foo_len = count;
	up(&foo_sem);

	return count;
}

static struct kobj_attribute id_attr = __ATTR(id, 0664, id_show, id_store);
static struct kobj_attribute jiffies_attr = __ATTR(jiffies, 0444, jiffies_show, jiffies_store);
static struct kobj_attribute foo_attr = __ATTR(foo, 0644, foo_show, foo_store);

static struct attribute *attrs[] = {
	&id_attr.attr,
	&jiffies_attr.attr,
	&foo_attr.attr,
	NULL,
};

static struct attribute_group eudypt_group = {
	.attrs = attrs,
};

static int __init my_init(void)
{
	int retval;

	eudypt_kobj = kobject_create_and_add("eudyptula", kernel_kobj);
	if (!eudypt_kobj)
		return -ENOMEM;

	retval = sysfs_create_group(eudypt_kobj, &eudypt_group);
	if (retval)
		kobject_put(eudypt_kobj);

	pr_debug("Sysfs module loaded.");
	return 0;
}

static void __exit my_exit(void)
{
	kobject_put(eudypt_kobj);
	pr_debug("Sysfs module unloaded.\n");
}

module_init(my_init);
module_exit(my_exit);

