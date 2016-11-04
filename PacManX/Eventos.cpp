//
//  Eventos.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "Eventos.hpp"

Eventos * Eventos::instancia = new Eventos();

Eventos * Eventos::getInstancia() {
    return instancia;
}

void Eventos::emitir(std::string signal) {
    if (observadores.find(signal) != observadores.end()) {
        for (unsigned int i = 0; i < observadores[signal].size(); i++) {
            observadores[signal][i]->onSignal(signal);
        }
    }
    else {
        std::cout << "Lost signal -> " << signal << "\n";
    }
}

void Eventos::adicionar(Observador * Observador, std::string signal) {
    observadores[signal].push_back(Observador);
}
