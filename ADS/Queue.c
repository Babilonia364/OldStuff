#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20								/* Debugador definido para debugar, ide e para os fracos */
#define bug(x) printf("%s: %d\n", #x, x)

int main()
{
	double cliente[MAX], ultimaChegada[MAX], tempoDeChegada[MAX];
	double tempoAtendimento[MAX], tempoInicio[MAX], tempoFila[MAX];
	double tempoFim[MAX], tempoClienteBan[MAX], tempoLivreCaixa[MAX];
	int i=0, clientes, valor;
	
	srand(time(NULL));			/* Usando o tempo como seed para não repetir os valores */
	clientes=(rand()%20)+1;			/* modulo 20 para os clientes não passarem de 20 */
	
	for(i=0; i<clientes; i++)
	{
		cliente[i]=i+1;
		
		valor=rand()%101;				/* Definindo o tempo desde a ultima chegada */
		if(valor<=35)					/* Em 35% dos casos, o ultimo tempo sera 10 */
			ultimaChegada[i]=10;
		else if(valor<=75)				/* Em 40% dos casos, o tempo sera 12 */
			ultimaChegada[i]=12;		/* Neste caso, usamos a frequencia acumulada */
		else
			ultimaChegada[i]=14;		/* Em 25% dos casos, o tempo sera 14 */
		
		if(i==0)														/* Caso ele tenha chegado primeiro */
			tempoDeChegada[i]=ultimaChegada[i];							/* O tempo de chegada no relogio sera o tempo desde a ultima chegada */
		else															/* Caso ele nao tenha chegado primeiro */
			tempoDeChegada[i]=ultimaChegada[i]+tempoDeChegada[i-1];		/* O tempo de chegada dele sera todo o tempo que ja passou mais a ultima chegada */
		
		//Esse negocio de chegada me lembra... coisas... ( ͡° ͜ʖ ͡°)
		
		valor=rand()%101;				/* Analogo a ultima chegada */
		if(valor<=30)
			tempoAtendimento[i]=9;
		else if(valor<=80)
			tempoAtendimento[i]=10;
		else
			tempoAtendimento[i]=11;
		
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
