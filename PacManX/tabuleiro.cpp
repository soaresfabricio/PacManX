#pragma once
//
//  tabuleiro.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include <GLUT/glut.h>
#include <iostream>
#include <Magick++.h>

#include "jogador.hpp"
#include "direcao.hpp"
#include "ladrilho.hpp"

#include "tabuleiro.hpp"


/**
 * @description Carrega uma imagem e a mapeia num Vetor de 2 dimensões;
 */
void tabuleiro::carrega(){
    
    tabuleiroDisplayList = glGenLists(1);
    Magick::Image img("mapa.png");
    largura = (int) img.columns();
    altura = (int) img.rows();
    
    // Criando um mapa RGB da imagem
    for (int x = 0; x < largura; x++) {
        for (int y = 0; y < altura; y++) {
            float * cor;
            cor = new float[3];
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

/**
 * @description Realiza a criação do tabuleiro, dispondo itens conforme suas posições. 
 * Esta função não desenha o tabuleiro, para isso veja `processar()`
 */

void tabuleiro::criar(){
    
    glNewList(tabuleiroDisplayList, GL_COMPILE);
    
    int alturaTabuleiro = getAltura();
    int larguraTabuleiro = getLargura();
    
    for (int x = 0; x < larguraTabuleiro; x++) {
        for(int y = 0; y < alturaTabuleiro; y++){
            float * cor = getPixel(x,y);
            
            ponto centro;
            centro.x = (float)x - (largura / 2 - 0.5);
            centro.y = (float)y - (altura / 2 - 0.5);
            centro.z = -19.5;
            
            ladrilhos[x][y].setCentro(centro);
            posicao p;
            p.x = x;
            p.y = y;
            ladrilhos[x][y].setPosicao(p);
            
            float somaDeCores = cor[0] + cor[1] + cor[2];
            
            
            // Se o ladrilho atual é vermelho, adicionar uma pílula nele
            if (cor[0] == 1.0 && somaDeCores == 1.0) {
                ladrilhos[x][y].setPilula();
            }
            
            // Se o ladrilho atual é amarelo, adicionar um ponto
            else if (cor[0] == 1.0 && cor[1] == 1.0 && cor[2] == 0.0 ) {
                
            }
            
            // Se o ladrilho atual é branco, não adicione nada (marque como visitado)
            else if (somaDeCores == 3.0){
                ladrilhos[x][y].setVisitado();
            }
            
            // Se não for nenhum dos casos anteriores, o ladrilho é na verdade uma parede
            else {
                // Marque então como visitado
                ladrilhos[x][y].setVisitado();
                if(somaDeCores > 0.0){
                    desenhaParede(x, y, cor);
                } else {
                    // desenhar teto
                }
            }
            
            
            
            
        }
    }
    glEndList();

}

void tabuleiro::desenhaParede(int x, int y, float *cor){
    float pontoX = (float)x - largura/2;
    float pontoY = (float)y - largura/2;
    glColor4f(cor[0], cor[1], cor[2], 1.0);
    desenhaLinhas(cor,x,y,pontoX,pontoY);
}

void tabuleiro::desenhaLinhas(float *cor, int x, int y, float pontoX, float pontoY){
    glLineWidth(3.0);
    
    float tamanho = 0.50;
    float copiaPontoX = pontoX;
    float copiaPontoY = pontoY;
    
    pontoX += (1.0 - tamanho ) / 2.0;
    pontoY += (1.0 - tamanho ) / 2.0;
    
    std::vector<ponto> pontos;
    std::vector<ponto> teto;
    
    float z = -19.5;
    glColor3f(0.0, 0.0, 1.0);
    
    bool paredes[5] = { true, true, true, true, true };
    
    DIRECAO direcaoParede = nenhuma;
    
    direcaoParede = esquerda;
    paredes[direcaoParede] = !ehParede(x-1, y);
    direcaoParede = direita;
    paredes[direcaoParede] = !ehParede(x+1, y);
    direcaoParede = baixo;
    paredes[direcaoParede] = !ehParede(x, y-1);
    direcaoParede = cima;
    paredes[direcaoParede] = !ehParede(x, y+1);
    
    if (paredes[cima] == true && paredes[direita] == false && paredes[esquerda] == false) {
        pontos.push_back(ponto(copiaPontoX+1.0, copiaPontoY + 0.5));
        pontos.push_back(ponto(copiaPontoY, copiaPontoY + 0.5));
        pontos.push_back(ponto(copiaPontoX, copiaPontoY));
        pontos.push_back(ponto(copiaPontoX+1.0, copiaPontoY));
        goto done;
    }
    
    done:;

    
// Falta terminar
    
//    glBegin(GL_QUADS);
//    for (unsigned int i = 0; i < pontos.size(); i++) {
//        ponto p = pontos[i];
//        glColor4f (0, 0.0, 0.5, 0.7);
//        glNormal3f(0, 0, 1);
//        glVertex3f(p.x, p.y, z-0.02);
//        std::cout << i << std::endl;
//    }
//    glEnd ();
//    
//    
//    // Linhas mais finas
//    glBegin (GL_LINE_STRIP);
//    for (unsigned int i = 0; i < pontos.size() && i < 2; i++) {
//        ponto p = pontos[i];
//        glColor4f (0.0, 0.0, 1.0, 1.0);
//        glVertex3f(p.x, p.y, z);
//    }
//    glEnd ();
    
    
}

void tabuleiro::processa(){
    
    glTranslatef(0, 0, -0.5);
    glCallList(tabuleiroDisplayList);
    glTranslatef(0, 0, 0.5);
    glCallList(tabuleiroDisplayList);
    
    for (int x = 0; x < largura; x++) {
        for (int y = 0; y < altura; y++) {
            ladrilhos[x][y].processa();
        }
    }
    
}

float * tabuleiro::getPixel(int x, int y){
    return pixels[x][y];
}

int tabuleiro::getLargura(){
    return largura;
}

int tabuleiro::getAltura(){
    return altura;
}
