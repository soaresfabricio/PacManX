//
//  game.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include "tabuleiro.hpp"
#include "jogador.hpp"

class game {
    tabuleiro L;
    jogador J;
    
    bool pausado;
    
public:
    void carregar();
    tabuleiro getLabirinto();
    void processa();
    bool ehPausado();
};

#endif /* game_hpp */
