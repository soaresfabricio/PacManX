//
//  Ladrilho.hpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <iostream>
#include <math.h>
#include <stdio.h>

#include "Direcao.hpp"
#include "Eventos.hpp"


class Ladrilho {
    
    Ladrilho * saidas[10];
//    Bonus * bonus;
    posicao pos;
    ponto centro;
    int cor;
    int passos;
    float cheiro;
    float tempoJogo;
    float ultimosTicks;
    
    bool energizer;
    bool visitado;
    
public:
    Ladrilho();
    
    void setCentro(ponto pontoCentral);
    ponto getCentro();
    void setSaida(DIRECAO d, Ladrilho * l);
    bool temSaida(DIRECAO d);
    Ladrilho * getSaida(DIRECAO d);
    void setCor(int c);
    void setVisitado();
    void setEnergizer();
    void atualiza(float ticks, float tempo);
    void processa();
    void setPosicao(posicao pos);
    posicao getPosicao();
};
