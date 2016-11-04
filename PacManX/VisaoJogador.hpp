//
//  VisaoJogador.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once
#include "headers.hpp"
#include <stdio.h>
#include <math.h>
#include <map>
#include <vector>
#include "direcao.hpp"

class VisaoJogador{
private:
    ponto normalizaVetor(ponto v);
    double raio;
    double rotacao;
    
public:
    void setRotacao(double r);
    void setRaio(double r);
    void processa(float direcao, float abertura, bool desenhado);
};
