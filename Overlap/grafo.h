/* Cabecalho provisorio */
/* Prototipos de struct */
typedef struct Vertex Vertex;
typedef struct Path Path;

/* Prototipos de funcoes */
void show(Path *path);
void initPath(Path *path);
void push(Path *path, int vertex, double proba);
void insertionSort(int arr[], int n);

/* Declaracao de struct */
typedef struct Vertex							/* Struct de vertices com o proximo apontando para um vertice que se liga */
{
	int vertex;									/* Armazena qual o vertice esta no struct */
	int used;									/* Armazena 1 para vertice usado e 0 para vertice ainda nao usado para caminhos minimos */
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

void push(Path *path, int vertex, double proba)	/* Funcao para adicionar elementos a lista, ou seja, adicionar o proximo vertice do caminho */
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
		
		path->length--;	
		garbage=path->head;									/* Variavel lixo agora recebe a variavel do topo da pilha */
		path->head=path->head->next;						/* Indicador de variavel do topo e passado para o proximo vertice, afinal, o anterior vai sumir */
		free(garbage);										/* Funcao free usada para desalocar a regiao de memoria alocada para o vertice que esta sendo deletado */

		return 1;											/* Sucesso, retorna 1, usada para apagar tudo em um loop */
	}else
		return -1;											/* Caso nao tenha mais nada para apagar, retorna -1, auxiliador de erros e loops */
}

int compare(Path *path1, Path *path2)						/* Retorna 1 caso sejam diferentes e -1 caso sejam iguais */
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
	if(flag)
		return 0;
	else
	{
		if(prox==NULL && ant==NULL)
			return 1;
		else
			return 0;
	}
}

Path* interseccao(Path* p1, Path* p2)
{
	Path *aux;
	Vertex *v1, *v2;
	int vertices[100], size=0, i;
	
	aux=malloc(sizeof(Path));
	initPath(aux);
	
	for(v1=p1->head; v1!=NULL; v1=v1->next)
	{
		for(v2=p2->head; v2!=NULL; v2=v2->next)
			if(v1->vertex==v2->vertex)
			{
				vertices[size]=v1->vertex;
				size++;
				break;
			}
	}

	for(; size>0; size--)
	{
		push(aux, vertices[(size-1)], p1->head->prob);
	}
	
	//show(aux);
	return aux;
}

void uniao(Path* p1, Path* p2, Path *result)
{
	int tam=0, vet[99];
	int i, j, flag;
	
	Vertex *v1, *v2;
	
	
	for(v1=p1->head; v1!=NULL; v1=v1->next)
	{
		vet[tam]=v1->vertex;
		tam++;
	}
	
	for(v2=p2->head, j=0; v2!=NULL; v2=v2->next)
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
	for(i=tam-1; i>=0; i--)
		push(result, vet[i], p1->head->prob);
}

int onStack(Path* path, int vert)							/* Retorna 1 se o vertice ja estiver na pilha */
{
	Vertex *aux;
	
	for(aux=path->head; aux!=NULL; aux=aux->next)			/* Percore todos os vertices da lista */
	{
		if(aux->vertex==vert)								/* E compara com o vertice dado */
			return 1;
	}
	
	return 0;
}

int zeroPath(Path* path)									/* Apenas zera os caminhos visitados */
{
	Vertex *aux;
	
	for(aux=path->head; aux!=NULL; aux=aux->next)
		aux->used=0;
}

Path* simples(int n, int mat[n][n], int* size2, double proba)	/* Gerar os caminhos minimos e simples */
{
	int i, j, size;												/* Variaveis i e j de laco e variavel size para calcular a quantidade de caminhos diferentes*/
	int remover, nodo, addNodo;									/* Flag romover e addNodo e variavel nodo apenas para deixar o code mais legivel */
	
	Path *aux, *megaLista, *nos, *teste;						/* Varoaveos de caminho */
	Vertex *vAux;
	
	aux=malloc(sizeof(Path));									/* Criando espaco de memoria para alocar caminhos temporariamente */
	nos=malloc(n*sizeof(Path));									/* Criando uma lista de nos que estao ligados no grafo, POR EXEMPLO: 0 esta ligado com 1 e 2, a lista tera 0 -> 1 -> 2 */
	megaLista=malloc(99*sizeof(Path));							/* Criando a lista que vai armazenar todas as listas com caminhos minimos */
	
	size=0;
	
	for(i=(n-1); i>=0; i--)										/* Criando as listas de vertices ligados entre si usando a matriz de ajacencia */
	{
		for(j=(n-1); j>=0; j--)
		{
			if(mat[i][j]==1)
				push(&nos[i], j, proba);
		}
	}
	
	push(aux, 0, proba);												/* Colocando primeiro vertice da lista */
	remover=0;													/* A ultima acao foi adicionar, remover sera 0 */
	
	while(aux->head!=NULL)										/* Enquanto ainda existir elementos na lista, rodar o algoritmo de caminhos */
	{
		nodo=aux->head->vertex;									/* Nodo apenas para limpar mais o codigo */
		if(mat[nodo][n-1]==1)									/* Caso o no do topo da pilha tenha ligacao com o no destino */
		{
			push(aux, (n-1), proba);									/* Colocando o no destino no topo da pilha */
			for(vAux=aux->head; vAux!=NULL; vAux=vAux->next)			/* Salvando a pilha como caminho minimo */
			{
				push(&megaLista[size], vAux->vertex, proba);
			}
			size++;														/* Aumentando o contador de caminhos */
			for(i=0; i<2; i++)											/* Apagando os 2 nos do topo da pilha */
			{
				pop(aux);
			}
			remover=1;													/* Como foi removido algo, remover sera 1 */
		}else if(mat[nodo][n-1]==0)										/* Se nao ha ligacao do vertice no topo da filha com o vertice final */
		{
			teste=&nos[nodo];											/* Tava testando uma coisa */
			for(vAux=teste->head; vAux!=NULL; vAux=vAux->next)			/* Enquanto a pilha de nos ligado a um no X nao estiver vazia */
			{
				if(onStack(aux, vAux->vertex))							/* Caso o vertice ja esteja na pilha, passar para proximo vertice */
				{}
				else if(remover==0 || remover==1)						/* Caso o vertice nao esteja na pilha e a ultima acao tenha sido remover ou adicionar */
				{
					if(vAux->used==0)									/* Caso o vertice nao tenha sido usado ainda */
					{
						push(aux, vAux->vertex, proba);					/* Adiciona o vertice na pilha de caminhos */
						vAux->used=1;									/* Marca o vertice como ja usado */
						remover=0;										/* Marca a ultima acao como tendo sido adicionar, ou seja, remover e zero*/
						addNodo=1;										/* Sobe a flag que adicionou um no na pilha */
						break;
					}else												/* Caso contrario */
						addNodo=0;										/* a flag para adicionar nos na pilha sera zero */
				}
			}
			if(addNodo==0)												/* Caso a flag de adicionar no na pilha tenha continue 0 */
			{															/* Ou seja, nao tem ligacao direta com o destino e nem possui mais nos possiveis para adicionar na pilha */
				zeroPath(&nos[nodo]);									/* Zera os nos ja usados que estao ligados ao no atual */
				pop(aux);												/* Remove o no do topo da pilha */
				remover=1;												/* Defini a ultima acao como remover */
			}
			
		}
	}
	
	*size2=size;
	
	free(aux);
	free(nos);
	
	return megaLista;
}

void insertionSort(int arr[], int n)
{
   int i, key, j;
   
   if(n==0)
	   return;
   
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
