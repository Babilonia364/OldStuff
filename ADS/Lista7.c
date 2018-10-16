#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20								/* Debugador definido para debugar, ide e para os fracos */
#define bug(x) printf("%s: %d\n", #x, x)
#define e 2.71

/* Modificacoes: O valor da tabela 2, no caso, as variaveis ultimaChegada (variaveis pq e um vetor), seguirao distribuicao exponencial 
Ja o valor da tabela 4, no caso, as variaveis tempoAtendimento, seguirao distribuicao de poisson*/

int main()
{
	double cliente[MAX], ultimaChegada[MAX], tempoDeChegada[MAX];
	double tempoAtendimento[MAX], tempoInicio[MAX], tempoFila[MAX];
	double tempoFim[MAX], tempoClienteBan[MAX], tempoLivreCaixa[MAX];
	double percent, eXP, lambda;
	int i=0, clientes, valor;
	double n=0, P=1; 	/* Valores usados para metodo de poisson */
	
	valor=50;			/* Atribuindo o valor 50 para a seed do algoritmo de geracao de valores aleatorios */
	clientes=20;		/* Em vez de deixar os clientes aleatorios, atribuirei 20 clientes max logo */
	lambda=12;			/* Como a media da exponencial e 12, criaremos uma variavel que define essa media para testar futuras mudancas */
	eXP=pow(e, -6);
	
	for(i=0; i<clientes; i++)
	{
		cliente[i]=i+1;
		
		/* Usando o metodo de congruencia linear multiplicativa para definir novos valores aleatorios */
		valor=valor*MAX%127;									/* Definindo o tempo desde a ultima chegada, usar 127 porque ele e primo */
		percent=valor/127.00;									/* Transformando valores aleatorios inteiros em reais. Deixar os 0 apos a mantica pq se nao o valor ser truncado como inteiro */
		ultimaChegada[i]=(1/lambda);							/* Fazendo a primeira parte da equacao para exponencial: (-(1/lambda)*ln(1-ui)) onde u e o valor aleatorio da vez */
		ultimaChegada[i]=0-(ultimaChegada[i]*log(1-percent));	/* Em C, a funcao logaritmo natural, e escrita apenas log, enquanto log na base 10 e escrita log10 */
		
		/* Pegando valores de atendimento usando a frequencia acumulada ja dada na lista */
		if(ultimaChegada[i]<=0.35)
			ultimaChegada[i]=10;
		else if(ultimaChegada<=0.75)
			ultimaChegada[i]=12;
		else
			ultimaChegada[i]=14;
		
		if(i==0)														/* Caso ele tenha chegado primeiro */
			tempoDeChegada[i]=ultimaChegada[i];							/* O tempo de chegada no relogio sera o tempo desde a ultima chegada */
		else															/* Caso ele nao tenha chegado primeiro */
			tempoDeChegada[i]=ultimaChegada[i]+tempoDeChegada[i-1];		/* O tempo de chegada dele sera todo o tempo que ja passou mais a ultima chegada */
		
		/* Reaproveitando os valores aleatorios ja gerados para fazer os calculos da tabela 4, ou, tempoAtendimento */
		while(1)
		{
			P=P*percent;												/* Passo 2, reatribuir o valor de P */
			if(P<eXP)													/* Caso a condicao de aceitacao esteja concluida, calculamos o tempo de atendimento e resetamos os valores de n e P */
			{
				tempoAtendimento[i]=60/n;
				n=0;
				P=1;
				break;
			}else														/* Caso nao, permanecera no laco ate que a condicao seja satisfeita */
			{
				n++;
				valor=valor*MAX%127;
				percent=valor/127.00;
			}
		}
		
		
		
		if(i==0 || ((tempoAtendimento[i-1]-ultimaChegada[i])<=0))						/* Caso seja o primeiro cliente ou o caixa tiver ficado desocupado */
			tempoInicio[i]=tempoDeChegada[i];
		else
			tempoInicio[i]=tempoDeChegada[i]+(tempoAtendimento[i-1]-ultimaChegada[i]);
		
		if(i==0 || ((tempoAtendimento[i-1]-ultimaChegada[i])<=0))														/* Caso seja o primeiro cliente */
			tempoFila[i]=0;
		else
			tempoFila[i]=tempoAtendimento[i-1]-ultimaChegada[i];		/* Tempo na fila sera */
		
		tempoFim[i]=tempoAtendimento[i]+tempoInicio[i];					/* Tempo final do atendimento */
		
		tempoClienteBan[i]=tempoFila[i]+tempoAtendimento[i];			/* Tempo do cliente no banco */
		
		if(i==0)
			tempoLivreCaixa[i]=tempoDeChegada[i];
		else
			tempoLivreCaixa[i]=tempoDeChegada[i]-tempoFim[i-1];
	}
	
	printf("| Cliente | Chegada | Chegada relogio | Servico | Inicio | Fila | Final | Banco | Livre |\n");
	
	for(i=0; i<clientes; i++)
	{
		printf("|    %0.0lf    |  %0.2lf  |      %0.2lf     |  %0.2lf  |  %0.2lf  | %0.2lf  | %0.2lf | %0.2lf | %0.2lf |\n", 
		cliente[i], ultimaChegada[i], tempoDeChegada[i],
		tempoAtendimento[i], tempoInicio[i], tempoFila[i],
		tempoFim[i], tempoClienteBan[i], tempoLivreCaixa[i]);
	}
}