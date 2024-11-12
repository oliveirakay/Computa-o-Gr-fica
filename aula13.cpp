#include <GL/glut.h>
#include <cmath>  // Para funções trigonométricas

int ombro = 0, cotovelo = 0;
float cameraAngleX = 0.0f, cameraAngleY = 0.0f, lightIntensity = 1.0f;
GLuint textura;

// Função de inicialização
void inicializa() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    // Configuração inicial da luz
    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_diffuse[] = { lightIntensity, lightIntensity, lightIntensity, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Configuração da textura (placeholder para uma textura)
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char texData[3] = {255, 255, 255}; // Branco
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Configuração da câmera
    gluLookAt(5 * sin(cameraAngleX), 5 * sin(cameraAngleY), 5 * cos(cameraAngleX),
              0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
        glTranslatef(0.0, 0.0, -5.0);
        glPushMatrix();
            glTranslatef(-1.0, 0.0, 0.0);
            glRotatef((float)ombro, 0.0, 0.0, 1.0);
            glTranslatef(1.0, 0.0, 0.0);

            glPushMatrix();
                glScalef(2.0, 0.4, 1.0);
                glBindTexture(GL_TEXTURE_2D, textura);  // Aplica textura
                glutSolidCube(1.0);  // Usa SolidCube ao invés de WireCube para textura
            glPopMatrix();

            glTranslatef(1.0, 0.0, 0.0);
            glRotatef((float)cotovelo, 0.0, 0.0, 1.0);
            glTranslatef(1.0, 0.0, 0.0);

            glPushMatrix();
                glScalef(2.0, 0.4, 1.0);
                glBindTexture(GL_TEXTURE_2D, textura);  // Aplica textura
                glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

// Função para controle do teclado
void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'o':
            ombro = (ombro + 5) % 360;
            glutPostRedisplay();
            break;
        case 'O':
            ombro = (ombro - 5) % 360;
            glutPostRedisplay();
            break;
        case 'c':
            cotovelo = (cotovelo + 5) % 360;
            glutPostRedisplay();
            break;
        case 'C':
            cotovelo = (cotovelo - 5) % 360;
            glutPostRedisplay();
            break;
        case '+':  // Aumenta intensidade da luz
            lightIntensity = std::min(1.0f, lightIntensity + 0.1f);
            glutPostRedisplay();
            break;
        case '-':  // Diminui intensidade da luz
            lightIntensity = std::max(0.0f, lightIntensity - 0.1f);
            glutPostRedisplay();
            break;
        case 27:  // ESC para sair
            exit(0);
            break;
    }
}

// Função para controle do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cameraAngleX += 0.1f;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        cameraAngleY += 0.1f;
    }
    glutPostRedisplay();
}

// Função de redimensionamento
void reshape(int largura, int altura) {
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)largura / (float)altura, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Função para o menu
void menu(int option) {
    switch (option) {
        case 1:  // Reseta articulações
            ombro = 0;
            cotovelo = 0;
            break;
        case 2:  // Reseta intensidade da luz
            lightIntensity = 1.0f;
            break;
    }
    glutPostRedisplay();
}

// Cria o menu interativo
void criaMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Resetar Articulacoes", 1);
    glutAddMenuEntry("Resetar Intensidade da Luz", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Modelo Hierárquico com OpenGL");

    inicializa();
    criaMenu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
