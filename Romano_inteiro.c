#include <stdio.h>

char nroman[100], number[100];
int pos, resultado=0,i;

int romano_para_inteiro (char c){
    switch (c)
    {
      case 'I':  
        return 1;  
    case 'V':  
        return 5;  
    case 'X':  
        return 10;  
    case 'L':  
        return 50;  
    case 'C':  
        return 100;  
    case 'D':  
        return 500;  
    case 'M':  
        return 1000;  
    default:
        return 0;
    }
}

int calculo_romano (char *s){

resultado = romano_para_inteiro(s[0]);

for ( i = 1; s[i] != '\0'; i++)
{
 int numero_anterior = romano_para_inteiro(s[i-1]);
 int numero_atual= romano_para_inteiro (s[i]);

if (numero_anterior < numero_atual)
{
   resultado = resultado- numero_anterior + (numero_atual - numero_anterior); // linha inspirada do w3resource
} else 

resultado = resultado + numero_atual; // linha inspirada de um código do w3resource

}
return resultado;
}
 

int main   (){

scanf ("%s", &nroman);

printf ("O numero romano eh : %s\n", nroman);

printf ("Que em inteiro eh %i", calculo_romano(nroman));





}