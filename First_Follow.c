/*
Course: Compiler Construction Lab
Lab 5: FIRST & FOLLOW Sets
Name: Musfira Sehar
Roll No: 280048443
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][20];
char first[MAX][20];
char follow[MAX][20];
int n;

// Add symbol to set (no duplicates)
void add(char *set, char c) {
    for (int i = 0; set[i]; i++)
        if (set[i] == c) return;

    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
}

// Find index of non-terminal
int findIndex(char nt) {
    for (int i = 0; i < n; i++)
        if (productions[i][0] == nt)
            return i;
    return -1;
}

// FIRST
void computeFirst(int i) {

    for (int j = 2; productions[i][j]; j++) {

        char symbol = productions[i][j];

        if (symbol == '|') continue;

        // terminal
        if (!isupper(symbol)) {
            add(first[i], symbol);
            break;
        }

        // non-terminal
        int k = findIndex(symbol);
        if (k == -1) continue;

        computeFirst(k);

        for (int x = 0; first[k][x]; x++) {
            if (first[k][x] != 'e')
                add(first[i], first[k][x]);
        }

        break;
    }
}

// FOLLOW
void computeFollow(int i) {

    // Start symbol
    if (i == 0)
        add(follow[i], '$');

    for (int j = 0; j < n; j++) {

        for (int k = 2; productions[j][k]; k++) {

            if (productions[j][k] == productions[i][0]) {

                char next = productions[j][k + 1];

                if (next != '\0') {

                    if (!isupper(next)) {
                        add(follow[i], next);
                    } else {
                        int idx = findIndex(next);
                        if (idx == -1) continue;

                        for (int x = 0; first[idx][x]; x++) {
                            if (first[idx][x] != 'e')
                                add(follow[i], first[idx][x]);
                        }
                    }

                } else {
                    if (productions[j][0] != productions[i][0]) {
                        int idx = findIndex(productions[j][0]);
                        if (idx != -1) {
                            computeFollow(idx);
                            for (int x = 0; follow[idx][x]; x++)
                                add(follow[i], follow[idx][x]);
                        }
                    }
                }
            }
        }
    }
}

// Load grammars (FIXED version)
void loadGrammar(int choice) {

    if (choice == 1) {
        n = 5;
        strcpy(productions[0], "E=TX");
        strcpy(productions[1], "X=+TX|e");
        strcpy(productions[2], "T=FY");
        strcpy(productions[3], "Y=*FY|e");
        strcpy(productions[4], "F=(E)|i");
    }

    else if (choice == 2) {
        n = 3;
        strcpy(productions[0], "S=AB");
        strcpy(productions[1], "A=aA|e");
        strcpy(productions[2], "B=bB|c");
    }

    else if (choice == 3) {
        n = 1;
        strcpy(productions[0], "S=(S)S|e");
    }

    else if (choice == 4) {
        n = 3;
        strcpy(productions[0], "S=aB|bA");
        strcpy(productions[1], "A=cA|a");
        strcpy(productions[2], "B=dB|b");
    }

    else if (choice == 5) {
        n = 2;
        strcpy(productions[0], "S=Aa|b");
        strcpy(productions[1], "A=cA|e");
    }
}

// Main
int main() {

    int choice;
    printf("Select Grammar (1-5): ");
    scanf("%d", &choice);

    loadGrammar(choice);

    // Initialize
    for (int i = 0; i < n; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    // Compute FIRST
    for (int i = 0; i < n; i++)
        computeFirst(i);

    // Compute FOLLOW
    for (int i = 0; i < n; i++)
        computeFollow(i);

    // Print FIRST
    printf("\nFIRST Sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = { ", productions[i][0]);
        for (int j = 0; first[i][j]; j++)
            printf("%c ", first[i][j]);
        printf("}\n");
    }

    // Print FOLLOW
    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { ", productions[i][0]);
        for (int j = 0; follow[i][j]; j++)
            printf("%c ", follow[i][j]);
        printf("}\n");
    }

    return 0;
}