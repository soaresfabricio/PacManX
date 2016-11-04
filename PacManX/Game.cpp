#include "Game.hpp"

void Game::carregar(){
    vidas = 3;
    visaoJogador.setRaio(0.15);
    visaoJogador.setRotacao(280);
    srand(time(NULL));
    tabuleiro.carrega();
    //jogador.setJogo(this);
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

tabuleiro Game::getTabuleiro(){
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
    //    placar.atualiza(ticks);
    
    
    /**
     / TEMPORIZAR INIMIGOS AQUI
     */
    
    
    tabuleiro.atualiza(ticks, tempo);
    jogador.atualiza(ticks);
}

void Jogador::processa(){
    glDepthMask(GL_TRUE);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    ponto posicaoJogador = jogador.getPosicao();
    float lookAt = 1 + gameTime * 2.5;
    if (lookAt > 25) lookAt = 25;
    
    //gluLookAt (playerPos.x, playerPos.y, -18.0 + lookAt, playerPos.x/2, playerPos.y/2, playerPos.z, 0.0, 1.0, 0.0);
    //gluLookAt (0, -20, 18, 0, -2, playerPos.z, 0.0, 1.0, 0.0);
    // Close
    
    handleLighting();
    
    float startZ = -4;
    float endZ = playerPos.z;
    float startY = playerPos.y - 16;
    float endY = playerPos.y;
    
    float closestDistance = 100;
    
    for (unsigned int i = 0; i < enemies.size(); i++) {
        point a = player.getPosition();
        point b = enemies[i]->getPosition();
        
        float diffX = (float)a.x - (float)b.x;
        float diffY = (float)a.y - (float)b.y;
        if (diffX < 0.0) diffX = 0.0-diffX;
        if (diffY < 0.0) diffY = 0.0-diffY;
        
        float distance = sqrt((diffX*diffX) + (diffY*diffY));
        
        if (distance < closestDistance) {
            closestDistance = distance;
        }
        if (distance <= 1.1 && (enemies[i]->getState() == CHASE || enemies[i]->getState() == SCATTER)) {
            gameState = stopped;
            player.setDying();
            break;
        }
    }
    
    //gluLookAt (playerPos.x / 3.5, playerPos.y - 16, -4, playerPos.x / 3.5, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
    
    /*
     float zoomInFrom = 15;
     float multiplier = closestDistance > zoomInFrom ? 0.0 : 0.4 * (1.0-(1.0/zoomInFrom)*closestDistance);
     gluLookAt (playerPos.x, startY - (startY - endY)*multiplier, startZ - (startZ - endZ)*multiplier, playerPos.x, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
     */
    
    float lookY = playerPos.y + 2;
    float startX = playerPos.x;
    
    if (lookY < -5.5) lookY = -5.5;
    else if (lookY > 9.5) lookY = 9.5;
    
    if (startX < -5) startX = -5;
    else if (startX > 5) startX = 5;
    
    //std::cout << lookY << "\n";
    
    startY = lookY - 18;
    
    gluLookAt(startX, startY, startZ, startX, lookY, playerPos.z, 0.0, 1.0, 0.0);
    
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i]->render();
    }
    
    maze.render();
    player.render();
    
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
    
    scoreBoard.render();
    
    glDepthMask(GL_TRUE);
    
    for (int i = 0; i < lives; i++) {
        glPushMatrix();
        glTranslatef(2.3 - 0.4 * i, 1.75, -5);
        playerView.render((int)(gameTime * 50 + i * 20) % 360, 180 - 30, true);
        glPopMatrix();
    }
    
}

