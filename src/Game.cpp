#include "../include/Game.hpp"
#include <math.h>


void Game::carregar(){



    vidas = 7;
    visaoJogador.setRaio(0.15);
    visaoJogador.setRotacao(280);
    srand(time(NULL));
    tabuleiro.carrega();


    jogador.setGame(this);
    redefinir();
    Eventos::getInstancia()->adicionar(this, "playerdied");
    placar.reiniciar();

}

void Game::redefinir(){



    inimigos.clear();

    blinky = Blinky();
    pinky = Pinky();
    inky = Inky();
    clyde = Clyde();

    blinky.setGame(this);
    blinky.setJogador(&jogador);

    pinky.setGame(this);
    pinky.setJogador(&jogador);

    inky.setGame(this);
    inky.setJogador(&jogador);
    inky.setBlinky(&blinky);

    clyde.setGame(this);
    clyde.setJogador(&jogador);

    inimigos.push_back(&blinky);
    inimigos.push_back(&pinky);
    inimigos.push_back(&inky);
    inimigos.push_back(&clyde);

    jogador.setLadrilhoAtual(tabuleiro.getLadrilho(10,1));
    blinky.setLadrilhoAtual(tabuleiro.getLadrilho(10,10));
    pinky.setLadrilhoAtual(tabuleiro.getLadrilho(12,13));
    inky.setLadrilhoAtual(tabuleiro.getLadrilho(16,13));
    clyde.setLadrilhoAtual(tabuleiro.getLadrilho(8,7));

    for (unsigned int i = 0; i < inimigos.size(); i++) {
        inimigos[i]->iniciar();
    }

    estadoJogo = executando;

}

Tabuleiro Game::getTabuleiro(){
    return tabuleiro;
}

void Game::onSignal(std::string nome) {
    if (nome == "playerdied") {
        vidas--;
        redefinir();
    }
}

void Game::ilumina(){
    glEnable(GL_LIGHTING);

    GLfloat position[] = { 0.5, 2, 1, 0 };
     glLightfv(GL_LIGHT0, GL_POSITION, position);

     GLfloat ambient[] = { 0.1, 0.1, 0.1 };
     glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

     GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
     glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

     GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
     glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);

    glMateriali(GL_FRONT, GL_SHININESS, 96);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 0.6f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void Game::atualiza(float ticks){
    tempo += ticks;
    placar.atualiza(ticks);


    for (unsigned int i = 0; i < inimigos.size(); i++) {
        inimigos[i]->atualiza(ticks);
    }


    tabuleiro.atualiza(ticks, tempo);
    jogador.atualiza(ticks);
}

