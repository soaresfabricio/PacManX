
//
//  game.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "game.hpp"

void game::carregar(){
    
    t.carrega();
    
    j.setLadrilho(t.getLadrilho(1, 1));

}

void game::iluminaCena(){
    glEnable ( GL_LIGHTING ) ;
    
    GLfloat position[] = { 0.5, -0.5, 1, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    GLfloat ambient[] = {0.1, 0.1, 0.1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_LIGHT0);
    
    glMateriali(GL_FRONT, GL_SHININESS, 96);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
    
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;
}

void game::processa(float ticks){
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    tempo += ticks;
    contador++;
    
    ponto posicaoJogador = j.getPosicao();

    //gluLookAt (0, -20, 18, 0, -2, -20, 0.0, 1.0, 0.0);
    
    gluLookAt (posicaoJogador.x / 3.5, posicaoJogador.y - 16, -4, posicaoJogador.x / 3.5, posicaoJogador.y, posicaoJogador.z, 0.0, 1.0, 0.0);

    
    iluminaCena();
    
    
    // glutSolidSphere(2,20,20);
    
    j.processa(ticks);
    
    // processador inimigos
    
    t.processa();
    
    glLoadIdentity();

}

void game::teclaPressionada(unsigned char tecla){
    switch (tecla) {
        case 'w':
            j.setDirDesejada(cima);
            break;
        case 's':
            j.setDirDesejada(baixo);
            break;
        case 'a':
            j.setDirDesejada(esquerda);
            break;
        case 'd':
            j.setDirDesejada(direita);
            break;
        case 'p':
            pausado = !pausado;
            break;
    }
    
    if (pausado && tecla != 'p') {
        pausado = false;
    }
}

bool game::ehPausado(){
    return pausado;
}
