//
//  BMPLoader.hpp
//  PacManX
//
//  Created by Fabrício Soares on 18/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class BMPloader {
    
public:
    
    BMPloader( const string filename);
    ~BMPloader();
    
    const bool   Isvalid() const { return mIsOK;   }
    const char * Image()   const { return mImage;  }
    const int    Width()   const { return mWidth;  }
    const int    Heigth()  const { return mHeight; }
    
protected:
    ifstream * infile;
    char     * mImage;
    int        mWidth, mHeight;
    bool       mIsOK;
    
    const unsigned int getShort();
    const unsigned int getLong();
};
