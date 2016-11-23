//
//  Inky.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "Inimigo.hpp"
#include "Blinky.hpp"

class Inky : public Inimigo {
    
private:
    Blinky * blinky;
    
protected:
    posicao getPosicaoAlvo();
    void setCorReal();
    
public:
    void setBlinky(Blinky * blinky);
};
