#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>

ssize_t clipboard_write(struct file* file, char* buf, size_t count, loff_t* ppos)
{
	int len = 0;
	(void) len;

	return (len);
}

ssize_t clipboard_read(struct file* file, char* buf, size_t count, loff_t* ppos)
{
	char *testest = "Meh.\n";
	int len = strlen(testest);

	if (count < len)
		return (-EINVAL);
	if (*ppos != 0)
		return (0);
	if (copy_to_user(buf, testest, len))
		return (-EINVAL);
	*ppos = len;
	return (len);
}
