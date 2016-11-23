//
//  Explosao.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Explosao.hpp"
#include "Particula.cpp"
#include "ParticulaSangue.cpp"

#include <SFML/Audio.hpp>


Explosao::Explosao() {
    reiniciar();
}

void Explosao::reiniciar() {

    tocaSom("sounds/explosion.wav");

    totalTicks = 0;
    std::vector<Vector> pontos;
    particulas.clear();
    particulasSangue.clear();

    double r = 0.7;
    int lats = 24;
    int longs = 24;

    for(float i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for(float j = 0; j < 360; j += 360 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);

            pontos.push_back(Vector(r * x * zr1, r * y * zr1, r * z1));
            pontos.push_back(Vector(r * x * zr0, r * y * zr0, r * z0));
        }
    }

    for (unsigned int i = 0; i < pontos.size() - 2; i += 2) {
        int part = ((i % 48) / 6) + 100*(i / (48*4));

        if (particulas.find(part) == particulas.end()) {
            particulas[part] = Particula();
            particulas[part].setPosicao(pontos[i]);
        }

        std::vector<Vector> polyPoints;

        for (int j = 0; j < 4; j++) {
            Vector p = pontos[i + j];
            switch (j) {
                case 2:
                    p = pontos[i+3]; break;
                case 3:
                    p = pontos[i+2]; break;
            }
            polyPoints.push_back(p);
            Vector n = normaliza(p);
            particulas[part].adicionaQuadPonto(p, n);
        }

        for (int j = 0; j < 4; j++) {
            std::vector<Vector> polyVector;
            polyVector.push_back(polyPoints[(j + 1) % 4]);
            polyVector.push_back(polyPoints[j]);
            polyVector.push_back(Vector(0, 0, 0));
            for (unsigned int m = 0; m < polyVector.size(); m++) {
                Vector p = polyVector[m];
                Vector n = normaliza(p);
                particulas[part].adicionaTrianguloPonto(p, n);
            }
        }
    }
}

Vector Explosao::normaliza(Vector vector) {
    Vector normalizado;
    float comprimento = (float)(sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
    normalizado.x = vector.x / comprimento;
    normalizado.y = vector.y / comprimento;
    normalizado.z = vector.z / comprimento;
    return normalizado;
}

void Explosao::processa(float ticks) {

    glPushMatrix();

    for (unsigned int i = 0; i < particulasSangue.size(); i++) {
        particulasSangue[i].atualiza(ticks);
        particulasSangue[i].processa();
    }

    for (unsigned int i = 0; i < particulas.size(); i++) {
        particulas[i].atualiza(ticks);
        if (particulasSangue.size() < 300 && rand() % 500 == 1) {
            ParticulaSangue sangue;
            sangue.setPosicao(particulas[i].getPosicao());
            Vector vectorMovimento = particulas[i].getVectorMovimento();
            vectorMovimento.x *= 0.5;
            vectorMovimento.y *= 0.5;
            vectorMovimento.z *= 0.5;
            sangue.setVectorMovimento(vectorMovimento);
            particulasSangue.push_back(sangue);
        }
        particulas[i].processa();
    }

    glPopMatrix();
    totalTicks += ticks;
}

bool Explosao::completo() {
    return false;
}
