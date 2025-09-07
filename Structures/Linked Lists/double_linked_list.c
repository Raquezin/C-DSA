#include "stdio.h"
#include "stdlib.h"

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
} node;

typedef struct list {
    node *head;
    node *tail;
    int size;
} t_list;

node *add_element(node *element, int val, t_list *plista) {
    node *new = (node *)malloc(sizeof(node));
    if (!new) {
        perror("malloc failed");
        exit(1);
    }

    if (plista->size == 0) {
        plista -> head = plista -> tail = new;
        new -> next = new -> prev = NULL;
    } else { 
        if (element == plista->tail) {
                plista->tail = new;
            } else {
                element->next->prev = new;
            }
            new->next = element->next;
            new->prev = element;
            element->next = new;
    }
        
    new->val = val;
    plista->size += 1;
    return new;
}

void delete_element(node *element, t_list *plista) {
    if (element == plista->head) {
        plista->head = element->next;
        plista->head->prev = NULL;
    } else if (element == plista->tail) {
        plista->tail = element->prev;
        plista->tail->next = NULL;
    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;
    }
 
    plista->size -= 1;
    free(element);

    if (plista->size == 0) {
        printf("Lista vacía\n");
        plista->head = plista->tail = NULL;
    }
}

void free_double_linked_list(node *element, t_list *plista) {
    node *current = element;
    node *past = element->prev;
    
    while (current != NULL) {
        node *next = current->next;
        free(current);
        current = next;
    }

    while (past != NULL) {
        node *next = past->prev;
        free(past);
        past = next;    
    }

    free(plista);
}

void show_double_linked_list(t_list *plista) {
    node *element;
    if (plista->size > 0) {
        element = plista->head;
    } else {
        perror("La lista no tiene elementos");
    }
    
    printf("head: %p, tail: %p, size:%d\n", 
    (void*)plista->head, 
    (void*)plista->tail, 
    plista->size);
    
    printf("Start\n");
    while (element != NULL) {
        printf("prev: %p, current: %p, next:%p, val:%d\n", 
            (void*)element->prev, (void*)element, (void*)element->next, element->val
        );
        element = element->next;
    }
    printf("End\n");
}

int main() {
    t_list *plista = (t_list *)malloc(sizeof(t_list));
    if (!plista) {
        perror("malloc failed");
        exit(1);
    }

    plista->head = NULL;
    plista->tail = NULL;
    plista->size = 0;

    node *a = add_element(NULL, 1, plista);
    node *b = add_element(a, 2, plista);
    node *c = add_element(b, 3, plista);
    node *d = add_element(c, 4, plista);
    add_element(a, 50, plista);
    node *e = add_element(d, 5, plista);
    node *f = add_element(e, 6, plista);

    show_double_linked_list(plista);
    
    delete_element(plista->head, plista);
    delete_element(plista->tail, plista);
    delete_element(plista->head->next, plista);

    show_double_linked_list(plista);
    free_double_linked_list(e, plista);

    return 0;
}
