//
//  main.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

// Indicada ao compilador qual arquivo incluir, de acordo com o Sistema Operacional
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <iostream>
#include "processador.cpp"

int main(int argc, char * argv[]) {
    
    
    // Entrega os argumentos para a GLUT
    glutInit(&argc, argv);
    
    // Double buffer, cores RGBA, componentes alpha, clipping automático (depth buffer)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH );
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    
    janela = glutCreateWindow("PacMan X");
    
    glutDisplayFunc(&processador::desenha);
    
    glutIdleFunc(&processador::desenha);

    glutKeyboardFunc(&processador::teclaPressionada);
    
    processador::iniciaGL(800, 600);
    
    glutMainLoop();
    
    return 1;
    
}
