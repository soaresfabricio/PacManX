#pragma once


//
//  tabuleiro.hpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include <GLUT/glut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include <Magick++.h>
#include <stdio.h>

#include "jogador.hpp"

#include "ladrilho.hpp"
#include "direcao.hpp"

class tabuleiro {
    
    int altura, largura;
    
    float * pixels[28][31];
    float pixelsCores[28][31];
    ladrilho ladrilhos[28][31];
    jogador jog;
    std::map <const char *, int> vertices;
    
    GLuint tabuleiroDisplayList;
    
    /**
     * @description Verifica se um par de pontos é uma parede no tabuleiro.
     * @param x Coordenada X do ponto.
     * @param y Coordenada Y do ponto.
     * @return Valor booleano para a condição descrita.
     */
    
    bool ehParede(int x, int y){
        
        // Verifica limites do tabuleiro (parede)
        if (x < 0 || x >= largura || y < 0 || y >= altura){
            return true;
        }
        
        float * cor = getPixel(x, y);
        float somaDeCores = cor[0] + cor[1] + cor[2];
        
        // Verifica se é vermelho (pilula)
        if(cor[0] == 1.0 && somaDeCores == 1.0) {
            return false;
        }
        
        // Verifica se é amarelo (caminho possível)
        if(cor[0] == 1.0 && cor[1] == 1.0 && cor[2] == 0.0){
            return false;
        }
        
        // Verifica se é branco (caminho possível)
        return somaDeCores < 3.0;
    }
    
    void criar();
    
    void desenhaLinhas(float * cor, int x, int y, float pontoX, float pontoY);

    void desenhaParede(int x, int y, float * cor);
    
    
    void desenhaCantos();

public:
    void carrega();
    int getAltura();
    int getLargura();
    void processa();
    float * getPixel(int x, int y);
};
