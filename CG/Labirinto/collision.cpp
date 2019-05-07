#include <GL/glut.h>
#include <math.h>
#include "collision.h"

void colision(double* pos_x, double* pos_y, double* pos_x2, double* pos_y2, double* vel, double* wQad, unsigned char c)
{
	double dx, dy, dz, result;
	
	dx = *pos_x - *pos_x2;
	dy = *pos_y - *pos_y2;
	dz = 0;
	result = sqrt((dx*dx)+(dy*dy)+(dz*dz));
	dx=sqrt(*wQad);
		
	if(result <= (dx))
	{
		switch(c)
		{
			case 'W':
			case 'w':
				*pos_y-=(*vel);
				break;

			case 'S':
			case 's':
				*pos_y+=(*vel);
				break;
			
			case 'A':
			case 'a':
				*pos_x+=(*vel);
				break;
			
			case 'D':
			case 'd':
				*pos_x-=(*vel);
				break;
		}
	}
}

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

void checkSomething(double somex1, double somey1, double somex2, double somey2, double* ant, double* p_x, double* p_y)
{
	double dx, dy, dz, result;
	dx=somex1-somex2;
	dy=somey1-somey2;
	dz=0;
	result = sqrt((dx*dx)+(dy*dy)+(dz*dz));
	if(result<=(*ant))
	{
		*ant=result;
		*p_x=somex2;
		*p_y=somey2;
	}
}


