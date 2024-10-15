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

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'r':
        case 'R':
            red = 1.0f; green = 0.0f; blue = 0.0f;
            break;
        case 'g':
        case 'G':
            red = 0.0f; green = 1.0f; blue = 0.0f;
            break;
        case 'b':
        case 'B':
            red = 0.0f; green = 0.0f; blue = 1.0f;
            break;    
    }
    glutPostRedisplay();
}

void renderiza() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaQuadrado();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Quadrado e Teclado");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(renderiza);
    glutKeyboardFunc(teclado);

    glutMainLoop();

    return 0;
}
