#include "Game.hpp"

void Game::carregar(){
    vidas = 3;
    visaoJogador.setRaio(0.15);
    visaoJogador.setRotacao(280);
    srand(time(NULL));
    tabuleiro.carrega();
    jogador.setGame(this);
    redefinir();
    Eventos::getInstancia()->adicionar(this, "jogadormorreu");
    //placar.redefinir();
}

void Game::redefinir(){
    //inimigos.clear();
    
    
    
    /**
     /
     / ADICIONAR INSTANCIA DE INIMIGOS AQUI
     /
     */
    
    
    
    jogador.setLadrilhoAtual(tabuleiro.getLadrilho(1,1));
    estadoJogo = executando;
    
}

Tabuleiro Game::getTabuleiro(){
    return tabuleiro;
}

void Game::onSignal(std::string nome) {
    if (nome == "jogadormorreu") {
        vidas--;
        redefinir();
    }
}

void Game::ilumina(){
    glEnable(GL_LIGHTING);
    
    GLfloat position[] = { 0.5, -0.3, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    GLfloat ambient[] = { 0.1, 0.1, 0.1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_LIGHT0);
    
    glMateriali(GL_FRONT, GL_SHININESS, 96);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void Game::atualiza(float ticks){
    tempo += ticks;
    placar.atualiza(ticks);
    
    
    /**
     / TEMPORIZAR INIMIGOS AQUI
     */
    
    
    tabuleiro.atualiza(ticks, tempo);
    jogador.atualiza(ticks);
}

void Game::processa(){
    glDepthMask(GL_TRUE);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    ponto posicaoJogador = jogador.getPosicao();
    float lookAt = 1 + tempo * 2.5;
    if (lookAt > 25) lookAt = 25;
    
    //gluLookAt (playerPos.x, playerPos.y, -18.0 + lookAt, playerPos.x/2, playerPos.y/2, playerPos.z, 0.0, 1.0, 0.0);
    //gluLookAt (0, -20, 18, 0, -2, playerPos.z, 0.0, 1.0, 0.0);
    // Close
    
    ilumina();
    
    float inicioZ = -4;
    float finalZ = posicaoJogador.z;
    float inicioY = posicaoJogador.y - 16;
    float fimY = posicaoJogador.y;
    
    float distanciaProxima = 100;
    
//    for (unsigned int i = 0; i < inimigos.size(); i++) {
//        ponto a = jogador.getPosicao();
//        ponto b = inimigos[i]->getPosicao();
//        
//        float dx = (float)a.x - (float)b.x;
//        float dy = (float)a.y - (float)b.y;
//        if (dx < 0.0) dx = 0.0-dx;
//        if (dy < 0.0) dy = 0.0-dy;
//        
//        float distancia = sqrt((dx*dx) + (dy*dy));
//        
//        if (distancia < distanciaProxima) {
//            distanciaProxima = distancia;
//        }
//        if (distancia <= 1.1 && (inimigos[i]->getEstado() == PERSEGUINDO || inimigos[i]->getEstado() == ESPALHADO)) {
//            estadoJogo = parado;
//            jogador.setMorrendo();
//            break;
//        }
//    }
    
    //gluLookAt (playerPos.x / 3.5, playerPos.y - 16, -4, playerPos.x / 3.5, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
    
    /*
     float zoomInFrom = 15;
     float multiplier = closestDistance > zoomInFrom ? 0.0 : 0.4 * (1.0-(1.0/zoomInFrom)*closestDistance);
     gluLookAt (playerPos.x, startY - (startY - endY)*multiplier, startZ - (startZ - endZ)*multiplier, playerPos.x, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
     */
    
    float lookY = posicaoJogador.y + 2;
    float inicioX = posicaoJogador.x;
    
    if (lookY < -5.5) lookY = -5.5;
    else if (lookY > 9.5) lookY = 9.5;
    
    if (inicioX < -5) inicioX = -5;
    else if (inicioX > 5) inicioX = 5;
    
    //std::cout << lookY << "\n";
    
    inicioY = lookY - 18;
    
    gluLookAt(inicioX, inicioY, inicioZ, inicioX, lookY, posicaoJogador.z, 0.0, 1.0, 0.0);
    
//    for (unsigned int i = 0; i < inimigos.size(); i++) {
//        inimigos[i]->processa();
//    }
    
    tabuleiro.processa();
    jogador.processa();
    
    glLoadIdentity();
    
    glDepthMask(GL_FALSE);
    glBegin(GL_POLYGON);
    glColor4f(0, 0, 0, 1);
    glNormal3f(0, 0, -1);
    glVertex3f(-2.8, 2.1, -5);
    
    glNormal3f(0, 0, -1);
    glVertex3f(-2.8, 1.5, -5);
    
    glNormal3f(0, 0, -1);
    glVertex3f(2.8, 1.5, -5);
    
    glNormal3f(0, 0, -1);
    glVertex3f(2.8, 2.1, -5);
    
    glEnd();
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glColor4f(0, 0, 1, 1);
    glVertex3f(2.8, 2.1, -5);
    glVertex3f(-2.8, 2.1, -5);
    glVertex3f(-2.8, 1.5, -5);
    glVertex3f(2.8, 1.5, -5);
    glEnd();
    
    placar.processa();
    
    glDepthMask(GL_TRUE);
    
    for (int i = 0; i < vidas; i++) {
        glPushMatrix();
        glTranslatef(2.3 - 0.4 * i, 1.75, -5);
        visaoJogador.processa((int)(tempo * 50 + i * 20) % 360, 180 - 30, true);
        glPopMatrix();
    }
    
}

void Game::teclaEspecial(int tecla) {
    switch (tecla) {
        case GLUT_KEY_UP:    jogador.setDirecaoDesejada(cima); break;
        case GLUT_KEY_DOWN:  jogador.setDirecaoDesejada(baixo); break;
        case GLUT_KEY_LEFT:  jogador.setDirecaoDesejada(esquerda); break;
        case GLUT_KEY_RIGHT: jogador.setDirecaoDesejada(direita); break;
    }

    if (pausado) {
        pausado = false;
    }
}

void Game::tecla(unsigned char tecla) {
    if (pausado) {
        pausado = false;
        return;
    }

    switch (tecla) {
        case 'w': jogador.setDirecaoDesejada(cima); break;
        case 's': jogador.setDirecaoDesejada(baixo); break;
        case 'a': jogador.setDirecaoDesejada(esquerda); break;
        case 'd': jogador.setDirecaoDesejada(direita); break;
        case 'p': pausado = !pausado; break;
    }
}



bool Game::ehPausado() {
    return pausado;
}

ESTADOGAME Game::getEstado() {
    return estadoJogo;
}
