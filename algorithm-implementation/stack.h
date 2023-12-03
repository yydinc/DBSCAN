#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// An implementation of the resizing stack data structure

#define MIN_STACK_SIZE 10
#define EXPAND_MULTIPLIER 2
#define SHRINK_MULTIPLIER 0.5

struct ResizingStack {
    int top;
    unsigned capacity;
    int* array;
};

struct ResizingStack* createStackFromArray(int* array, unsigned capacity);

struct ResizingStack* createStack(unsigned capacity);

void freeStack(struct ResizingStack* stack);

int isFull(struct ResizingStack* stack);

int isEmpty(struct ResizingStack* stack);

void push(struct ResizingStack* stack, int item);

int pop(struct ResizingStack* stack);