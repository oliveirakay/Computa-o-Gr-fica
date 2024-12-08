#include <GL/glut.h>
#include <cmath>
#include <algorithm>


float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 10.0f;

float posX = 0.0f, posZ = 0.0f; // Posição do trator
float direcao = 0.0f; // Direção do trator (ângulo em graus)

float velocidade = 0.5f; // Velocidade do trator



void inicializa() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);   // Cor de fundo cinza escuro
    glEnable(GL_DEPTH_TEST);                // Habilita o teste de profundidade
    glEnable(GL_LIGHTING);                  // Habilita iluminação
    glEnable(GL_LIGHT0);                    // Habilita a luz 0

    GLfloat light_pos[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


void desenhaRoda(float raio, float largura) {
    int numLados = 32; // Número de lados do cilindro
    float anguloIncremento = 2.0f * M_PI / numLados;

    // Parte externa da roda (pneu preto)
    glColor3f(0.1f, 0.1f, 0.1f); // Cor preta para o pneu
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numLados; i++) {
        float angulo = i * anguloIncremento;
        float x = cos(angulo) * raio;
        float y = sin(angulo) * raio;

        glNormal3f(cos(angulo), sin(angulo), 0.0f);
        glVertex3f(x, y, largura / 2.0f);
        glVertex3f(x, y, -largura / 2.0f);
    }
    glEnd();

    // Tampão frontal do pneu
    glColor3f(0.1f, 0.1f, 0.1f); // Cor preta para o pneu
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, largura / 2.0f); // Centro do tampão frontal
    for (int i = 0; i <= numLados; i++) {
        float angulo = i * anguloIncremento;
        glVertex3f(cos(angulo) * raio, sin(angulo) * raio, largura / 2.0f);
    }
    glEnd();

    // Tampão traseiro do pneu
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -largura / 2.0f); // Centro do tampão traseiro
    for (int i = 0; i <= numLados; i++) {
        float angulo = i * anguloIncremento;
        glVertex3f(cos(angulo) * raio, sin(angulo) * raio, -largura / 2.0f);
    }
    glEnd();

    // Parte central (encaixe laranja)
    float raioEncaixe = raio * 0.5f; // Raio menor para o centro laranja
    glColor3f(.968f, 0.58f, 0.11f);    // Cor amarelo alaranjado para o encaixe

    // Frente do encaixe
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, largura / 2.0f + 0.01f); // Levemente para frente
    for (int i = 0; i <= numLados; i++) {
        float angulo = i * anguloIncremento;
        glVertex3f(cos(angulo) * raioEncaixe, sin(angulo) * raioEncaixe, largura / 2.0f + 0.01f);
    }
    glEnd();

    // Traseira do encaixe
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -largura / 2.0f - 0.01f); // Levemente para trás
    for (int i = 0; i <= numLados; i++) {
        float angulo = i * anguloIncremento;
        glVertex3f(cos(angulo) * raioEncaixe, sin(angulo) * raioEncaixe, -largura / 2.0f - 0.01f);
    }
    glEnd();
}


void desenhaCabine() {
    // Dimensões da cabine
    float larguraTeto = 2.f;  // Largura do teto
    float profundidadeTeto = 1.5f; // Profundidade do teto
    float alturaCabine = 1.8f; // Altura da cabine a partir do topo do trator
    float espessuraHaste = 0.2f; // Espessura das hastes

    // Hastes (quatro cantos da cabine)
    glColor3f(0.1f, 0.1f, 0.1f); // Preto
    for (int i = 0; i < 4; ++i) {
        float x = (i % 2 == 0) ? larguraTeto / 2 : -larguraTeto / 2;
        float z = (i < 2) ? profundidadeTeto / 2 : -profundidadeTeto / 2;

        glPushMatrix();
        glTranslatef(x, alturaCabine / 2, z);
        glScalef(espessuraHaste, alturaCabine, espessuraHaste);
        glutSolidCube(1.0f); // Cubo para representar a haste
        glPopMatrix();
    }

    // Teto da cabine
    glColor3f(1.0f, 0.5f, 0.0f); // Amarelo alaranjado
    glPushMatrix();
    glTranslatef(0.0f, alturaCabine, 0.0f);
    glScalef(larguraTeto, espessuraHaste, profundidadeTeto);
    glutSolidCube(1.0f); // Teto como um cubo achatado
    glPopMatrix();
}


