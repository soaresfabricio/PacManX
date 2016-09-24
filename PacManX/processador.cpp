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

#define ESCAPE 27

int janela; // Número da janela GLUT

class processador {
    
public:
    
    static void desenha(){
        
        glLoadIdentity();
        
        
        //TODO: Mover para classe Game junto com as instruções de rendering
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        // Já que estamos usando Double Buffering
        glutSwapBuffers();
        
    }
    
    static void teclaPressionada(unsigned char tecla, int x, int y){
        
        //TODO: enviar teclas recebidas ao fluxo do jogo
        if(tecla == ESCAPE){
            glutDestroyWindow(janela);
            exit(0);
        }
        
    }
    
    static void iniciaGL(int largura, int altura){
        
        // carregar o fluxo do jogo aqui
        glClearColor(0.0, 0.0, 0.0, 0.5);
    }
    
};
