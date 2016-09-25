//
//  tabuleiro.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include <Magick++.h>

#include "tabuleiro.hpp"


/**
 * Carrega uma imagem e analisa
 */

void tabuleiro::carrega(){
    
    Magick::Image img("mapa.png");
    largura = (int)img.columns();
    altura = (int)img.rows();
    
    
    // Criando um mapa RGB da imagem
    for (int x = 0; x < largura; x++) {
        for (int y = 0; y < altura; y++) {
            float * cor = new float[3];
            Magick::ColorRGB rgb(img.pixelColor(x, y));
            cor[0] = rgb.red();
            cor[1] = rgb.green();
            cor[2] = rgb.blue();
            pixels[x][altura - 1 - y] = cor;
            pixelsCores[x][altura - 1 - y] = rgb.red() * 10000 + rgb.green() * 100 + rgb.blue();
        }
    }
    
    criar();
}
