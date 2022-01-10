//
//  Ator.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//


#pragma once

#include "Direcao.hpp"
#include "Observador.hpp"

class Game;

class Ator : public Observador {
protected:
    Game * game;
    void resolvePosicao(float movemento);
    bool ehOposto(DIRECAO a, DIRECAO b);
    DIRECAO getOposto(DIRECAO dir);
    float distancia(posicao a, posicao b);
    
    ponto normalizaVetor(ponto vetor);
    void offsetVetor(ponto *entrada, ponto * offset, ponto * saida);
    void getNormal(ponto * a, ponto * b, ponto * saida);
    bool normalizaVetor(ponto * entrada, ponto * saida);
    ponto faceNormal(ponto * p1, ponto * p2, ponto * p3, ponto * saida);
    ponto computaVerticeNormal(ponto a, ponto b, ponto c, ponto d);
    
public:
    void setGame(Game * gPonteiro);
    void atualiza(float ticks);
    void processa();
    
};

