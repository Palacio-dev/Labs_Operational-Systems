#include <linux/syscalls.h>
#include "pc_linked_list.h"

SYSCALL_DEFINE2(parent_control_change, unsigned long, remove, unsigned char __user *, url){
    if(remove){
        return pc_list_remove(url);
    }

    return pc_list_add(url);
}

SYSCALL_DEFINE1(parent_control_check, unsigned char __user *, url){
    return pc_list_contains(url);
}