float anguloBraco = 300.0f;  // Ângulo de rotação do braço
float anguloPá = 270.0f;     // Ângulo de rotação da pá

void desenhaPá() {
    // Dimensões da pá
    float larguraPá = 1.0f;       // Largura da pá
    float alturaPá = 0.8f;        // Altura da pá (para comportar mais coisas)
    float profundidadePá = 2.0f;  // Profundidade da pá

    // Desenhar a pá com base funda e laterais tampadas
    glPushMatrix();
    glColor3f(0.968f, 0.58f, 0.11f); // Amarelo alaranjado

    // Base da pá (trapezoidal)
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior esquerdo traseiro
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2);  // Inferior direito traseiro
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior direito frontal
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior esquerdo frontal
    glEnd();

    // Lado esquerdo da pá
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro esquerdo
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro esquerdo
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2);  // Superior frontal esquerdo
    glVertex3f(-larguraPá / 2, -alturaPá / 2, profundidadePá / 2);        // Inferior frontal esquerdo
    glEnd();

    // Lado direito da pá
    glBegin(GL_QUADS);
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro direito
    glVertex3f(larguraPá / 2, -alturaPá / 2, profundidadePá / 2);  // Inferior frontal direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior frontal direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro direito
    glEnd();

    // Traseira da pá
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior esquerdo traseiro
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2);  // Inferior direito traseiro
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior direito traseiro
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior esquerdo traseiro
    glEnd();

    glPopMatrix();
}

void desenhaBracoDuplo() {
    // Dimensões dos braços
    float larguraBraco = 0.3f;
    float alturaBraco = 3.0f;
    float profundidadeBraco = 0.2f;

    // Posição inicial dos braços (laterais do trator)
    float baseY = 1.0f;   // Altura do eixo dos braços
    float baseZDireita = 1.1f; // Deslocamento lateral do braço direito
    float baseZEsquerda = -1.1f; // Deslocamento lateral do braço esquerdo
    float baseX = -1.0f;  // Posição na frente do corpo do trator

    // Braço direito
    glPushMatrix();
    glTranslatef(baseX, baseY, baseZDireita);       // Posição do eixo de rotação (direita)
    glRotatef(anguloBraco, 0.0f, 0.0f, 1.0f);      // Rotação do braço em torno do eixo Z
    glTranslatef(0.0f, -alturaBraco / 2, 0.0f);    // Ajusta a posição do braço para girar corretamente

    // Desenha o braço direito
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Cinza escuro
    glScalef(larguraBraco, alturaBraco, profundidadeBraco);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();

    // Braço esquerdo
    glPushMatrix();
    glTranslatef(baseX, baseY, baseZEsquerda);      // Posição do eixo de rotação (esquerda)
    glRotatef(anguloBraco, 0.0f, 0.0f, 1.0f);      // Rotação do braço em torno do eixo Z
    glTranslatef(0.0f, -alturaBraco / 2, 0.0f);    // Ajusta a posição do braço para girar corretamente

    // Desenha o braço esquerdo
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Cinza claro
    glScalef(larguraBraco, alturaBraco, profundidadeBraco);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();

    // Desenhar a pá na ponta dos braços
    glPushMatrix();
    glTranslatef(baseX, baseY, 0.0f);              // Posição inicial da pá no eixo
    glRotatef(anguloBraco, 0.0f, 0.0f, 1.0f);      // Mesma rotação dos braços
    glTranslatef(0.0f, -alturaBraco, 0.0f);        // Ajusta a pá para a ponta dos braços
    glRotatef(anguloPá, 0.0f, 0.0f, 1.0f);         // Rotação da pá
    desenhaPá();
    glPopMatrix();
}

