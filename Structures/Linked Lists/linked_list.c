#include "stdio.h"
#include "stdlib.h"

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct list {
    node *head;
    int size;
} t_list;


node *add_element(node *element, int val, t_list *plista) {
    node *new = (node *)malloc(sizeof(node));
    if (!new) {
        perror("malloc failed");
        exit(1);
    }
    
    new->val = val;
    new->next = element->next;
    element->next = new;
    plista->size += 1;
    return new;
}

void delete_by_value(int val, t_list *plista) {
    node *element = plista->head;
    node *prev = element;

    while (element != NULL) {
        if (element->val == val) {
            if (element == plista->head) {
                plista->head = element->next;
            }
            prev->next = element->next;
            free(element);
            break;
        } else {
            prev = element;
            element = element->next;
        }
    }
    plista->size -= 1;
}

void delete_next(node *element, t_list *plista) {
    node *delete = element->next;
    if (delete != NULL){
        element->next = delete->next;
        plista->size -= 1;
        free(delete);
    }

}

void free_linked_list(t_list *plista) {
    node *element = plista->head;
    
    while (element != NULL) {
        node *next = element->next;
        free(element);
        element = next;
    }
    free(plista);
}

void show_linked_list(t_list *plista) {
    node *element;

    if (plista->size > 0) {
        element = plista->head;
    } else {
        perror("La lista no tiene elementos");
    }
    
    printf("head: %p, size:%d\n", 
    (void*)plista->head, 
    plista->size);

    printf("Start\n");
    while (element != NULL) {
        printf("current: %p, next:%p, val:%d\n", 
            (void*)element, (void*)element->next, element->val
        );
        element = element->next;
    }
    printf("End\n");
}

int main() {
    t_list *plista = (t_list *)malloc(sizeof(t_list));
    node *a = (node *)malloc(sizeof(node));
    if (!a || !plista) {
        perror("malloc failed");
        exit(1);
    }
    a->next = NULL;
    a->val = 1;
    plista->head = a;
    plista->size = 1;

    node *b = add_element(a, 2, plista);
    node *c = add_element(b, 3, plista);
    node *d = add_element(c, 4, plista);
    add_element(a, 50, plista);
    node *e = add_element(d, 5, plista);
    node *f = add_element(e, 6, plista);

    show_linked_list(plista);
    
    delete_by_value(50, plista);
    delete_by_value(1, plista);
    delete_next(d, plista);
    delete_next(f, plista);

    show_linked_list(plista);
    free_linked_list(plista);

    return 0;
}
