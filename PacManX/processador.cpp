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

#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "game.hpp"
#include "direcao.hpp"

// Tecla Esc
#define ESCAPE 27

int janela; // Número da janela GLUT
game g;

class processador {
    
public:
    
    static void desenha(){
        glLoadIdentity();
        // Chama ciclo de processamento do jogo
        g.processa();
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
    
    static void teclaEspecial(int tecla, int x, int y){
        
    }
    
    static void iniciaGL(int largura, int altura){
        
        g.carregar();
        
        glClearColor(0.0, 0.0, 0.0, 0.5);

        
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
    
    static void redesenha(int largura, int altura){
        if (altura == 0)
            altura = 1;
        
        glViewport(0, 0, largura, altura);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        gluPerspective(45.0f, (GLfloat)largura / (GLfloat)altura, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
    }
    
};