//
//void Game::render() {
//    glDepthMask(GL_TRUE);
//
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//    point playerPos = player.getPosition();
//    float lookAt = 1 + gameTime * 2.5;
//    if (lookAt > 25) lookAt = 25;
//
//    //gluLookAt (playerPos.x, playerPos.y, -18.0 + lookAt, playerPos.x/2, playerPos.y/2, playerPos.z, 0.0, 1.0, 0.0);
//    //gluLookAt (0, -20, 18, 0, -2, playerPos.z, 0.0, 1.0, 0.0);
//    // Close
//
//    handleLighting();
//
//    float startZ = -4;
//    float endZ = playerPos.z;
//    float startY = playerPos.y - 16;
//    float endY = playerPos.y;
//
//    float closestDistance = 100;
//
//    for (unsigned int i = 0; i < enemies.size(); i++) {
//        point a = player.getPosition();
//        point b = enemies[i]->getPosition();
//
//        float diffX = (float)a.x - (float)b.x;
//        float diffY = (float)a.y - (float)b.y;
//        if (diffX < 0.0) diffX = 0.0-diffX;
//        if (diffY < 0.0) diffY = 0.0-diffY;
//
//        float distance = sqrt((diffX*diffX) + (diffY*diffY));
//
//        if (distance < closestDistance) {
//            closestDistance = distance;
//        }
//        if (distance <= 1.1 && (enemies[i]->getState() == CHASE || enemies[i]->getState() == SCATTER)) {
//            gameState = stopped;
//            player.setDying();
//            break;
//        }
//    }
//
//    //gluLookAt (playerPos.x / 3.5, playerPos.y - 16, -4, playerPos.x / 3.5, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
//
//    /*
//     float zoomInFrom = 15;
//     float multiplier = closestDistance > zoomInFrom ? 0.0 : 0.4 * (1.0-(1.0/zoomInFrom)*closestDistance);
//     gluLookAt (playerPos.x, startY - (startY - endY)*multiplier, startZ - (startZ - endZ)*multiplier, playerPos.x, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
//     */
//
//    float lookY = playerPos.y + 2;
//    float startX = playerPos.x;
//
//    if (lookY < -5.5) lookY = -5.5;
//    else if (lookY > 9.5) lookY = 9.5;
//
//    if (startX < -5) startX = -5;
//    else if (startX > 5) startX = 5;
//
//    //std::cout << lookY << "\n";
//
//    startY = lookY - 18;
//
//    gluLookAt(startX, startY, startZ, startX, lookY, playerPos.z, 0.0, 1.0, 0.0);
//
//    for (unsigned int i = 0; i < enemies.size(); i++) {
//        enemies[i]->render();
//    }
//
//    maze.render();
//    player.render();
//
//    glLoadIdentity();
//
//    glDepthMask(GL_FALSE);
//    glBegin(GL_POLYGON);
//    glColor4f(0, 0, 0, 1);
//    glNormal3f(0, 0, -1);
//    glVertex3f(-2.8, 2.1, -5);
//
//    glNormal3f(0, 0, -1);
//    glVertex3f(-2.8, 1.5, -5);
//
//    glNormal3f(0, 0, -1);
//    glVertex3f(2.8, 1.5, -5);
//
//    glNormal3f(0, 0, -1);
//    glVertex3f(2.8, 2.1, -5);
//
//    glEnd();
//    glLineWidth(1.5);
//    glBegin(GL_LINE_LOOP);
//    glColor4f(0, 0, 1, 1);
//    glVertex3f(2.8, 2.1, -5);
//    glVertex3f(-2.8, 2.1, -5);
//    glVertex3f(-2.8, 1.5, -5);
//    glVertex3f(2.8, 1.5, -5);
//    glEnd();
//
//    scoreBoard.render();
//
//    glDepthMask(GL_TRUE);
//
//    for (int i = 0; i < lives; i++) {
//        glPushMatrix();
//        glTranslatef(2.3 - 0.4 * i, 1.75, -5);
//        playerView.render((int)(gameTime * 50 + i * 20) % 360, 180 - 30, true);
//        glPopMatrix();
//    }
//}
//
//void Game::handleSpecialKeystoke(int key) {
//    switch (key) {
//        case GLUT_KEY_UP:    player.setWantedDirection(up); break;
//        case GLUT_KEY_DOWN:  player.setWantedDirection(down); break;
//        case GLUT_KEY_LEFT:  player.setWantedDirection(left); break;
//        case GLUT_KEY_RIGHT: player.setWantedDirection(right); break;
//    }
//
//    if (paused) {
//        paused = false;
//    }
//}
//
//void Game::handleKeystroke(unsigned char key) {
//    if (paused) {
//        paused = false;
//        return;
//    }
//
//    switch (key) {
//        case 'w': player.setWantedDirection(up); break;
//        case 's': player.setWantedDirection(down); break;
//        case 'a': player.setWantedDirection(left); break;
//        case 'd': player.setWantedDirection(right); break;
//        case 'p': paused = !paused; break;
//    }
//}
//
//bool Game::isPaused() {
//    return paused;
//}
//
//GAMESTATE Game::getState() {
//    return gameState;
//}
