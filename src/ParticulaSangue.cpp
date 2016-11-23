//
//  ParticulaSangue.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/ParticulaSangue.hpp"

ParticulaSangue::ParticulaSangue() {
    tamanho = 0.04 + 0.06 * (rand() % 100 / 100.0);
    caiu = false;
    ondulacoes = 5 + rand() % 5;
    direcaoOndulacao = (rand() % 100) / 50.0 * M_PI;
}

void ParticulaSangue::setPosicao(Vector _posicao) {
    posicao = posicao;
}

void ParticulaSangue::setVectorMovimento(Vector _vectorMovimento) {
    vectorMovimento = vectorMovimento;
}

void ParticulaSangue::atualiza(float ticks) {
    if (caiu) return;

    ticks *= 20;
    posicao.x += vectorMovimento.x * ticks;
    posicao.y += vectorMovimento.y * ticks;
    posicao.z += vectorMovimento.z * ticks;

    vectorMovimento.y = vectorMovimento.y - ticks/10;

    vectorMovimento.x = vectorMovimento.x * (1 - ticks/50);
    vectorMovimento.y = vectorMovimento.y * (1 - ticks/50);
    vectorMovimento.z = vectorMovimento.z * (1 - ticks/50);

    if (posicao.y < -1) {
        caiu = true;
        posicao.y = -1;
        vectorMovimento.x = 0;
        vectorMovimento.y = 0;
        vectorMovimento.z = 0;
    }
}

void ParticulaSangue::processa() {
    glPushMatrix();
    glTranslatef(posicao.x, posicao.y, posicao.z);
    glColor3f(1, 0, 0);
    glutSolidSphere(tamanho, 6, 6);

    glPopMatrix();
}
