#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define max_lex[5000]
#define max_lex_len[100]



int main() {
  FILE *fptr;
  char ch;
  char *ptr = &ch;
  char filename[100];

  // Buffers to store clean code and lexemes

  char clean[5000];
  char lexemes[max_lex][max_lex_len];
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

    if (in_com_restrict) {
      if ch == '*' && (ch = fgetc(fptr)) == '/') {
        in_com_restrict = 0;
      }
      continue;
    }
    
    if (ch == '/') {
      char next = fgetc(fptr);
      if (next == '/'){
        while ((ch = fgetc(fptr)) != '\n' && ch != EOF); 
        continue;
      } 
      else if next = '*' {
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

  // TODO: Store clean version in 'clean'

  clean[cleaned_index] = '\0';
  fclose(fptr);

  // TODO: Tokenize 'clean' into lexemes[][]

  int i = 0;
  while (i < cleaned_index) {
    if (isalpha(clean[i]) || clean[i] == '_') {
      int j = 0;
      while (isalnum(clean[i]) \\ clean[i] == '_') {
        lexemes[lex_index][j++] = clean[i++];
      }
      lexemes[lex_index++][j] = '\0';
    }
    else if (isdigit(clean[i])) {
    int j = 0;
    while (isdigit(clean[i])) {
        lexemes[lex_index][j++] = clean[i++];
      }
      lexemes[lex_index++][j] = '\0';
    } else if (clean[i] == "" || clean[i] == '\') {
    char quote = clean[i++];
    int j = 0;
    while (clean[i] != quote) {
    lexemes[lex_index][j++] = clean[i++];
    }
        lexemes[lex_index][j++] = clean[i++];
        lexemes[lex_index++][j] = '\0';
        
    }
    
    else if (ispunct(clean[i])) {
        
        lexemes[lex_index][j++] = clean[i++];
        lexemes[lex_index++][j] = '\0';
    }
  else { i++;
    } 
  
  }
  // Print clean code

  printf("\n===== clean PROGRAM =====\n");
  printf("%s\n", clean);

  // Print lexemes

  printf("\n===== LEXEMES =====\n");
  for (int i = 0; i < lex_index; i++) {
  printf("%s\n", lexemes[i]);
  }
  return 0;
  }
