#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define LARGURA  600		/* Width */
#define ALTURA   800		/* Heigth */

int pos_x, pos_y;
int dir_x, dir_y;

void Draw_House()
{
	/* Cor azul */
	glColor3f(0.0, 0.0, 1.0);
	
	/* Funcao dos anos 90 para desenhar quadrados */
	glBegin(GL_QUADS);
		glVertex2i(LARGURA/10, ALTURA/10);
		glVertex2i(LARGURA/10, ALTURA/5 );
		glVertex2i(LARGURA/5 , ALTURA/5 );
		glVertex2i(LARGURA/5 , ALTURA/10);
	glEnd();
	
	/* Cor vermelha */
	glColor3f(1.0, 0.0, 0.0);
	
	/* Draw triangles */
	glBegin(GL_TRIANGLES);
		glVertex2i(LARGURA/10								, ALTURA/5 );
		glVertex2i(LARGURA/10+((LARGURA/5)-(LARGURA/10))/2	, ALTURA/4 );
		glVertex2i(LARGURA/5								, ALTURA/5 );
	glEnd();
	
	/* Color: Dunno */
	glColor3f(0.5, 0.6, 0.2);
	
	/* Draw more quads */
	glBegin(GL_QUADS);
		glVertex2i(LARGURA/8.5, ALTURA/10 );
		glVertex2i(LARGURA/8.5, ALTURA/6.5);
		glVertex2i(LARGURA/7  , ALTURA/6.5);
		glVertex2i(LARGURA/7  , ALTURA/10 );
	glEnd();
	
	/* Color: Grey */
	glColor3f(0.5, 0.5, 0.5);
	
	/* No more quads */
	glBegin(GL_QUADS);
		glVertex2i(LARGURA/6.5, ALTURA/8);
		glVertex2i(LARGURA/6.5, ALTURA/6.5);
		glVertex2i(LARGURA/5.5, ALTURA/6.5);
		glVertex2i(LARGURA/5.5, ALTURA/8);
	glEnd();
}

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/* Doing the thing */
	glTranslated(pos_x, pos_y, 0.0);
	
	Draw_House();
	
	glutSwapBuffers();
}

void Animation(int value)
{
	/* When the steering vector change, change the translation position, não tradução mas translação */
	if(dir_x%2==0)
		pos_x += 1;
	else
		pos_x -= 1;
	if(dir_y%2==0)
		pos_y += 1;
	else
		pos_y -= 1;
	
	/* If the point closest to the edge touch the edge, change de steering vector */
	if((pos_x+LARGURA/5)==LARGURA)
		dir_x++;
	else if((pos_x+LARGURA/10)==0)
		dir_x++;
	if((pos_y+ALTURA/4)==ALTURA)
		dir_y++;
	else if((pos_y+ALTURA/10)==0)
		dir_y++;
	
	glutPostRedisplay();
	glutTimerFunc(10, Animation, 1);
}

void Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, LARGURA, 0, ALTURA, -1 ,1);
}

/* I'M STIIIIIIIIIIIIIIIIIIIL IN A DREAM, SNEAK EATEEEEEEEEEEEEEER!!! */
int main(int argc, char **argv)
{
	/* Just some random stuff */
	srand (time(NULL));
	
	dir_x=rand()%100;
	dir_y=rand()%40;
	
	/* End */
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Arcana 21 - O Mundo");
	glutDisplayFunc(Draw);
	Init();
	glutTimerFunc(100, Animation, 1);
	//glutIdleFunc(Anima);
	glutMainLoop();
}