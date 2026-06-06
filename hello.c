#include <stdio.h>
  
  int main() {
  
    // Declare file pointer
    
    FILE *fptr;
    
    // Declare character variable and pointer
    
    char ch;
    char *ptr = &ch;
    
    // Declare filename array
    
    char filename[100];
    
    // Declare counter variables
    
    int total = 0;
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    
    // Prompt user for filename
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    // Open file in read mode
    
    fptr = fopen(filename, "r");
    
      // Check if file opened successfully
    
      if (fptr == NULL) {
      printf("Error: Unable to open file!\n");
      return 1;
      }
    
      // Read file character by character
    
      while ((*ptr = fgetc(fptr)) != EOF) {
    
      // Increment total character count
    
      total++;
        // Check if character is an alphabet
    
        if ((ch >= 'a' && ch <= 'z' ) || (ch >= 'A' && ch <= 'Z' )) {
    
        // Increment alphabet counter
        alphabets++;    
    
        }
        // Check if character is a digit
        else if (ch >= '0' && ch <= '9' ) {
        // Increment digit counter
        digits++;
        }
   
        // Otherwise it's a special symbol
        else {
    
        // Increment special symbol counter
        special++;
    
        }
    
      }
    
    // Close the file

    fclose(fptr);
     
    // Display results

    printf("\nFile Analysis Results:\n");
    printf("======================\n");
    printf("Total Characters: %d\n", total);
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special Symbols: %d\n", special);
    return 0;

}

//cd ~/Desktop
//gcc hello.c -o hello
//./hello


//ERRORS

//ls: cannot access 'desktop': No such file or directory
//cc1: fatal error: hello.c: No such file or directory compilation terminated.
//hello.c: In function ‘main’:
//hello.c:50:44: error: expected expression before ‘)’ token
//   50 |         if ((/* condition for lowercase */ ) || (/* condition for
//      |                                            ^
//hello.c:57:43: error: expected expression before ‘)’ token
//   57 |         else if (/* condition for digit */) {
//hello.c: In function ‘main’:
//hello.c:50:23: error: expected ‘)’ before ‘or’
//   50 |         if ((ch >= 'a' or ch <= 'z' ) || (ch >= 'A' or ch <= 'Z' )) {
//      |             ~         ^~~
//      |                       )
//hello.c:50:52: error: expected ‘)’ before ‘or’
//   50 |         if ((ch >= 'a' or ch <= 'z' ) || (ch >= 'A' or ch <= 'Z' )) {
  //    |                                          ~         ^~~
    //  |                                                    )
//hello.c:53:20: error: expected ‘;’ before ‘}’ token
  // 53 |         alphabets++
    //  |                    ^
      //|                    ;
//   54 | 
  // 55 |         }
    //  |         ~           
//hello.c:57:27: error: expected ‘)’ before ‘or’
  // 57 |         else if (ch >= '0' or ch <= '9' ) {
    //  |                 ~         ^~~
      //|                           )
//hello.c:59:17: error: expected ‘;’ before ‘}’ token
//   59 |         digits++
//      |                 ^
  //    |                 ;
   //60 |         }
     // |         ~        
//hello.c:66:18: error: expected ‘;’ before ‘}’ token
  // 66 |         special++
    //  |                  ^
      //|                  ;
 //  67 | 
   //68 |         }
     // |         ~         


