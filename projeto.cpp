#include <GL/glut.h>
#include <iostream>
#include <cmath> // Adicione esta linha para usar sin, cos, etc.


// Variáveis para controle de rotação das articulações
float shoulderAngle = 0.0f, elbowAngle = 0.0f;

// Variáveis para controle de iluminação
float lightIntensity = 1.0f;

// Variáveis de controle de câmera
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 5.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configuração inicial da luz
    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void drawArm() {
    // Desenha o ombro
    glPushMatrix();
        glRotatef(shoulderAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(2.0f, 0.5f, 0.5f);
            glutSolidCube(1.0f);
        glPopMatrix();

        // Desenha o cotovelo
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(elbowAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(2.0f, 0.5f, 0.5f);
            glutSolidCube(1.0f);
        glPopMatrix();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Configuração da câmera
    gluLookAt(cameraDistance * sin(cameraAngleX), cameraDistance * sin(cameraAngleY), cameraDistance * cos(cameraAngleX),
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Iluminação
    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    // Desenho do braço robótico
    drawArm();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': shoulderAngle += 5.0f; break; // Rotação do ombro
        case 's': shoulderAngle -= 5.0f; break;
        case 'e': elbowAngle += 5.0f; break; // Rotação do cotovelo
        case 'd': elbowAngle -= 5.0f; break;
        case '+': lightIntensity = std::min(1.0f, lightIntensity + 0.1f); break; // Aumenta a intensidade da luz
        case '-': lightIntensity = std::max(0.0f, lightIntensity - 0.1f); break; // Diminui a intensidade da luz
        case 27: exit(0); // Tecla ESC para sair
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cameraAngleX += 0.1f;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        cameraAngleY += 0.1f;
    }
    glutPostRedisplay();
}

void menu(int option) {
    switch (option) {
        case 1: shoulderAngle = 0.0f; elbowAngle = 0.0f; break; // Reinicia articulações
        case 2: lightIntensity = 1.0f; break; // Reseta intensidade da luz
    }
    glutPostRedisplay();
}

void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Resetar Articulacoes", 1);
    glutAddMenuEntry("Resetar Intensidade de Luz", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modelo 3D Articulado - OpenGL");

    init();
    createMenu();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
