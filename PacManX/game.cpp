
//
//  game.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "game.hpp"

void game::carregar(){

    
}


void game::processa(){
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    gluLookAt (0, -20, 18, 0, -2, 10, 0.0, 1.0, 0.0);
    glEnable ( GL_LIGHTING ) ;
    GLfloat position[] = { 0.5, -0.5, 1, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    GLfloat ambient[] = {0.1, 0.1, 0.1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_LIGHT0);
    
    glMateriali(GL_FRONT, GL_SHININESS, 96);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
    
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;
    
    
    tabuleiro.processa();
    

    
    glLoadIdentity();

}
