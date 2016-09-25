//
//  tabuleiro.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include <Magick++.h>

#include "tabuleiro.hpp"

void tabuleiro::carrega(){
    
    Magick::Image img("mapa.png");
    largura = (int)img.columns();
    altura = (int)img.rows();
    
    
    
}
