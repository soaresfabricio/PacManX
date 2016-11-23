//
//  Pinky.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Pinky.hpp"

posicao Pinky::getPosicaoAlvo() {
    if (estado == DISPERSO) {
        posicao p;
        p.x = 28;
        p.y = 32;
        return p;
    }
    if (estado == PERSEGUINDO) {
        posicao pos = jogador->getLadrilhoAtual()->getPosicao();
        switch (jogador->getDirecao()) {
            case cima:
                pos.y += 4; break;
            case baixo:
                pos.y -= 4; break;
            case esquerda:
                pos.x -= 4; break;
            case direita:
                pos.x += 4; break;
        }
        return pos;
    }
    return Inimigo::getPosicaoAlvo();
}

void Pinky::setCorReal() {
    glColor3f(1, 0.0, 1);
}
