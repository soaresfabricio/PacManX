//
//  ladrilho.cpp
//  PacManX
//
//  Created by Fabrício Soares on 25/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "ladrilho.hpp"
#include <iostream>

ladrilho::ladrilho() {
}

void ladrilho::setCentro(ponto c) {
    centro = c;
}

void ladrilho::setPosicao(posicao p){
    pos = p;
}


void ladrilho::setVisitado(){
    if (!visitado) {
        visitado = true;
    }
}

posicao ladrilho::getPosicao(){
    return pos;
}

ponto ladrilho::getCentro(){
    return centro;
}

void ladrilho::setSaida(DIRECAO d, ladrilho *saida){
    saidas[(int)d] = saida;
}

bool ladrilho::temSaida(DIRECAO d){
    return saidas[(int)d] != NULL;
}

ladrilho * ladrilho::getSaida(DIRECAO d){
    return saidas[(int)d];
}

void ladrilho::setCor(int c){
    cor = c;
}

void ladrilho::setPilula(){
    pilula = true;
}

void ladrilho::processa(){
    
    float pontoX = centro.x-0.5;
    float pontoY = centro.y-0.5;
    
    
    if(visitado) {
        return;
    }
    
    if(pilula){
        glColor4f(1, 1.0/255*184, 1.0/255*151, 0.2 + 0.8*sin(M_PI));
        glPushMatrix();
        glTranslatef(pontoX+0.5, pontoY+0.5, -19.5);
        glutSolidSphere(0.4, 12, 12);
        glPopMatrix();
    }
    
    else {

        glColor4f(1, 1.0/255*184, 1.0/255*151, 1);
        glPushMatrix();
        glTranslatef(pontoX+0.5, pontoY+0.5, -19.5);
        glutSolidSphere(0.08, 4, 4);
        glPopMatrix();
    }
    
}

