#include "pc_linked_list.h"
#include <linux/syscalls.h>

static pc_list_node *pc_list = NULL;

pc_list_node *create_pc_list_node(){
    pc_list_node *list = kmalloc(sizeof(pc_list_node), GFP_KERNEL);

    list->next = NULL;
    list->url = NULL;

    return list;
}

int pc_list_add(unsigned char *url){
    size_t url_size = strlen(url);
    int ret;

    if(pc_list_contains(url)) return 0;

    unsigned char *kernel_url = kmalloc(url_size * sizeof(unsigned char), GFP_KERNEL);
    ret = copy_from_user(kernel_url, url, url_size * sizeof(unsigned char));

    // TODO: lidar com possível incapacidade de alocar na função create_pc_list_node
    if(pc_list == NULL){
        pc_list = create_pc_list_node();
        pc_list->url = kernel_url;
        return 0;
    }

    pc_list_node *current_node = pc_list;
    while(current_node->next != NULL) current_node = current_node->next;

    current_node->next = create_pc_list_node();
    current_node->next->url = kernel_url;

    return 0;
}

int pc_list_remove(unsigned char *url){
    if(pc_list == NULL) return 0;

    pc_list_node *current_node = pc_list;

    if(strcmp(url, current_node->url) == 0){
        pc_list = current_node->next;
        kfree(current_node);
        return 0;
    }

    while(current_node->next != NULL){
        if(strcmp(url, current_node->next->url) == 0){
            pc_list_node *removed = current_node->next;
            current_node->next = removed->next;
            kfree(removed);
            return 0;
        }
    }

    return 0;
}

bool pc_list_contains(unsigned char *url){
    if(pc_list == NULL) return false;

    pc_list_node *current_node = pc_list;

    while(current_node->next != NULL){
        if(strcmp(current_node->url, url) == 0){
            return true;
        }

        current_node = current_node->next;
    }

    return false;
}