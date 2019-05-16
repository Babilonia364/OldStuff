#include <iostream>				/* printf(), scanf(), abs(), std::min() std::max() */
#include <math.h>				/* floor() */

#define ROWS 10
#define COLUMNS 10

int main()
{
	double pointIni[2], pointEnd[2];	/* ponto de inicio e ponto de fim da reta que sera desenahda na tela */
	double minX, maxX;					/* Maximos e minimos dos valores de x e y da reta */
	double minY, maxY;
	int matrix[ROWS][COLUMNS];			/* Matriz criada com linhas e colunas para representar uma tela */
	double angCoef;						/* Coeficiente angular da reta */
	int x, y;							/* auxiliares x e y para desenhar a reta na tela */
	
	/* Coordenadas de x */
	pointIni[0]=8;
	pointEnd[0]=5;
	/* Coordenadas de y */
	pointIni[1]=-2;
	pointEnd[1]=5;
	
	printf("Coordenadas do ponto inicial:\n");
	scanf("%lf%lf", &pointIni[0], &pointIni[1]);
	printf("\n");
	printf("Coordenadas do ponto final:\n");
	scanf("%lf%lf", &pointEnd[0], &pointEnd[1]);
	printf("\n");
	
	if(pointIni[0]==pointEnd[0])					/* Esse if e else poderia ser um try-catch... */
		angCoef=0.0;
	else
		angCoef = (pointEnd[1]-pointIni[1])/		/* i=0 serao os valores de x e i=1 serao os de y */
				  (pointEnd[0]-pointIni[0]);		/* Determinando o coeficiente angular da reta */
	
	/* Determinando os máximos e minimos de das coordenadas de x e y para facilitar futuras operacoes */
	minX=std::min(pointIni[0], pointEnd[0]);
	maxX=std::max(pointIni[0], pointEnd[0]);
	minY=std::min(pointIni[1], pointEnd[1]);
	maxY=std::max(pointIni[1], pointEnd[1]);

	printf("Coeficiente Angular: %lf\n", angCoef);	/* Lembrar de apagar */

	for(int j=0; j<COLUMNS; j++)
		for(int i=0; i<ROWS; i++)
			matrix[i][j]=0;						/* Iniciando a matriz com zeros */

	/* Desenhando efetivamente a reta: inicio */
	
	x=(int)floor(minX);
	
	if(x<0)													/* Caso o ponto inicial de x esteja fora da tela */
		x=0;												/* Começar o primeiro ponto com 0 */

	y=(int)floor((angCoef*(x-pointIni[0]))+pointIni[1]);	/* Calculando o proximo valor de y */
	
	if(y<0)													/* Caso o ponto de y no qual x seja 0 também esteja fora da tela */
	{
		y=0;												/* y sera setado como 0 */
		if(angCoef==0.0)
			x=pointIni[0];
		else
			x=(int)floor(((y-pointIni[1])/angCoef)+pointIni[0]);	/* Sera calculado o primeiro ponto para x dentro da tela */
	}else if(y>=COLUMNS-1)
	{
		y=COLUMNS-1;
		if(angCoef==0.0)
			x=pointIni[0];
		else
			x=(int)floor(((y-pointIni[1])/angCoef)+pointIni[0]);
	}
	
	while(true)
	{
		if((x>=ROWS || y >= COLUMNS) ||
		   (x<0 || y<0))
			break;
		if(((x>=minX)&&(x<=maxX)) &&			/* Caso x pertenca ao conjunto de pontos de x que pertecem a reta */
		   ((y>=minY)&&(y<=maxY)))				/* Caso y pertenca ao conjunto de pontos de y que pertecem a reta */
			matrix[x][y]=1;
		else
			break;
		if(abs((int)(maxX-minX))>=abs((int)(maxY-minY)))	/* Caso uma das coordenadas tenha mais pontos na reta que a outra */
		{													/* O algoritmo percorrera a reta usando esta coordenada */
			x++;
			y=(int)floor((angCoef*(x-pointIni[0]))+pointIni[1]);
		}
		else
		{
			if(angCoef<0.0)
				y--;
			else
				y++;
			if(angCoef==0.0)
				x=pointIni[0];
			else
				x=(int)floor(((y-pointIni[1])/angCoef)+pointIni[0]);
		}
	}
	
	/* Fim */
	
	/* Imprimindo a telinha */
	for(int j=(COLUMNS-1); j>=0; j--)
	{
		for(int i=0; i<ROWS; i++)
		{
			if(matrix[i][j]==0)
				printf("- ");
			else
				printf("# ");
		}
		printf("\n");
	}
}
