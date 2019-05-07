#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>		/* sqrt */

#define LARGURA  500		/* Width */
#define ALTURA   500		/* Heigth */

double pos_x, pos_y;
double pos_x2, pos_y2;
double radius=0.7, wQad=2;
int dir_x, dir_y;
int dir_x2, dir_y2;
int flag;

void ParametrosIluminacao(GLfloat R, GLfloat G, GLfloat B)
{
	GLfloat percent = 0.8;
	/* Parâmetros para a Luz GL_LIGHT0 sendo uma fonte de Luz Pontual */
	GLfloat luzAmbiente[4]={0.5, 0.5, 0.5, 1.0};	/* cor azul */
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};	  	/* cor branca */
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; 	/* cor branca - brilho */
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};	/* Fonte de Luz Pontual */

	/* Define os parâmetros da luz de número 0 (Luz Pontual) */
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	/* Ativa o uso de uma fonte de luz ambiente */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	/* Características do material */
	GLfloat ka[4]={0.11, 0.06, 0.11, 1.0};		/* Reflete porcentagens da cor ambiente */
	GLfloat kd[4]={R*percent, G*percent, B*percent, 1.0};		/* Reflete porcentagens da cor difusa */
	GLfloat ks[4]={1.0, 1.0, 1.0, 1.0};		/* Reflete porcentagens da cor especular */
	GLfloat shininess = 60.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks); /* Refletância do material */
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);   /* Concentração do brilho */
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();				/* Carrega a identidade para resetar o matriz antes dos desenhos */
	
    gluLookAt(0.0, 0.0, 30.0,		/* eye */
    		  0.0, 0.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */
	
	ParametrosIluminacao(0.5, 0.5, 0.5);
	
	glPushMatrix ();
		glTranslatef(pos_x, pos_y, 0.0);
		glutSolidSphere(radius, 50, 50);
	glPopMatrix();
	
	if(pos_x>5 || pos_x<-5)
		flag=1;
	if(flag)
	{
		glPushMatrix ();
			//glTranslatef(pos_x2, pos_y2, 0.0);
			//glutSolidSphere(0.7, 50, 50);
			glutSolidCube(wQad);
		glPopMatrix();
	}
	
	printf("%lf, %lf\n", pos_x, pos_y);
	
	glutSwapBuffers();
}

void changedirections(double* pos_x, double* pos_y, int* dir_x, int* dir_y)
{
	/* When the steering vector change, change the translation position, não tradução mas translação */
	if(*dir_x%2==0)
		*pos_x += 0.1;
	else
		*pos_x -= 0.1;
	if(*dir_y%2==0)
		*pos_y += 0.1;
	else
		*pos_y -= 0.1;
	
	/* If the point closest to the edge touch the edge, change de steering vector */
	if((*pos_x+0.7)>=10.0)			/* Largura */
		(*dir_x)++;
	else if((*pos_x+0.7)<=-9.0)
		(*dir_x)++;
	if((*pos_y+0.7)>=10.0)			/* Altura */
		(*dir_y)++;
	else if((*pos_y+0.7)<=-9.0)
		(*dir_y)++;
}

void colision(double pos_x1, double pos_y1, int* dir_x1, int* dir_y1, double pos_x2, double pos_y2, int* dir_x2, int* dir_y2)
{
	double dx, dy, dz, result;
	
	dx = pos_x1 - pos_x2;
	dy = pos_y1 - pos_y2;
	dz = 0;
	result = sqrt((dx*dx)+(dy*dy)+(dz*dz));
	dx=sqrt(2);
	
	if(result <= (0.7+dx))
	{
		(*dir_x1)++;
		(*dir_y1)++;
		(*dir_x2)++;
		(*dir_y2)++;
	}
}

void Animation(int value)
{
	changedirections(&pos_x, &pos_y, &dir_x, &dir_y);
	
	if(flag)
	{
		//changedirections(&pos_x2, &pos_y2, &dir_x2, &dir_y2);
		colision(pos_x, pos_y, &dir_x, &dir_y, pos_x2, pos_y2, &dir_x2, &dir_y2);
	}
	
	glutPostRedisplay();
	glutTimerFunc(10, Animation, 1);
}

void Inicializa()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(40.0f, ((GLfloat)LARGURA/(GLfloat)ALTURA), 1, 50.0f);
	
	/* Habilita o uso de iluminação */
	glEnable(GL_LIGHTING);
	/* Habilita a luz de número 0 */
	glEnable(GL_LIGHT0);
	/* Habilita o depth-buffering para remoção de faces escondidas */
	glEnable(GL_DEPTH_TEST);

	/* Modelos de Iluminação Defaut */
	glShadeModel(GL_SMOOTH); 		/* Gouraud */
}

int main(int argc, char **argv)
{
	/* Just some random stuff */
	srand (time(NULL));
	
	dir_x=rand()%100;
	dir_y=rand()%40;
	
	/* End */
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);								/* Tamanho da tela, vai esticar as figuras */
	glutInitWindowPosition (0, 0);
	glutCreateWindow("PIM BAU");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutTimerFunc(100, Animation, 1);
	glutMainLoop();
}
