#include <stdio.h>
#include <string.h>
int E();
int E_prime();
char expr[100];
int count,l;
int main()
{
count = 0;
printf("\nRecursive descent parsing for the following grammar\n");
printf("\nE->iE'\nE'->+iE'|@\n");
printf("\nEnter the string to be checked:");
fgets(expr,100,stdin);
if(E())
{
if(expr[count]=='$')
printf("\nString is accepted");
else
printf("\nString is not accepted");
}
else{
printf("\nString not accepted");
}
return 0;
}
int E()
{
//E --> iE'
if(expr[count] == 'i')
{
count++;
if(E_prime())
{
return 1;
}
else
return 0;
}
else
return 0;
}
int E_prime()
{
//E' --> +iE' | @
if(expr[count] == '+')
{
count++;
if(expr[count] == 'i'){
count++;
if(E_prime())
return 1;
else
return 0;
}
else
return 0;
}
else
return 1;
}




