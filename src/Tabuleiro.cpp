//
//  Tabuleiro.cpp
//  PacManX
//
//  Created by Fabrício Soares on 03/11/16.
//  Copyright © 2016 Fabrício, Yooh e Wesnydy. All rights reserved.
//

#include "../include/Tabuleiro.hpp"
#include "BMPLoader.cpp"


void LoadTexture( const std::string & textureFilename, GLuint *texname) {
  static int num = 0;
  BMPloader * bitmap = new BMPloader(textureFilename);
  if (bitmap->Isvalid()) {

    glGenTextures (1, texname);
    glBindTexture (GL_TEXTURE_2D, *texname);

    glPixelStoref( GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D( GL_TEXTURE_2D, num++, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->Image());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    std::cout << textureFilename << " loaded." << std::endl;

  } else {
    std::cout << textureFilename << " not loaded." << std::endl;
  }

  delete bitmap;
}

void Tabuleiro::desenhaParedePequena(){

  std::vector<ponto> pontos;
  pontos.push_back(ponto(0.5, 0.30));
  pontos.push_back(ponto(-0.5, 0.30));
  pontos.push_back(ponto(-0.5, -0.30));
  pontos.push_back(ponto(0.5, -0.30));

  glBegin(GL_QUADS);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, 0, 1);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, -1, 0);
    glVertex3f(p.x, p.y, -0.02);
    glVertex3f(p.x, p.y, -1.02);
  }
  glEnd ();

}


void Tabuleiro::desenhaFimPequeno() {
  std::vector<ponto> pontos;
  pontos.push_back(ponto(0.5, 0.30));
  pontos.push_back(ponto(-0.3, 0.30));
  pontos.push_back(ponto(-0.3, -0.30));
  pontos.push_back(ponto(0.5, -0.30));

  glBegin(GL_QUADS);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, 0, 1);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, -1, 0);
    glVertex3f(p.x, p.y, -0.02);
    glVertex3f(p.x, p.y, -1.02);
  }
  glEnd ();
}



void Tabuleiro::desenhaCantoPequeno() {
  std::vector<ponto> pontos;
  pontos.push_back(ponto(-0.3, 0.5));
  pontos.push_back(ponto(-0.3, -0.3));
  pontos.push_back(ponto(0.5, -0.3));
  pontos.push_back(ponto(0.5, 0.3));
  pontos.push_back(ponto(0.3, 0.3));
  pontos.push_back(ponto(0.3, 0.5));

  glBegin(GL_POLYGON);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, 0, 1);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();


  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, -1, 0);
    glVertex3f(p.x, p.y, -0.02);
    glVertex3f(p.x, p.y, -1.02);
  }
  glEnd ();
}

void Tabuleiro::desenhaParedeGrande() {
  std::vector<ponto> pontos;
  pontos.push_back(ponto(0.5, 0.149));
  pontos.push_back(ponto(-0.5, 0.149));
  pontos.push_back(ponto(-0.5, -0.15));
  pontos.push_back(ponto(0.5, -0.15));

  glBegin(GL_QUADS);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    /*
    if (i < 2)
    glNormal3f(0, 1, 0);
    else
    glNormal3f(0, -1, 0);*/
    glNormal3f(0, 0, 1);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    if (i < 2) {
      glNormal3f(0, 1, 0);
      glColor3f(0,0,0.50);
    }
    else {
      glNormal3f(0, -1, 0);
      glColor3f(0,0,1);
    }
    glVertex3f(p.x, p.y, -0.02);
    if (i < 2) {
      glNormal3f(0, 1, 0);
      glColor3f(0,0,1);
    }
    else {
      glNormal3f(0, -1, 0);
      glColor3f(0,0,0.25);
    }
    glVertex3f(p.x, p.y, -1.02);
  }
  glColor3f(0,0,1);
  glEnd ();


}



