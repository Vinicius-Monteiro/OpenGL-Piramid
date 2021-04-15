#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     0.0, 1.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6
#define ROSA 	 1.0, 0.2, 0.8
#define ROXO	 0.4, 0.0, 0.8
#define BRANCO	 1.0, 1.0, 1.0

static GLfloat vertices[27]={
	0.0,  30.0, 30.0, /* 0 */ // left top front
	30.0, 30.0, 30.0, /* 1 */ // right top front
	30.0,  0.0, 30.0, /* 2 */ // right bot front
	0.0,   0.0, 30.0, /* 3 */ // left bot front
	0.0,  30.0,  0.0, /* 4 */ // left top back
	30.0, 30.0,  0.0, /* 5 */ // right top back
	30.0,  0.0,  0.0, /* 6 */ // right bot back
	0.0,   0.0,  0.0, /* 7 */ // left bot back
	15.0, 45.0, 15.0, /* 8 */ // middle top middle
};


static GLubyte frenteIndices[]    		 = {0,3,2,1}; // anti horario
static GLubyte trasIndices[]      		 = {4,5,6,7}; // horario
static GLubyte esquerdaIndices[]  		 = {0,4,7,3}; // anti horario
static GLubyte direitaIndices[]   		 = {1,2,6,5}; // horario
static GLubyte topoIndices[]      		 = {0,1,5,4}; // anti horario
static GLubyte fundoIndices[]     		 = {3,7,6,2}; // horario
static GLubyte piramideFrenteIndices[] 	 = {0, 1, 8}; // anti horario
static GLubyte piramideTrasIndices[] 	 = {4, 8, 5}; //horario horario
static GLubyte piramideEsquerdaIndices[] = {0, 8, 4}; // anti horario
static GLubyte piramideDireitaIndices[]	 = {1, 5, 8}; // horario
static GLubyte piramideFundoIndices[]	 = {0, 4, 5, 1}; // horario

static int eixoy, eixox;
int largura, altura;

int main(int argc, char** argv){
	int i;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (256, 256); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow (argv[0]);
	init();
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho (-50, 50, -50, 50, -50 , 50);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	largura=w; 
	altura=h;
}

void display(void){
	glPushMatrix();
	glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
	glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glColor3f (AZUL); /* frente do cubo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frenteIndices);

	glColor3f (AMARELO); /* esquerda do cubo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

	glColor3f (VERMELHO); /* tras do cubo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, trasIndices);

	glColor3f (VERDE); /* direita do cubo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, direitaIndices);

	glColor3f (LARANJA); /* fundo do cubo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

	glColor3f (ROSA); /* frente da piramide */
  	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramideFrenteIndices);

	glColor3f (ROXO); /* esquerda da piramide*/
  	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramideEsquerdaIndices);

	glColor3f (CYAN); /* tras da piramide */
  	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramideTrasIndices);

	glColor3f (BRANCO); /* direita da piramide */
  	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramideDireitaIndices);

	glDisableClientState (GL_VERTEX_ARRAY);

	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'a':
		printf("%d, %d\n",x,y);
		break;
	case 'y':
		eixoy = (eixoy + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		eixoy = (eixoy - 5) % 360;
		glutPostRedisplay();
		break;
	case 'x':
		eixox = (eixox + 5) % 360;
		glutPostRedisplay();
		break;
	case 'X':
		eixox = (eixox - 5) % 360;
		glutPostRedisplay();
		break;
	case 'p':
		glLoadIdentity();
		gluPerspective(75.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
		gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'o':
		glLoadIdentity();
		glOrtho (-50, 50, -50, 50, -50 , 50);
		glutPostRedisplay();
		break;
	}
}