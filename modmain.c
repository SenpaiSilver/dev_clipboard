#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>

#include "clipboard.h"

static const struct file_operations clipboard_fops = {
	.owner = THIS_MODULE,
	.read = &clipboard_read,
	.write = &clipboard_write
//.open = &clipboard_open,
//.close = &clipboard_close
};

static struct miscdevice clipboard_dev = {
	MISC_DYNAMIC_MINOR,
	"clipboard",
	&clipboard_fops
};

static int __init clipboard_init(void)
{
	int ret;
	printk("Starting clipboard...\n");

	ret = misc_register(&clipboard_dev);
	if (ret)
		printk(KERN_ERR "Unable to register clipboard misc device\n");
	return (ret);
}

static void __exit clipboard_exit(void)
{
	printk("Ending clipboard...\n");
	misc_deregister(&clipboard_dev);
}

module_init(clipboard_init);
module_exit(clipboard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SenpaiSilver");
MODULE_DESCRIPTION("Clipboard device.");
MODULE_VERSION("clipboard");
