//
//  tabuleiro.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#ifndef tabuleiro_hpp
#define tabuleiro_hpp

#include <Magick++.h>


#include <stdio.h>

class tabuleiro {
    
    int altura, largura;
    
    float * pixels[28][31];
    float pixelsCores[28][31];


    
    void criar();
    void desenhaParede();
    
    
    void desenhaCantos();
    // TODO: desenhar também paredes, teto, etc

public:
    void carrega();
    int getAltura();
    int getLargura();
    void processa();
};

#endif /* tabuleiro_hpp */
