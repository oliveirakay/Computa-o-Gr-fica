#include <GL/glut.h>

void inicializa() {
 glClearColor(0.1, 0.1, 0.1, 1.0);
 glEnable(GL_DEPTH_TEST);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0, 1.0, 1.0, 100.0);
 glMatrixMode(GL_MODELVIEW);
}

void desenhaObjetos3D()
{
 // esfera
 glPushMatrix();
   glTranslatef(-7.0, 7.0, 0.0);
   glColor3f(1.0, 0.0, 0.0);
   glutWireSphere(2.0, 20, 20);
   //glutSolidSphere(2.0, 20, 20);
 glPopMatrix();

 // cubo
 glPushMatrix();
   glTranslatef(7.0, 7.0, 0.0);
   glColor3f(0.0, 1.0, 0.0);
   glutWireCube(3.0);
   //glutSolidCube(3.0);
 glPopMatrix();

// chaleira
 glPushMatrix();
   glTranslatef(0.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   //glutWireTeapot(2.0);
   glutSolidTeapot(3.0);
 glPopMatrix();

 // cone
 glPushMatrix();
   glTranslatef(-7.0, -7.0, 0.0);
   glRotatef(45.0, 0.0, 1.0, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glutWireCone(2.0, 4.0, 20, 20);
   //glutSolidCone(2.0, 4.0, 20, 20);
 glPopMatrix();

 // toro
 glPushMatrix();
   glTranslatef(5.0, -7.0, 0.0);
   glColor3f(1.0, 1.0, 0.0);
   glutWireTorus(0.5, 2.0, 20, 20);
   //glutSolidTorus(0.5, 2.0, 20, 20);
 glPopMatrix();

 // dodecaedro (12)
 glPushMatrix();
   glTranslatef(-10.0, 0.0, 0.0);
   glColor3f(0.5, 0.0, 0.5);
   glutWireDodecahedron();
   //glutSolidDodecahedron();
 glPopMatrix();

 // octaedro (8)
 glPushMatrix();
   glTranslatef(10.0, 0.0, 0.0);
   glColor3f(0.0, 1.0, 1.0);
   glScalef(2.0, 2.0, 2.0);
   glutWireOctahedron();
   //glutSolidOctahedron();
 glPopMatrix();

 // tetraedro (4)
 glPushMatrix();
   glTranslatef(-10.0, -5.0, 0.0);
   glColor3f(1.0, 0.5, 0.0);
   glScalef(2.0, 2.0, 2.0);
   glutWireTetrahedron();
   //glutSolidTetrahedron();
 glPopMatrix();

 // icosaedro (20)
 glPushMatrix();
   glTranslatef(10.0, -5.0, 0.0);
   glColor3f(1.0, 0.0, 1.0);
   glScalef(2.0, 2.0, 2.0);
   glutWireIcosahedron();
   //glutSolidIcosahedron();
 glPopMatrix();


}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();

 // camera
 gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

 desenhaObjetos3D();

 glutSwapBuffers();
}
 
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 800);
 glutCreateWindow("Objetos 3D");

 inicializa();

 glutDisplayFunc(display);
 
 glutMainLoop();

 return 0;
}