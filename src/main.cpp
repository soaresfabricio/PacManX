//
//  main.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/headers.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#include "Processador.cpp"

int main(int argc, char ** argv) {

    // Entrega os argumentos para a GLUT
    glutInit(&argc, argv);

    // Double buffer, cores RGBA, componentes alpha, clipping automático (depth buffer)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    // Configura dimensão e posição da janela
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);

    // Nome na barra de título da janela
    janela = glutCreateWindow("PacMan");

    // Entrega funções de (re)desenho a GLUT
    glutDisplayFunc(&Processador::desenha);
    glutIdleFunc(&Processador::desenha);
    glutReshapeFunc(&Processador::redimensiona);

    // Trata recebimento de teclas
    glutKeyboardFunc(&Processador::tecla);
    glutSpecialFunc(&Processador::teclaEspecial);



    // Inicia renderização
    Processador::iniciaGL(1024, 768);

#ifdef __EMSCRIPTEN__
    // For WebAssembly, use emscripten_set_main_loop instead of glutMainLoop
    // This allows the browser to handle the event loop properly
    emscripten_set_main_loop(Processador::desenha, 0, 1);
#else
    // Native desktop version uses glutMainLoop
    glutMainLoop();
#endif

    return 1;

}
