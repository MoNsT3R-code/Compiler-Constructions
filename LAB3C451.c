#include <stdio.h>
    
    // Function to check if a character is a letter
    int isLetter(char c) {
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
      return 0;
    }
    
    // Function to check if a character is a digit
    
    int isDigit(char c) {
      if (c >= '0' && c <= '9')
        return 1;
      return 0;
    }
    
    // Function to manually compare input with keyword
    int isKeyword(char str[]) {
    
        if (str[0]=='i' && str[1]=='n' && str[2]=='t' && str[3]=='\0')
            return 1;
        
        if (str[0]=='w' && str[1]=='h' && str[2]=='i' && str[3]=='l' && str[4]=='e' && str[5]=='\0')
            return 1;
            
        if (str[0]=='c' && str[1]=='h' && str[2]=='a' && str[3]=='r' && str[4]=='\0')
            return 1;
            
        if (str[0]=='f' && str[1]=='o' && str[2]=='r' && str[3]=='\0')
            return 1;
            
        if (str[0]=='i' && str[1]=='f' && str[2]=='\0')
            return 1;
            
        if (str[0]=='e' && str[1]=='l' && str[2]=='s' && str[3]=='e' && str[4]=='\0')
            return 1;
            
        if (str[0]=='f' && str[1]=='l' && str[2]=='o' && str[3]=='a' && str[4]=='t' && str[5]=='\0')
            return 1;
            
        if (str[0]=='d' && str[1]=='o' && str[2]=='u' && str[3]=='b' && str[4]=='l' && str[5]=='e' && str[6]=='\0')
            return 1;
            
        if (str[0]=='r' && str[1]=='e' && str[2]=='t' && str[3]=='u' && str[4]=='r' && str[5]=='n' && str[6]=='\0')
            return 1;

        return 0; // temporary
        
    }
    
int main() {

    char input[100];
    int i = 0;
    int state = 0; // DFA state
      printf("Enter input: ");
      scanf("%s", input);
    // DFA processing loop

   while (input[i] != '\0') {

    char c = input[i];

    if (state == 0) {   
        if (isLetter(c) || c == '_')
            state = 1;
        else
            state = -1;
        }

    else if (state == 1 || state == 2) {  
        
        if (isLetter(c) || isDigit(c) || c == '_')
            state = 2;
        else
            state = -1;
        }

    if (state == -1)
        break;

    i++;
    }


    // After processing all characters
    if (state != -1) {

        if (isKeyword(input)) {       
        printf("Invalid Identifier\n");
      } else {
        printf("Valid Identifier\n");
      } else {
       printf("Invalid Identifier\n");
      }
      return 0;
}
