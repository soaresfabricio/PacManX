#pragma once

//
//  ladrilho.hpp
//  PacManX
//
//  Created by Fabrício Soares on 25/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>



#include <GLUT/glut.h>

#include <stdio.h>
#include "direcao.hpp"

class ladrilho {
 
    ladrilho * saidas[10];
    posicao pos;
    ponto centro;
    int cor;
    int passos;
    
    bool pilula;
    bool visitado;
    
public:
    ladrilho();
    
    void setCentro(ponto centro);
    ponto getCentro();
    
    void setSaida(DIRECAO d, ladrilho * saida);
    bool temSaida(DIRECAO d);
    ladrilho * getSaida(DIRECAO d);
    
    void setCor(int c);
    void setVisitado();
    void setPilula();
    void setPosicao(posicao p);
    posicao getPosicao();
    
    void processa();


};

