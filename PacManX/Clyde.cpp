//
//  Clyde.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Clyde.hpp"

posicao Clyde::getPosicaoAlvo() {
    if (estado == DISPERSO) {
        posicao p;
        p.x = 0;
        p.y = 32;
        return p;
    }
    if (estado == PERSEGUINDO && this->distancia(ladrilhoAtual->getPosicao(), jogador->getLadrilhoAtual()->getPosicao()) < 8) {
        posicao p;
        p.x = 0;
        p.y = 32;
        return p;
    }
    return Inimigo::getPosicaoAlvo();
}

void Clyde::setCorReal() {
    glColor3f(1.0, 0.5, 0.0);
}
