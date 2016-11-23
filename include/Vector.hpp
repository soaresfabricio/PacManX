//
//  Vector.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#pragma once

struct Vector
{
    float x,y,z;
    
    Vector() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    
    Vector(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    Vector operator+(const Vector &outro)
    {
        Vector resultado;
        resultado.x = x + outro.x;
        resultado.y = y + outro.y;
        resultado.z = z + outro.z;
        return resultado;
    }
    
    Vector operator*(float escalar)
    {
        Vector resultado;
        resultado.x = x * escalar;
        resultado.y = y * escalar;
        resultado.z = z * escalar;
        return resultado;
    }
};
