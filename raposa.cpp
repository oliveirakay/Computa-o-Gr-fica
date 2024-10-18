#include <GL/glut.h>

// Função para desenhar um triângulo com cor
void drawTriangle(float vertices[3][2], float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Função para desenhar um quadrado (ou trapézio) com cor
void drawQuad(float vertices[4][2], float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Função de renderização
void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Cabeça da raposa (laranja)
    float headColor[] = {1.0f, 0.6f, 0.0f};
    float headVertices[4][2] = {
        {-0.5f, -0.3f},
        {0.5f, -0.3f},
        {0.6f, 0.2f},
        {-0.6f, 0.2f}
    };
    drawQuad(headVertices, headColor);

    // Focinho da raposa (laranja claro)
    float muzzleColor[] = {1.0f, 0.8f, 0.5f};
    float muzzleVertices[4][2] = {
        {-0.2f, -0.3f},
        {0.2f, -0.3f},
        {0.15f, -0.1f},
        {-0.15f, -0.1f}
    };
    drawQuad(muzzleVertices, muzzleColor);

    // Orelhas (marrom)
    float earColor[] = {0.5f, 0.25f, 0.0f};
    float leftEarVertices[3][2] = {
        {-0.6f, 0.2f},
        {-0.35f, 0.55f},
        {-0.2f, 0.2f}
    };
    float rightEarVertices[3][2] = {
        {0.6f, 0.2f},
        {0.35f, 0.55f},
        {0.2f, 0.2f}
    };
    drawTriangle(leftEarVertices, earColor);
    drawTriangle(rightEarVertices, earColor);

    // Área escura nas orelhas
    float darkEarColor[] = {0.2f, 0.1f, 0.0f};
    float leftDarkEarVertices[3][2] = {
        {-0.55f, 0.3f},
        {-0.35f, 0.5f},
        {-0.3f, 0.2f}
    };
    float rightDarkEarVertices[3][2] = {
        {0.55f, 0.3f},
        {0.35f, 0.5f},
        {0.3f, 0.2f}
    };
    drawTriangle(leftDarkEarVertices, darkEarColor);
    drawTriangle(rightDarkEarVertices, darkEarColor);

    // Olhos (preto)
    float eyeColor[] = {0.0f, 0.0f, 0.0f};
    float leftEyeVertices[3][2] = {
        {-0.2f, 0.0f},
        {-0.1f, 0.0f},
        {-0.15f, 0.1f}
    };
    float rightEyeVertices[3][2] = {
        {0.2f, 0.0f},
        {0.1f, 0.0f},
        {0.15f, 0.1f}
    };
    drawTriangle(leftEyeVertices, eyeColor);
    drawTriangle(rightEyeVertices, eyeColor);

    // Nariz (preto)
    float noseColor[] = {0.0f, 0.0f, 0.0f};
    float noseVertices[3][2] = {
        {-0.05f, -0.3f},
        {0.05f, -0.3f},
        {0.0f, -0.25f}
    };
    drawTriangle(noseVertices, noseColor);

    glFlush();
}

// Função de inicialização
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Definir cor de fundo branca
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Configuração de visualização 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Raposa Estilizada OpenGL");

    init();  // Inicializar configurações

    glutDisplayFunc(render); // Chamar função de renderização

    glutMainLoop(); // Iniciar loop principal
    return 0;
}
//g++ -Wall -Iinclude -g raposa.cpp -o rap.exe -Llib -lopengl32 -lglu32 -lfreeglut 