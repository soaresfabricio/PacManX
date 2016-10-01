//
//  jogador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "jogador.hpp"

DIRECAO jogador::getDirecao(){
    return dir;
}

void jogador::setDirecao(DIRECAO d){
    dir = d;
}

DIRECAO jogador::getDirDesejada(){
    return dirDesejada;
}

void jogador::setDirDesejada(DIRECAO d){
    dirDesejada = d;
}

void jogador::atualizaDirecao(){
    dir = dirDesejada;
}

void jogador::setLadrilho(ladrilho *l){
    ladAtual = l;
}

ladrilho * jogador::getLadrilho(){
    return ladAtual;
}


