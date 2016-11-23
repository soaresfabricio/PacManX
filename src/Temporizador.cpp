//
//  Temporizador.cpp
//  PacManX
//
//  Created by Fabrício Soares on 21/10/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Temporizador.hpp"

Temporizador::Temporizador(){
    iniciar();
}

void Temporizador::iniciar(){
    struct timeval iniciar;
    gettimeofday(&iniciar, NULL);
    segundoInicial = iniciar.tv_sec;
}

float Temporizador::getSegundos(){
    struct timeval iniciar;
    gettimeofday(&iniciar, NULL);

    return (iniciar.tv_sec - segundoInicial) + iniciar.tv_usec/1000000.0;
}
