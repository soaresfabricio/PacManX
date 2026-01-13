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

#include "Direcao.hpp"
#include "Game.hpp"
#include "Temporizador.hpp"

#define ESC 27

extern enum DIRECAO direcao;

extern int janela;

extern float deslocaX;
extern float deslocaY;
extern int fps;
extern int ultimoFps;

constexpr int FPSMAX = 50;
extern Game game;

typedef struct {
  float x;
  float y;
} CIRCULO;

class Processador {
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