void desenhaCorpoTrator() {
    // Variáveis para ajustar o corpo do trator
    float larguraBase = 2.0f;  // Largura da base do corpo
    float alturaBase = 1.5f;   // Altura da base do corpo
    float profundidadeBase = 2.0f; // Profundidade do corpo
    float topoAjuste = 0.8f;   // Proporção da largura no topo em relação à base
    float alturaTopo = 0.7f;   // Altura relativa do topo (posição vertical máxima)

    glPushMatrix();

    // Escala geral do corpo do trator
    glScalef(larguraBase, alturaBase, profundidadeBase);

    glBegin(GL_QUADS);

    // Face frontal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -0.5f, 0.5f);           // Inferior esquerdo
    glVertex3f(1.0f, -0.5f, 0.5f);            // Inferior direito
    glVertex3f(topoAjuste, alturaTopo, 0.5f); // Superior direito
    glVertex3f(-topoAjuste, alturaTopo, 0.5f);// Superior esquerdo

    // Face traseira
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -0.5f, -0.5f);          // Inferior esquerdo
    glVertex3f(1.0f, -0.5f, -0.5f);           // Inferior direito
    glVertex3f(topoAjuste, alturaTopo, -0.5f);// Superior direito
    glVertex3f(-topoAjuste, alturaTopo, -0.5f);// Superior esquerdo

    // Face superior
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-topoAjuste, alturaTopo, -0.5f); // Traseiro esquerdo
    glVertex3f(topoAjuste, alturaTopo, -0.5f);  // Traseiro direito
    glVertex3f(topoAjuste, alturaTopo, 0.5f);   // Frontal direito
    glVertex3f(-topoAjuste, alturaTopo, 0.5f);  // Frontal esquerdo

    // Face inferior
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -0.5f, -0.5f);           // Traseiro esquerdo
    glVertex3f(1.0f, -0.5f, -0.5f);            // Traseiro direito
    glVertex3f(1.0f, -0.5f, 0.5f);             // Frontal direito
    glVertex3f(-1.0f, -0.5f, 0.5f);            // Frontal esquerdo

    // Face lateral direita
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -0.5f, -0.5f);            // Inferior traseiro
    glVertex3f(topoAjuste, alturaTopo, -0.5f); // Superior traseiro
    glVertex3f(topoAjuste, alturaTopo, 0.5f);  // Superior frontal
    glVertex3f(1.0f, -0.5f, 0.5f);             // Inferior frontal

    // Face lateral esquerda
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -0.5f, -0.5f);           // Inferior traseiro
    glVertex3f(-topoAjuste, alturaTopo, -0.5f);// Superior traseiro
    glVertex3f(-topoAjuste, alturaTopo, 0.5f); // Superior frontal
    glVertex3f(-1.0f, -0.5f, 0.5f);            // Inferior frontal

    glEnd();
    glPopMatrix();
}


float anguloBracoTraseiro = 150.0f;  // Ângulo de rotação do braço traseiro
float anguloAntebraco = 250.0f;      // Ângulo do antebraço traseiro
float anguloPaTraseira = 180.0f;     // Ângulo da pá traseira

void desenhaPáTraseira() {
    // Dimensões da pá traseira
    float larguraPá = 1.5f;       // Largura da pá
    float alturaPá = 0.7f;        // Altura da pá
    float profundidadePá = 1.0f;  // Profundidade da pá

    glPushMatrix();
    glColor3f(0.968f, 0.58f, 0.11f); // Amarelo alaranjado

    // Base da pá (fundo inclinado)
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro esquerdo
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2);  // Inferior traseiro direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior frontal direito
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior frontal esquerdo
    glEnd();

    // Lado esquerdo da pá
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro esquerdo
    glVertex3f(-larguraPá / 2, -alturaPá / 2, profundidadePá / 2);  // Inferior frontal esquerdo
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior frontal esquerdo
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro esquerdo
    glEnd();

    // Lado direito da pá
    glBegin(GL_QUADS);
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro direito
    glVertex3f(larguraPá / 2, -alturaPá / 2, profundidadePá / 2);  // Inferior frontal direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, profundidadePá / 2); // Superior frontal direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro direito
    glEnd();

    // Traseira da pá
    glBegin(GL_QUADS);
    glVertex3f(-larguraPá / 2, -alturaPá / 2, -profundidadePá / 2); // Inferior traseiro esquerdo
    glVertex3f(larguraPá / 2, -alturaPá / 2, -profundidadePá / 2);  // Inferior traseiro direito
    glVertex3f(larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro direito
    glVertex3f(-larguraPá / 2 * 0.8f, alturaPá / 2, -profundidadePá / 2); // Superior traseiro esquerdo
    glEnd();

    glPopMatrix();
}

