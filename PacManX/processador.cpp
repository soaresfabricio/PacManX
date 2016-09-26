//
//  processador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <stdlib.h>
#include "game.hpp"

#include "direcao.hpp"


#define ESCAPE 27



int janela; // Número da janela GLUT
game game;


class processador {
    
public:
    
    static void desenha(){
        
        glLoadIdentity();
        
        
        //TODO: Mover para classe Game junto com as instruções de rendering
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        
        game.processa();
        
        
        // Já que estamos usando Double Buffering
        glutSwapBuffers();
        
    };
    
    static void teclaPressionada(unsigned char tecla, int x, int y){
        
        //TODO: enviar teclas recebidas ao fluxo do jogo
        if(tecla == ESCAPE){
            glutDestroyWindow(janela);
            exit(0);
        }
        
    };
    
    static void iniciaGL(int largura, int altura){
        
        game.carregar();
        
        glClearColor(0.0, 0.0, 0.0, 0.5);

        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glClearDepth(1.0);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        
        glLoadIdentity();
        
        gluPerspective(45.0f, (GLfloat)largura/(GLfloat)altura, 0.1f, 100.0f);
        
        glMatrixMode(GL_MODELVIEW);

        
    };
    
};
