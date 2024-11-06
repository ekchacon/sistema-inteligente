#Ek Chacón

libsom_path = ../libsom

all: som

som: prueba.o som.o
	g++ prueba.o som.o -o som

prueba.o: prueba.cpp
	g++ -c prueba.cpp


som.o: $(libsom_path)/som.cpp

		g++ -c $(libsom_path)/som.cpp
clean:
	rm -rf *o som
