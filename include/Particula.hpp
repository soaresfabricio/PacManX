//
//  Particula.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <vector>
#include <math.h>

#include "Vector.hpp"

class Particula {
    
    std::vector<Vector> qPontos;
    std::vector<Vector> qNormais;
    
    std::vector<Vector> tPontos;
    std::vector<Vector> tNormais;
    
    Vector posicao;
    Vector vectorMovimento;
    float totalTicks;
    
public:
    Particula();
    void adicionaQuadPonto(Vector ponto, Vector normal);
    void adicionaTrianguloPonto(Vector ponto, Vector normal);
    void setPosicao(Vector p);
    void atualiza(float ticks);
    void processa();
    
    Vector getPosicao();
    Vector getVectorMovimento();
    
};
