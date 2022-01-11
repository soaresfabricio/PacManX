//
//  Game.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once
#define M_PI 3.14159265358979323846

#include <time.h>

#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Blinky.hpp"
#include "Pinky.hpp"
#include "Inky.hpp"
#include "Clyde.hpp"
#include "Placar.hpp"
#include "VisaoJogador.hpp"
#include "Direcao.hpp"
#include "Tabuleiro.hpp"
#include "Observador.hpp"
#include "Eventos.hpp"

#include <chrono>
#include <thread>



class Game : public Observador {
private:

    int tipoDirecao;


    VisaoJogador visaoJogador;
    Tabuleiro tabuleiro;
    Placar placar;


    Pinky pinky;
    Blinky blinky;
    Inky inky;
    Clyde clyde;
    std::vector<Inimigo*> inimigos;

    char vidas;
    float tempo;
    bool pausado;
    ESTADOGAME estadoJogo;
    void ilumina();

public:

    Jogador jogador;
    virtual void onSignal(std::string nome);
    void carregar();
    void redefinir();
    Tabuleiro getTabuleiro();
    void atualiza(float ticks);
    void processa();
    void tecla(unsigned char tecla);
    void teclaEspecial(int tecla);
    bool ehPausado();
    ESTADOGAME getEstado();


};
