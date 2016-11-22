//
//  Placar.hpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <bitset>
#include <stack>

#include "Observador.hpp"
#include "Eventos.hpp"

#include <SFML/Audio.hpp>


class Placar : public Observador {

private:
    unsigned int pontuacao;
    int pontuacaoFantasmas;
    float ultimosTicks;
    std::vector< std::bitset<15> > digitos;
    std::stack<int> numerosPilha;
    float brilho[10][15];

    sf::Sound* som;
    sf::SoundBuffer* bufferSom;

public:

    void reiniciar();
    virtual void onSignal(std::string name);
    void atualiza(float ticks);
    void processa();
    Placar();

    void tocaSom(std::string s) {
        delete som;
        delete bufferSom;
        bufferSom = new sf::SoundBuffer;
        if (!bufferSom->loadFromFile(s)) {
            return;
        }
        som = new sf::Sound;
        som->setBuffer(*bufferSom);
        som->play();
    }

};