void desenhaBracoTraseiro() {
    // Dimensões do braço e antebraço
    float larguraBraco = 0.3f;
    float alturaBraco = 2.4f;
    float profundidadeBraco = 0.3f;

    // Posição inicial do braço traseiro
    float baseX = 1.5f;  // Parte traseira do trator
    float baseY = 1.0f;  // Altura da base do braço
    float baseZ = 0.0f;  // Centralizado na parte traseira

    // Braço principal
    glPushMatrix();
    glTranslatef(baseX, baseY, baseZ);             // Posição do eixo de rotação
    glRotatef(anguloBracoTraseiro, 0.0f, 0.0f, 1.0f); // Rotação do braço principal em torno do eixo Z
    glTranslatef(0.0f, -alturaBraco / 2, 0.0f);    // Ajusta a posição para rotação correta

    // Desenhar o braço principal
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Cinza escuro
    glScalef(larguraBraco, alturaBraco, profundidadeBraco);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Antebraço (conectado ao braço principal)
    glPushMatrix();
    glTranslatef(0.0f, -alturaBraco / 2, 0.0f);    // Conecta o antebraço ao final do braço principal
    glRotatef(anguloAntebraco, 0.0f, 0.0f, 1.0f);  // Rotação do antebraço
    glTranslatef(0.0f, -alturaBraco / 2, 0.0f);    // Ajusta para o eixo correto de rotação

    // Desenhar o antebraço
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Cinza escuro
    glScalef(larguraBraco, alturaBraco, profundidadeBraco);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Pá na ponta do antebraço
    glPushMatrix();
    glTranslatef(0.3f, -alturaBraco / 2, 0.0f);    // Conecta a pá ao final do antebraço
    glRotatef(anguloPaTraseira, 0.0f, 0.0f, 1.0f); // Rotação da pá traseira
    desenhaPáTraseira();                           // Substituição pelo desenho da nova pá
    glPopMatrix();

    glPopMatrix(); // Final do antebraço
    glPopMatrix(); // Final do braço principal
}
void desenhaMapa() {
    glPushMatrix();
    glColor3f(0.5f, 0.8f, 0.5f); // Verde claro para o chão
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, -0.5f, -50.0f);
    glVertex3f(-50.0f, -0.5f, 50.0f);
    glVertex3f(50.0f, -0.5f, 50.0f);
    glVertex3f(50.0f, -0.5f, -50.0f);
    glEnd();
    glPopMatrix();
}


