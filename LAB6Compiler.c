/*Task 1:*/

// E → E + E
// E → E * E
// E → ( E )
// E → id

/*
Terminals:
id, +, *, (, ), $

Precedence Table

	id	+	*	(	)	$
id		>	>		>	>
+	<	>	<	<	>	>
*	<	>	>	<	>	>
(	<	<	<	<	=	
)		>	>		>	>
$	<	<	<	<		  
*/
/*Task 2*/

#include <stdio.h>
#include <string.h>

#define SIZE 100

char stack[SIZE];
char input[SIZE];
int top = -1;
int ip = 0;

char precedence(char a, char b) {

    if (a == 'i' && (b == '+' || b == '*' || b == ')' || b == '$')) return '>';
    if ((a == '+' || a == '*' || a == '(' || a == '$') && b == 'i') return '<';

    if (a == '+' && b == '+') return '>';
    if (a == '+' && b == '*') return '<';
    if (a == '*' && b == '+') return '>';
    if (a == '*' && b == '*') return '>';

    if (a == '(' && b == ')') return '=';
    if (a == '(') return '<';

    if (b == '(') return '<';

    if (b == ')') return '>';
    if (b == '$') return '>';

    if (a == ')') return '>';
    if (a == '$') return '<';

    return '?';  
}

char getTopTerminal() {
    for (int i = top; i >= 0; i--) {
        if (stack[i] != 'E')
            return stack[i];
    }
    return '$';
}

void printStack() {
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int reduce() {

    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        printf("Reduce E→id\n");
        return 1;
    }

    if (top >= 2 && stack[top] == 'E' &&
        (stack[top - 1] == '+' || stack[top - 1] == '*') &&
        stack[top - 2] == 'E') {

        char op = stack[top - 1];
        top -= 2;
        stack[top] = 'E';

        if (op == '+')
            printf("Reduce E→E+E\n");
        else
            printf("Reduce E→E*E\n");

        return 1;
    }

    if (top >= 2 && stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(') {

        top -= 2;
        stack[top] = 'E';
        printf("Reduce E→(E)\n");
        return 1;
    }

    return 0;
}

int main() {

    char temp[SIZE];

    printf("Enter input (use id, +, *, (), end with $): ");
    fgets(temp, SIZE, stdin);

    int j = 0;
    for (int i = 0; temp[i] != '\0'; i++) {

        if (temp[i] == 'i' && temp[i + 1] == 'd') {
            input[j++] = 'i';
            i++; 
        }
        else if (temp[i] != ' ' && temp[i] != '\n') {
            input[j++] = temp[i];
        }
    }
    input[j] = '\0';

    stack[++top] = '$';

    printf("\nStack\t\tInput\t\tAction\n");

    while (1) {

        printStack();
        printf("\t\t%s\t\t", &input[ip]);

        char a = getTopTerminal();
        char b = input[ip];

        if (a == '$' && b == '$' && top == 1 && stack[top] == 'E') {
            printf("Accept\n");
            break;
        }

        char rel = precedence(a, b);

        if (rel == '<' || rel == '=') {
            stack[++top] = input[ip++];
            printf("Shift\n");
        }

        else if (rel == '>') {
            if (!reduce()) {
                printf("Error\n");
                break;
            }
        }
        else {
            printf("Error\n");
            break;
        }
    }

    return 0;
}












