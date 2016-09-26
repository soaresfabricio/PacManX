//
//  ladrilho.cpp
//  PacManX
//
//  Created by Fabrício Soares on 25/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "ladrilho.hpp"

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