void Game::processa(){


    glDepthMask(GL_TRUE);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    ponto posicaoJogador = jogador.getPosicao();

    ilumina();

    float inicioZ = -4;
    float finalZ = posicaoJogador.z;
    float startY = posicaoJogador.y - 16;
    float endY = posicaoJogador.y;

    float distanciaMaisProxima = 100;

    for (unsigned int i = 0; i < inimigos.size(); i++) {
        ponto a = jogador.getPosicao();
        ponto b = inimigos[i]->getPosicao();

        float diffX = (float)a.x - (float)b.x;
        float diffY = (float)a.y - (float)b.y;
        if (diffX < 0.0) diffX = 0.0-diffX;
        if (diffY < 0.0) diffY = 0.0-diffY;

        float distance = sqrt((diffX*diffX) + (diffY*diffY));

        if (distance < distanciaMaisProxima) {
            distanciaMaisProxima = distance;
        }
        if (distance <= 1.1 && (inimigos[i]->getEstado() == PERSEGUINDO || inimigos[i]->getEstado() == DISPERSO)) {
            estadoJogo = parado;
            jogador.setMorrendo();
            break;
        }
    }


    float lookY = posicaoJogador.y + 2;
   float startX = posicaoJogador.x;

   if (lookY < -5.5) lookY = -5.5;
   else if (lookY > 9.5) lookY = 9.5;

   if (startX < -5) startX = -5;
   else if (startX > 5) startX = 5;

   startY = lookY - 18;
   float startZ = -4;


 static float eyeX, eyeY, eyeZ;



  if (jogador.getDirecao() == direita) {

    tipoDirecao = 1;

     eyeX = eyeX + ((posicaoJogador.x - 10) - eyeX) * (0.05);
     eyeY = eyeY + ((posicaoJogador.y) - eyeY) * (0.05);
     eyeZ = eyeZ + ((posicaoJogador.z + 4) - eyeZ) * (0.5);

      //eyeX =  posicaoJogador.x - 10;
      // eyeY =  posicaoJogador.y ;
      // eyeZ =  posicaoJogador.z + 3 ;

  }

  if (jogador.getDirecao() == esquerda) {

     tipoDirecao = 2;

     eyeX = eyeX + ((posicaoJogador.x + 10) - eyeX) * (0.05);
     eyeY = eyeY + ((posicaoJogador.y) - eyeY) * (0.05);
     eyeZ = eyeZ + ((posicaoJogador.z+4) - eyeZ) * (0.5);

      //eyeX = posicaoJogador.x + 10;
      // eyeY = posicaoJogador.y ;
      // eyeZ =  posicaoJogador.z + 3 ;
  }

  if (jogador.getDirecao() == cima) {

    tipoDirecao = 0;

    eyeX = eyeX + ((posicaoJogador.x) - eyeX) * (0.05);
    eyeY = eyeY + ((posicaoJogador.y - 10) - eyeY) * (0.05);
    eyeZ = eyeZ + ((posicaoJogador.z + 4) - eyeZ) * (0.5);

  }

  if (jogador.getDirecao() == baixo) {

    tipoDirecao = 3;

    eyeX = eyeX + ((posicaoJogador.x) - eyeX) * (0.05);
    eyeY = eyeY + ((posicaoJogador.y + 10) - eyeY) * (0.05);
    eyeZ = eyeZ + ((posicaoJogador.z + 4) - eyeZ) * (0.5);
  }



   gluLookAt(eyeX , eyeY, eyeZ,
             posicaoJogador.x , posicaoJogador.y, posicaoJogador.z,
             0, 0, 1);


    tabuleiro.processa();
    jogador.processa();

    for (unsigned int i = 0; i < inimigos.size(); i++) {
            inimigos[i]->processa();
        }


    glLoadIdentity();

    glDepthMask(GL_FALSE);
    glBegin(GL_POLYGON);
    glColor4f(0, 0, 0, 0.4);
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


  if (tipoDirecao == 0) {
    switch (tecla) {
        case 'w': jogador.setDirecaoDesejada(cima); break;
        case 's': jogador.setDirecaoDesejada(baixo); break;
        case 'a': jogador.setDirecaoDesejada(esquerda); break;
        case 'd': jogador.setDirecaoDesejada(direita); break;
        case 'p': pausado = !pausado; break;
    }
  }

  if (tipoDirecao == 1) {
    switch (tecla) {
        case 'w': jogador.setDirecaoDesejada(direita); break;
        case 's': jogador.setDirecaoDesejada(esquerda); break;
        case 'a': jogador.setDirecaoDesejada(cima); break;
        case 'd': jogador.setDirecaoDesejada(baixo); break;
        case 'p': pausado = !pausado; break;
    }
  }

  if (tipoDirecao == 2) {
    switch (tecla) {
        case 'w': jogador.setDirecaoDesejada(esquerda); break;
        case 's': jogador.setDirecaoDesejada(direita); break;
        case 'a': jogador.setDirecaoDesejada(baixo); break;
        case 'd': jogador.setDirecaoDesejada(cima); break;
        case 'p': pausado = !pausado; break;
    }
  }

  if (tipoDirecao == 3) {
    switch (tecla) {
      case 'w': jogador.setDirecaoDesejada(baixo); break;
      case 's': jogador.setDirecaoDesejada(cima); break;
      case 'a': jogador.setDirecaoDesejada(direita); break;
      case 'd': jogador.setDirecaoDesejada(esquerda); break;
      case 'p': pausado = !pausado; break;
    }
  }

}



bool Game::ehPausado() {
    return pausado;
}

ESTADOGAME Game::getEstado() {
    return estadoJogo;
}
