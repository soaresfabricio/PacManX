//
//  jogador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 24/09/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "jogador.hpp"

DIRECAO jogador::getDirecao(){
    return dir;
}

void jogador::setDirecao(DIRECAO d){
    dir = d;
}

DIRECAO jogador::getDirDesejada(){
    return dirDesejada;
}

void jogador::setDirDesejada(DIRECAO d){
    dirDesejada = d;
}

void jogador::atualizaDirecao(){
    dir = dirDesejada;
}

void jogador::setLadrilho(ladrilho *l){
    ladAtual = l;
}

ladrilho * jogador::getLadrilho(){
    return ladAtual;
}

ponto jogador::getPosicao(){
    ponto posAtual = ladAtual->getCentro();
    
    switch (dir) {
            
            // Adiciona um delta positivo a coordenada x atual
        case direita:
            posAtual.x = posAtual.x + pos;
            break;
            
            // Adiciona um delta negativo a coordenada x atual
        case esquerda:
            posAtual.x = posAtual.x - pos;
            
            // Adiciona um delta positivo a coordenada y atual
        case cima:
            posAtual.y = posAtual.y + pos;
            
            // Adiciona um delta negativo a coordenada y atual
        case baixo:
            posAtual.y = posAtual.y + pos;
            
        default:
            break;
    }
    
    return posAtual;
}

void jogador::posiciona(float movimento){
    
    if (this->eh) {
        <#statements#>
    }
    
//    // Backwardo
//    if (this->isOpposite(direction, wantedDirection)) {
//        currentTile = currentTile->getExit(direction);
//        position = 1.0-position;
//        direction = wantedDirection;
//        std::cout << "Pacman se vira" << std::endl;
//    }
//    
//    if (direction != none) position += movement;
//    if (direction != none && position < 1.0) return;
//    
//    if (direction == none && currentTile->hasExit(wantedDirection)) {
//        direction = wantedDirection;
//        currentTile->getExit(direction)->setColor(1);
//        wantedDirection = none;
//        std::cout << "Pacman volta a ativa" << std::endl;
//    }
//    
//    if (position >= 1.0) {
//        currentTile = currentTile->getExit(direction);
//        currentTile->setVisited();
//        if (currentTile->hasExit(wantedDirection)) {
//            position -= 1.0;
//            direction = wantedDirection;
//            wantedDirection = none;
//            std::cout << "Pacman recebe novo comando" << std::endl;
//            return;
//        }
//        position = 0.0;
//        if (!currentTile->hasExit(direction)) {
//            direction = none;
//            std::cout << "Pacman encontra parede" << std::endl;
//            
//        }
//    }


/**
 * Processa posição do jogador e renderiza PacMan.
 */

void jogador::processa(float ticks){
    
    // Configura uma certa velocidade
    this->posiciona(ticks * 8.0);
    
    ponto centro = ladAtual->getCentro();
    
    switch (dir) {
            
            // Adiciona um delta positivo ao ladrilho x atual
        case direita:
            centro.x = centro.x + pos;
            break;
            
            // Adiciona um delta negativo ao ladrilho x atual
        case esquerda:
            centro.x = centro.x - pos;
            
            // Adiciona um delta positivo ao ladrilho y atual
        case cima:
            centro.y = centro.y + pos;
            
            // Adiciona um delta negativo ao ladrilho y atual
        case baixo:
            centro.y = centro.y + pos;
            
        default:
            break;
    }
    
    // tamanho do personagem
    double raio = 0.7;
    
    // triângulos que formam o personagem
    int latitudes = 12;
    int longitudes = 12;
    
    float i, j;
    
    glPushMatrix();
    
    glTranslatef(centro.x, centro.y, -19.5);
    glRotatef(90, 0, 1, 0);
    
    switch (dir) {
        case esquerda:
            glRotatef(90, 1, 0, 0);
            break;
        case direita:
            glRotatef(270, 1, 0, 0);
            break;
        case cima:
            glRotatef(180, 1, 0, 0);
            break;
        case baixo:
            glRotatef(0, 1 , 0, 0);
            break;
        case nenhuma:
            glRotatef(0, 1, 0, 0);
            break;
        default:
            break;
    }
    
    // velocidade da boca
    int limite = (int)(pos * 180 + 90) % 180;
    if(limite > 90){
        limite = 180 - limite;
    }
    
    // Animação do personagem
    
    for (i = 1; i <= latitudes; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i-1) / latitudes );
        double z0 = sin(lat0);
        double zr0 = cos(lat0);
        
        double lat1 = M_PI * (-0.5 + (double)i / latitudes);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        bool desenhado = false;
        
        float metadeLimite = limite / 2;
        float m;
        
        
        // Desenhando...
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= 360; j += 360 / longitudes) {
            
            if (j <= 180 + 45 + metadeLimite || j >= 360 - 45 - metadeLimite) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                
                double x = cos(lng);
                double y = sin(lng);
                
                glColor3f(1, 1, 0);
                
                
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr1, raio * y * zr1, raio * z1);
                
            } else if (!desenhado){
                
                desenhado = true;
                m = (int)(0.5 + 180 + 45 + metadeLimite);
                
                double lng = 2 * M_PI + 45 + metadeLimite;
                double x = cos(lng);
                double y = sin(lng);
                
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z1);
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr1, raio * y * zr1, raio * z1);
                glColor3f(1,0,0);
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr1, raio * y * zr1, raio * z1);
                glVertex3f(0, 0, raio * z0);
                glVertex3f(0, 0, raio * z1);
                
    
                
                m = (int)(0.5 + 360 - 45 - metadeLimite);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);
                
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr1, raio * y * zr1, raio * z1);
                glColor3f(1,1,0);
                glVertex3f(raio * x * zr0, raio * y * zr0, raio * z0);
                glVertex3f(raio * x * zr1, raio * y * zr1, raio * z1);
                
            }
            
            
        }
        glEnd();
        
    }
    
    glPopMatrix();
    
    
}
