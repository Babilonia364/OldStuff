/* Cabecalho provisorio */
/* Prototipos de struct */
typedef struct Vertex Vertex;
typedef struct Path Path;

/* Prototipos de funcoes */
void show(Path *path);
void initPath(Path *path);
void push(Path *path, int vertex, int proba);
void insertionSort(int arr[], int n);

/* Declaracao de struct */
typedef struct Vertex							/* Struct de vertices com o proximo apontando para um vertice que se liga */
{
	int vertex;									/* Armazena qual o vertice esta no struct */
	double prob;								/* Armazena a probabilidade definida no vertice */
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

void push(Path *path, int vertex, int proba)	/* Funcao para adicionar elementos a lista, ou seja, adicionar o proximo vertice do caminho */
{
	Vertex *aux;								/* Cria um vertice auxiliar */
	
	aux=malloc(sizeof(Vertex));					/* Aloca uma regiao de memoria para o vertice auxiliar */

	aux->vertex=vertex;							/* Armazena conteudo no vertice auxiliar, no caso, o proximo vertice do caminho */
	aux->prob=proba;							/* Define a probabilidade do vertice falhar */
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

int pop(Path *path)											/* Funcao usada para retirar vertices da pilha, para finalizar a pilha quando tudo tiver sido usado */
{
	if(path->head!=NULL)									/* Se o indicador do topo da pilha nao for NULL, ou seja, se a pilha nao estiver vazia */
	{
		Vertex *garbage;									/* Variavel auxiliar lixo usada para apagar o vertice da pilha */
	
		garbage=path->head;									/* Variavel lixo agora recebe a variavel do topo da pilha */
		path->head=path->head->next;						/* Indicador de variavel do topo e passado para o proximo vertice, afinal, o anterior vai sumir */
		free(garbage);										/* Funcao free usada para desalocar a regiao de memoria alocada para o vertice que esta sendo deletado */

		return 1;											/* Sucesso, retorna 1, usada para apagar tudo em um loop */
	}else
		return -1;											/* Caso nao tenha mais nada para apagar, retorna -1, auxiliador de erros e loops */
}

int compare(Path *path1, Path *path2)
{
	int flag=0;
	Vertex *ant=path1->head, *prox=path2->head;
	while((ant!=NULL) && (prox!=NULL))
	{
		if(ant->vertex!=prox->vertex)
		{
			flag=1;
			break;
		}
		ant=ant->next;
		prox=prox->next;
	}
	if(flag || ((ant!=prox) && ((ant==NULL) || (prox==NULL))))
		return 1;
	else
		return -1;
}

Path* interseccao(Path* p1, Path* p2)
{
	Path *aux;
	Vertex *v1, *v2=p2->head;
	
	aux=malloc(sizeof(Path));
	
	for(v1=p1->head; v1!=NULL; v1=v1->next)
	{
		for(v2=p2->head; v2!=NULL; v2=v2->next)
			if(v1->vertex==v2->vertex)
			{
				push(aux, v1->vertex, v1->prob);
				break;
			}
	}
	
	show(aux);
	return aux;
}

Path* uniao(Path* p1, Path* p2)
{
	int tam=0, vet[99];
	int i, flag;
	
	Path *aux;
	Vertex *v1, *v2=p2->head;
	
	aux=malloc(sizeof(Path));
	
	for(v1=p1->head; v1!=NULL; v1=v1->next)
	{
		vet[tam]=v1->vertex;
		tam++;
	}
	
	for(v2=p2->head; v2!=NULL; v2=v2->next)
	{
		for(i=0, flag=0; i<tam; i++)
		{
			if(vet[i]==v2->vertex)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			vet[tam]=v2->vertex;
			tam++;
		}
	}
	
	insertionSort(vet, tam);
	for(i=0; i<tam; i++)
		push(aux, vet[i], p1->head->prob);
	
	return aux;
}

Path* genPath(int n, int mat[n][n], int count, double proba)/* Funcao usada para gerar caminho e adiciona - los na pilha */
{															/* Recebe o tamanho da matriz de incidencia, a propria matriz e a pilha onde os caminhos vao ser armazenados*/
	int i, j, repeat, auxInt;								/* Variaveis para contagem dos lacos */
	Path *aux;
	
	aux=malloc(sizeof(Path));
	for(i=0; i<n; i++)
	{
		for(j=i, repeat=0; j<n; j++)
		{
			if(i==0 && j==0)								/* Caso esteja na primeira iteracao */
			{
				push(aux, i, proba);						/* Adicionar V0, ou seja, o vertice inicial a pilha */
			}else if(aux->head->vertex!=i)					/* Caso o vertice nao esteja na pilha, interromper o laco */
			{
				break;
			}else if(mat[i][n-1]==1)						/* Caso o vertice tenha ligacao com o ultimo vertice da matriz */
			{
				push(aux, (n-1), proba);					/* Salvar o ultimo vertice no topo da pilha */
				goto END;									/* Terminar o algoritmo */
			}else if(mat[i][j]==1 && count==0)				/* Caso nao tenha ligacao com o ultimo vertice da matriz mas tenha ligacao com outro vertice (o primeiro que achar) */
			{
				push(aux, j, proba);						/* Alocar esse vertice na pilha para ser a proxima iteracao no laco */
				break;										/* Termina o laco do j */
			}else if(mat[i][j]==1)
			{
				if(repeat<count)
				{
					repeat++;
					auxInt=j;
				}else if(repeat==count)
				{
					push(aux, j, proba);
					break;
				}
			}else if(j==(n-1))
				push(aux, auxInt, proba);
		}
	}
	END:;
	return aux;
}

/* As quatro estacoes - inverno */
/* Antonio Vivaldi */
Path* multiPath(int n, int mat[n][n], double proba)
{
	Path *path, *aux;
	int count=0, i, j;
	
	aux=malloc(n*sizeof(Path));

	while(count<n)
	{
		aux[count]=*genPath(n, mat, count, proba);
		count++;
	}
	
	for(i=1; i<n; i++)
	{
		if(compare(&aux[i-1], &aux[i])==-1)
			break;
	}
	
	path=malloc(i*sizeof(Path));
	for(j=0; j<i; j++)
	{
		path[j]=aux[j];
		show(&path[j]);
	}
	
	interseccao(&path[0], &path[1]);
	return path;
}

void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}
