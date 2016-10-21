//
//  processador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "direcao.hpp"
#include "Temporizador.cpp"
#include "game.hpp"

// Tecla Esc
#define ESCAPE 27

enum DIRECAO dir = nenhuma;

int janela; // Número da janela GLUT
game g;

class processador {

public:
    
    static int x;
    static Temporizador temporizador;
    static float ultimoClock;
    

    /**
     * Função para iniciar o rendering do game.
     */
    static void desenha() {
        
        float agora = temporizador.getSegundos();
        float ticks = agora - ultimoClock;
        
        bool pausado = g.ehPausado();
        
        if(pausado){
            sleep(1);
            ultimoClock = temporizador.getSegundos();
            return;
        }
        
    
        ultimoClock = agora;
        
        
        glLoadIdentity();
        // Chama ciclo de processamento do jogo
        g.processa(ticks);
        // Já que estamos usando Double Buffering
        glutSwapBuffers();
    };

    /**
     * Recebe teclas 
     * @param tecla [description]
     * @param x     [Coordenada de tela X do mouse no momento que a tecla é teclaPressionada]
     * @param y     [Coordenada de tela Y do mouse no momento que a tecla é pressionada]
     */
    static void teclaPressionada(unsigned char tecla, int x, int y) {

        g.teclaPressionada(tecla);
        if (tecla == ESCAPE) {
            glutDestroyWindow(janela);
            exit(0);
        }

    };

    static void teclaEspecial(int tecla, int x, int y) {

    }

    /**
     * Função que constrói um ambiente de OpenGL apropriado.
     * @param largura Largura do viewport.
     * @param altura  Altura do viewport.
     */
    static void iniciaGL(int largura, int altura) {

        g.carregar();

        glClearColor(0.0, 0.0, 0.0, 0.5);

        // Transparências / Alpha blending
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClearDepth(1.0);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);

        glLoadIdentity();

        gluPerspective(45.0f, (GLfloat)largura / (GLfloat)altura, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);

    };

    
    static void redesenha(int largura, int altura) {
        if (altura == 0)
            altura = 1;

        glViewport(0, 0, largura, altura);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, (GLfloat)largura / (GLfloat)altura, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
    }

};

Temporizador processador::temporizador;
float processador::ultimoClock;
