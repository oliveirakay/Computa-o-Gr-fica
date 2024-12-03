
#include <GL/glut.h>
#include <cmath>
#include <algorithm>

int ombro = 0, cotovelo = 0, pulso = 0;
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 15.0f;
bool rotatingCamera = false;
bool animatingCamera = false;
float animationSpeed = 0.005f; // Update: Changed animationSpeed to 0.005f

void inicializa() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void desenhaCubo(float tamanho) {
    glPushMatrix();
    glScalef(tamanho, tamanho, tamanho);
    
    // Face frontal
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);  // Vermelho
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();

    // Face traseira
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);  // Verde
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();

    // Face superior
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);  // Azul
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);  // Amarelo
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    // Face direita
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glEnd();

    // Face esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 1.0f);  // Ciano
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    glPopMatrix();
}

void display() {
    if (animatingCamera) {
        cameraAngleY += animationSpeed;
        if (cameraAngleY > 2 * M_PI) {
            cameraAngleY -= 2 * M_PI;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posicionar a câmera
    float camX = cameraDistance * sin(cameraAngleY) * cos(cameraAngleX);
    float camY = cameraDistance * sin(cameraAngleX);
    float camZ = cameraDistance * cos(cameraAngleY) * cos(cameraAngleX);
    gluLookAt(camX, camY, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Parte do ombro
    glPushMatrix();
    glRotatef(static_cast<float>(ombro), 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 0.4f, 1.0f);
    desenhaCubo(0.5f);
    glPopMatrix();

    // Parte do cotovelo
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef(static_cast<float>(cotovelo), 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 0.4f, 1.0f);
    desenhaCubo(0.5f);
    glPopMatrix();

    // Parte do pulso
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef(static_cast<float>(pulso), 0.0f, 0.0f, 1.0f);
    glTranslatef(0.5f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0f, 0.4f, 1.0f);
    desenhaCubo(0.5f);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

    if (animatingCamera) {
        glutPostRedisplay();
    }
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'o':
        ombro = (ombro + 5) % 360;
        glutPostRedisplay();
        break;
    case 'O':
        ombro = (ombro - 5 + 360) % 360;
        glutPostRedisplay();
        break;
    case 'c':
        cotovelo = std::min(cotovelo + 5, 150);
        glutPostRedisplay();
        break;
    case 'C':
        cotovelo = std::max(cotovelo - 5, -150);
        glutPostRedisplay();
        break;
    case 'p':
        pulso = std::min(pulso + 5, 90);
        glutPostRedisplay();
        break;
    case 'P':
        pulso = std::max(pulso - 5, -90);
        glutPostRedisplay();
        break;
    case 'r':
    case 'R':
        animatingCamera = !animatingCamera;
        if (animatingCamera) {
            glutIdleFunc(display);
        } else {
            glutIdleFunc(NULL);
        }
        glutPostRedisplay();
        break;
    case 'w':
        cameraAngleX = std::min(cameraAngleX + 0.1f, static_cast<float>(M_PI_2));
        glutPostRedisplay();
        break;
    case 's':
        cameraAngleX = std::max(cameraAngleX - 0.1f, -static_cast<float>(M_PI_2));
        glutPostRedisplay();
        break;
    case 'a':
        cameraAngleY -= 0.1f;
        glutPostRedisplay();
        break;
    case 'd':
        cameraAngleY += 0.1f;
        glutPostRedisplay();
        break;
    case '+':
        cameraDistance = std::max(cameraDistance - 0.5f, 5.0f);
        glutPostRedisplay();
        break;
    case '-':
        cameraDistance = std::min(cameraDistance + 0.5f, 30.0f);
        glutPostRedisplay();
        break;
    case 27:  // ESC key
        exit(0);
        break;
    }
}

void reshape(int largura, int altura) {
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, static_cast<float>(largura) / static_cast<float>(altura), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    if (animatingCamera) {
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Braço Mecânico com 3 Eixos - Câmera Orbital");
    inicializa();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


