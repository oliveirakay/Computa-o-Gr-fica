#include <GL/glut.h>

float posX = 0.0f;
float posY = 0.0f;
float size = 0.1f;
const float speed = 0.05f;
const float sizeStep = 0.01f;

float red = 1.0f, green = 0.0f, blue = 0.0f;

void desenhaQuadrado() {
  glColor3f(red, green, blue);
  glBegin(GL_QUADS);
    glVertex2f(-size + posX, -size + posY);
    glVertex2f(size + posX, -size + posY);
    glVertex2f(size + posX, size + posY);
    glVertex2f(-size + posX, size + posY);
  glEnd();
}

void renderiza() {
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaQuadrado();
  glFlush();
}

int main(int argc, char** argv)
 {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Quadrado e Teclado");

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glutDisplayFunc(renderiza);

  glutMainLoop();

  return 0;
}
//g++ -Wall -Iinclude -g main.cpp -o main.exe -Llib -lopengl32 -lglu32 -lfreeglut

