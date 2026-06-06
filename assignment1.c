#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

FILE *fp, *tokens, *symtab;

char symbolTable[MAX][50];
int symCount = 0;

int isKeyword(char *str)
{
   if(strcmp(str,"if")==0) return 1;
   if(strcmp(str,"while")==0) return 1;
   if(strcmp(str,"break")==0) return 1;
   if(strcmp(str,"print")==0) return 1;
   return 0;
}

int isOperator(char c)
{
   if(c=='+'||c=='-'||c=='*'||c=='/'||c=='>'||c=='<'||c=='='||c=='!'||c=='&')
       return 1;
   return 0;
}

int isDelimiter(char c)
{
   if(c=='{'||c=='}'||c=='('||c==')')
       return 1;
   return 0;
}

void addSymbol(char *str)
{
   int i;
   for(i=0;i<symCount;i++)
   {
       if(strcmp(symbolTable[i],str)==0)
           return;
   }

   strcpy(symbolTable[symCount++],str);
}

int isFloat(char *str)
{
   int i, dot=0;

   for(i=0;i<strlen(str);i++)
   {
       if(str[i]=='.')
           dot++;
       else if(!isdigit(str[i]))
           return 0;
   }

   return dot==1;
}

void DFASimulator(char *lexeme)
{
   if(isKeyword(lexeme))
       fprintf(tokens,"<KEYWORD, %s>\n",lexeme);

   else if(isFloat(lexeme))
       fprintf(tokens,"<FLOAT, %s>\n",lexeme);

   else if(isalpha(lexeme[0]))
   {
       fprintf(tokens,"<IDENTIFIER, %s>\n",lexeme);
       addSymbol(lexeme);
   }
}

void lexicalAnalyzer()
{
   char c, buffer[50];
   int i=0;

   while((c=fgetc(fp))!=EOF)
   {
       if(isalnum(c) || c=='.')
       {
           buffer[i++]=c;
       }
       else
       {
           if(i>0)
           {
               buffer[i]='\0';
               DFASimulator(buffer);
               i=0;
           }

           if(isOperator(c))
               fprintf(tokens,"<OPERATOR, %c>\n",c);

           if(isDelimiter(c))
               fprintf(tokens,"<DELIMITER, %c>\n",c);
       }
   }
}

void printSymbolTable()
{
   int i;

   fprintf(symtab,"Symbol Table\n");
   fprintf(symtab,"-----------------\n");

   for(i=0;i<symCount;i++)
       fprintf(symtab,"%d\t%s\n",i+1,symbolTable[i]);
}

int main()
{
   fp = fopen("input.txt","r");

   tokens = fopen("tokens.txt","w");
   symtab = fopen("symbol_table.txt","w");

   lexicalAnalyzer();
   printSymbolTable();

   fclose(fp);
   fclose(tokens);
   fclose(symtab);

   printf("Lexical Analysis Completed\n");

   return 0;
}
