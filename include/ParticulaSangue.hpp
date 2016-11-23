//
//  ParticulaSangue.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <math.h>
#include <stdio.h>

#include "Vector.hpp"

class ParticulaSangue {
    
    Vector posicao;
    Vector vectorMovimento;
    float tamanho;
    float direcaoOndulacao;
    bool caiu;
    int ondulacoes;
    int semente;
    
public:
    ParticulaSangue();
    void setPosicao(Vector posicao);
    void setVectorMovimento(Vector vectorMovimento);
    void atualiza(float ticks);
    void processa();
};
