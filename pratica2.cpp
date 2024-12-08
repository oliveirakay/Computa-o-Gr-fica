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

    if (!dados) {
        printf("Erro ao carregar a textura %s\n", nomeArquivo);
        exit(1);
    }

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

void inicializa() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    carregarTextura("madeira.jpg", 0);
    carregarTextura("metal.jpg", 1);
    carregarTextura("esponja.jpg", 2);
}

void desenhaEsfera(float raio, int texturaIndice) {
    glBindTexture(GL_TEXTURE_2D, idsTextura[texturaIndice]);

    int stacks = 20; // Divisões ao longo do eixo z
    int slices = 20; // Divisões ao longo do círculo

    for (int i = 0; i <= stacks; i++) {
        float lat0 = M_PI * (-0.5f + (float)(i) / stacks);    // Latitude inferior
        float z0  = sin(lat0) * raio;                           // Coordenada z do ponto inferior
        float r0  = cos(lat0) * raio;                           // Raio do círculo na latitude inferior

        float lat1 = M_PI * (-0.5f + (float)(i + 1) / stacks);  // Latitude superior
        float z1 = sin(lat1) * raio;                            // Coordenada z do ponto superior
        float r1 = cos(lat1) * raio;                            // Raio do círculo na latitude superior

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2 * M_PI * (float)(j) / slices;          // Longitude
            float x = cos(lng);                                  // Coordenada x do ponto
            float y = sin(lng);                                  // Coordenada y do ponto

            // Coordenadas de textura
            float s = (float)(j) / slices;                       // Coordenada s da textura
            float t0 = (float)(i) / stacks;                      // Coordenada t da textura
            float t1 = (float)(i + 1) / stacks;                  // Coordenada t+1 da textura

            glTexCoord2f(s, t0);
            glVertex3f(x * r0, y * r0, z0);                      // Ponto inferior da esfera

            glTexCoord2f(s, t1);
            glVertex3f(x * r1, y * r1, z1);                      // Ponto superior da esfera
        }
        glEnd();
    }
}

void desenhaCilindro(float raio, float altura, int texturaIndice) {
    glBindTexture(GL_TEXTURE_2D, idsTextura[texturaIndice]);
    GLUquadric* cilindro = gluNewQuadric();
    gluQuadricTexture(cilindro, GL_TRUE);
    gluCylinder(cilindro, raio, raio, altura, 32, 32); // Criando o cilindro com a textura aplicada
    gluDeleteQuadric(cilindro);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posicionar a câmera
    gluLookAt(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Definir uma boa posição para a câmera

    // Parte do ombro
    glPushMatrix();
    glRotatef(static_cast<float>(rotacaoX), 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);

    // Cilindro do ombro
    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);  // Girar para alinhar ao eixo Y
    desenhaCilindro(0.4f, 2.0f, 0); // Cilindro de ombro
    glPopMatrix();

    // Adiciona a esfera manual na junção do ombro
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);  // Posição da esfera
    desenhaEsfera(0.3f, 2); // Esfera de junção
    glPopMatrix();

    // Parte do cotovelo
    glTranslatef(2.0f, 0.0f, 0.0f);  // Posicionar cotovelo na extremidade do ombro
    glRotatef(static_cast<float>(rotacaoY), 0.0f, 0.0f, 1.0f);

    // Cilindro do cotovelo
    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);  // Girar para alinhar ao eixo Y
    desenhaCilindro(0.3f, 2.0f, 1); // Cilindro de cotovelo
    glPopMatrix();

    // Adiciona a esfera manual na junção do cotovelo
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);  // Posição da esfera
    desenhaEsfera(0.3f, 2); // Esfera de junção
    glPopMatrix();

    // Parte do pulso
    glTranslatef(2.0f, 0.0f, 0.0f);  // Posicionar pulso na extremidade do cotovelo
    glRotatef(static_cast<float>(rotacaoZ), 0.0f, 0.0f, 1.0f);

    // Cilindro do pulso
    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f);  // Girar para alinhar ao eixo Y
    desenhaCilindro(0.2f, 1.5f, 2); // Cilindro de pulso
    glPopMatrix();

    // Adiciona a esfera manual na junção do pulso
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);  // Posição da esfera
    desenhaEsfera(0.2f, 2); // Esfera de junção
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        rotacaoX += 5;
        break;
    case 's':
        rotacaoX -= 5;
        break;
    case 'a':
        rotacaoY += 5;
        break;
    case 'd':
        rotacaoY -= 5;
        break;
    case 'q':
        rotacaoZ += 5;
        break;
    case 'e':
        rotacaoZ -= 5;
        break;
    case 27: // ESC
        exit(0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modelo com Esferas nas Junções");

    inicializa();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}
