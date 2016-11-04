//
//  Evento.hpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// Padrão de Projeto: Observador

class Observador{
    
public:
    virtual void onSignal(std::string name);
    
};
