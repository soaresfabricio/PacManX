//
//  Blinky.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Blinky.hpp"

posicao Blinky::getPosicaoAlvo() {
    if (estado == DISPERSO) {
        posicao p;
        p.x = 0;
        p.y = 0;
        return p;
    }
    return Inimigo::getPosicaoAlvo();
}

void Blinky::setCorReal() {
    glColor3f(1, 0, 0);
}
