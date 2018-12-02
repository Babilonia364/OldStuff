#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAX 9999
#define SUB 1
#define SUM 2

double confiabilidade;

void overlap(int** mat, Path *caminho_minimo1, Path *caminho_minimo2, int op, int tam)
{
	int i, j, k;																				/* Variaveis de laco */
	int delete[MAX];
	int n=0, flag=0;
	int pConfiabilidade;
	
	Path *aux;
	Vertex *vAux;
	aux=malloc(tam*sizeof(Path));
	
	
	/* Passo 1 */
	if(compare(caminho_minimo1, caminho_minimo2)==-1)											/* Caso os caminho minimos sejam iguais, mudar operacao para soma */
		op=SUM;																					/* Operacao anterior */
	else if((compare(caminho_minimo1, caminho_minimo2)) && (op==SUB))
		op=SUM;
	else
		op=SUB;
	
	/* Passo 2 */
	for(i=0; i<((sizeof(caminho_minimo1)/sizeof(Path))-2); i++)
	{
		for(j=i+1; j<((sizeof(caminho_minimo1)/sizeof(Path))-1); j++)
		{
			if(compare(interseccao(caminho_minimo1[i], caminho_minimo2[j]), caminho_minimo1[i]))
			{
				for(k=0; k<n; k++)
					if(delete[k]==j)
						flag=1;
				if(flag==0)
				{
					delete[n]=j;
					n++;
				}
			}
			else if(compare(interseccao(caminho_minimo1[i], caminho_minimo2[j]), caminho_minimo1[j]))
			{
				for(k=0; k<n; k++)
					if(delete[k]==i)
						flag=1;
				if(flag==0)
				{
					delete[n]=i;
					n++;
				}
			}
		}
	}
	
	insertionSort(delete, n);																	/* Organizando os indices de caminhos redundantes */
	for(i=0, j=0; i<n; i++)																		/* Caso os indices nao estejam no vetor delete */
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
				for(vAux=aux->head; vAux!=NULL; vAux=vAux->prox)
					pConfiabilidade *= vAux->prob;
				confiabilidade += pConfiabilidade;
			}
		else
			{
				pConfiabilidade=1;
				for(vAux=aux->head; vAux!=NULL; vAux=vAux->prox)
					pConfiabilidade *= vAux->prob;
				confiabilidade -= pConfiabilidade;
			}
	}
	
	/* Passo 4 */
	if(op==SUM)																				/* Definindo a confiabilidade total do grafo */
		for(i=0; i<j; i++)
		{
			pConfiabilidade=1;
			for(vAux=aux->head; vAux!=NULL; vAux=vAux->prox)
				pConfiabilidade *= vAux->prob;
			confiabilidade += pConfiabilidade;
		}
	else
		for(i=0; i<j; i++)
		{
			pConfiabilidade=1;
			for(vAux=aux->head; vAux!=NULL; vAux=vAux->prox)
				pConfiabilidade *= vAux->prob;
			confiabilidade -= pConfiabilidade;
		}
	
	/* Passo 5 */
	if(j>1)
		for(i=1; i<j; i++)
		{
			
		}
		
	/* Passo 6 */
	return;
}

int main()
{
	int i, j, n=5;
	Path *caminho_minimo;
	int mat[5][5] ={0, 1, 1, 0, 0,
					1, 0, 0, 1, 0,
					1, 0, 0, 1, 0,
					0, 1, 1, 0, 1,
					0, 0, 0, 1, 0};
	double vProbabilidade;

	printf("Confiabilidade dos vertices:\n");
	scanf("%lf", &vProbabilidade);
	printf("Confiabilidade: %lf\n", vProbabilidade);
	
	//Gerando caminhos minimos
	caminho_minimo=multiPath(n, mat, vProbabilidade);
	
	/* 1 vai ser sub */
	overlap(mat, caminho_minimo, caminho_minimo, SUB, n)
}
