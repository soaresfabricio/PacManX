//
//  Inimigo.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include "headers.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Direcao.hpp"
#include "Ladrilho.hpp"

#include "Ator.hpp"
#include "Jogador.hpp"

enum ESTADOINIMIGO {
    PERSEGUINDO,
    DISPERSO,
    FUGINDO,
    COMIDO
};

class Inimigo : public Ator {
    
protected:
    ESTADOINIMIGO estado;
    DIRECAO direcao;
    Jogador * jogador;
    Ladrilho * ladrilhoAtual;
    float pos;
    float totalTicks;
    float tempoJogo;
    float tempoAssustado;
    
    void direcaoContraria();
    void setDirecaoAleatoria();
    virtual void resolvePosicao(float movimento);
    virtual void resolvePosicaoAssustado(float movimento);
    virtual posicao getPosicaoAlvo();
    virtual void setCor();
    virtual void setCorReal();
    posicao posicaoAlvo;
    void processaCorpo();
    void processaOlhos();
    
public:
    virtual ~Inimigo() {};
    
    ESTADOINIMIGO getEstado();
    void onSignal(std::string name);
    void iniciar();
    void atualiza(float ticks);
    void processa();
    DIRECAO getDirecao();
    ponto getPosicao();
    void setLadrilhoAtual(Ladrilho * l);
    Ladrilho * getLadrilhoAtual();
    void setJogador(Jogador * j);
};
