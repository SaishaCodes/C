#include<stdio.h>
#include<stdlib.h>
#define max 5
int top = -1;

struct Stack{
    int stack[max];
    int data;
}

void push(){
    int data;
    if(top == max -1){
        printf("Stack is Full");
    }
    else{
        printf("Enter the element: ");
        scanf("%d", &val);
        top = top + 1;
        stack[top] = data;
    }
}

void pop{
    if(top == -1){
        printf("Stack is Empty");
    }
    else{
        printf("Deleted element: %d", stack[top]);
        top = top - 1;
    }
}

void display{
    int i;
    if(top == -1){
        printf("stack undrflow");
    }
    else{
        printf("stack elements are: ");
        for(i = 0; i<top; i++){
            printf("%d", stack[i]);
        }
    }
}

