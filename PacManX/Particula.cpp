//
//  Particula.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Particula.hpp"

Particula::Particula() {
    float direcao = M_PI * (rand() % 1000) / 500.0;
    float mudanca = (rand() % 100) / 150.0;
    
    vectorMovimento.x = sin(direcao) * mudanca;
    vectorMovimento.y = (rand() % 100) / 100.0;
    vectorMovimento.z = cos(direcao) * mudanca;
}

Vector Particula::getPosicao() {
    return posicao;
}

Vector Particula::getVectorMovimento() {
    return vectorMovimento;
}

void Particula::adicionaQuadPonto(Vector ponto, Vector normal) {
    qPontos.push_back(ponto);
    qNormais.push_back(normal);
}

void Particula::adicionaTrianguloPonto(Vector ponto, Vector normal) {
    tPontos.push_back(ponto);
    tNormais.push_back(normal);
}

void Particula::setPosicao(Vector posicao) {
}

void Particula::atualiza(float ticks) {
    totalTicks += ticks;
    
    ticks *= 20;
    posicao.x += vectorMovimento.x * ticks;
    posicao.y += vectorMovimento.y * ticks;
    posicao.z += vectorMovimento.z * ticks;
    
    vectorMovimento.y = vectorMovimento.y - ticks/10;
    
    vectorMovimento.x = vectorMovimento.x * (1 - ticks/50);
    vectorMovimento.y = vectorMovimento.y * (1 - ticks/50);
    vectorMovimento.z = vectorMovimento.z * (1 - ticks/50);
    
    if (posicao.y < -1) {
        posicao.y = -1 - (posicao.y+1);
        vectorMovimento.y = 0 - vectorMovimento.y;
        vectorMovimento.x *= 0.55;
        vectorMovimento.y *= 0.55;
        vectorMovimento.z *= 0.55;
    }
    
    if (fabs(vectorMovimento.x) < 0.01 && fabs(vectorMovimento.y) < 0.01 && fabs(vectorMovimento.z) < 0.01 && fabs(posicao.y + 1) < 0.01) {
        vectorMovimento.x = 0;
        vectorMovimento.y = 0;
        vectorMovimento.z = 0;
    }
}

void Particula::processa() {
    glColor3f(1, 1, 0);
    for (unsigned int i = 0; i < qPontos.size(); i++) {
        if (i % 4 == 0) {
            glBegin(GL_QUADS);
        }
        Vector p = qPontos[i];
        Vector normal = qNormais[i];
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(p.x + posicao.x, p.y + posicao.y, p.z + posicao.z);
        if (i % 4 == 3) {
            glEnd();
        }
    }
    
    for (unsigned int i = 0; i < tPontos.size(); i++) {
        if (i % 3 == 0) {
            glBegin(GL_TRIANGLES);
        }
        Vector p = tPontos[i];
        Vector normal = tNormais[i];
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(p.x + posicao.x, p.y + posicao.y, p.z + posicao.z);
        if (i % 3 == 2) {
            glEnd();
        }
    }
}
