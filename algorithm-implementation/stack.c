#include "stack.h"

struct Stack* createStack(unsigned capacity)
{
    if(capacity < MIN_STACK_SIZE) capacity = MIN_STACK_SIZE;

    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack)
{
    return stack->top >= stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top < 0;
}

void expand(struct Stack* stack) {
    int* newArray = (int*)malloc(stack->capacity * EXPAND_MULTIPLIER * sizeof(int));
    memcpy(newArray, stack->array, stack->capacity * sizeof(int));
    free(stack->array);
    stack->array = newArray;
    stack->capacity *= EXPAND_MULTIPLIER;
}

void shrink(struct Stack* stack) {
    if(stack->capacity <= MIN_STACK_SIZE) return;

    int* newArray = (int*)malloc(stack->capacity * SHRINK_MULTIPLIER  * sizeof(int));
    memcpy(newArray, stack->array, stack->capacity * sizeof(int));
    free(stack->array);
    stack->array = newArray;
    stack->capacity *= SHRINK_MULTIPLIER;
}

void push(struct Stack* stack, int item)
{
    if (isFull(stack)) {
        expand(stack);
    }
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack)) {
        return 0;
    }

//    if(stack->capacity / stack->top + 1 < 4) {
//        shrink(stack);
//    }

    return stack->array[stack->top--];
}

void freeStack(struct Stack* stack) {
    free(stack->array);
    free(stack);
}

