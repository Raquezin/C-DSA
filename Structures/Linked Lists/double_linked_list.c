#include "stdio.h"
#include "stdlib.h"
#include <stdarg.h>

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
} node;

node *add_element(node *element, int count, ...) {
    node *new;
    int val;

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        val = va_arg(args, int);
        new = (node *)malloc(sizeof(node));
        if (!new) {
            perror("malloc failed");
            exit(1);
        }

        if (element == NULL) {
            new -> next = new -> prev = NULL;
        } else { 
            if (element->next != NULL) {
                    element->next->prev = new;
                }
                new->next = element->next;
                new->prev = element;
                element->next = new;
        }  
        new->val = val;
        element = new;
    }
    va_end(args);
    return new;
}

void delete_element(node *element) {
    if (element == NULL) {
        return;
    }
    
    if (element->prev == NULL) {
        element->next->prev = NULL;
    } else if (element->next == NULL) {
            element->prev->next = NULL;
    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;
    }
 
    free(element);
}

void free_double_linked_list(node *element) {
    if (element == NULL) {
        return;
    }
    
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
}

void show_double_linked_list(node *element) {
    if (element == NULL) {
        return;
    }

    node *prev;
    while (element != NULL) {
        prev = element;
        element = element -> prev;
    }

    element = prev;
    prev = NULL;

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
    node *a = add_element(NULL, 5, 1, 3, 4, 5, 6);  

    show_double_linked_list(a);
    
    node *b = add_element(a, 1, 2);
    
    b = a->prev;
    show_double_linked_list(a);
    delete_element(a->next);
    delete_element(a);
    a = NULL;

    show_double_linked_list(b);

    node *c = add_element(b, 1, 51);
    node *d = add_element(c, 1, 52);
    node *e = add_element(d, 1, 53);
    add_element(c, 1, 54);
    node *f = add_element(e, 1, 55);
    node *g = add_element(f, 1, 56);
    
    show_double_linked_list(b);
    free_double_linked_list(b);
    return 0;
}
