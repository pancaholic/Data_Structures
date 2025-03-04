#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// PUTRA PANCA PRASETYA
// 2502006726

// INFIX TO POSTFIX

struct Stack
{
    char value[MAX_SIZE];
    int top;
};

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char ch)
{
    if (isFull(s))
    {
        printf("Stack Is Full\n");
        return;
    }
    // increment top lalu di push ke stack
    s->value[++(s->top)] = ch;
}

char pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("The Stack Is Empty\n");
        return '\0';
    }
    return s->value[(s->top)--];
}

// Mengambil top
char topValue(Stack *s)
{
    if (isEmpty(s))
    {
        return '\0';
    }
    return s->value[s->top];
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Get precedence of an operator
int precedence(char ch)
{
    switch (ch)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void infixToPostfix(char *infix, char *postfix)
{
    struct Stack s;
    // Set top menjadi -1 (NULL)
    s.top = -1;

    int i = 0, j = 0;

    // Loop untuk cek setiap karakter hingga end of string.
    while (infix[i] != '\0')
    {
        char ch = infix[i];

        // Cek Operand
        if (isalnum(ch))
        {
            // add ke postfix
            postfix[j++] = ch;
        }
        // Jika karakter adalah open bracket'(', push ke stack
        else if (ch == '(')
        {
            push(&s, ch);
        }
        // Jika karakter adalah close bracket')', pop sampai open bracket '('
        else if (ch == ')')
        {
            while (!isEmpty(&s) && topValue(&s) != '(')
            {
                // add ke postfix
                postfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && topValue(&s) == '(')
            {
                pop(&s); // Pop '(' dari stack
            }
        }
        // Cek Operator
        else if (isOperator(ch))
        {
            while (!isEmpty(&s) && precedence(topValue(&s)) >= precedence(ch))
            {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }

        i++;
    }

    // Pop semua ke postfix string
    while (!isEmpty(&s))
    {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Input Infix: ");
    fgets(infix, MAX_SIZE, stdin);

    infixToPostfix(infix, postfix);

    printf("Postfix    : %s\n", postfix);

    return 0;
}