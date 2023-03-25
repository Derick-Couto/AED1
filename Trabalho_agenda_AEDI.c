/*Faça uma agenda capaz de incluir, apagar, buscar e listar
quantas pessoas o usuário desejar, porém, toda a informação
incluída na agenda deve ficar num único lugar chamado: “void
*pBuffer”.
•
Não pergunte para o usuário quantas pessoas ele vai incluir.
Não pode alocar espaço para mais pessoas do que o
necessário.

Cada pessoa tem nome[10], idade e telefone.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  *first = NULL;
//nodo = ||char[10](10bytes)||idade(4bytes)||telefone(4bytes)||prev(4bytes)||next(4bytes)||

//Adiciona nodo no inicio da fila
int *push_first (int *first, void *pessoa_nova){

    if ( first == NULL ){
		return pessoa_nova;
	}	//Se estiver vazio retorna nodo como primeiro elemento
    
	void *st = pessoa_nova; //Guarda novo novo como inicio da fila
	void **ppbuffer = (void*)&first; //Double-pointer apontando pro antigo primeiro

	pessoa_nova += 10*sizeof(char)+3*sizeof(int); //ponteiro do novo nodo vai pro "next"

	*(int*)pessoa_nova = (int)first; //coloca o "next" do novo nodo como o antigo first
	*(int*)(*ppbuffer+10*sizeof(char)+2*sizeof(int)) = (int)st; //antigo primeiro "prev" recebe novo nodo

	return st; 
}

void push_next (int *first, void *pessoa_nova){
	//Aqui o first entra como penúltimo nodo (atual último) por causa da chamada do push()
    
    void **penutimobuffer = (void*)&first;
    int *nextpenultimo = (int*)(*penutimobuffer+10*sizeof(char)+3*sizeof(int));

    *nextpenultimo = (int)pessoa_nova;
    pessoa_nova += 10*sizeof(char)+2*sizeof(int);
    *(int*)pessoa_nova = (int)(int*)(*penutimobuffer);
}

int *push (int *first, void *pessoa_nova){

    if (first == NULL){
		first = push_first(first, pessoa_nova);
		return first;
	}

    if (strcmp((char*)pessoa_nova,(char*)first)<1)
    {
		first = push_first(first, pessoa_nova);
		return first;
    }  

    int *st = first;
	int *anterior;
	void **ppbuffer = (void*)&first;
	void **panterior = (void*)&anterior;

	while ( 1 )
    {
		anterior = first;
		

		if (strcmp((char*)pessoa_nova,(char*)first)<1){
			anterior = (int*)*(int*)(*panterior+10*sizeof(char)+2*sizeof(int));
			*(int*)(*panterior+10*sizeof(char)+3*sizeof(int)) = (int)pessoa_nova;
			
	
			*(int*)(*ppbuffer+10*sizeof(char)+2*sizeof(int)) = (int) pessoa_nova;

			pessoa_nova += 10*sizeof(char)+2*sizeof(int);
			*(int*)pessoa_nova = *(int*)panterior;
			pessoa_nova += sizeof(int);
			*(int*)pessoa_nova= *(int*)ppbuffer;
			
			return st;
		}

		if(*(int*)(*ppbuffer+10*sizeof(char)+3*sizeof(int))==0)
		{ //inserir no final
			push_next(anterior, pessoa_nova);
			return st;
		}else
        first = (int*)*(int*)(*ppbuffer+10*sizeof(char)+3*sizeof(int));
		//Enquanto tiver "next" e o nome do nodo for "maior" do que o node que está sendo visto, incrementa
	}
}

int *pop (int *first)
{
	void **controlfirst = (void*)&first;
	void *kira = first;

    if (first == NULL){
    printf("\nNão e possível tirar elementos de uma fila vazia!\n");
    return 0;
    }
    if (*(int*)(*controlfirst+10*sizeof(char)+3*sizeof(int))==0){ 
		free(first);
		return 0;
		//se houver apenas um elemento, ele é removido sem outras ações
	}

	first = (int*)*(int*)(*controlfirst+10*sizeof(char)+3*sizeof(int));
	*(int*)(*controlfirst+10*sizeof(char)+2*sizeof(int)) = 0;
	free(kira);
	return first;
}

void imprimir(int *first)
{
    if (first == NULL)
    {
        printf("Vazio\n");
        return;
    }
        
        void **ppbuffer = (void*)&first;

    if (*(int*)(*ppbuffer+10*sizeof(char)+3*sizeof(int))== 0) //uma pessoa
    {
        printf("\n");
        printf("\nNome: %s",(char*)first);
		printf("\nIdade: %d",(int)*(int*)(*ppbuffer+10*sizeof(char)));
		printf("\nTelefone: %d \n",(int)*(int*)(*ppbuffer+10*sizeof(char)+sizeof(int)));
		return;
    }
    
   while (first!=0){
		printf("\n------------------");
		printf("\nNome: %s",(char*)first);
		printf("\nIdade: %d",(int)*(int*)(*ppbuffer+10*sizeof(char)));
		printf("\nTelefone: %d",(int)*(int*)(*ppbuffer+10*sizeof(char)+sizeof(int)));
		first = (int*)*(int*)(*ppbuffer+10*sizeof(char)+3*sizeof(int));
	}
	printf("\n------------------");
}

void search(char *pessoa_nova,void *first){
	
	void **ppbuff = &first;
	while (first!=NULL){
		if (strcmp((char*)first,pessoa_nova)==0){
			printf("\nNome: %s",(char*)first);
			printf("\nIdade: %d",(int)*(int*)(*ppbuff+10*sizeof(char)));
			printf("\nTelefone: %d \n",(int)*(int*)(*ppbuff+10*sizeof(char)+sizeof(int)));
			return;
		}
		first = *(int*)(*ppbuff+10*sizeof(char)+3*sizeof(int));
	}
	printf("Nao possui este nome na fila\n");
}

void *reset(void *first){
	void *kira, **nodoatual = (void*)&first;
	if (first != NULL){
		while (1){
			kira = *(void**)(nodoatual);
			if (*(int*)(*nodoatual+10*sizeof(char)+3*sizeof(int))==0){ //apenas um elemento
				free(kira);
				return NULL;
			}
			first = (int*)*(int*)(*nodoatual+10*sizeof(char)+3*sizeof(int));
			free(kira);
		}
	}
	return NULL;
}

int main(){
    
void *pessoa_nova;

 while (1){
     printf("\n1 Adicionar\n2 Remover\n3 Listar\n4 Buscar\n5:Sair\n");
    switch ( getchar() )
    {
        case '1':
        {
            pessoa_nova = malloc(10*sizeof(char)+4*sizeof(int));
            if (pessoa_nova == NULL)
            {
             printf("Erro ao alocar memoria");
                exit(1);
            }else{}
            printf("Digite o nome da pessoa:");
            scanf("%s",(char*)pessoa_nova);
            printf("A idade da pessoa:");
            scanf("%d",(int*)(pessoa_nova+10*sizeof(char)));
            printf("O telefone da pessoa:");
            scanf("%d",(int*)(pessoa_nova+10*sizeof(char)+1*sizeof(int)));
    
            *(int*)(pessoa_nova+10*sizeof(char)+2*sizeof(int)) = 0;
            *(int*)(pessoa_nova+10*sizeof(char)+3*sizeof(int)) = 0;

            first = push (first, pessoa_nova);
            getchar();
        
            break;
        }
        
         case '2':
        first = pop(first);
		getchar();
        break;

        case '3':
        imprimir(first);
		getchar();
        break;

        case '4':
			pessoa_nova = malloc(10*sizeof(char));
				if (pessoa_nova == NULL){
					exit(0);
				}
			printf("\nDigite nome: ");
			scanf("%s",(char*)pessoa_nova);
			search(pessoa_nova,first);
			getchar();
			free(pessoa_nova);
			break;
 
		default:
			first = reset(first);
			printf("Memória Limpa!");
			exit(0);
			break;
		}
	}
} 