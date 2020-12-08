#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct personal_list_head {
struct personal_list_head *next;
ktime_t time;
};

MODULE_AUTHOR("Halatsyn Zakhar IO-82");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct personal_list_head *header;

static uint times = 1;
module_param(times,uint,S_IRUGO);
MODULE_PARM_DESC(times, "The amount of times to print hello world");

static int __init initter(void)
{
  uint i = 0;
  struct personal_list_head *first_variable, *second_variable;

  printk(KERN_INFO "times: %d\n", times);

  if(times == 0) {
    printk(KERN_WARNING "Times = 0");
  }else if(times >=5 && times <= 10) {
    printk(KERN_WARNING "Times between 5 and 10");
  } else if(times > 10) {
    printk(KERN_ERR "Times > 10");
    return -EINVAL;
  }

  header = kmalloc(sizeof(struct personal_list_head *), GFP_KERNEL);
  first_variable = header;
  
  for(i = 0; i < times; i++){
  first_variable->next = kmalloc(sizeof(struct personal_list_head), GFP_KERNEL);
    first_variable->time = ktime_get();
    pr_info("Hello World!");
    second_variable = first_variable;
    first_variable = first_variable->next;
    }
    if (times != 0) {
      kfree(second_variable->next);
      second_variable->next = NULL;

  }
  printk(KERN_INFO "times: %d\n", times);
  return 0;
}

static void __exit exitter(void)
{
  struct personal_list_head *variable;
  while (header != NULL && times != 0) {
    variable = header;
    pr_info("Time : %lld", variable->time);
    header = variable->next;
    kfree(variable);
  }
  if (times == 0) {
    pr_info("Time is 0 because print wasn't used");
  }
  pr_info("");
}

module_init(initter);
module_exit(exitter);
