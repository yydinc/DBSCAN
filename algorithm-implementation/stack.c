#include "stack.h"

struct ResizingStack* createStack(unsigned capacity)
{
    if(capacity < MIN_STACK_SIZE) capacity = MIN_STACK_SIZE;

    struct ResizingStack* stack = (struct ResizingStack*)malloc(sizeof(struct ResizingStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

struct ResizingStack* createStackFromArray(int* array, unsigned capacity) {
    struct ResizingStack* stack = (struct ResizingStack*)malloc(sizeof(struct ResizingStack));
    stack->capacity = capacity;
    stack->top = capacity - 1;
    stack->array = array;
    return stack;
}

int isFull(struct ResizingStack* stack)
{
    return stack->top >= stack->capacity - 1;
}

int isEmpty(struct ResizingStack* stack)
{
    return stack->top < 0;
}

void expand(struct ResizingStack* stack) {
    stack->array = (int*) realloc(stack->array, stack->capacity * EXPAND_MULTIPLIER  * sizeof(int));
    if(stack->array == NULL) {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }

    stack->capacity *= EXPAND_MULTIPLIER;
}

void shrink(struct ResizingStack* stack) {
    if(stack->capacity <= MIN_STACK_SIZE) return;

    stack->array = (int*) realloc(stack->array, stack->capacity * SHRINK_MULTIPLIER  * sizeof(int));

    if(stack->array == NULL) {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }

    stack->capacity *= SHRINK_MULTIPLIER;
}

void push(struct ResizingStack* stack, int item)
{
    if (isFull(stack)) {
        expand(stack);
    }
    stack->array[++stack->top] = item;
}

int pop(struct ResizingStack* stack)
{
    if (isEmpty(stack)) {
        return 0;
    }

    if(((float)stack->top + 1) / stack->capacity < 0.25) {
        shrink(stack);
    }

    return stack->array[stack->top--];
}

void freeStack(struct ResizingStack* stack) {
    free(stack->array);
    free(stack);
}

