#include "stdio.h"
#include "stdlib.h"

struct node;

typedef struct list {
    struct node *head;
    struct node *tail;
    int size;
} t_list;

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
    t_list *data;
} node;

t_list *init_plista(){
    t_list *plista = (t_list*)malloc(sizeof(t_list));
    if (!plista) {
        perror("malloc failed");
        exit(1);
    }
    plista->size = 0;
    plista->head = plista->tail = NULL;
    return plista;
}

node *add_element(node *element, int val) {
    t_list *plista;
    node *new = (node *)malloc(sizeof(node));
    if (!new) {
        perror("malloc failed");
        exit(1);
    }

    if (element == NULL) {
        plista = init_plista();
        plista -> head = plista -> tail = new;
        new -> next = new -> prev = NULL;
    } else { 
        plista = element->data;
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
    new->data = plista;
    plista->size += 1;
    return new;
}

void delete_element(node *element) {
    if (element == NULL) {
        return;
    }
    
    t_list *plista = element->data;
    if (element == plista->head) {
        plista->head = element->next;
        if (plista->head != NULL){
            plista->head->prev = NULL;
        }
    } else if (element == plista->tail) {
        plista->tail = element->prev;
        if (plista->tail != NULL){
            plista->tail->next = NULL;
        }
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

void free_double_linked_list(node *element) {
    if (element == NULL) {
        return;
    }
    
    t_list *plista = element->data;
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

void show_double_linked_list(node *element) {
    if (element == NULL) {
        return;
    }
    element = element->data->head;

    printf("head: %p, tail: %p, size:%d\n", 
    (void*)element->data->head, 
    (void*)element->data->tail, 
    element->data->size);
    
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
    node *a = add_element(NULL, 1);    
    node *b = add_element(a, 2);

    show_double_linked_list(a);
    t_list *data = a->data;
    delete_element(data->head);
    show_double_linked_list(data->head);
    delete_element(data->head);
    a = b = NULL;
    data = NULL;

    node *c = add_element(NULL, 3);
    node *d = add_element(c, 3);
    node *e = add_element(d, 4);
    add_element(c, 50);
    node *f = add_element(e, 5);
    node *g = add_element(f, 6);
    
    show_double_linked_list(c);
    free_double_linked_list(f);
    return 0;
}
