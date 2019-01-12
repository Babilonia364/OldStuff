#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAX 9999
#define SUB 1
#define SUM 2

/*											IMPOTRTANTE												*/
/*										Olhar interseccao											*/
/*											IMPOTRTANTE												*/

double confiabilidade;

void overlap(Path *caminho_minimo1, Path *caminho_minimo2, int op, int tam)
{
	int i, j, k;																				/* Variaveis de laco */
	int delete[MAX];
	int n=0, flag=0;
	double pConfiabilidade;
	
	Path *aux, *inter;																			/* Pilha de caminhos auxiliar que vai armazenar os valores que nao foram deletados */
	Path *newStack;																				/* Pilha de caminhos que vai armazenar a uniao dos caminhos */
	Vertex *vAux;																				/* Pilha de vetices auxiliar usado para definir a confiabilidade dos vertices */
	
	aux=malloc(tam*sizeof(Path));
	newStack=malloc(99*sizeof(Path));
	
	/* Passo 1 */
	if(compare(caminho_minimo1, caminho_minimo2))											/* Caso os caminho minimos sejam iguais, mudar operacao para soma */
		op=SUM;																					/* Operacao anterior */
	else if((compare(caminho_minimo1, caminho_minimo2)) && (op==SUB))
		op=SUM;
	else
		op=SUB;
	
	/* Passo 2 */
	for(i=0; i<(tam-2); i++)																	/* tam sera a quantidade de caminhos/pilhas diferentes que existem no grafo */
	{
		for(j=i+1; j<(tam-1); j++)
		{																						/* Algoritmo vai fazer a interseccao dos caminhos armazenados na pilha */
			flag=0;
			inter=interseccao(&caminho_minimo2[i], &caminho_minimo2[j]);
			if(compare(inter, &caminho_minimo2[i]))
			{																					/* Se a interseccao for igual ao caminho de indice j, o indice i sera marcado para ser deletado */
				for(k=0; k<n; k++)
					if(delete[k]==j)
						flag=1;
				if(flag==0)
				{
					delete[n]=j;
					n++;
				}
			}
			else if(compare(inter, &caminho_minimo2[j]))
			{																					/* Caso contrario o indice i sera marcado como deletado */
				for(k=0; k<n; k++)
					if(delete[k]==i)
						flag=1;
				if(flag==0)
				{
					delete[n]=i;
					n++;
				}
			}
			pop(inter);
			free(inter);
		}
	}
	
	insertionSort(delete, n);																	/* Organizando os indices de caminhos redundantes */
	for(i=0, j=0; i<tam; i++)																	/* Caso os indices nao estejam no vetor delete */
	{																							/* E criado outra pilha apenas com os indices a serem mantidos */
		flag=0;
		for(k=0; k<n; k++)																		/* Percorre o vetor de delecao */
		{
			if(i==delete[k])																	/* Caso o indice esteja no vetor, subir uma flag */
			{
				flag=1;
				break;
			}
		}
		if(flag==0)																				/* Caso a flag nao tenha sido ativada */
		{
			aux[j]=caminho_minimo2[i];															/* O primeiro caminho sera adicionado na nova lista */
			printf("aux de j=%d\n", j);
			show(&aux[j]);
			j++;
		}
	}
	
	/* Passo 3 */
	if(j==1)																					/* Caso o tamanho da nova pilha seja 1 */
	{																							/* Neste caso j sera o tamanho da nova pilha */
		if(op==SUM)																				/* Definindo a confiabilidade total do grafo */
			for(i=0; i<j; i++)
			{
				pConfiabilidade=1;
				for(vAux=aux->head; vAux!=NULL; vAux=vAux->next)
					pConfiabilidade *= vAux->prob;
				confiabilidade += pConfiabilidade;
			}
		else
			{
				pConfiabilidade=1;
				for(vAux=aux->head; vAux!=NULL; vAux=vAux->next)
					pConfiabilidade *= vAux->prob;
				confiabilidade -= pConfiabilidade;
			}
		return;
	}
	
	/* Passo 4 */
	if(op==SUM)																					/* Definindo a confiabilidade total do grafo */
		for(i=0; i<j; i++)
		{
			pConfiabilidade=1;
			for(vAux=aux->head; vAux!=NULL; vAux=vAux->next)
			{
				pConfiabilidade *= vAux->prob;
			}
			confiabilidade += pConfiabilidade;
		}
	else
		for(i=0; i<j; i++)
		{
			pConfiabilidade=1;
			for(vAux=aux->head; vAux!=NULL; vAux=vAux->next)
				pConfiabilidade *= vAux->prob;
			confiabilidade -= pConfiabilidade;
		}
	
	/* Passo 5 */
	if(j>1)
		for(i=1; i<j; i++)
		{
			for(k=0; k<i; k++)
			{
				printf("stack[i]\n");
				show(&aux[i]);
				printf("stack[j]\n");
				show(&aux[j]);
				uniao(&aux[i], &aux[k], &newStack[k]);
				printf("uniao\n");
				show(&newStack[k]);
			}
			overlap(caminho_minimo1, newStack, op, k);
		}
		
	/* Passo 6 */
	for(i=0; i<j; i++)
		while(pop(&aux[i])==1);
	
	free(aux);
	free(newStack);
	free(vAux);
	return;
}

int main()
{
	int i, tam, n=5;
	Path *caminho_minimo;
	int mat[5][5] ={0, 1, 1, 1, 0,
					1, 0, 1, 1, 0,
					1, 1, 0, 1, 0,
					1, 1, 1, 0, 1,
					0, 0, 0, 1, 0};
	double vProbabilidade;

	printf("Confiabilidade dos vertices:\n");
	scanf("%lf", &vProbabilidade);
	printf("Confiabilidade: %lf\n", vProbabilidade);
	
	//Gerando caminhos minimos
	caminho_minimo=simples(n, mat, &tam, vProbabilidade);
	
	printf("Tamanho: %d\n", tam);
	
	/* 1 vai ser sub */
	overlap(caminho_minimo, caminho_minimo, SUB, tam);
	printf("confiabilidade do grafo: %lf\n", confiabilidade);
}
