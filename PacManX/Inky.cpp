//
//  Inky.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Inky.hpp"

posicao Inky::getPosicaoAlvo() {
    if (estado == DISPERSO) {
        posicao p;
        p.x = 28;
        p.y = 0;
        return p;
    }
    if (estado == PERSEGUINDO) {
        posicao pos = jogador->getLadrilhoAtual()->getPosicao();
        posicao posicaoBlinky = blinky->getLadrilhoAtual()->getPosicao();
        
        switch (jogador->getDirecao()) {
            case cima:
                pos.y += 2; break;
            case baixo:
                pos.y -= 2; break;
            case esquerda:
                pos.x -= 2; break;
            case direita:
                pos.x += 2; break;
        }
        
        posicao novaPosicao;
        
        novaPosicao.x = pos.x - (2 * (posicaoBlinky.x - pos.x));
        novaPosicao.y = pos.y - (2 * (posicaoBlinky.y - pos.y));
        
        return novaPosicao;
    }
    return Inimigo::getPosicaoAlvo();
}

void Inky::setCorReal() {
    glColor3f(0.0, 0.9, 1);
}

void Inky::setBlinky(Blinky * b) {
    blinky = b;
}
