//
//  main.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "headers.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "Processador.cpp"
#include "BMPLoader.cpp"



void LoadTexture( const std::string & textureFilename) {
    BMPloader * bitmap = new BMPloader(textureFilename);
    if (bitmap->Isvalid()) {
        glPixelStoref( GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->Image());
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    } else {
        std::cout << "Problems Loading Texture" << std::endl;
    }

    delete bitmap;
}

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

    LoadTexture("darkmetal.bmp");



    glutMainLoop();

    return 1;

}
