#include <stdio.h>
#include "grafo.h"

#define MAX 9999
#define SUB 1
#define SUM 2

void overlap(int** mat, Path *caminho_minimo1, Path *caminho_minimo2, int op, int tam)
{
	int i, j, k;																				/* Variaveis de laco */
	int delete[MAX];
	int n=0, flag=0;
	
	Path *aux;
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
	insertionSort(delete, n);
	for(i=0, j=0; i<n; i++)
	{
		if(i!=delete[n])
		{
			aux[j]=caminho_minimo2[i];
			j++;
		}
	}
	
	/* Passo 3 */
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
	caminho_minimo=multiPath(n, mat);
	
	/* 1 vai ser sub */
	overlap(mat, caminho_minimo, caminho_minimo, SUB, n)
}