void desenhaTrator() {
    glPushMatrix();
    // Aplica a posição e rotação do trator
    glTranslatef(posX, 0.0f, posZ);
    glRotatef(direcao, 0.0f, 1.0f, 0.0f);

    // Desenhar o corpo do trator
    glColor3f(0.968f, 0.58f, 0.11f); // Amarelo alaranjado
    desenhaCorpoTrator();

    // Desenhar a cabine do motorista
    glPushMatrix();
    glTranslatef(0.5f, 1.0f, 0.0f); // Posição da cabine deslocada
    desenhaCabine();
    glPopMatrix();

    // Desenhar o braço frontal da retroescavadeira
    desenhaBracoDuplo();

    // Desenhar o braço traseiro da retroescavadeira
    desenhaBracoTraseiro();

    // Configuração das rodas
    float raioRodasTraseiras = 0.8f;   // Raio das rodas traseiras (maiores)
    float larguraRodasTraseiras = 0.7f; // Largura das rodas traseiras
    float raioRodasDianteiras = 0.6f;  // Raio das rodas dianteiras (menores)
    float larguraRodasDianteiras = 0.4f; // Largura das rodas dianteiras
    float posicaoRodasY = -0.5f;       // Altura das rodas
    float posicaoRodasTraseirasX = 1.3f;  // Posição X das rodas traseiras
    float posicaoRodasDianteirasX = -1.5f; // Posição X das rodas dianteiras
    float posZ = 1.2f;

    // Rodas traseiras - direita
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Preto
    glTranslatef(posicaoRodasTraseirasX, posicaoRodasY, posZ);
    desenhaRoda(raioRodasTraseiras, larguraRodasTraseiras);
    glPopMatrix();

    // Rodas traseiras - esquerda
    glPushMatrix();
    glTranslatef(posicaoRodasTraseirasX, posicaoRodasY, -posZ);
    desenhaRoda(raioRodasTraseiras, larguraRodasTraseiras);
    glPopMatrix();

    // Rodas dianteiras - direita
    glPushMatrix();
    glTranslatef(posicaoRodasDianteirasX, posicaoRodasY, posZ);
    desenhaRoda(raioRodasDianteiras, larguraRodasDianteiras);
    glPopMatrix();

    // Rodas dianteiras - esquerda
    glPushMatrix();
    glTranslatef(posicaoRodasDianteirasX, posicaoRodasY, -posZ);
    desenhaRoda(raioRodasDianteiras, larguraRodasDianteiras);
    glPopMatrix();

    glPopMatrix(); // Finaliza as transformações do trator
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posicionar a câmera
    float camX = cameraDistance * sin(cameraAngleY) * cos(cameraAngleX);
    float camY = cameraDistance * sin(cameraAngleX);
    float camZ = cameraDistance * cos(cameraAngleY) * cos(cameraAngleX);
    gluLookAt(camX, camY, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Desenhar o trator completo (corpo + cabine + rodas)
    desenhaTrator();

    glutSwapBuffers();
}


void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 's': // Mover para frente
        posX += velocidade * cos(direcao * M_PI / 180.0f);
        posZ -= velocidade * sin(direcao * M_PI / 180.0f);
        break;
    case 'w': // Mover para trás
        posX -= velocidade * cos(direcao * M_PI / 180.0f);
        posZ += velocidade * sin(direcao * M_PI / 180.0f);
        break;
    case 'a': // Girar para a esquerda
        direcao += 5.0f;
        if (direcao >= 360.0f) direcao -= 360.0f; // Mantém o ângulo entre 0 e 360
        break;
    case 'd': // Girar para a direita
        direcao -= 5.0f;
        if (direcao < 0.0f) direcao += 360.0f; // Mantém o ângulo entre 0 e 360
        break;
    case '+':
        cameraDistance = std::max(cameraDistance - 0.5f, 5.0f);
        break;
    case '-':
        cameraDistance = std::min(cameraDistance + 0.5f, 30.0f);
        break;
    case 'u': // Levanta o braço
        anguloBraco = std::min(anguloBraco + 5.0f, 320.0f); // Limite superior
        break;
    case 'j': // Abaixa o braço
        anguloBraco = std::max(anguloBraco - 5.0f, 180.0f); // Limite inferior
        break;
    case 'i': // Gira a pá para cima
        anguloPá = (anguloPá + 5.0f); // Limite superior
        break;
    case 'k': // Gira a pá para baixo
        anguloPá = (anguloPá - 5.0f); // Limite inferior
        break;
    case 'o': // Levanta o braço traseiro
        anguloBracoTraseiro = std::min(anguloBracoTraseiro + 5.0f, 170.0f);
        break;
    case 'l': // Abaixa o braço traseiro
        anguloBracoTraseiro = std::max(anguloBracoTraseiro - 5.0f, 50.0f);
        break;
    case 'p': // Inclina o antebraço traseiro para cima
        anguloAntebraco = std::min(anguloAntebraco + 5.0f, 355.0f);
        break;
    case ';': // Inclina o antebraço traseiro para baixo
        anguloAntebraco = std::max(anguloAntebraco - 5.0f, 200.0f);
        break;
    case '[': // Inclina a pá traseira para cima
        anguloPaTraseira = anguloPaTraseira + 5.0f;
        break;
    case ']': // Inclina a pá traseira para baixo
        anguloPaTraseira = anguloPaTraseira - 5.0f;
        break;
    case 27:  // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void teclasEspeciais(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_UP: // Seta para cima
        cameraAngleX = std::min(cameraAngleX + 0.1f, static_cast<float>(M_PI_2));
        break;
    case GLUT_KEY_DOWN: // Seta para baixo
        cameraAngleX = std::max(cameraAngleX - 0.1f, -static_cast<float>(M_PI_2));
        break;
    case GLUT_KEY_LEFT: // Seta para a esquerda
        cameraAngleY -= 0.1f;
        break;
    case GLUT_KEY_RIGHT: // Seta para a direita
        cameraAngleY += 0.1f;
        break;
    }
    glutPostRedisplay(); // Redesenha a cena após a interação
}


void reshape(int largura, int altura) {
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, static_cast<float>(largura) / static_cast<float>(altura), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Retroescavadeira");
    inicializa();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(teclasEspeciais); // Callback para teclas especiais (setas)
    glutKeyboardFunc(teclado);       // Callback para teclas regulares, caso necessário
    glutMainLoop();
    return 0;
}
