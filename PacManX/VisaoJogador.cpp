//
//  VisaoJogador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "VisaoJogador.hpp"

ponto VisaoJogador::normalizaVetor(ponto v) {
    ponto normalizado;
    float comprimento = (float)(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
    normalizado.x = v.x / comprimento;
    normalizado.y = v.y / comprimento;
    normalizado.z = v.z / comprimento;
    return normalizado;
}

void VisaoJogador::setRotacao(double r) {
    rotacao = r;
}

void VisaoJogador::setRaio(double r) {
    raio = r;
}

void VisaoJogador::processa(float direcao, float abertura, bool desenhado) {
    glRotatef(90, 0, 1, 0);
    glRotatef(rotacao, 0, 0, 1);
    glRotatef(direcao, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    
    if (!desenhado) return;
    
    std::vector<ponto> pontos;
    std::map<int,bool> boca;
    
    int lats = 24;
    int longs = 24;
    
    float i, j;
    
    for(i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);
        
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        bool desenhadon = false;
        
        float m;
        
        for(j = 0; j <= 360; j += 360 / longs) {
            if (j <= abertura || j >= 360 - abertura) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
                
                glColor3f(1, 1, 0);
                
                pontos.push_back(ponto(raio * x * zr1, raio * y * zr1, raio * z1));
                pontos.push_back(ponto(raio * x * zr0, raio * y * zr0, raio * z0));
            }
            else if (!desenhadon) {
                desenhadon = true;
                
                m = (int)(0.5 + abertura);
                
                double lng = 2 * M_PI * (double) (m - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
                
                
                pontos.push_back(ponto(raio * x * zr1, raio * y * zr1, raio * z1));
                pontos.push_back(ponto(raio * x * zr0, raio * y * zr0, raio * z0));
                boca[(int)pontos.size()] = true;
                pontos.push_back(ponto(raio * x * zr1, raio * y * zr1, raio * z1));
                pontos.push_back(ponto(raio * x * zr0, raio * y * zr0, raio * z0));
                pontos.push_back(ponto(0, 0, raio * z1));
                pontos.push_back(ponto(0, 0, raio * z0));
                
                m = (int)(0.5 + 360 - abertura);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);
                
                pontos.push_back(ponto(raio * x * zr1, raio * y * zr1, raio * z1));
                pontos.push_back(ponto(raio * x * zr0, raio * y * zr0, raio * z0));
                
                boca[(int)pontos.size()] = false;
                pontos.push_back(ponto(raio * x * zr1, raio * y * zr1, raio * z1));
                pontos.push_back(ponto(raio * x * zr0, raio * y * zr0, raio * z0));
            }
        }
    }
    
    glColor3f(1,1,0);
    
    bool isboca = false;
    
    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < pontos.size(); i++) {
        
        if (boca.find(i) != boca.end()) {
            if (boca.find(i)->second) {
                glColor3f(1, 0, 0);
                isboca = true;
            }
            else {
                glColor3f(1, 1, 0);
                isboca = false;
            }
        }
        
        ponto p = pontos[i];
        
        ponto n = normalizaVetor(p);
        if (isboca) {
            glNormal3f(-1, 0, 0);
        }
        else {
            glNormal3f(n.x, n.y, n.z);
        }
        
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}