void Tabuleiro::desenhaCantoGrande(bool isInset) {
  float x, y;
  float raioGrande = 0.65;
  float raioPequeno = 0.35;

  std::vector<ponto> opontos;
  std::vector<ponto> pontos;
  std::vector<ponto> normais;

  for(float j = 90; j >= 0; j -= 15)
  {
    float step = 90 - j;
    x = 1 - raioGrande * cos(step * PI/180.0);
    y = 1 - raioGrande * sin(step * PI/180.0);
    pontos.push_back(ponto(x - 0.5, y - 0.5));

    x = 1 - raioPequeno * cos(step * PI/180.0);
    y = 1 - raioPequeno * sin(step * PI/180.0);
    opontos.push_back(ponto(x - 0.5, y - 0.5));

    x = 0 - cos(step * PI/180.0);
    y = 0 - sin(step * PI/180.0);
    normais.push_back(ponto(x, y));
  }

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    ponto n = normais[i];
    glColor3f(0, 0, 1 - isInset * 0.50);
    glNormal3f(n.x, n.y, 0);
    glVertex3f(p.x, p.y, -0.02);
    glColor3f(0, 0, 0.4 - isInset * 0.25);
    glNormal3f(n.x, n.y, 0);
    glVertex3f(p.x, p.y, -1.02);
  }
  glEnd ();


  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = opontos[i];
    ponto n = normais[i];
    if (isInset) glColor3f(0, 0, 0.25);
    else glColor3f(0, 0, 0);
    glNormal3f(0-n.x, 0-n.y, 0);
    glVertex3f(p.x, p.y, -1.02);
    if (isInset) glColor3f(0, 0, 1);
    else glColor3f(0, 0, 0.5);
    glNormal3f(0-n.x, 0-n.y, 0);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();



  glColor3f(0, 0, 1);

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < opontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0-(p.x-0.5), 0-(p.y-0.5), 0);
    glNormal3f(0,0,1);
    glVertex3f(opontos[i].x, opontos[i].y, -0.02);
    //glNormal3f((p.x-0.5), (p.y-0.5), 0);
    glNormal3f(0,0,1);
    glVertex3f(pontos[i].x, pontos[i].y, -0.02);
  }
  glEnd ();
}



void Tabuleiro::desenhaGrandeInset() {
  std::vector<ponto> pontos;
  pontos.push_back(ponto(0.5, 0.5));
  pontos.push_back(ponto(-0.5, 0.5));
  pontos.push_back(ponto(-0.5, 0));
  pontos.push_back(ponto(0, -0.5));
  pontos.push_back(ponto(0.5, -0.5));

  glBegin(GL_POLYGON);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    glNormal3f(0, 0, 1);
    glVertex3f(p.x, p.y, -0.02);
  }
  glEnd ();

  glBegin(GL_QUAD_STRIP);
  for (unsigned int i = 0; i < pontos.size(); i++) {
    ponto p = pontos[i];
    if (i == 2)
    glNormal3f(0, -1, 0);
    if (i == 3)
    glNormal3f(-1, 0, 0);
    glVertex3f(p.x, p.y, -0.02);
    glNormal3f(-0.6, -0.6, 0);
    if (i == 2)
    glNormal3f(0, -1, 0);
    if (i == 3)
    glNormal3f(-1, 0, 0);
    glVertex3f(p.x, p.y, -1.02);
  }
  glEnd ();
}

