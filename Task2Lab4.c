#include <stdio.h>
#include <string.h>

int S();
int X();
int Z();

char expr[100];
int count;

int main()
{
    count = 0;

    printf("\nRecursive descent parsing for grammar:\n");
    printf("S -> rXd | rZd\nX -> oa | ea\nZ -> ai\n");

    printf("\nEnter string: ");
    fgets(expr, 100, stdin);

    // Remove newline
    expr[strcspn(expr, "\n")] = '\0';

    if(S())
    {
        if(expr[count] == '\0')
            printf("\nString is accepted\n");
        else
            printf("\nString is not accepted\n");
    }
    else
    {
        printf("\nString is not accepted\n");
    }

    return 0;
}

// S → rXd | rZd
int S()
{
    if(expr[count] == 'r')
    {
        count++;

        int temp = count;

        // Try X
        if(X())
        {
            if(expr[count] == 'd')
            {
                count++;
                return 1;
            }
        }

        // Backtrack
        count = temp;

        // Try Z
        if(Z())
        {
            if(expr[count] == 'd')
            {
                count++;
                return 1;
            }
        }
    }

    return 0;
}

// X → oa | ea
int X()
{
    if(expr[count] == 'o' && expr[count+1] == 'a')
    {
        count += 2;
        return 1;
    }
    else if(expr[count] == 'e' && expr[count+1] == 'a')
    {
        count += 2;
        return 1;
    }

    return 0;
}

// Z → ai
int Z()
{
    if(expr[count] == 'a' && expr[count+1] == 'i')
    {
        count += 2;
        return 1;
    }

    return 0;
}
