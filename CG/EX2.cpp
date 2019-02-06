#include <GL/glut.h>

#define LARGURA 500
#define ALTURA 500

#define CLAR 150
#define CALT 305
#define COL 100
#define COA 100

void Desenha_Carinha();
void Desenha_Cabecao();
void Desenha_Braco();
void Desenha_Franja();
void Desenha_Ante_Braco();

float teta1=0.0, teta2=0.0;
float up=0, left=0;

void Desenha_Cabecao()
{
	
	glColor3f(0.5f, 0.5f, 0.5f);						/* Definindo a cor para tons de cinza, UI!!! */
	glBegin(GL_QUADS);
		glVertex2i(CLAR		, CALT	  );
		glVertex2i(CLAR		, CALT+100);
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex2i(CLAR+100	, CALT+100);
		glVertex2i(CLAR+100	, CALT	  );
	glEnd();
}

void Desenha_Franja()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex2i(CLAR	,	 CALT+100);
		glColor3f(0.1f, 0.1f, 0.1f);
		glVertex2i(CLAR+100, CALT+100);
		glVertex2i(CLAR+100, CALT+50 );
	glEnd();
}

void Desenha_Carinha()
{
	glColor3f(0.0f, 0.0f, 0.5f);
	glPointSize(16);
	glBegin(GL_POINTS);
		glVertex2i(CLAR+25, CALT+75);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex2i(CLAR+75, CALT+75);
	glEnd();
}

void Desenha_Boquinha()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
		for(int i=25, j=25; i<=75; i=i+2)
		{
			if(j%2==0)
				j=(j-7);
			else
				j=(j+7);
			glVertex2i(CLAR+i, CALT+j);
		}
	glEnd();
}

void Desenha_Corpo()
{
	
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2i(COL		,	COA		);
		glVertex2i(COL		,	COA+200	);
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex2i(COL+200	,	COA+200	);
		glVertex2i(COL+200	,	COA		);
	glEnd();
}

void Desenha_Braco()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(COL+205, COA+100);
		glVertex2i(COL+205, COA+200);
		glVertex2i(COL+245, COA+200);
		glVertex2i(COL+245, COA+100);
	glEnd();
}

void Desenha_Ante_Braco()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2i(COL+205, COA+40);
		glVertex2i(COL+205, COA+95);
		glVertex2i(COL+245, COA+95);
		glVertex2i(COL+245, COA+40);
	glEnd();
}

void Desenha()
{
	glTranslatef(left, up, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_Cabecao();
	Desenha_Carinha();
	Desenha_Boquinha();
	Desenha_Franja();
	Desenha_Corpo();
	glTranslatef(325.0, 300.0, 0.0);
	glRotatef(teta1, 0.0, 0.0, 1.0);
	glTranslatef(-325.0, -300.0, 0.0);
	Desenha_Braco();
	glTranslatef(325.0, 300.0, 0.0);
	glRotatef(teta2, 0.0, 0.0, 1.0);
	glTranslatef(-325.0, -300.0, 0.0);
	Desenha_Ante_Braco();
	
	glFlush();
}
void GerenciaTeclado(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch(key)
	{
		case 'W':
		case 'w':
			glPopMatrix();
			glTranslatef(0.0, 5.0, 0.0);
			glPushMatrix();
			up+=5;
			break;
		
		case 'A':
		case 'a':
			glPopMatrix();
			glTranslatef(-5.0, 0.0, 0.0);
			glPushMatrix();
			left=left-5;
			break;
		
		case 'S':
		case 's':
			glPopMatrix();
			glTranslatef(0.0, -5.0, 0.0);
			glPushMatrix();
			up=up-5;
			break;
		
		case 'D':
		case 'd':
			glPopMatrix();
			glTranslatef(5.0, 0.0, 0.0);
			glPushMatrix();
			left+=5;
			break;
		
		//Escalonamento
		case 'O':
		case 'o':
			glPopMatrix();
			glTranslatef(-200.0, -200.0, 0.0);
			glScalef(0.5, 0.5, 1.0);
			glTranslatef(600.0, 600.0, 0.0);
			glPushMatrix();
			break;
		
		case 'P':
		case 'p':
			glPopMatrix();
			glTranslatef(-200.0, -200.0, 0.0);
			glScalef(1.5, 1.5, 1.0);
			glTranslatef(75.0, 75.0, 0.0);
			glPushMatrix();
			break;
		
		//Rotacao
		case 'K':
		case 'k':
			teta1+=5;
			glPopMatrix();
			glLoadIdentity();
			glutDisplayFunc(Desenha);
			glPushMatrix();
			break;

		case 'L':
		case 'l':
			teta2+=5;
			glPopMatrix();
			glLoadIdentity();
			glutDisplayFunc(Desenha);
			glPushMatrix();
			break;
		
		case ',':
			teta1=teta1-5;
			glPopMatrix();
			glLoadIdentity();
			glutDisplayFunc(Desenha);
			glPushMatrix();
			break;
		
		case '.':
			teta2=teta2-5;
			glPopMatrix();
			glLoadIdentity();
			glutDisplayFunc(Desenha);
			glPushMatrix();
			break;
		
		//CLear
		case 'C':
		case 'c':
			glPopMatrix();
			glLoadIdentity();
			glPushMatrix();
			teta1=teta2=0.0;
			up=left=0.0;
			break;
	}
	glutPostRedisplay();
	
}

void Inicia()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	 
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA, 0, ALTURA, -1 ,1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Robo emo");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(GerenciaTeclado);
	Inicia();
	glutMainLoop();
}
