#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include "pc_linked_list.h"

SYSCALL_DEFINE2(parent_control_change, unsigned long, remove, unsigned char __user *, url){

    int ret;
    unsigned char *safe_url = strndup_user(url, PC_STR_BUF_LEN);
    
    if(remove){
        ret = pc_list_remove(safe_url);
    } else {
        ret = pc_list_add(safe_url);
    }

    kfree(safe_url);

    return ret;
}

SYSCALL_DEFINE1(parent_control_check, unsigned char __user *, url){
    unsigned char *safe_url = strndup_user(url, PC_STR_BUF_LEN);

    bool ret = pc_list_contains(safe_url);

    kfree(safe_url);

    return ret;
}