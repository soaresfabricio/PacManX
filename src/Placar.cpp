//
//  Placar.cpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Placar.hpp"

Placar::Placar() {
    Eventos::getInstancia()->adicionar(this, "pellet");
    Eventos::getInstancia()->adicionar(this, "energizer");
    Eventos::getInstancia()->adicionar(this, "ghost_eaten");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            brilho[i][j] = 0.0;
        }
    }

    digitos.push_back(std::bitset<15>(std::string("111101101101111"))); // 0
    digitos.push_back(std::bitset<15>(std::string("001001001001001"))); // 1
    digitos.push_back(std::bitset<15>(std::string("111001111100111"))); // 2
    digitos.push_back(std::bitset<15>(std::string("111001111001111"))); // 3
    digitos.push_back(std::bitset<15>(std::string("101101111001001"))); // 4
    digitos.push_back(std::bitset<15>(std::string("111100111001111"))); // 5
    digitos.push_back(std::bitset<15>(std::string("111100111101111"))); // 6
    digitos.push_back(std::bitset<15>(std::string("111001001010010"))); // 7
    digitos.push_back(std::bitset<15>(std::string("111101111101111"))); // 8
    digitos.push_back(std::bitset<15>(std::string("111101111001111"))); // 9

    reiniciar();
}

void Placar::reiniciar() {
    pontuacaoFantasmas = 1000;
    pontuacao = 0;
}

void Placar::onSignal(std::string nome) {


    if (nome == "energizer") {
        pontuacaoFantasmas = 1000;
        pontuacao += 50;

        tocaSom("sound/energizer.wav");
    }
    else if (nome == "pellet") {
        pontuacao += 10;
    }
    else if (nome == "ghost_eaten") {
        tocaSom("sound/eaten.wav");
        pontuacao += pontuacaoFantasmas;
        pontuacaoFantasmas += 1000;
    }
}

void Placar::atualiza(float ticks) {
    ultimosTicks = ticks;
}

void Placar::processa() {
    glPushMatrix();
    glTranslatef(-2.28, 1.60, -5);

    unsigned int pontuacaoAtual = pontuacao;
    while (pontuacaoAtual > 0) {
        numerosPilha.push(pontuacaoAtual % 10);
        pontuacaoAtual = (int)pontuacaoAtual / 10;
    }

    int tamanhoPilha = numerosPilha.size();
    for (int d = 0; d < tamanhoPilha; d++) {
        std::bitset<15> digito = digitos[(int)numerosPilha.top()];

        if ((int)numerosPilha.top() == 1) {
            //glTranslatef(-0.20, 0, 0);
        }

        int contador = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 3; x++) {
                float brilhoDesejado = 1*digito[contador];
                float novoBrilho = (1.0 - 10*ultimosTicks) * brilho[d][contador] + 10*ultimosTicks * brilhoDesejado;
                if (brilhoDesejado > 0.1) {
                    brilho[d][contador] = novoBrilho;
                    glColor4f(1-novoBrilho, 1, 1-novoBrilho, 1);
                    glColor4f(1, 0.3, 0.3, 1);
                    glTranslatef(-x/11.0, y/11.0, 0);
                    glutSolidSphere(0.04, 10, 10);
                    glTranslatef(x/11.0, -y/11.0, 0);
                }
                else {
                    brilho[d][contador] = brilhoDesejado;
                }
                contador++;
            }
        }
        glTranslatef(0.35, 0, 0);

        numerosPilha.pop();
    }
    glPopMatrix();
}
