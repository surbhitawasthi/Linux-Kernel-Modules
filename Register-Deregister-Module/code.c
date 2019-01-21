#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init code_init(void) {
    printk(KERN_INFO "Module has been loaded\n");
    return 0;
}

static void __exit code_exit(void) {
	printk(KERN_INFO "Module has been unloaded\n");
}

module_init(code_init);
module_exit(code_exit);
