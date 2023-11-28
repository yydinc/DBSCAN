#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// An implementation of the expanding (dynamic) Stack data structure

#define MIN_STACK_SIZE 10
#define EXPAND_MULTIPLIER 2
#define SHRINK_MULTIPLIER 0.5

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity);

void freeStack(struct Stack* stack);

int isFull(struct Stack* stack);

int isEmpty(struct Stack* stack);

void push(struct Stack* stack, int item);

int pop(struct Stack* stack);