//Compilar usando g++ teste.cpp -o teste collision.cpp -lglut -lGLU -lGL && ./teste

#include <GL/glut.h>
#include "collision.h"

#define LARGURA  1500		/* Width */
#define ALTURA   1000		/* Heigth */

double pos_x=-28, pos_y=-3;
double pos_x2=5, pos_y2=5;
double radius=0.7, wQad=3, vel=0.5;
double anterior=1000;

void init()
{
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
void mapa(){
    //-28 é o x mínimo e -18 é o y mínimo
    //a bola inicia no x = -28 e y = -3
	for(int i=-28, j=-18; i<=-1; i+=3)
	{
		glPushMatrix();
			//inicio do pisinho inferior
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

	//End of maze: Begin in -1;-18

    //espaco onde a bola deve chegar

	//End of maze: End in -5;-18
	for(int i=5, j=-18; i<=29; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //final do pisinho
    //inicio da parede do lado esquerdo

	for(int i=-28, j=-15; j<=-6; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //espaco onde a bola inicia

	for(int i=-28, j=0; j<=18; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //final da parede esquerda
    //inicio do teto

	for(int i=-25, j=18; i<=29; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
    
    //final do teto
    //inicio da parede direita

	for(int i=29, j=15; j>=-15; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //final da parede direita
    //essa parte aqui foi meio random pra ver onde era as coisas
	
	for(int i=-15, j=9; i>=-21; i-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

	for(int i=-21, j=6; j>=-9; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
    //cubo adicional pra fazer o encaixe e deixar um gapziho abaixo da entrada
	for(int i=-24, j=-9; i>=-27; i-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

	for(int i=-12, j=9; i<=-9; i+=3)
	{
		//primeira linha superior
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
    //terceira coluna

	for(int i=-9, j=6; j<=3; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //terceira linha
	for(int i=-12, j=3; i<=-15; i-=3)
	{
		glPushMatrix();
			glTranslatef(-12,3,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
    //segunda coluna

	for(int i=-15, j=-3; i<=-12; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
    //aqui é um cubo random
    //continuacao da terceira coluna
	
	for(int i=-15, j=-6; j>=-15; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
    //outra parte aleatoria
    glPushMatrix();
        glTranslatef(-9,-3,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, -9, -3, &anterior, &pos_x2, &pos_y2);
    //quarta coluna
	
	for(int i=-3, j=9; j>=-12; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
    //quarta linha
    //"ultima linha"
	
	for(int i=-6, j=-12; i>=-9; i-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	

    glPushMatrix();
        glTranslatef(-9,-9,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, -9, -9, &anterior, &pos_x2, &pos_y2);
    //ultima linha propriamente dita, mas so tem uns cubos espalhados nela
    glPushMatrix();
        glTranslatef(-6,-15,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, -6, -15, &anterior, &pos_x2, &pos_y2);

	for(int i=0, j=9; i<=9; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //continuacao da quarta coluna
	
	for(int i=-3, j=12; j<=15; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
	for(int i=12, j=9; i<=15; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

	for(int i=15, j=6; j>=-12; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

	for(int i=9, j=-12; j>=-15; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    // ultima coluna
	
    glPushMatrix();
        glTranslatef(21,-6,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 21, -6, &anterior, &pos_x2, &pos_y2);
	
	for(int i=21, j=0; j<=6; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //paredinha que bloqueia a as duas ultimas colunas
	
	for(int i=24, j=6; i<=27; i+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
    //ainda ultima coluna
    glPushMatrix();
        glTranslatef(21,9,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 21, 9, &anterior, &pos_x2, &pos_y2);

    glPushMatrix();
        glTranslatef(21,0,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 21, 0, &anterior, &pos_x2, &pos_y2);

	for(int i=21, j=-9; j>=-15; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
	for(int i=21, j=12; j<=15; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}

    //outro cubo pra bloquear a parte de cima
    glPushMatrix();
        glTranslatef(24,6,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 24, 6, &anterior, &pos_x2, &pos_y2);

    //mais coisa da quarta linha pra bloquear uma entrada
	
    glPushMatrix();
        glTranslatef(0,-12,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 0, -12, &anterior, &pos_x2, &pos_y2);
    //quinta coluna
	
	for(int i=3, j=-9; j>=-12; j-=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
	for(int i=3, j=-6; j<=3; j+=3)
	{
		glPushMatrix();
			glTranslatef(i,j,0);
			ParametrosIluminacao(1.0, 0.0, 0.0);
			glutSolidCube(3);
		glPopMatrix();
		checkSomething(pos_x, pos_y, i, j, &anterior, &pos_x2, &pos_y2);
	}
	
    //so um cubo pra impedir uma entrada
    glPushMatrix();
        glTranslatef(6,3,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 6, 3, &anterior, &pos_x2, &pos_y2);

    //sexta coluna
    glPushMatrix();
        glTranslatef(9,3,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 9, 3, &anterior, &pos_x2, &pos_y2);

    glPushMatrix();
        glTranslatef(9,0,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 9, 0, &anterior, &pos_x2, &pos_y2);

    glPushMatrix();
        glTranslatef(9,-3,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 9, -3, &anterior, &pos_x2, &pos_y2);

    glPushMatrix();
        glTranslatef(9,-6,0);
        ParametrosIluminacao(1.0, 0.0, 0.0);
        glutSolidCube(3);
    glPopMatrix();
	checkSomething(pos_x, pos_y, 9, -6, &anterior, &pos_x2, &pos_y2);
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'W':
		case 'w':
			pos_y+=vel;
			colision(&pos_x, &pos_y, &pos_x2, &pos_y2, &vel, &wQad, key);
			break;

		case 'S':
		case 's':
			pos_y-=vel;
			colision(&pos_x, &pos_y, &pos_x2, &pos_y2, &vel, &wQad, key);
			break;
		
		case 'A':
		case 'a':
			pos_x-=vel;
			colision(&pos_x, &pos_y, &pos_x2, &pos_y2, &vel, &wQad, key);
			break;
		
		case 'D':
		case 'd':
			pos_x+=vel;
			colision(&pos_x, &pos_y, &pos_x2, &pos_y2, &vel, &wQad, key);
			break;
	}
	glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // move back a bit
    glTranslatef( 0, 0, -35 );

    static float angle = 0;
    angle += 1.0f;
    mapa();
	
	ParametrosIluminacao(0.5, 0.5, 0.5);
	
	glPushMatrix ();
		glTranslatef(pos_x, pos_y, 0.0);
		glutSolidSphere(radius, 50, 50);
	glPopMatrix();
	
    glutSwapBuffers();

}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(LARGURA, ALTURA);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("mAzEmArE");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

	glutKeyboardFunc(GerenciaTeclado);

    init();

    glutMainLoop();
    return 0;
}
