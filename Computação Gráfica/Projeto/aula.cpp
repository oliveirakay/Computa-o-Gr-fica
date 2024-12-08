#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

float distanciaCamera = 10.0f;
float anguloCamera = 0.0f; // Define a câmera inicialmente de frente
float velocidadeRotacao = 0.5f;

float anguloBracos = 0.0f;
float anguloPernas = 0.0f;
bool aumentandoBracos = true;
bool aumentandoPernas = true;

float direcaoPersonagem = 0.0f; // Ângulo inicial do personagem (frente para a tela)
bool andando = false;
bool correndo = false;
bool desacelerando = false; // Indica se o personagem está desacelerando

void atualizaAnimacao(int value) {
    if (andando || correndo) {
        float velocidade = correndo ? 6.0f : 4.0f;

        if (aumentandoBracos) {
            anguloBracos += velocidade;
            if (anguloBracos > 45.0f) aumentandoBracos = false;
        } else {
            anguloBracos -= velocidade;
            if (anguloBracos < -45.0f) aumentandoBracos = true;
        }

        if (aumentandoPernas) {
            anguloPernas += velocidade;
            if (anguloPernas > 45.0f) aumentandoPernas = false;
        } else {
            anguloPernas -= velocidade;
            if (anguloPernas < -45.0f) aumentandoPernas = true;
        }
    } else if (desacelerando) {
        // Reduz gradualmente os ângulos dos braços e pernas até 0
        if (anguloBracos > 0.0f) {
            anguloBracos -= 2.0f;
            if (anguloBracos < 0.0f) anguloBracos = 0.0f;
        } else if (anguloBracos < 0.0f) {
            anguloBracos += 2.0f;
            if (anguloBracos > 0.0f) anguloBracos = 0.0f;
        }

        if (anguloPernas > 0.0f) {
            anguloPernas -= 2.0f;
            if (anguloPernas < 0.0f) anguloPernas = 0.0f;
        } else if (anguloPernas < 0.0f) {
            anguloPernas += 2.0f;
            if (anguloPernas > 0.0f) anguloPernas = 0.0f;
        }

        // Se ambos os ângulos forem 0, desativa a desaceleração
        if (anguloBracos == 0.0f && anguloPernas == 0.0f) {
            desacelerando = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualizaAnimacao, 0);
}

void teclado(unsigned char key, int x, int y) {
    if (key == 'a') {
        andando = true;
        correndo = false;
        direcaoPersonagem = -M_PI / 4; // Ângulo -45° (anti-horário)
    } else if (key == 'A') {
        correndo = true;
        andando = false;
        direcaoPersonagem = -M_PI / 4; // Ângulo -45° (anti-horário)
    } else if (key == 'd') {
        andando = true;
        correndo = false;
        direcaoPersonagem = M_PI / 4; // Ângulo +45° (horário)
    } else if (key == 'D') {
        correndo = true;
        andando = false;
        direcaoPersonagem = M_PI / 4; // Ângulo +45° (horário)
    } else if (key == 's') {
        andando = true;
        correndo = false;
        direcaoPersonagem = 0.0f; // Ângulo 0° (frente para a tela)
    } else if (key == 'S') {
        correndo = true;
        andando = false;
        direcaoPersonagem = 0.0f; // Ângulo 0° (frente para a tela)
    } else if (key == 'w') {
        andando = true;
        correndo = false;
    } else if (key == 'W') {
        correndo = true;
        andando = false;
    }
    glutPostRedisplay();
}

void tecladoUp(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A' || key == 'd' || key == 'D' || key == 's' || key == 'S') {
        andando = false;
        correndo = false;
        desacelerando = true; // Ativa a desaceleração
    } else if (key == 'w') {
        andando = false;
    } else if (key == 'W') {
        correndo = false;
    }
    glutPostRedisplay();
}


void desenhaCubo(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_QUADS);

    // Frente
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);

    // Trás
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);

    // Esquerda
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);

    // Direita
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);

    // Cima
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);

    // Embaixo
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, -y, z);
    glVertex3f(-x, -y, z);

    glEnd();
}

void desenhaPersonagem()
{
    // Cabeça
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.8f);
    desenhaCubo(0.5f, 0.5f, 0.5f);
    glPopMatrix();

    // Tronco
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    desenhaCubo(0.5f, 0.75f, 0.25f);
    glPopMatrix();
    // Braço esquerdo
    glPushMatrix();
    glTranslatef(-0.75f, 0.25f, 0.0f);          // Move para a posição inicial
    glTranslatef(0.0f, 0.75f, 0.0f);            // Move para que o topo do cubo seja o pivô
    glRotatef(-anguloBracos, 1.0f, 0.0f, 0.0f); // Rotaciona ao redor do topo
    glTranslatef(0.0f, -0.75f, 0.0f);           // Volta para a posição original
    glColor3f(1.0f, 0.75f, 0.8f);
    desenhaCubo(0.25f, 0.75f, 0.25f);
    glPopMatrix();

    // Braço direito
    glPushMatrix();
    glTranslatef(0.75f, 0.25f, 0.0f);          // Move para a posição inicial
    glTranslatef(0.0f, 0.75f, 0.0f);           // Move para que o topo do cubo seja o pivô
    glRotatef(anguloBracos, 1.0f, 0.0f, 0.0f); // Rotaciona ao redor do topo
    glTranslatef(0.0f, -0.75f, 0.0f);          // Volta para a posição original
    glColor3f(1.0f, 0.75f, 0.8f);
    desenhaCubo(0.25f, 0.75f, 0.25f);
    glPopMatrix();

    // Perna esquerda
    glPushMatrix();
    glTranslatef(-0.25f, -1.5f, 0.0f);         // Move para a posição inicial
    glTranslatef(0.0f, 1.0f, 0.0f);            // Move para que o topo do cubo seja o pivô
    glRotatef(anguloPernas, 1.0f, 0.0f, 0.0f); // Rotaciona ao redor do topo
    glTranslatef(0.0f, -1.0f, 0.0f);           // Volta para a posição original
    glColor3f(0.0f, 0.0f, 0.5f);
    desenhaCubo(0.25f, 1.0f, 0.25f);
    glPopMatrix();

    // Perna direita
    glPushMatrix();
    glTranslatef(0.25f, -1.5f, 0.0f);           // Move para a posição inicial
    glTranslatef(0.0f, 1.0f, 0.0f);             // Move para que o topo do cubo seja o pivô
    glRotatef(-anguloPernas, 1.0f, 0.0f, 0.0f); // Rotaciona ao redor do topo
    glTranslatef(0.0f, -1.0f, 0.0f);            // Volta para a posição original
    glColor3f(0.0f, 1.0f, 0.5f);
    desenhaCubo(0.25f, 1.0f, 0.25f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 2.0, distanciaCamera,  // Câmera centralizada e olhando para frente
              0.0, 1.0, 0.0,             // Ponto para onde a câmera está olhando
              0.0, 1.0, 0.0);            // Vetor "para cima"

    // Aplica a direção do personagem
    glPushMatrix();
    glRotatef(direcaoPersonagem * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
    desenhaPersonagem();
    glPopMatrix();

    glutSwapBuffers();
}

void inicializa() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Personagem Minecraft");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoUp);
    glutTimerFunc(16, atualizaAnimacao, 0);

    glutMainLoop();
    return 0;
}