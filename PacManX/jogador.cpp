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

ponto jogador::getPosicao(){
    ponto posAtual = ladAtual->getCentro();
    
    switch (dir) {

        // Adiciona um delta positivo a coordenada x atual
        case direita:
            posAtual.x = posAtual.x + pos;
            break;
        
        // Adiciona um delta negativo a coordenada x atual
        case esquerda:
            posAtual.x = posAtual.x - pos;
            
        // Adiciona um delta positivo a coordenada y atual
        case cima:
            posAtual.y = posAtual.y + pos;
            
        // Adiciona um delta negativo a coordenada y atual
        case baixo:
            posAtual.y = posAtual.y + pos;
            
        default:
            break;
    }
    
    return posAtual;
}

void jogador::posiciona(float movimento){
    
}


/**
 * Processa posição do jogador e renderiza PacMan.
 */
 
void jogador::processa(float ticks){
    
    // Configura uma certa velocidade
    this->posiciona(ticks * 4.0);
    
    ponto centro = ladAtual->getCentro();
    
    switch (dir) {
            
            // Adiciona um delta positivo ao ladrilho x atual
        case direita:
            centro.x = centro.x + pos;
            break;
            
            // Adiciona um delta negativo ao ladrilho x atual
        case esquerda:
            centro.x = centro.x - pos;
            
            // Adiciona um delta positivo ao ladrilho y atual
        case cima:
            centro.y = centro.y + pos;
            
            // Adiciona um delta negativo ao ladrilho y atual
        case baixo:
            centro.y = centro.y + pos;
            
        default:
            break;
    }
    
    
    
    
    
    
    
}
