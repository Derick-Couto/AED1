#include <stdio.h>

/*Primeira atividade de AED 1 escolhida no leetcode. Criar um código que receba números romanos e retorne 
o seu valor respectivo em número inteiro.*/

char nroman[100], number[100];
int pos, resultado=0,i;

/*
====================
Função que faz a conversão de cada posição da string para número inteiro.
====================
*/
int romano_para_inteiro ( char c ){
    switch ( c )
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

/*
====================
Função que observa a posição atual e anterior a esta na string, chama a função anterior e faz 
os devidos cálculos.
====================
*/
int calculo_romano ( char *s )
{
    resultado = romano_para_inteiro( s[0] );

    for ( i = 1; s[i] != '\0'; i++)
    {
        int numero_anterior = romano_para_inteiro( s[i-1] );
        int numero_atual= romano_para_inteiro ( s[i] );

        if ( numero_anterior < numero_atual )
        {
         resultado = resultado- numero_anterior + ( numero_atual - numero_anterior );
        } else 

        resultado = resultado + numero_atual;
    }
return resultado;
}
 

int main()
{
    char *p=nroman;

    scanf ( "%s", &nroman );
    printf ( "O numero romano eh : %s\n", nroman );
    printf ( "Que em inteiro eh %i", calculo_romano( p ) );
}
