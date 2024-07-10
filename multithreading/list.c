// list.c
#include <stdlib.h>
#include "list.h"

void list_init(list_t *list) {
    list->head = NULL;
    list->tail = NULL;
}

void list_add(list_t *list, void *data) {
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    new_node->next = NULL;

    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
}

