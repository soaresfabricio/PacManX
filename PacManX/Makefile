CXX=g++
CXXFLAGS=-Wall -Wno-unused-parameter -Wno-switch  `Magick++-config --cppflags --cxxflags --ldflags --libs` -framework OpenGL -framework GLUT

all: main

main: main.cpp jogador.o tabuleiro.o game.o ladrilho.o
		$(CXX) $(CXXFLAGS) main.cpp jogador.o tabuleiro.o game.o ladrilho.o -o PacManX
		
jogador.o: jogador.cpp
		$(CXX) $(CXXFLAGS) -c jogador.cpp
		
game.o: game.cpp 
		$(CXX) $(CXXFLAGS) -c game.cpp
				
tabuleiro.o: tabuleiro.cpp
		$(CXX) $(CXXFLAGS) -c tabuleiro.cpp
				
ladrilho.o: ladrilho.cpp
		$(CXX) $(CXXFLAGS) -c ladrilho.cpp


clean:
		rm *.o PacManX
