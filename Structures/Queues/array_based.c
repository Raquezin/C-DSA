#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int queue[MAX_SIZE];
    int front;
    int rear;
} Queue;

int isFull(Queue *cola){
    return (cola->rear == MAX_SIZE - 1);
}

int isEmpty(Queue *cola){
    return (cola->front == -1);
}

void push(Queue *cola, int val) {
    if (isFull(cola)) {
        printf("The Queue is full\n");
        return;
    }

    if (cola->front == -1) {
        cola->front = 0;
    }

    cola->rear++;
    cola->queue[cola->rear] = val;
}

int pop(Queue *cola) {
    if (isEmpty(cola)) {
        return -1;
    }

    int val = cola->queue[cola->front];
    if (cola->front == cola->rear) {
        cola->front = -1;
        cola->rear = -1;
    } else {
        cola->front++;
    }

    return val;
}

void show(Queue *cola) {
    if (isEmpty(cola)) {
        return;
    }

    for (int i = cola->front; i < cola->rear; i++) {
        printf("%d ", cola->queue[i]);
    }
    printf("\n");
}


int main() {
    Queue cola;
    Queue *q = &cola;
    q->front = q->rear = -1;

    push(q, 1);
    push(q, 2);
    push(q, 3);
    push(q, 4);
    push(q, 5);
    
    show(q);

    pop(q);
    pop(q);

    show(q);
    return 0;
}