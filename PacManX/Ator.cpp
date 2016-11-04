//
//  Ator.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include "math.h"

#include "Ator.hpp"
#include "Game.hpp"

void Ator::setGame(Game *gamePointer) {
    game = gamePointer;
}

DIRECAO Ator::getOposto(DIRECAO dir) {
    switch (dir) {
        case esquerda: return direita;
        case cima: return baixo;
        case baixo: return cima;
        case direita: return esquerda;
        default: return nenhuma;
    }
}

bool Ator::ehOposto(DIRECAO a, DIRECAO b) {
    return a != nenhuma && b != nenhuma && getOposto(a) == b;
}

float Ator::distancia(posicao a, posicao b) {
    float dx = (float)a.x - (float)b.x;
    float dy = (float)a.y - (float)b.y;
    if (dx < 0.0) dx = 0.0-dx;
    if (dy < 0.0) dy = 0.0-dy;
    
    return sqrt((dx*dx) + (dy*dy));
}

ponto Ator::normalizaVetor(ponto v) {
    ponto normalizado;
    float comprimento = (float)(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
    normalizado.x = v.x / comprimento;
    normalizado.y = v.y / comprimento;
    normalizado.z = v.z / comprimento;
    return normalizado;
}

void Ator::offsetVetor (ponto *pIn, ponto *pOffset, ponto *pOut)
{
    pOut->x = pIn->x - pOffset->x;
    pOut->y = pIn->y - pOffset->y;
    pOut->z = pIn->z - pOffset->z;
}

void Ator::getNormal (ponto *a, ponto *b, ponto *pOut)
{
    pOut->x = a->y * b->z - a->z * b->y;
    pOut->y = a->z * b->x - a->x * b->z;
    pOut->z = a->x * b->y - a->y * b->x;
}

bool Ator::normalizaVetor (ponto *pIn, ponto *pOut)
{
    float comprimento = (float)(sqrt(pIn->x*pIn->x + pIn->y*pIn->y + pIn->z*pIn->z));
    if (comprimento)
    {
        pOut->x = pIn->x / comprimento;
        pOut->y = pIn->y / comprimento;
        pOut->z = pIn->z / comprimento;
        return true;
    }
    return false;
}

ponto Ator::faceNormal (ponto *p1, ponto *p2, ponto *p3, ponto *pOut)
{
    // usa p2 como nova origem de p1, p3
    ponto a;
    offsetVetor(p3, p2, &a);
    ponto b;
    offsetVetor(p1, p2, &b);
    // Computa o produto vetorial de a e b para achar a face normal
    ponto pn;
    getNormal(&a, &b, &pn);
    // Return a normalized vector
    normalizaVetor(&pn, pOut);
    
    return *pOut;
}

ponto Ator::computaVerticeNormal (ponto a, ponto b, ponto c, ponto d) {
    ponto v;
    v.x = (a.x + b.x + c.x + d.x) / 4;
    v.y = (a.y + b.y + c.y + d.y) / 4;
    v.z = (a.z + b.z + c.z + d.z) / 4;
    return normalizaVetor(v);
}
