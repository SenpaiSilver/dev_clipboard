#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>

char* membuffer = NULL;
static ssize_t membuffsize = 0;

ssize_t clipboard_write(struct file* file, const char* buf, size_t count, loff_t* ppos)
{
#ifdef DEBUG
	unsigned int i;
	
	printk("%d\t%d\n", *ppos, count);
	printk("Data: \n");
	for (i = 0; i < count - 1; ++i)
		printk("%c", buf[i]);
	printk("### END ###\n");
#endif
	if (*ppos != 0)
		return (0);
	if (*ppos == 0)
		membuffsize = count;
	else
		membuffsize += count;
	if (membuffer != NULL)
		kfree(membuffer);
	if ((membuffer = kmalloc((membuffsize + 1) * sizeof(membuffer), GFP_USER)) == NULL)
		return (-EINVAL);
	membuffer = memcpy(membuffer + (membuffsize - count), buf, count);
	membuffer[membuffsize] = '\0';
	*ppos += count;
#ifdef DEBUG
	printk("Current clipboard data: \n%s\n### END ###\n", membuffer);
#endif
	return (count);
}

ssize_t clipboard_read(struct file* file, char* buf, size_t count, loff_t* ppos)
{
	unsigned int len = membuffer == NULL ? 0 : strlen(membuffer);

#ifdef DEBUG
	printk("No buffer in clipboard.");
#endif
	if (*ppos != 0)
		return (0);
	if (copy_to_user(buf, membuffer, len))
		return (-EINVAL);
	*ppos = len;
	return ((ssize_t)*ppos);
}

void free_clipboard_buffer(void)
{
	if (membuffer != NULL)
		kfree(membuffer);
}
