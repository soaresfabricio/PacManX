//
//  Processador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 04/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Processador.hpp"

void Processador::iniciaGL(int largura, int altura){
    game.carregar();
    glClearColor(0.0, 0.0, 0.0, 0.5);
    
    glEnable(GL_CULL_FACE);
    
    //glPolygonMode(GL_FRONT, GL_LINE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glLoadIdentity();
    
    gluPerspective(45.0f, (GLfloat)largura/(GLfloat)altura, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    
}


void Processador::redimensiona(int largura, int altura) {
    if (altura == 0) altura = 1;// Não deixa dividir por 0
    
    glViewport(0, 0, largura, altura);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f,(GLfloat)largura/(GLfloat)altura,0.1f,100.0f);
    //gluPerspective(85.0f,(GLfloat)largura/(GLfloat)altura,0.1f,1300.0f);

    glMatrixMode(GL_MODELVIEW);
};


void Processador::desenha() {
    fps++;
    
    float agora = temporizador.getSegundos();
    float ticks = agora - ultimoClock;
    
    if (int(ultimoClock) != int(agora)) {
        ultimoFps = fps;
        std::cout << "FPS: " << fps << "\n";
        std::cout << "--------\n";
        fps = 0;
    }
    
    bool pausado = game.ehPausado();
    if (pausado) {
        sleep(1);
        ultimoClock = temporizador.getSegundos();
        return;
    }
    ultimoClock = agora;
    
    glLoadIdentity();
    game.atualiza(ticks);
    game.processa();
    
    glutSwapBuffers();
};


void Processador::tecla(unsigned char tecla, int x, int y)
{
    game.tecla(tecla);
    if (tecla == ESC || tecla == 'q')
    {
        glutDestroyWindow(janela);
        exit(0);
    }
};

void Processador::teclaEspecial(int tecla, int x, int y) {
    game.teclaEspecial(tecla);
}
