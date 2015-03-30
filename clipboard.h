#ifndef __CLIPBOARD_H__
#define __CLIPBOARD_H__

ssize_t clipboard_write(struct file* file, const char* buf, size_t count, loff_t* ppos);
ssize_t clipboard_read(struct file* file, char* buf, size_t count, loff_t* ppos);
void free_clipboard_buffer(void);

#endif
