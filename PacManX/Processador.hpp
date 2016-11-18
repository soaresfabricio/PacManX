//
//  Processador.hpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once
#include <iostream>
#include <math.h>
#include <vector>

#include <stdio.h>
#include <unistd.h>

#include "direcao.hpp"
#include "Temporizador.cpp"
#include "Game.hpp"

#define ESC 27

enum DIRECAO direcao = nenhuma;

int janela;

float deslocaX = 0.0f;
float deslocaY = 0.0f;
int fps = 0;
int ultimoFps = 0;

const int FPSMAX = 50;
Game game;

typedef struct {
    float x;
    float y;
} CIRCULO ;


class Processador{
public:
    static int x;
    static int lookAt;
    static Temporizador temporizador;
    
    static float ultimoClock;
    
    static void iniciaGL(int largura, int altura);
    static void redimensiona(int largura, int altura);
    static void desenha();
    static void tecla(unsigned char tecla, int x, int y);
    static void teclaEspecial(int key, int x, int y);
};

Temporizador Processador::temporizador;
float Processador::ultimoClock;
