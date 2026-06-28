#include "pc_linked_list.h"
#include <linux/gfp_types.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/syscalls.h>

static pc_list_node *pc_list = NULL;

pc_list_node *create_pc_list_node(unsigned char *url){
    pc_list_node *list = kmalloc(sizeof(pc_list_node), GFP_KERNEL);

    if (list == NULL) return NULL;

    list->next = NULL;
    list->url = url;

    return list;
}

int destroy_pc_list_node(pc_list_node *pc_node){
    kfree(pc_node->url);
    kfree(pc_node);
    
    return 0;
}

int pc_list_add(unsigned char *url){
    if(pc_list_contains(url)) return 0;

    unsigned char *kernel_url = kstrdup(url, GFP_KERNEL);

    // TODO: lidar com possível incapacidade de alocar na função create_pc_list_node
    if(pc_list == NULL){
        pc_list = create_pc_list_node(kernel_url);
        return 0;
    }

    pc_list_node *current_node = pc_list;
    while(current_node->next != NULL) current_node = current_node->next;

    current_node->next = create_pc_list_node(kernel_url);

    return 0;
}

int pc_list_remove(unsigned char *url){
    
    if(pc_list == NULL) {
        return 0;
    }

    pc_list_node *current_node = pc_list;

    if(strcmp(url, current_node->url) == 0){
        pc_list = current_node->next;
        destroy_pc_list_node(current_node);
        return 0;
    }

    while(current_node->next != NULL){
        if(strcmp(url, current_node->next->url) == 0){
            pc_list_node *removed = current_node->next;
            current_node->next = removed->next;
            destroy_pc_list_node(removed);
            return 0;
        }
        current_node = current_node->next;
    }

    return 0;
}

bool pc_list_contains(unsigned char *url){
    if(pc_list == NULL) return false;

    pc_list_node *current_node = pc_list;

    while(current_node != NULL){
        if(strcmp(current_node->url, url) == 0){
            return true;
        }

        current_node = current_node->next;
    }

    return false;
}