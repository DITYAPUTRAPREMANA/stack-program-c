#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == MAX_SIZE - 1;
}

char peek() {
    if (!isEmpty()) {
        return stack[top];
    } else {
        exit(1);
    }
}

void push(char item) {
    if (isFull()) {
        exit(1);
    }
    stack[++top] = item;
}

char pop() {
    if (!isEmpty()) {
        return stack[top--];
    } else {
        exit(1);
    }
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

void infixToPostfix(char *expression) {
    int i, j;
    char *postfix = (char *)malloc(sizeof(char) * MAX_SIZE);
    j = 0;

    for (i = 0; expression[i] != '\0'; i++) {
        char item = expression[i];

        if (isalnum(item)) {
            postfix[j++] = item;
        } else if (item == '(') {
            push(item);
        } else if (item == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else {
            while (!isEmpty() && precedence(peek()) >= precedence(item)) {
                postfix[j++] = pop();
            }
            push(item);
        }
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
    strcpy(expression, postfix);
}

int main() {
    char input [MAX_SIZE];
    printf("+------------------------+\n");
    printf("|       TUGAS STACK      |\n");
    printf("+------------------------+\n");
    printf("add ifiks value:");
    scanf("%s", input);
  
    infixToPostfix(input);
    printf("+------------------------+\n");
    printf("|  CALCULATION RESULTS   |\n");
    printf("+------------------------+\n");
    printf("Postfiks value is: %s\n", input);

    return 0;
}
