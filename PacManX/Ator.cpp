//
//  Ator.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "math.h"
#include "Ator.hpp"
#include "game.hpp"

void Ator::setGame(game *gPonteiro){
    g = gPonteiro;
}

DIRECAO Ator::getOposto(DIRECAO dir){
    switch (dir) {
        case esquerda: return direita;
        case cima: return baixo;
        case baixo: return cima;
        case direita: return esquerda;
        default: return nenhuma;
    }
}

bool Ator::ehOposto(DIRECAO a, DIRECAO b){
    return a != nenhuma && b != nenhuma && getOposto(a) == b;
}

float Ator::distancia(posicao a, posicao b){
    float dx = (float)a.x - (float)b.x;
    float dy = (float)a.y - (float)b.y;
    if (dx < 0.0) dx = 0.0 - dx;
    if (dy < 0.0) dy = 0.0 - dy;
    
    return sqrt(dx*dx + dy*dy);
}


ponto Ator::normalizaVetor(ponto v){
    ponto vetorNormalizado;
    float comprimento = (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vetorNormalizado.x = v.x / comprimento;
    vetorNormalizado.y = v.y / comprimento;
    vetorNormalizado.z = v.z / comprimento;
    return vetorNormalizado;
}

void Ator::offsetVetor(ponto *entrada, ponto *offset, ponto *saida){
    saida->x = entrada->x - offset->x;
    saida->y = entrada->y - offset->y;
    saida->z = entrada->z - offset->z;
    
}

// Produto vetorial a X b
void Ator::getNormal(ponto *a, ponto *b, ponto *saida) {
    saida->x = a->y * b->z - a->z * b->y;
    saida->y = a->z * b->x - a->x * b->z;
    saida->z = a->x * b->y - a->y * b->x;
    
}


bool Ator::normalizaVetor(ponto *entrada, ponto *saida){
    float comprimento = (float)(
                                sqrt(entrada->x * entrada->x +
                                     entrada->y * entrada->y +
                                     entrada->z * entrada->z));
    if (comprimento) {
        saida->x = entrada->x / comprimento;
        saida->y = entrada->y / comprimento;
        saida->z = entrada->z / comprimento;
    }
    return false;
}

ponto Ator::calculaFaceNormal(ponto *p1, ponto *p2, ponto *p3, ponto *saida){
    
    // p2 vira nova origem para p1 e p3
    ponto a;
    offsetVetor(p3, p2, &a);
    ponto b;
    offsetVetor(p1, p2, &b);
    
    // Computa o produto vetorial a X b para obter a face normal
    
    ponto pn;
    getNormal(&a, &b, &pn);
    
    normalizaVetor(&pn, saida);
    
    return * saida;
}

ponto Ator::computaVerticeNormal(ponto a, ponto b, ponto c, ponto d){
    ponto valor;
    valor.x = (a.x + b.x + c.x + d.x) / 4;
    valor.y = (a.y + b.y + c.y + d.y) / 4;
    valor.z = (a.z + b.z + c.z + d.z) / 4;
    
    return normalizaVetor(valor);
}
