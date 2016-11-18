//
//  Explosao.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

#include "direcao.hpp"
#include "Vector.hpp"
#include "Particula.hpp"
#include "ParticulaSangue.hpp"

class Explosao {
    
private:
    float totalTicks;
    std::map<int, Particula> particulas;
    std::vector<ParticulaSangue> particulasSangue;
    Vector normaliza(Vector v);
    
public:
    Explosao();
    void reiniciar();
    void processa(float ticks);
    bool completo();
    
};
