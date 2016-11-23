//
//  Inimigo.cpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Inimigo.hpp"
#include "../include/Game.hpp"

void Inimigo::setLadrilhoAtual(Ladrilho *l) {
    ladrilhoAtual = l;
}

void Inimigo::setJogador(Jogador *j) {
    jogador = j;
}

ponto Inimigo::getPosicao() {
    ponto posicaoAtual = ladrilhoAtual->getCentro();
    switch (direcao) {
        case direita: posicaoAtual.x += pos; break;
        case esquerda: posicaoAtual.x -= pos; break;
        case cima: posicaoAtual.y += pos; break;
        case baixo: posicaoAtual.y -= pos; break;
        default: break;
    }
    return posicaoAtual;
}

void Inimigo::iniciar() {
    Eventos::getInstancia()->adicionar(this, "energizer");
    resolvePosicao(0.0);
}

void Inimigo::resolvePosicaoAssustado(float ticks) {
    std::vector<DIRECAO> direcoes;
    DIRECAO dirs[] = {cima, baixo, esquerda, direita};
    DIRECAO dir = nenhuma;

    int distancia = 0;
    for (int i = 0; i < 4; i++) {
        if (ladrilhoAtual->temSaida(dirs[i])) {
            float essaDistancia = this->distancia(ladrilhoAtual->getSaida(dirs[i])->getPosicao(), jogador->getLadrilhoAtual()->getPosicao());
            if (!this->ehOposto(dirs[i], direcao)) direcoes.push_back(dirs[i]);
            if (essaDistancia > distancia && !this->ehOposto(dirs[i], direcao)) {
                dir = dirs[i];
                distancia = essaDistancia;
            }
        }
    }

    direcao = dir;
}

void Inimigo::resolvePosicao(float ticks) {
    std::vector<DIRECAO> direcoes;
    DIRECAO dirs[] = {cima, baixo, esquerda, direita};
    DIRECAO dir = nenhuma;

    posicaoAlvo = this->getPosicaoAlvo();

    int distancia = 99;
    for (int i = 0; i < 4; i++) {
        if (ladrilhoAtual->temSaida(dirs[i])) {
            float essaDistancia = this->distancia(ladrilhoAtual->getSaida(dirs[i])->getPosicao(), posicaoAlvo);
            if (!this->ehOposto(dirs[i], direcao)) direcoes.push_back(dirs[i]);
            if (essaDistancia < distancia && !this->ehOposto(dirs[i], direcao)) {
                dir = dirs[i];
                distancia = essaDistancia;
            }
        }
    }

    direcao = dir;
}

posicao Inimigo::getPosicaoAlvo() {
    if (estado == COMIDO) {
        posicao p;
        p.x = 15.5;
        p.y = 15.5;
        return p;
    }
    return jogador->getLadrilhoAtual()->getPosicao();
}

void Inimigo::direcaoContraria() {
    ladrilhoAtual = ladrilhoAtual->getSaida(direcao);
    direcao = getOposto(direcao);
    pos = 1.0 - pos;
}

ESTADOINIMIGO Inimigo::getEstado() {
    return estado;
}

void Inimigo::onSignal(std::string nome) {
    if (nome == "energizer" && estado != COMIDO) {
        if (estado != FUGINDO) {
            direcaoContraria();
        }
        tempoAssustado = 8;
        estado = FUGINDO;
    }
}

void Inimigo::setCor() {
    if (estado == FUGINDO) {
        bool branco = tempoAssustado < 3 && (int)((3.0-tempoAssustado) * (3.0-tempoAssustado)) % 2 == 0;
        glColor3f((int)branco, (int)branco, 1);
    }
    else {
        setCorReal();
    }
}

void Inimigo::setCorReal() {
    glColor3f(1, 1, 1);
}

