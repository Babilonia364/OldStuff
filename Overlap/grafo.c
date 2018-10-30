#include <stdio.h>
#include <stdlib.h>

/* Cabecalho provisorio */
/* Prototipos de struct */
typedef struct Vertex Vertex;
typedef struct Path Path;

/* Prototipos de funcoes */
void show(Path *path);
void initPath(Path *path);
void push(Path *path, int vertex);

/* Declaracao de struct */
typedef struct Vertex							/* Struct de vertices com o proximo apontando para um vertice que se liga */
{
	int vertex;									/* Armazena qual o vertice esta no struct */
	struct Vertex *next;						/* Aponta para o proximo struct do caminho, ou seja, para o membro do caminho anteior (por se tratar de pilha) */
}Vertex;										/* Ex.: V0 -> V1, em uma pilha, ficaria armazenado como V1 -> V0, onde o V1 apontaria para V0 mas o V0 e o vertice inicial do grafo e V1 o final */

typedef struct Path								/* Pilha responsavel por amazenar o caminho gerado */
{
	int length;									/* Variavel para armazenar o tamanho da pilha, meio inutil, to pensando em retirar */
	Vertex *head;								/* Aponta sempre para o elemento do topo da pilha */
}Path;

void initPath(Path *path)						/* Funcao para iniciar a lista, meio inutil, to pensando em retirar */
{
	path->head=NULL;
	path->length=0;
}

void push(Path *path, int vertex)				/* Funcao para adicionar elementos a lista, ou seja, adicionar o proximo vertice do caminho */
{
	Vertex *aux;								/* Cria um vertice auxiliar */
	
	aux=malloc(sizeof(Vertex));					/* Aloca uma regiao de memoria para o vertice auxiliar */

	aux->vertex=vertex;							/* Armazena conteudo no vertice auxiliar, no caso, o proximo vertice do caminho */
	aux->next=path->head;						/* O vertice armazenado aponta para o vertice anterior, formando um caminho */
	path->head=aux;								/* O indicador de topo da pilha agora vai indicar o vertice auxiliar como topo */
	path->length++;								/* Incrementando em 1 a variavel muito util de tamanho */
}

void show(Path *path)							/* Funcao usada para mostrar os elementos da pilha (como se fosse lista huehuehuehue) */
{
	int i;										/* Funcao apenas para auxiliar na montagem da biblioteca nao ha necessidade de explicacao */
	
	Vertex *aux;
	
	printf("Caminho:\n| ");
	for(aux=path->head; aux!=NULL; aux=aux->next)
		printf("%d <- ", aux->vertex);
	printf("init |\n");
}

int pop(Path *path)								/* Funcao usada para retirar vertices da pilha, para finalizar a pilha quando tudo tiver sido usado */
{
	if(path->head!=NULL)						/* Se o indicador do topo da pilha nao for NULL, ou seja, se a pilha nao estiver vazia */
	{
		Vertex *garbage;						/* Variavel auxiliar lixo usada para apagar o vertice da pilha */

		garbage=path->head;						/* Variavel lixo agora recebe a variavel do topo da pilha */
		path->head=path->head->next;			/* Indicador de variavel do topo e passado para o proximo vertice, afinal, o anterior vai sumir */
		free(garbage);							/* Funcao free usada para desalocar a regiao de memoria alocada para o vertice que esta sendo deletado */

		return 1;								/* Sucesso, retorna 1, usada para apagar tudo em um loop */
	}else
		return -1;								/* Caso nao tenha mais nada para apagar, retorna -1, auxiliador de erros e loops */
}

void greedPath(int n, int mat[n][n], Path *aux)	/* Funcao usada para gerar caminho e adiciona - los na pilha */
{												/* Recebe o tamanho da matriz de incidencia, a propria matriz e a pilha onde os caminhos vao ser armazenados*/
	int i, j;									/* Variaveis para contagem dos lacos */
	for(i=0; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			if(i==0 && j==0)					/* Caso esteja na primeira iteracao */
			{
				push(aux, i);					/* Adicionar V0, ou seja, o vertice inicial a pilha */
			}else if(aux->head->vertex!=i)		/* Caso o vertice nao esteja na pilha, interromper o laco */
			{
				break;
			}else if(mat[i][n-1]==1)			/* Caso o vertice tenha ligacao com o ultimo vertice da matriz */
			{
				push(aux, (n-1));				/* Salvar o ultimo vertice no topo da pilha */
				goto END;						/* Terminar o algoritmo */
			}else if(mat[i][j]==1)				/* Caso nao tenha ligacao com o ultimo vertice da matriz mas tenha ligacao com outro vertice (o primeiro que achar) */
			{
				push(aux, j);					/* Alocar esse vertice na pilha para ser a proxima iteracao no laco */
				break;							/* Terminar o primeiro laco */
			}
		}
	}
	END:;
	return;
}

int main()
{
	Path caminho_teste;
	int mat[5][5] ={0, 1, 1, 0, 0,
					1, 0, 0, 1, 0,
					1, 0, 0, 1, 0,
					0, 1, 1, 0, 1,
					0, 0, 0, 1, 0};
	
	greedPath(5, mat, &caminho_teste);
	show(&caminho_teste);
	while(pop(&caminho_teste)==1);
	show(&caminho_teste);
}
