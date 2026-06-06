#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEX 5000
#define MAX_LEX_LEN 100

int main() {
    FILE *fptr;
    char ch;
    char filename[100];

    // Buffers to store clean code and lexemes
    char clean[5000];
    char lexemes[MAX_LEX][MAX_LEX_LEN];

    int cleaned_index = 0, lex_index = 0;

    printf("Enter filename: ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Error: Unable to open file!\n");
        return 1;
    }

    int in_com_restrict = 0;

    while ((ch = fgetc(fptr)) != EOF) {

        // Handle multi-line comments
        if (in_com_restrict) {
            if (ch == '*') {
                char next = fgetc(fptr);
                if (next == '/') {
                    in_com_restrict = 0;
                } else {
                    ungetc(next, fptr);
                }
            }
            continue;
        }

        // Handle single-line and multi-line comments
        if (ch == '/') {
            char next = fgetc(fptr);

            if (next == '/') {
                while ((ch = fgetc(fptr)) != '\n' && ch != EOF);
                continue;
            }
            else if (next == '*') {
                in_com_restrict = 1;
                continue;
            }
            else {
                ungetc(next, fptr);
            }
        }

        if (!isspace(ch)) {
            clean[cleaned_index++] = ch;
        }
    }

    clean[cleaned_index] = '\0';
    fclose(fptr);

    // Tokenize clean code into lexemes
    int i = 0;

    while (i < cleaned_index) {

        // Identifiers
        if (isalpha(clean[i]) || clean[i] == '_') {
            int j = 0;
            while (isalnum(clean[i]) || clean[i] == '_') {
                lexemes[lex_index][j++] = clean[i++];
            }
            lexemes[lex_index][j] = '\0';
            lex_index++;
        }

        // Numbers
        else if (isdigit(clean[i])) {
            int j = 0;
            while (isdigit(clean[i])) {
                lexemes[lex_index][j++] = clean[i++];
            }
            lexemes[lex_index][j] = '\0';
            lex_index++;
        }

        // String or character literals
        else if (clean[i] == '"' || clean[i] == '\'') {
            char quote = clean[i];
            int j = 0;
            lexemes[lex_index][j++] = clean[i++];

            while (clean[i] != quote && clean[i] != '\0') {
                lexemes[lex_index][j++] = clean[i++];
            }

            if (clean[i] == quote) {
                lexemes[lex_index][j++] = clean[i++];
            }

            lexemes[lex_index][j] = '\0';
            lex_index++;
        }

        // Punctuation / Operators
        else if (ispunct(clean[i])) {
            int j = 0;
            lexemes[lex_index][j++] = clean[i++];
            lexemes[lex_index][j] = '\0';
            lex_index++;
        }

        else {
            i++;
        }
    }

    // Print clean code
    printf("\n===== CLEAN PROGRAM =====\n");
    printf("%s\n", clean);

    // Print lexemes
    printf("\n===== LEXEMES =====\n");
    for (int k = 0; k < lex_index; k++) {
        printf("%s\n", lexemes[k]);
    }

    return 0;
}

