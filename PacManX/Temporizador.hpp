//
//  timer.hpp
//  PacManX
//
//  Created by Fabrício Soares on 21/10/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//
#pragma once

class Temporizador{
private:
    long segundoInicial;
public:
    Temporizador();
    void iniciar();
    float getSegundos();
};
