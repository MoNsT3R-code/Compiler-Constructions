#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100


int stack[MAX];
int top = -1;

char input[MAX];

char action[8][5][10] = {
    {"Shift2", "",  "",  "Shift3", ""},  
    {"",   "",  "",  "",   "accept"},
    {"Shift2", "",  "",  "Shift3", ""},   
    {"",   "Shift5","",  "",   ""},  
    {"",   "Shift6","Shift7","",   ""},  
    {"Reduce3", "Reduce3","Reduce3","Reduce3","Reduce3"}, 
    {"Reduce1", "Reduce1","Reduce1","Reduce1","Reduce1"}, 
    {"Reduce2", "Reduce2","Reduce2","Reduce2","Reduce2"}  
};

int goTo[8][1] = {
    {1}, {-1}, {4}, {-1}, {-1}, {-1}, {-1}, {-1}
};


char *productions[] = {
    "S->S",     
    "S->aSb",   
    "S->aSc",   
    "S->db"     
};


int getCol(char c) {
    switch(c) {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case '$': return 4;
    }
    return -1;
}


void push(int val) {
    stack[++top] = val;
}


void pop(int n) {
    top -= n;
}

int main() {
    int i = 0;
    int state = 0;
    
    printf("Enter input string (end with $): ");
    scanf("%s", input);

    push(0);

    printf("\nStack\tInput\tAction\n");

    while(1) {
        state = stack[top];
        char sym = input[i];
        int col = getCol(sym);

        char act[10];
        strcpy(act, action[state][col]);

        for(int j = 0; j <= top; j++)
            printf("%d", stack[j]);

        printf("\t%s\t", input + i);

        if(strcmp(act, "accept") == 0) {
            printf("accept\n");
            break;
        }

        else if(act[0] == 'S') {
            int next = atoi(&act[1]);
            printf("Shift %d\n", next);

            push(next);
            i++;
        }

        else if(act[0] == 'R') {
            int rule = atoi(&act[1]);
            printf("Reduce by %s\n", productions[rule]);

            int len = strlen(productions[rule]) - 3; 
            pop(len);

            int prev = stack[top];
            int gotoState = goTo[prev][0];

            push(gotoState);
        }

        else {
            printf("Rejected\n");
            break;
        }
    }

    return 0;
}
