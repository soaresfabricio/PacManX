//
//  Jogador.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#pragma once
#define M_PI 3.14159265358979323846

#include "headers.hpp"
#include <stdio.h>
#include <math.h>
#include <map>

#include "Eventos.hpp"
#include "direcao.hpp"
#include "ladrilho.hpp"
// #include explosao.hpp
#include "VisaoJogador.hpp"
#include "Ator.hpp"

enum ESTADOJOGADOR {
    VIVO,
    MORRENDO,
    MORTO
};

class Jogador : public Ator {
private:
    DIRECAO direcao;
    DIRECAO direcaoDesejada;
    ESTADOJOGADOR estado;
    // TODO: Explosao explosao;
    
    float progressoMorte;
    float totalTicks;
    
    Ladrilho * ladrilhoAtual;
    float posicao;
    float ultimosTicks;
    
    void resolvePosicao(float movemento);
    VisaoJogador visaoJogador;

public:
    ESTADOJOGADOR getEstado();
    void setMorrendo();
    DIRECAO getDirecao();
    void setDirecao(DIRECAO d);
    DIRECAO getDirecaoDesejada();
    void setDirecaoDesejada(DIRECAO d);
    void atualizaDirecao();
    void atualiza(float ticks);
    void processa();
    
    ponto getPosicao();
    void incrementaPosicao(float number);
    void setLadrilhoAtual(Ladrilho * l);
    Ladrilho * getLadrilhoAtual();

};
