 #include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float color[3] = {1.0f, 0.0f, 0.0f};
float xPos = 0.0, yPos = 0.0;
float size = 0.2;

float tx = 0.0, ty = 0.0;
float angulo = 0.0;
float escala = 1.0;

float speedX = 0.02, speedY = 0.02;

void desenhaQuadrado(float x, float y)
{
    glColor3f(color[0], color[1], color[2]);

    glBegin(GL_QUADS);
        glVertex2f(xPos - size, yPos - size);
        glVertex2f(xPos + size, yPos - size);
        glVertex2f(xPos + size, yPos + size);
        glVertex2f(xPos - size, yPos + size);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity(); // Reset transformations

    glTranslatef(tx, ty, 0.0);
    glRotatef(angulo, 0.0, 0.0, 1.0);
    glScalef(escala, escala, 1.0);

    desenhaQuadrado(xPos, yPos);

    glutSwapBuffers();
}

void atualiza(int valor)
{
    tx += speedX;
    ty += speedY;
    angulo += 3.0;

    // Reflete a direção ao atingir as bordas da tela
    if(tx + size > 1.0 || tx - size < -1.0)
        speedX = -speedX;
    if(ty + size > 1.0 || ty - size < -1.0)
        speedY = -speedY;

    glutPostRedisplay();
    glutTimerFunc(16, atualiza, 0);
}

void mouse(int botao, int estado, int x, int y)
{
    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        // Altera as velocidades de movimento aleatoriamente ao clicar com o botão esquerdo do mouse
        speedX = ((rand() % 100) / 100.0) * 0.04 - 0.02;
        speedY = ((rand() % 100) / 100.0) * 0.04 - 0.02;

        color[0] = (rand() % 100) / 100.0;
        color[1] = (rand() % 100) / 100.0;
        color[2] = (rand() % 100) / 100.0;
    }
    if(botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {
        speedX==0? speedX = ((rand() % 100) / 100.0) * 0.04 - 0.02 : speedX = 0 ;
        speedY==0? speedY = ((rand() % 100) / 100.0) * 0.04 - 0.02 : speedY = 0 ;
    }
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'w':
        ty += 0.05;
        break;
    case 's':
        ty -= 0.05;
        break;
    case 'a':
        tx -= 0.05;
        break;
    case 'd':
        tx += 0.05;
        break;
    case 'q':
        angulo += 5.0;
        break;
    case 'e':
        angulo -= 5.0;
        break;
    case 'm':
        escala += 0.1;
        break;
    case 'n':
        escala -= 0.1;
        break;
    }
    glutPostRedisplay(); // Atualiza a tela após pressionar a tecla
}

void inicializa()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Alterado para GLUT_DOUBLE
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformacoes Geometricas");

    inicializa();

    glutKeyboardFunc(teclado);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutTimerFunc(16, atualiza, 0);

    glutMainLoop();

    return 0;
}
