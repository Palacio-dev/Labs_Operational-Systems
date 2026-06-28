#ifndef PC_LINKED_LIST_H
#define PC_LINKED_LIST_H

#include <linux/types.h>

typedef struct s_pc_list_node * pc_list_node_p;

typedef struct s_pc_list_node{
    unsigned char *url;
    pc_list_node_p next;
} pc_list_node;

pc_list_node *create_pc_list_node(void);

int pc_list_add(unsigned char *url);

int pc_list_remove(unsigned char *url);

bool pc_list_contains(unsigned char *url);

#endif