#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "textlandslide"

// mknod DEVICE_NAME c major minor

// The license type
MODULE_LICENSE("GPL"); 
  
// The author -- visible when you use modinfo 
MODULE_AUTHOR("Surbhit Awasthi"); 
  
// The description -- modinfo 
MODULE_DESCRIPTION("A character device LKM!"); 
  
// The version of the module 
MODULE_VERSION("0.1");

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int major;

static int __init code_init(void) {
	major = register_chrdev(0, DEVICE_NAME, &fops);
	
	if(major < 0) {
		printk(KERN_ALERT "text landslide: load failed\n");
		return major;
	}

	printk(KERN_INFO "text landslide module loaded: %d\n",major);
	return 0;
}

static void __exit code_exit(void) {
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "text landslide module has been unloaded\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "text landslide device opened\n");
	return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
	printk(KERN_INFO "Sorry, text landslide is read only\n");
	return -EFAULT;
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "text landslide device closed\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	int errors = 0;
	char *message = "linux kernel modules are cool... ";
	int message_len = strlen(message);

	errors = copy_to_user(buffer, message, message_len);

	return errors == 0 ? message_len : -EFAULT;
}

module_init(code_init);
module_exit(code_exit);