void Tabuleiro::desenhaLinhas(float * cor, int x, int y, float px, float py) {
  glLineWidth(1.0);

  std::bitset<9> grade;

  grade[0] = ehParede(x-1, y-1);
  grade[1] = ehParede(x+0, y-1);
  grade[2] = ehParede(x+1, y-1);
  grade[3] = ehParede(x-1, y+0);
  grade[4] = ehParede(x+0, y+0);
  grade[5] = ehParede(x+1, y+0);
  grade[6] = ehParede(x-1, y+1);
  grade[7] = ehParede(x+0, y+1);
  grade[8] = ehParede(x+1, y+1);

  float size = 0.50;

  float rpx = px;
  float rpy = py;
  px += (1.0 - size) / 2.0;
  py += (1.0 - size) / 2.0;

  std::vector<ponto> pontos;

  float z = -19;

  int contador = 0;
  int desenhar = -1;
  while (true) {
    int tipoDesenho = contador / 4;
    float rotacao = (contador % 4) * 90;

    switch (tipoDesenho) {
      case 0:
      if (!grade[1] && !grade[7] && grade[3] && grade[5]) desenhar = 0;
      break;
      case 1:
      if (!grade[1] && !grade[7] && grade[5]) desenhar = 1;
      break;
      case 2:
      if (!grade[1] && grade[7] && !grade[3] && grade[5] && !grade[8]) desenhar = 2;
      break;
      case 3:
      if (!grade[1] && grade[7] && grade[3] && grade[5]) desenhar = 3;
      break;
      case 4:
      if (!grade[1] && grade[7] && !grade[3] && grade[5]) desenhar = 4;
      break;
      case 5:
      if (grade.count() == 8 && !grade[0]) desenhar = 5;
      break;
      default:
      return;
    }

    if (desenhar > -1) {
      glPushMatrix();
      glTranslatef(rpx+0.5, rpy+0.5, z);
      glRotatef(rotacao, 0, 0, 1);

      switch (desenhar) {
        case 0:
        desenhaParedePequena();
        break;
        case 1:
        desenhaFimPequeno();
        break;
        case 2:
        desenhaCantoPequeno();
        break;
        case 3:
        desenhaParedeGrande();
        break;
        case 4:
        desenhaCantoGrande(false);
        break;
        case 5:
        glRotatef(180, 0, 0, 1);
        desenhaCantoGrande(true);
        break;
      }

      glRotatef(0 - rotacao, 0, 0, 1);
      glPopMatrix();
      return;
    }
    grade = gridRotacoes(grade);
    contador++;
  }
}


void Tabuleiro::desenhaCanto(float xc, float yc, float z, float start, bool interno) {
  float x,y;
  float raio = 0.5f;

  glPushMatrix();
  glTranslatef(xc, yc, z);
  glRotatef(start, 0, 0, 1);

  glBegin(GL_LINE_STRIP);
  x = (float)raio * cos(359 * PI/180.0f);
  y = (float)raio * sin(359 * PI/180.0f);
  for(float j = 0; j <= 90; j += 15)
  {
    float step = interno ? j : 90 - j;
    x = (float)raio * cos(step * PI/180.0f);
    y = (float)raio * sin(step * PI/180.0f);
    glVertex3f(x-0.5, y-0.5, 0);
  }
  glEnd();



  glBegin(GL_POLYGON);
  x = (float)raio * cos(359 * PI/180.0f);
  y = (float)raio * sin(359 * PI/180.0f);

  if (!interno) {
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5, 0.5, -0.02);
  }

  for(float j = 0; j <= 90; j += 15)
  {
    float step = interno ? j : 90 - j;
    x = (float)raio * cos(step * PI/180.0f);
    y = (float)raio * sin(step * PI/180.0f);
    glNormal3f(0, 0, 1);
    glVertex3f(x-0.5, y-0.5, -0.02);
  }
  if (interno) {
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5, -0.5, -0.02);
  }
  else {
    glNormal3f(0, 0, 1);
    glVertex3f(0.5, -0.5, -0.02);

    glNormal3f(0, 0, 1);
    glVertex3f(0.5, 0.5, -0.02);
  }
  glEnd();





  glRotatef(-start, 0, 0, 1);
  glPopMatrix();
}

void Tabuleiro::criaNormal(float x, float y, float z) {
  glNormal3f(x,y,z);
}



