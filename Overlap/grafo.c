#include <stdio.h>
#include <stdlib.h>

//Listas de caminhos
typedef struct Vertex
{
	int vertex;
	struct Vertex *prox;
}Vertex;

typedef struct Path
{
	Vertex *init;
	int length;
}Path;

void pathInit (Path *caminho)
{
	printf("Init sendo NULL\n");
	caminho->init=NULL;
	printf("Definindo tamanho");
	caminho->length=0;
}

void push(Path *caminho, int vertex)
{

	Vertex *new_vert;
	new_vert->vertex=vertex;
	new_vert->prox=caminho->init;
	caminho->init=new_vert;
	caminho->length++;
}

int pop(Path *caminho)
{
	if(caminho->length==0)
		return -1;
	else
	{
		Vertex *del;
		
		del=caminho->init;
		caminho->init=caminho->init->prox;
		del->prox=del;
		free(del);
		caminho->length--;
		return 1;
	}
}

void show(Path *caminho)
{
	Vertex *att;
	int i;
	att=caminho->init;
	
	printf("Paths: [ ");
	for(i=0; i<(caminho->length); i++)
	{
		printf("%d -> ", att->vertex);
		att=att->prox;
	}
	printf("end ]\n");
}

int main()
{
	Path *caminho;
	int i, j;
	int mat[5][5] ={0, 1, 1, 0, 0,
					1, 0, 0, 1, 0,
					1, 0, 0, 1, 0,
					0, 1, 1, 0, 1,
					0, 0, 0, 1, 0};
	
	printf("Iniciando caminho\n");
	pathInit(caminho);
	printf("Caminho iniciado\nAdicionando zero ao caminho\n");
	push(caminho, 0);
	printf("Zero adicionado\nEntrando no laco\n");
	for(i=0; i<5; i++)
		if(mat[0][i]==1)
		{
			printf("Rodei ele uma vez\n");
			push(caminho, 1);
			break;
		}
	show(caminho);
	while(pop(caminho)==1)
		printf("Deletando\n");
	free(caminho);
}