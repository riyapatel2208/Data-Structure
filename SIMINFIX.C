#include <stdio.h>
#include <stdlib.h>
#define MAX 50

void push(char [], int *, char);
char pop(char [], int *);
char peek(char [], int);
int precedence(char);
void infixToPostfix(char [], char []);

void main()
{
    char infix[MAX], postfix[MAX];
    clrscr();
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    getch();
}
void push(char stack[], int *top, char val)
{
    if (*top >= MAX - 1)
    {
	printf("Stack overflow\n");
	return;
    }
    stack[++(*top)] = val;
}

char pop(char stack[], int *top)
{
    if (*top <= -1)
    {
	printf("Stack underflow\n");
	return '\0';
    }
    return stack[(*top)--];
}

char peek(char stack[], int top)
{
    if (top <= -1)
    {
	return '\0';
    }
    return stack[top];
}

int precedence(char op)
{
    switch (op) {
	case '+':
	case '-':
	    return 1;
	case '*':
	case '/':
	    return 2;
	default:
	    return 0;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    char stack[MAX];
    int top = -1,i;
    int k = 0;
    for (i = 0; infix[i] != '\0'; i++)
    {
	if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '0' && infix[i] <= '9'))
	{
	    postfix[k++] = infix[i];
	}
	else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
	{
	    while (top != -1 && precedence(peek(stack, top)) >= precedence(infix[i]))
	    {
		postfix[k++] = pop(stack, &top);
	    }
	    push(stack, &top, infix[i]);
	}
    }
    while (top != -1)
    {
	postfix[k++] = pop(stack, &top);
    }

    postfix[k] = '\0';
}