//
//  Pinky.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "Inimigo.hpp"

class Pinky : public Inimigo {
    
protected:
    posicao getPosicaoAlvo();
    void setCorReal();
};