void Tabuleiro::criaTabuleiro() {
  glNewList(tabuleiroDisplayList, GL_COMPILE);

  int alturaTabuleiro = getAltura();
  int larguraTabuleiro = getLargura();

  GLuint floor;
  LoadTexture("texture/darkmetal.bmp", &floor);

  glBindTexture(GL_TEXTURE_2D, floor);

  glPushMatrix();
  //glLoadIdentity();
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);

  glColor3d(1, 1, 1);
  glTexCoord2f(-4.0f, -4.0f);
  glVertex3d(-13.5,-14.5,-20);

  glTexCoord2f(4.0f, -4.0f);
  glVertex3d(13.5,-14.5,-20);

  glTexCoord2f(4.0f, 4.0f);
  glVertex3d(13.5,15.5,-20);

  glTexCoord2f(-4.0f, 4.0f);
  glVertex3d(-13.5,15.5,-20);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();


  for (int x = 0; x < larguraTabuleiro; x++) {
    for (int y = 0; y < alturaTabuleiro; y++) {

      float * cor = getPixel(x,y);

      ponto centro;
      centro.x = (float)x - (largura / 2 - 0.5);
      centro.y = (float)y - (altura / 2 - 0.5);
      centro.z = -19.5;
      ladrilhos[x][y].setCentro(centro);

      posicao pos;
      pos.x = x;
      pos.y = y;
      ladrilhos[x][y].setPosicao(pos);

      float somaCores = cor[0] + cor[1] + cor[2];

      if (cor[0] == 1.0 && somaCores == 1.0) {
        ladrilhos[x][y].setEnergizer();
      }
      else if (cor[0] == 1.0 && cor[1] == 1.0 && cor[2] == 0.0) {
        // Ponto
      }
      else if (somaCores == 3.0) {
        ladrilhos[x][y].setVisitado();
      }
      else {
        ladrilhos[x][y].setVisitado();
        if (somaCores > 0.0) {
          desenhaParede(x, y, cor);
        }
        else {

        }
      }
    }
  }

  for (int x = 1; x < larguraTabuleiro; x++) {
    for (int y = 1; y < alturaTabuleiro; y++) {
      if (!ehParede(x,y)) {
        if (!ehParede(x,y-1)) {
          ladrilhos[x][y].setSaida(baixo, &ladrilhos[x][y-1]);
          ladrilhos[x][y-1].setSaida(cima, &ladrilhos[x][y]);
        }
        if (!ehParede(x-1,y)) {
          ladrilhos[x][y].setSaida(esquerda, &ladrilhos[x-1][y]);
          ladrilhos[x-1][y].setSaida(direita, &ladrilhos[x][y]);
        }
      }
    }
  }

  for (int x = 0; x < larguraTabuleiro; x++) {
    if (!ehParede(x,0) && !ehParede(x, alturaTabuleiro-1)) {
      ladrilhos[x][0].setSaida(cima, &ladrilhos[x][alturaTabuleiro-1]);
      ladrilhos[x][alturaTabuleiro-1].setSaida(baixo, &ladrilhos[x][0]);
    }
  }

  for (int y = 1; y < alturaTabuleiro; y++) {
    if (!ehParede(0,y) && !ehParede(larguraTabuleiro - 1, y)) {
      ladrilhos[0][y].setSaida(esquerda, &ladrilhos[larguraTabuleiro - 1][y]);
      ladrilhos[larguraTabuleiro - 1][y].setSaida(direita, &ladrilhos[0][y]);
    }
  }


  glEndList();
}




void Tabuleiro::desenhaParede(int x, int y, float * cor) {
  float px = (float)x-largura/2;
  float py = (float)y-altura/2;
  desenhaLinhas(cor, x, y, px, py);
}

