#pragma once

// Estados válido de direção
enum DIRECAO {
    nenhuma,
    cima,
    baixo,
    direita,
    esquerda
};

struct ponto {
public:
    float x;
    float y;
    float z;
    
    ponto() {
        
    }
    
    ponto(float _x, float _y, float _z = 0.0) {
        x = _x;
        y = _y;
        z = _z;
    }
};


struct posicao {
    int x;
    int y;
};
