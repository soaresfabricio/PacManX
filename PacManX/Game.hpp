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
#include "VisaoJogador.hpp"
#include "direcao.hpp"
#include "tabuleiro.hpp"
#include "Observador.hpp"
#include "Eventos.hpp"

class Game : public Observador {
private:
    VisaoJogador visaoJogador;
    tabuleiro tabuleiro;
    // Placar placar;
    
    // inimigos
    
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
    tabuleiro getTabuleiro();
    void atualiza(float ticks);
    void processa();
    void tecla(unsigned char tecla);
    void teclaEspecial(int tecla);
    bool ehPausado();
    ESTADOGAME getEstado();
    
    
};