void Tabuleiro::carrega() {


  std::vector<std::string> mapa;

  mapa.push_back("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");
  mapa.push_back("BGGGGGGGGGGGGBBGGGGGGGGGGGGB");
  mapa.push_back("BGBBBBGBBBBBGBBGBBBBBGBBBBGB");
  mapa.push_back("BRBZZBGBZZZBGBBGBZZZBGBZZBRB");
  mapa.push_back("BGBBBBGBBBBBGBBGBBBBBGBBBBGB");
  mapa.push_back("BGGGGGGGGGGGGGGGGGGGGGGGGGGB");
  mapa.push_back("BGBBBBGBBGBBBBBBBBGBBGBBBBGB");
  mapa.push_back("BGBBBBGBBGBBBBBBBBGBBGBBBBGB");
  mapa.push_back("BGGGGGGBBGGGGBBGGGGBBGBBBBBB");
  mapa.push_back("BBBBBBGBBBBBWBBWBBBBBGBBBBBB");
  mapa.push_back("ZZZZZBGBBBBBWBBWBBBBBGBZZZZZ");
  mapa.push_back("ZZZZZBGBBWWWWWWWWWWBBGBZZZZZ");
  mapa.push_back("ZZZZZBGBBWBBBWWBBBWBBGBZZZZZ");
  mapa.push_back("BBBBBBGBBWBWWWWWWBWBBGBBBBBB");
  mapa.push_back("WWWWWWGWWWBWWWWWWBWWWGWWWWWW");
  mapa.push_back("BBBBBBGBBWBWWWWWWBWBBGBBBBBB");
  mapa.push_back("ZZZZZBGBBWBBBBBBBBWBBGBZZZZZ");
  mapa.push_back("ZZZZZBGBBWWWWWWWWWWBBGBZZZZZ");
  mapa.push_back("ZZZZZBGBBWBBBBBBBBWBBGBZZZZZ");
  mapa.push_back("BBBBBBGBBWBBBBBBBBWBBGBBBBBB");
  mapa.push_back("BGGGGGGGGGGGGBBGGGGGGGGGGGGB");
  mapa.push_back("BGBBBBGBBBBBGBBGBBBBBGBBBBGB");
  mapa.push_back("BRBBBBGBBBBBGBBGBBBBBGBBBBRB");
  mapa.push_back("BGGGBBGGGGGGGGGGGGGGGGBBGGGB");
  mapa.push_back("BBBGBBGBBGBBBBBBBBGBBGBBGBBB");
  mapa.push_back("BBBGBBGBBGBBBBBBBBGBBGBBGBBB");
  mapa.push_back("BGGGGGGBBGGGGBBGGGGBBGGGGGGB");
  mapa.push_back("BGBBBBBBBBBBGBBGBBBBBBBBBBGB");
  mapa.push_back("BGBBBBBBBBBBGBBGBBBBBBBBBBGB");
  mapa.push_back("BGGGGGGGGGGGGGGGGGGGGGGGGGGB");
  mapa.push_back("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");


  tabuleiroDisplayList = glGenLists(1);

  largura = 28;
  altura = 31;

  for (int x = 0; x < largura; x++) {
    for (int y = 0; y < altura; y++) {
      char letra = mapa[y][x];

      float *cor;
      cor = new float[3];
      cor[0] = 0.0;
      cor[1] = 0.0;
      cor[2] = 0.0;

      switch (letra) {
        case 'B': cor[2] = 1.0; break;
        case 'W': cor[0] = 1.0; cor[1] = 1.0; cor[2] = 1.0; break;
        case 'R': cor[0] = 1.0; break;
        case 'G': cor[0] = 1.0; cor[1] = 1.0; break;
      }

      pixels[x][altura - (y + 1)] = cor;
    }
  }




  criaTabuleiro();

}

int Tabuleiro::getLargura() {
  return largura;
}

int Tabuleiro::getAltura() {
  return altura;
}

float * Tabuleiro::getPixel(int x, int y) {
  return pixels[x][y];
}

Ladrilho * Tabuleiro::getLadrilho(int x, int y) {
  return &ladrilhos[x][y];
}

void Tabuleiro::atualiza(float ticks, float tempo) {
  ultimosTicks = ticks;
  this->tempo = tempo;
}





void Tabuleiro::processa() {



  //glTranslatef(0,0,-0.5);
  glCallList(tabuleiroDisplayList);
  //glTranslatef(0,0,0.5);

  for (int x = 0; x < largura; x++) {
    for (int y = 0; y < altura; y++) {
      ladrilhos[x][y].atualiza(ultimosTicks, this->tempo);
      ladrilhos[x][y].processa();
    }
  }



}
