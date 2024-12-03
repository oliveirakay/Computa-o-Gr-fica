
#include <GL/glut.h>
#include <cmath>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint idsTextura[3];
float rotacaoX = 0.0;
float rotacaoY = 0.0;
float rotacaoZ = 0.0;

void carregarTextura(const char* nomeArquivo, int indice)
{
    int largura, altura, canais;

    unsigned char *dados = stbi_load(nomeArquivo, &largura, &altura, &canais, 0);

    if (!dados)
        exit(1);

    // gerar textura
    glGenTextures(1, &idsTextura[indice]);
    glBindTexture(GL_TEXTURE_2D, idsTextura[indice]);

    // configurar parametros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, (canais == 4) ? GL_RGBA : GL_RGB, 
                 largura, altura, 0, (canais == 4) ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, dados);

    // liberar a memoria da imagem
    stbi_image_free(dados);              
}

int ombro = 0, cotovelo = 0, pulso = 0;
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 15.0f;
bool rotatingCamera = false;
bool animatingCamera = false;
float animationSpeed = 0.005f;

void inicializa() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    carregarTextura("madeira.jpg", 0);
    carregarTextura("metal.jpg", 1);
    carregarTextura("esponja.jpg", 2);
}

void desenhaCubo(float tamanho, int texturaIndice) {
    glBindTexture(GL_TEXTURE_2D, idsTextura[texturaIndice]);
    glPushMatrix();
    glScalef(tamanho, tamanho, tamanho);
    
    glBegin(GL_QUADS);
    // Face frontal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Face traseira
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

    // Face superior
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Face inferior
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

    // Face direita
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

    // Face esquerda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
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
    desenhaCubo(0.5f, 0);
    glPopMatrix();

    // Parte do cotovelo
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef(static_cast<float>(cotovelo), 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 0.4f, 1.0f);
    desenhaCubo(0.5f, 1);
    glPopMatrix();

    // Parte do pulso
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef(static_cast<float>(pulso), 0.0f, 0.0f, 1.0f);
    glTranslatef(0.5f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0f, 0.4f, 1.0f);
    desenhaCubo(0.5f, 2);
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

