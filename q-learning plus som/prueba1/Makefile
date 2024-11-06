qllib_path=../qllib

all: ql

ql: prueba1.o ql.o
	g++ -std=gnu++11 prueba1.o ql.o -o ql

prueba1.o: prueba1.cpp
	g++ -std=gnu++11 -c prueba1.cpp

ql.o: $(qllib_path)/ql.cpp
	g++ -std=gnu++11 -c $(qllib_path)/ql.cpp

clean:
	rm -rf *o ql
