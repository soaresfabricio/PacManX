//
//  Ladrilho.cpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Ladrilho.hpp"


Ladrilho::Ladrilho() {
    if (rand() % 50 == 7) {
        //delete bonus;
        //bonus = new Cherry();
    }
}

void Ladrilho::setPosicao(posicao p) {
    pos = p;
}

posicao Ladrilho::getPosicao() {
    return pos;
}

ponto Ladrilho::getCentro() {
    return centro;
}

void Ladrilho::setCentro(ponto c) {
    centro = c;
}

void Ladrilho::setSaida(DIRECAO dir, Ladrilho * saida) {
    saidas[(int)dir] = saida;
}

bool Ladrilho::temSaida(DIRECAO dir) {
    return saidas[(int)dir] != NULL;
}

Ladrilho * Ladrilho::getSaida(DIRECAO dir) {
    return saidas[(int)dir];
}

void Ladrilho::setCor(int c) {
    cor = c;
}

void Ladrilho::setVisitado() {
    if (!visitado) {
        if (energizer) {
            Eventos::getInstancia()->emitir("energizer");
        }
        else {
            Eventos::getInstancia()->emitir("pellet");
        }
        visitado = true;
    }
}

void Ladrilho::setEnergizer() {
    energizer = true;
}

void Ladrilho::atualiza(float ticks, float tempo) {
    ultimosTicks = ticks;
    this->tempoJogo = tempo;
}

void Ladrilho::processa() {
    float px = centro.x - 0.5;
    float py = centro.y - 0.5;
    
    if (visitado) return;
    
    if (energizer) {
        glColor4f(1, 1.0/255*200, 1.0/255*151, 0.2 + 0.8*sin(M_PI * (tempoJogo - (int)tempoJogo)));
        glPushMatrix();
        glTranslatef(px+0.5, py+0.5, -19.5);
        glutSolidSphere(0.5, 12, 12);
        glPopMatrix();
    }
    else {
        glColor4f(1, 0, 0, 1);
        glPushMatrix();
        glTranslatef(px+0.5, py+0.5, -19.5);
        glutSolidSphere(0.2, 4, 4);
        glPopMatrix();
    }
//    
//    if (bonus != NULL) {
//        ponto center = getCentro();
//        glPushMatrix();
//        glTranslatef(centro.x, centro.y, -19.5);
//        bonus->atualiza(ultimosTicks, tempoJogo);
//        bonus->processa();
//        glPopMatrix();
//    }
}
