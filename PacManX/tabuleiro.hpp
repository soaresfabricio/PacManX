#pragma once


//
//  tabuleiro.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include <GLUT/glut.h>


#include <Magick++.h>
#include <stdio.h>

#include "jogador.hpp"

#include "ladrilho.hpp"

class tabuleiro {
    
    int altura, largura;
    
    float * pixels[28][31];
    float pixelsCores[28][31];
    ladrilho ladrilhos[28][31];
    jogador jogador;
    std::map <const char *, int> vertices;
    
    GLuint tabuleiroDisplayList;
    
    bool ehParede(int x, int y);
    
    void criar();
    
    void desenhaLinhas(float * cor, int x, int y, float pontoX, float pontoY);

    void desenhaParede(int x, int y, float * cor);
    
    
    void desenhaCantos();
    // TODO: desenhar também paredes, teto, etc

public:
    void carrega();
    int getAltura();
    int getLargura();
    void processa();
    float * getPixel(int x, int y);
};
