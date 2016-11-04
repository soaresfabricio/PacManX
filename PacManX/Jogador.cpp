//
//  Jogador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Jogador.hpp"
#include "game.hpp"

DIRECAO Jogador::getDirecao(){
    return direcao;
}

void Jogador::setDirecao(DIRECAO d){
    direcao = d;
}

DIRECAO Jogador::getDirecaoDesejada(){
    return direcaoDesejada;
}

void Jogador::setDirecaoDesejada(DIRECAO d){
    direcaoDesejada = d;
}

void Jogador::atualizaDirecao(){
    direcao = direcaoDesejada;
}

void Jogador::setLadrilhoAtual(ladrilho *l){
    ladrilhoAtual = l;
}

ESTADOJOGADOR Jogador::getEstado(){
    return estado;
}

void Jogador::setMorrendo(){
    if (estado != MORRENDO) {
        estado = MORRENDO;
        progressoMorte = 0;
        // explosao.reset();
    }
}

void Jogador::resolvePosicao(float movemento){
    
    if (this->ehOposto(direcao, direcaoDesejada)) {
        ladrilhoAtual = ladrilhoAtual->getSaida(direcao);
        posicao = 1.0-posicao;
        direcao = direcaoDesejada;
    }
    
    if (direcao != nenhuma) posicao += movemento;
    if (direcao != nenhuma && posicao < 1.0) return;
    
    if (direcao == nenhuma && ladrilhoAtual->temSaida(direcaoDesejada)) {
        direcao = direcaoDesejada;
        ladrilhoAtual->getSaida(direcao)->setCor(1);
        direcaoDesejada = nenhuma;
    }
    
    if (posicao >= 1.0) {
        ladrilhoAtual = ladrilhoAtual->getSaida(direcao);
        ladrilhoAtual->setVisitado();
        if (ladrilhoAtual->temSaida(direcaoDesejada)) {
            posicao -= 1.0;
            direcao = direcaoDesejada;
            direcaoDesejada = nenhuma;
            return;
        }
        posicao = 0.0;
        if (!ladrilhoAtual->temSaida(direcao)) {
            direcao = nenhuma;
        }
    }
}

ponto Jogador::getPosicao(){

        ponto posicaoAtual = ladrilhoAtual->getCentro();
        switch (direcao) {
            case direita: posicaoAtual.x += posicao; break;
            case esquerda: posicaoAtual.x -= posicao; break;
            case cima: posicaoAtual.y += posicao; break;
            case baixo: posicaoAtual.y -= posicao; break;
            default: break;
        }
        return posicaoAtual;

}

//void Jogador::atualiza(float ticks){
//    ultimosTicks = ticks;
//    totalTicks += ticks;
//    if (game->getEstado() != parado) {
//        this->resolvePosicao(ultimosTicks * 8.0);
//    }
//}


void Jogador::processa(){
    ponto posicaoAtual = getPosicao();
    glPushMatrix();
    
    
        glTranslatef(posicaoAtual.x, posicaoAtual.y, -19.5);
    
        float direcaoDesenho = 0;
        switch (direcao) {
            case esquerda:
                direcaoDesenho = 90; break;
            case direita:
                direcaoDesenho = 270; break;
            case cima:
                direcaoDesenho = 180; break;
            case baixo:
                direcaoDesenho = 0; break;
            case nenhuma:
                direcaoDesenho = 0; break;
        }
    
        float limiar = 0;
    
        if (estado == VIVO) {
            limiar = (int)(posicao * 90 + 45) % 90;
            if (limiar > 45) {
                limiar = 90 + limiar;
            }
            else {
                limiar = 180 - limiar;
            }
        }
        else if (estado == MORRENDO) {
            limiar = 180 - (int)(progressoMorte * 180);
            if (limiar < -320) {
                direcao = nenhuma;
                estado = VIVO;
                Eventos::getInstancia()->emitir("morreu");
            }
            progressoMorte += ultimosTicks * 1;
        }
    
        visaoJogador.setRaio(0.7);
        if (direcao == nenhuma) {
            visaoJogador.processa(direcaoDesenho, 180-25, estado == VIVO);
        }
        else {
            visaoJogador.processa(direcaoDesenho, limiar, estado == VIVO);
        }
    
        if (estado == MORRENDO) {
            //pacmanExplosion.render(lastTicks);
        }
        
        glPopMatrix();
}

ladrilho * Jogador::getLadrilhoAtual(){
    return ladrilhoAtual;
}
