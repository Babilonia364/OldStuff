#include <GL/glut.h>

/* Pode definir qualquer proporção que rodará, com tanto que o tamanho estimado caiba na tela, tratamento de erros que n sei fazer... ainda!!! */
#define LARGURA 500
#define ALTURA 600

void Desenha_triangulo()
{
	glColor3f(1.0, 1.0, 1.0);									/* Definindo a cor para branco */
	
	glBegin(GL_TRIANGLES);										/* Desenhando o triangulo */
		glVertex2i(0		, ALTURA/2);						/* Imaginando a uma tela com tamanho 800, cada viewport tera no maximo 400/400 de altura/largura */
		glVertex2i(LARGURA/2, ALTURA  );						/* Assim, esse triangulo começara "no meio da altura" */
		glVertex2i(LARGURA  , ALTURA/2);
	glEnd();
}

void Desenha_strip_triagulo()
{
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2i(LARGURA/2, ALTURA  );
		glVertex2i(0		, ALTURA/2);
		glVertex2i(LARGURA  , ALTURA/2);
		glColor3f(0.0, 0.0, 1.0);								/* Definindo a cor do ultimo vertice como azul para dar o efeito de fade */
		glVertex2i(LARGURA/2, 0		  );
	glEnd();
}

void Desenha_strip_linha()
{
	glColor3f(0.5, 1.0, 0.5);
	
	glBegin(GL_LINE_STRIP);
		glVertex2i(LARGURA/4, ALTURA/2);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(LARGURA-(LARGURA/4),ALTURA-(ALTURA/4));
		glVertex2i(LARGURA/2 ,0);
	glEnd();
}

void Desenha_quadrado()
{
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(LARGURA/2, ALTURA/2);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(LARGURA/2, ALTURA  );
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(LARGURA	, ALTURA  );
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i(LARGURA	, ALTURA/2);
	glEnd();
}

void Desenha()
{
	glClear(GL_COLOR_BUFFER_BIT);					/* Aparentemente pinta a tela com a cor de fundo como se tivesse em um eterno loop alternando entre desenha/"limpa" */
	
	/* Primeiro dos viewportanos */
	glViewport(0, ALTURA/2, LARGURA/2, ALTURA/2);	/*Criando uma viewport com metade das coordenadas do tamanho total*/
	glScissor(0, ALTURA/2, LARGURA/2, ALTURA/2);
	glEnable(GL_SCISSOR_TEST);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_triangulo();							/* Chamando a função de pintar o triângulo */
	
	/* Segundo viewport */
	glViewport(LARGURA/2, ALTURA/2, LARGURA/2, ALTURA/2);
	glScissor(LARGURA/2, ALTURA/2, LARGURA/2, ALTURA/2);
	glEnable(GL_SCISSOR_TEST);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_strip_triagulo();
	
	/* Terceiro viewport */
	glViewport(0, 0, LARGURA/2, ALTURA/2);
	glScissor(0, 0, LARGURA/2, ALTURA/2);
	glEnable(GL_SCISSOR_TEST);
	glClearColor(0.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_strip_linha();
	
	/* Quarto viewport */
	glViewport(LARGURA/2, 0, LARGURA/2, ALTURA/2);
	glScissor(LARGURA/2, 0, LARGURA/2, ALTURA/2);
	glEnable(GL_SCISSOR_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_quadrado();
	
	glFlush();										/* Aparentemente força a execução de comandos GL que estão no buffer e limpa eles, ver documentação */
}

void Inicializar()
{
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			/* Definindo a cor de fundo da janela de visu como branca, por que os 'f's? */
	
	glOrtho(0, LARGURA, 0, ALTURA, -1 ,1);			/* Esse tamanho aqui ele... meio que aumenta a resolução */
}

int main(int argc, char **argv)						/* Muitas coisas que fazem a openGL desenhar os paranauê */
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);			/* Tamanho da tela, vai esticar as figuras */
	glutInitWindowPosition(0, 0);
	glutCreateWindow("ZA WARUDO");
	glutDisplayFunc(Desenha);						/* Passando função como argumento de outra função, já fazem eras que n vejo isso */
	Inicializar();
	glutMainLoop();
}
