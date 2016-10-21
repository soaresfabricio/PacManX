#pragma once
#define M_PI 3.14159265358979323846
#include <time.h>


//
//  game.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include "jogador.hpp"
#include "tabuleiro.hpp"


#ifndef game_hpp
#define game_hpp


class game {
    tabuleiro t;
    jogador j;
    
    bool pausado;
    int contador;
    float tempo;
    
protected:
    void iluminaCena();
    
public:
    void carregar();
    tabuleiro getTabuleiro();
    void processa(float ticks);
    void teclaPressionada(unsigned char tecla);
    bool ehPausado();
};

#endif /* game_hpp */
