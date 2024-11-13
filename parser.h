#include <stdio.h>
#include <stdlib.h>

//Stack Definition
typedef struct 
{
    //Array to store stack elements
    int arr[100];
    // Indez of the top element in the stack
    int top; 
} Stack; 


typedef enum
{
    A, // value 0
    B, // value 1
    C, // value 2
    D, // value 3
    E, // value 4
    F, // value 5
    G // value 6
} NONTERMINAL;


extern const char ACTION [][11];
extern const char GOTO [][7]; 


extern const char ruleSize [13];
extern const NONTERMINAL ruleTransform [13];


void initialize(Stack *stack);

int isEmpty(Stack *stack);

int isFull(Stack *stack);

void push(Stack *stack, int state);

void pop(Stack *stack);

int peek(Stack *stack);