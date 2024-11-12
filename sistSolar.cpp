#include <GL/glut.h>

float anguloSol = 0.0;
float anguloMercurio = 0.0;
float anguloVenus = 0.0;
float anguloTerra = 0.0;
float anguloMarte = 0.0;

float anguloMercurioRotacao = 0.0;
float anguloVenusRotacao = 0.0;
float anguloTerraRotacao = 0.0;
float anguloMarteRotacao = 0.0;

float cameraPosZ = -20.0;
float velocidadeOrbita = 1.0;
float velocidadeRotacao = 1.0;

void inicializa() {
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glEnable(GL_DEPTH_TEST);
}

void desenhaEsfera(GLfloat raio)
{
 glutWireSphere(raio, 20, 20);   
}

void display() {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();

 glTranslatef(0.0, 0.0, cameraPosZ);

 // sol
 glPushMatrix();
   glRotatef(anguloSol, 0.0, 1.0, 0.0);
   glColor3f(1.0, 1.0, 0.0);
   desenhaEsfera(3.0);
 glPopMatrix();

 // mercurio
 glPushMatrix();
   glRotatef(anguloMercurio * velocidadeOrbita, 0.0, 1.0, 0.0);
   glTranslatef(6.0, 0.0, 0.0);
   glPushMatrix();
     glRotatef(anguloMercurioRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
     glColor3f(0.7, 0.7, 0.7);
     desenhaEsfera(0.3);
   glPopMatrix();  
 glPopMatrix();

 // venus
 glPushMatrix();
   glRotatef(anguloVenus * velocidadeOrbita, 0.0, 1.0, 0.0);
   glTranslatef(9.0, 0.0, 0.0);
   glPushMatrix();
     glRotatef(anguloVenusRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
     glColor3f(0.8, 0.5, 0.0);
     desenhaEsfera(0.7);
   glPopMatrix();  
 glPopMatrix();

 // terra
 glPushMatrix();
   glRotatef(anguloTerra * velocidadeOrbita, 0.0, 1.0, 0.0);
   glTranslatef(12.0, 0.0, 0.0);
   glPushMatrix();
     glRotatef(anguloTerraRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
     glColor3f(0.0, 0.0, 1.0);
     desenhaEsfera(1.0);
   glPopMatrix();  
 glPopMatrix();

 // marte
 glPushMatrix();
   glRotatef(anguloMarte * velocidadeOrbita, 0.0, 1.0, 0.0);
   glTranslatef(15.0, 0.0, 0.0);
   glPushMatrix();
     glRotatef(anguloMarteRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
     glColor3f(1.0, 0.0, 0.0);
     desenhaEsfera(0.8);
   glPopMatrix();  
 glPopMatrix();

 glutSwapBuffers();
}

void reshape(int largura, int altura) {
 glViewport(0, 0, largura, altura);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 gluPerspective(65.0, (float)largura / (float)altura, 1.0, 50.0);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}

void atualiza(int valor)
{
 anguloSol += 0.2;

 anguloMercurio += 1.5 * velocidadeOrbita;
 anguloMercurioRotacao += 5.0 * velocidadeRotacao;

 anguloVenus += 1.2 * velocidadeOrbita;
 anguloVenusRotacao += 2.0 * velocidadeRotacao;

 anguloTerra += 0.8 * velocidadeOrbita;
 anguloTerraRotacao += 1.0 * velocidadeRotacao;

 anguloMarte += 0.6 * velocidadeOrbita;
 anguloMarte += 0.8 * velocidadeRotacao;

 glutPostRedisplay();
 glutTimerFunc(16, atualiza, 0);   
}
 
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutCreateWindow("Sistema Solar");

 inicializa();

 glutDisplayFunc(display);
 glutReshapeFunc(reshape);

 glutTimerFunc(1000, atualiza, 0);   
  
 glutMainLoop();

 return 0;
}