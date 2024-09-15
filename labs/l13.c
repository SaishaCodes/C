#include<stdio.h>
#define MAX 10
int stack[MAX];
int top = -1;

int isEmpty(){
    return top == -1;
}

int isFull(){
    return top == MAX - 1;
}

void push(int data){
    if(isFull()){
        printf("Stack Overflow");
        return;
    }
    stack[top++] = data;
}

int pop(){
    if(isEmpty()){
        printf("Stack Underflow!");
        return -1;
    }
    return stack[top--];
}

void cal(){
    int data[MAX];
    int i = 0;
    while(!isEmpty()){
        data[++i] = pop();
    }
    int sum = 0;
    for(int j = 0; j< i; j++){
        sum += data[j];
    }

    float avg = (float) sum / i;
    int min = data[0];
    int max = data[0];
    for(int j =1; j< i; j++){
        if(data[j] > max){
            max = data[j];
        }
        if(data[j] < min){
            min = data[j];
        }
    }
    push(min);
    push(max);
    push((int)avg);
    push(sum);

    for(int j = i -1; j>= 0; j--){
        push(data[j]);
    }
}

int main() {
    int num;

    printf("Enter 5 integer numbers:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &num);
        push(num);
    }

    cal();

    printf("Modified stack:\n");
    while (!isEmpty()) {
        printf("%d\n", pop());
    }

    return 0;
}