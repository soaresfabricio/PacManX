//
//  Tabuleiro.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#define PI 3.14159265358979323846

#include "headers.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>

// #include <Magick++.h>

#include "Jogador.hpp"
#include "direcao.hpp"
#include "Ladrilho.hpp"



class Tabuleiro {
    
private:
    int largura;
    int altura;
    
    float ultimosTicks;
    float tempo;
    
    float * pixels[28][31];
    Ladrilho ladrilhos[28][31];
    GLuint tabuleiroDisplayList;
    Jogador jogador;
    // std::map <const char *, int> vertexes;
    
    void desenhaLinhas(float * cor, int x, int y, float px, float py);
    void criaNormal(float x, float y, float z);
    void criaTabuleiro();
    void desenhaParede(int x, int y, float *color);
    void desenhaTeto(int x, int y);
    
    void desenhaParedePequena();
    void desenhaFimPequeno();
    void desenhaCantoPequeno();
    void desenhaParedeGrande();
    void desenhaCantoGrande(bool isInset);
    void desenhaGrandeInset();
    
    std::bitset<9> gridRotacoes(std::bitset<9> grade) {
        std::bitset<9> novaGrade;
        novaGrade[6] = grade[0];
        novaGrade[3] = grade[1];
        novaGrade[0] = grade[2];
        novaGrade[7] = grade[3];
        novaGrade[4] = grade[4];
        novaGrade[1] = grade[5];
        novaGrade[8] = grade[6];
        novaGrade[5] = grade[7];
        novaGrade[2] = grade[8];
        return novaGrade;
    }
    
    bool ehParede(int x, int y) {
        bool resultado = false;
        if (x < 0 || x >= largura || y < 0 || y >= altura) {
            resultado = true;
        }
        else {
            float * cor = getPixel(x,y);
            float somaCores = cor[0] + cor[1] + cor[2];
            if (cor[0] == 1.0 && somaCores == 1.0) {
                resultado = false;
            }
            else if (cor[0] == 1.0 && cor[1] == 1.0 && cor[2] == 0.0) {
                resultado = false;
            }
            else {
                resultado = somaCores < 3.0;
            }
        }
        return resultado;
    };
    
    void desenhaCanto(float xc, float yc, float z, float inicio, bool interior);
    
public:
    void carrega();
    int getLargura();
    int getAltura();
    float * getPixel(int x, int y);
    void atualiza(float ticks, float gameTime);
    void processa();
    
    Ladrilho * getLadrilho(int x, int y);
};