void Inimigo::atualiza(float ticks) {
    if (game->getEstado() == parado) {
        ticks = 0;
    }

    tempoJogo += ticks;
    float velocidade = 6.0;
    if (estado == FUGINDO) velocidade = 3.5;
    totalTicks += ticks * velocidade;

    if (estado == COMIDO) {
        if (ladrilhoAtual->getPosicao().x >= 14 && ladrilhoAtual->getPosicao().x <= 16
            && ladrilhoAtual->getPosicao().y >= 14 && ladrilhoAtual->getPosicao().y <= 16) {
            estado = PERSEGUINDO;
        }
    }

    if (estado == FUGINDO && tempoAssustado > 0) {
        tempoAssustado -= ticks;
        if (tempoAssustado <= 0) {
            direcaoContraria();
        }
    }
    else if (estado != COMIDO) {
        int mod = (int)tempoJogo % 27;

        if (mod <= 7) {
            estado = DISPERSO;
        }
        else {
            estado = PERSEGUINDO;
        }
    }

    if (estado == FUGINDO) {
        float distancia = this->distancia(ladrilhoAtual->getPosicao(), jogador->getLadrilhoAtual()->getPosicao());
        if (distancia < 1) {
            Eventos::getInstancia()->emitir("ghost_eaten");
            estado = COMIDO;
        }
    }

    if (direcao != nenhuma) {
        pos += ticks * velocidade;
    }
    if (pos >= 1.0) {
        pos--;
        ladrilhoAtual = ladrilhoAtual->getSaida(direcao);

        DIRECAO tDirecao = direcao;
        if (estado == FUGINDO) {
            resolvePosicaoAssustado(ticks * velocidade);
        }
        else {
            this->resolvePosicao(ticks * velocidade);
        }
        if (direcao == nenhuma) direcao = getOposto(tDirecao);
    }
}

void Inimigo::processa() {
    ponto centro = ladrilhoAtual->getCentro();

    switch (direcao) {
        case direita: centro.x += pos; break;
        case esquerda: centro.x -= pos; break;
        case cima: centro.y += pos; break;
        case baixo: centro.y -= pos; break;
        default: break;
    }

    this->setCor();

    glPushMatrix();
    glLineWidth(0.5);

    float delta = (totalTicks / 3 - (int)(totalTicks / 3));
    float altura = 0.2 * sin(M_PI * delta);

    glTranslatef(centro.x, centro.y, -19.4 + altura);

    switch (direcao) {
        case baixo:
            glRotatef(90,0,0,1); break;
        case cima:
            glRotatef(270,0,0,1); break;
        case esquerda:
            glRotatef(0,0,0,1); break;
        case direita:
            glRotatef(180,0,0,1); break;
    }

    if (estado != COMIDO) {
        processaCorpo();
    }
    processaOlhos();
    glPopMatrix();
}

void Inimigo::processaCorpo() {
    double r = 0.6;
    int lats = 24;
    int longs = 24;
    float i, j;

    std::vector<ponto> pontos;

    for(i = lats/2; i <= lats; i++) {
        double lat0, z0, zr0;

        if (i == lats / 2) {
            double d = lats / 2;
            lat0 = M_PI * (-0.5 + (double) (d) / lats);
            z0  = sin(M_PI * (-0.5 + (double)1.0 / lats));
            zr0 = cos(lat0);
        }
        else {
            lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            z0  = sin(lat0);
            zr0 = cos(lat0);
        }

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(M_PI * (-0.5 + (double) i / lats));
        double zr1 = cos(lat1);

        bool impar = true;
        for(j = 0; j <= 360; j += 360.0 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);

            double ext = 0;
            if (i == lats / 2 && impar) {
                ext = 0.2;
            }

            pontos.push_back(ponto(r * x * zr1, r * y * zr1, r * z1));
            pontos.push_back(ponto(r * x * zr0, r * y * zr0, r * z0 + ext));

            impar = !impar;
        }
    }

    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < pontos.size(); i++) {
        ponto p = pontos[i];

        ponto n = normalizaVetor(p);
        glNormal3f(n.x, n.y, n.z);

        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

}

void Inimigo::processaOlhos() {
    glColor3f(1, 1, 1);
    glTranslatef(-0.40, 0.15, 0.1);
    glutSolidSphere(0.25, 8, 8);

    glTranslatef(0, -0.3, 0);
    glutSolidSphere(0.25, 8, 8);

    glColor3f(0, 0, 0);
    glTranslatef(-0.22, -0.035, 0);
    glutSolidSphere(0.05, 8, 8);

    glTranslatef(0, 0.035+0.3, 0);
    glutSolidSphere(0.05, 8, 8);
}

Ladrilho * Inimigo::getLadrilhoAtual() {
    return ladrilhoAtual;
}
