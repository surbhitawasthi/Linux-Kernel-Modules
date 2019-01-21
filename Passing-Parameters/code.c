#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
// This include is to let us include and use a parameter from
// the console.
#include <linux/moduleparam.h>

// create a variable to store param
int param_value = 0;
int param_array[3] = {0, 0, 0};
/*
 * register (macro)
 * module_param(name_var, type, permissions)
 * S_IRUSR
 * S_IWUSR
 * S_IXUSR
 * S_IWGRP
 * S_IRGRP
 *
 * Combination like this can be used: S_IRUSR|S_IWUSR
 * */

module_param(param_value, int, S_IRUSR|S_IWUSR);
module_param_array(param_array, int, NULL, S_IRUSR|S_IWUSR); // NULL -> can be change to number of parameters

void displayParam(void) 
{
	printk(KERN_INFO "parameter value = %d", param_value);
	printk(KERN_INFO "paramter array = %d, %d, %d", param_array[0], param_array[1], param_array[2]);
}

static int __init code_init(void) 
{
    printk(KERN_INFO "Module has been loaded\n");
    displayParam();
    return 0;
}

static void __exit code_exit(void) 
{
	printk(KERN_INFO "Module has been unloaded\n");
}

module_init(code_init);
module_exit(code_exit);
