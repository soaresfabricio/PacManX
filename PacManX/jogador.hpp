#pragma once

#define M_PI 3.14159265358979323846

//
//  jogador.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#ifndef jogador_hpp
#define jogador_hpp

#include <GLUT/glut.h>

#include <stdio.h>
#include <math.h>
#include "direcao.hpp"
#include "ladrilho.hpp"

#include "jogador.hpp"

class jogador {
    
private:
    DIRECAO dir;
    DIRECAO dirDesejada;
    ladrilho * ladAtual;
    float pos;
    
    void posiciona(float movimento);
    
public:
    
    DIRECAO getDirecao();
    void setDirecao(DIRECAO d);
    DIRECAO getDirDesejada();
    void setDirDesejada(DIRECAO d);
    
    void atualizaDirecao();
    void processa(float ticks);
    
    ponto getPosicao();
    void incrementaPosicao(float n);
    
    void setLadrilho(ladrilho * l);
    ladrilho * getLadrilho();
    
};


#endif /* jogador_hpp */
