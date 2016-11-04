//
//  Eventos.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

#include "Observador.hpp"

class Eventos {
    
private:
    static Eventos * instancia;
    std::map<std::string, std::vector<Observador*> > observadores;
    
public:
    static Eventos * getInstancia();
    void emitir(std::string signal);
    void adicionar(Observador * observadorEventos, std::string signal);
    
};
