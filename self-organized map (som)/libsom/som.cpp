///Ek Chacón 

#include <iostream>
#include "libsom.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>    // std::random_shuffle

neighborhood::neighborhood(int _numfilas, int _numcolumnas, int _longexamples, int _radii){
	
			numFilas = _numfilas;
			numColumnas = _numcolumnas;
			longExamples = _longexamples;
			radii = _radii;
			neighboorsunits.clear();
			train.clear();
			test.clear();
			eficiencia.clear();
			
	}
	
void neighborhood::imprimeEficiencia(){
	
	float sum = 0, media;
	
		for(int i = 0; i < eficiencia.size(); i++){
				cout << "efi: " << i << " .-" << eficiencia[i] << endl;
				sum = sum + eficiencia[i];
			}
		media = (sum/float(eficiencia.size()));
		
		cout << "media efi : " << media << endl;
	}
	
void neighborhood::match(){				
		
		float sumaD = 0.0, Djmenor;
		int indiceJ, indiceI,  xTest, yTest, xClus, yClus, estadoTest, estadoClus;
		int cont = 0;
		
		for(int x = 0; x < test.size();x++)	///Recorre todas las x de entrada test.size()
			{
				for(int j = 0; j < clusters.size();j++)
					{
						for(int i = 0; i < longExamples; i++)
						{
							sumaD += pow((clusters[j][i] - test[x][i]),2);
						}																	
						
						if(j == 0)
							{
								Djmenor = sumaD;
								indiceJ = j;
							}
						
						if(Djmenor > sumaD){
								Djmenor = sumaD;
								indiceJ = j;
							}
						
						sumaD = 0.0;						
					}
						
				//~ cout << "cluster ganador: " << indiceJ << endl << endl;
				///Estado test
				xTest = test[x][0];
				yTest = test[x][1];
				
				//~ cout << "xtest " << test[x][0] << endl;
				//~ cout << "ytest " << test[x][1] << endl;
				
				estadoTest = (yTest*13 + xTest);
				//~ cout << "estadoTest: " << estadoTest << endl;
				
				///Estado clus
				xClus = clusters[indiceJ][0];
				yClus = clusters[indiceJ][1];
				
				//~ cout << "xclus " << clusters[indiceJ][0] << endl;
				//~ cout << "yclus " << clusters[indiceJ][1] << endl;
				
				estadoClus = (yClus*13 + xClus);
				//~ cout << "estadoClus: " << estadoClus << endl;
				
				if(estadoTest == estadoClus){
						cont++;
						//~ cout << "iguales " << endl;
						
					}else{
						//~ cout << "deferentes " << endl;
						}
			}
			//~ cout << "cont: " << cont << endl;
			//~ cout << "test size: " << test.size() << endl;
			cout << "efi vistPrev: " << (float(cont)/float(test.size())) << endl;
			
		 eficiencia.push_back(float(cont)/float(test.size()));
	}
	
void neighborhood::divideTestTrain(int _fold){
	
		int cont = 0; //Para crear ventanas de test
		
		test.clear();
		train.clear();
		
		for(int x = 0; x < mIn.size(); x++)	///Recorre todas las x de entrada
			{
				if(cont == 600){
						cont = 0;
					}
				
				if( (cont >= ((_fold - 1)*100)) && (cont < (_fold*100)) ){
					
						test.push_back(mIn[x]);
						
					}else{
						train.push_back(mIn[x]);
					}
				cont++;	
			}	
			
			random_shuffle ( train.begin(), train.end() );
			
			//~ cout << "sizeTest" << test.size() << endl;
			//~ cout << "sizeTrain" << train.size() << endl;
									
			//~ cout << "test" << endl;
		//~ for(unsigned int i = 100; i < 102; i++)
			//~ {
				//~ for(int j = 0; j < longExamples; j++)
					//~ {
						//~ cout << test[i][j] << " ";
					//~ }
					//~ cout << endl;
			//~ }
			//~ 
			//~ cout << "train" << endl;
		//~ for(unsigned int i = 500; i < 502; i++)
			//~ {
				//~ for(int j = 0; j < longExamples; j++)
					//~ {
						//~ cout << train[i][j] << " ";
					//~ }
					//~ cout << endl;
			//~ }			
		//~ 
	}
	
void neighborhood::inputPatterns()
	{
		srand(time(0));
		vector < float > v, v1;
		
		int x = 0;

		ifstream in("dataset.cpp");
		float valor;

		while(in >> valor)
		{
			v.push_back(valor);
			x++;
			if(x == 2)
				{
					mIn.push_back(v);
					v.clear();
					x = 0;
				}
		}
		
		//~ v = mIn[0];		
		//~ 
		//~ for(unsigned int i = 0; i < mIn.size(); i++)
		//~ {
			//~ for(int j = 0; j < v.size(); j++)
				//~ {
					//~ cout << mIn[i][j] << " ";
				//~ }
				//~ cout << endl;
		//~ }
	}

void neighborhood::parameters(int _numclusters, int _longexamples)
	{
		srand(time(0));
		vector < float > cluster, v1, v2;
		float a = -0.05;
		float b = 0.05;
		
		clusters.clear();
		
		///Inicialización de pesos
		for(unsigned int i = 0; i < _numclusters; i++)			
		{
			for(int j = 0; j < _longexamples; j++)
				{
					 cluster.push_back(((b-a)*((float)rand()/RAND_MAX) + a));   //(((double)rand()/RAND_MAX)) (((double)rand()/RAND_MAX)-0.05)
				}	
				clusters.push_back(cluster);
				cluster.clear();								
		}	
						
		//~ v1.push_back(0.2);
		//~ v1.push_back(0.6);
		//~ v1.push_back(0.5);
		//~ v1.push_back(0.9);
		//~ 
		//~ v2.push_back(0.8);
		//~ v2.push_back(0.4);
		//~ v2.push_back(0.7);
		//~ v2.push_back(0.3);
		//~ 
		//~ clusters.push_back(v1);
		//~ clusters.push_back(v2);
		
		
		//~ for(unsigned int i = 0; i < _numclusters; i++)
		//~ {
			//~ for(int j = 0; j < _longexamples; j++)
				//~ {
					//~ cout << clusters[i][j] << " ";
				//~ }
				//~ cout << endl;
		//~ }
		
	}
	
void neighborhood::training(int _fold, float _alpha, int _epoca, int _iteracion)
	{
		
		float sumaD = 0.0, Djmenor;
		int indiceJ = 0;
		
		int cont = 0; //Para crear ventanas de test
		
		for(int x = 0; x < train.size(); x++)	///Recorre todas las x de entrada train.size()
			{
																	
						for(int j = 0; j < clusters.size();j++)
							{
								for(int i = 0; i < longExamples; i++)
								{
									sumaD += pow((clusters[j][i] - train[x][i]),2);
								}																	
								
								if(j == 0)
									{
										Djmenor = sumaD;
										indiceJ = j;
									}
								
								if(Djmenor > sumaD){
										Djmenor = sumaD;
										indiceJ = j;
									}
								
								sumaD = 0.0;	
								
							}
							
						//~ cout << "Winner neuron " << indiceJ << endl;
						
						updateNeighbooringUnits(indiceJ);								
						
						//~ cout << "size neigh " << neighboorsunits.size() << endl;
						
						for(int j = 0; j < neighboorsunits.size(); j++)
							{
								for(int i = 0; i < longExamples; i++)
									{
										clusters[neighboorsunits[j]][i] = clusters[neighboorsunits[j]][i] + _alpha*((train[x][i])-(clusters[neighboorsunits[j]][i]));
									}		
							}
							neighboorsunits.clear();
				
			}	
				
		cout << "Epoca: " << _iteracion << endl;
		
		//~ if(_iteracion == (_epoca-1)){			
			//~ ///instanciacion de un archivo			
				//~ for(unsigned int i = 0; i < clusters.size(); i++)
				//~ {
					//~ for(int j = 0; j < _longexamples; j++)
						//~ {
							//~ cout << clusters[i][j] << " ";							
			//~ 
						//~ }
						//~ cout << endl;
			//~ 
				//~ }							
			//~ }					
	}
	
void neighborhood::updateNeighbooringUnits(int _unidadJ){
			
			int fila1 = 0, columna1 = 0;
			int fila2 = 0, columna2 = 0;					
						
			int unidadActual = _unidadJ, punto1, punto2;
			
			
			for(int i = 0; i < radii; i++){
					
					unidadActual = movimiento(0, movimiento(3, unidadActual));
					
				}
				
				punto1 = unidadActual;
				unidadActual = _unidadJ;
				fila1 = punto1 / numColumnas;
				//~ cout << "f1: " << fila1 << endl;
				columna1 = punto1 % numColumnas;
				//~ cout << "c1: " << columna1 << endl;
			
			for(int i = 0; i < radii; i++){
					
					unidadActual = movimiento(2, movimiento(1, unidadActual));
					
				}
				
				punto2 = unidadActual;
				fila2 = punto2 / numColumnas;
				//~ cout << "f2: " << fila2 << endl;
				columna2 = punto2 % numColumnas;
				//~ cout << "c2: " << columna2 << endl;
				
				//~ cout << "p1: " << punto1 << endl;
				//~ cout << "p2: " << punto2 << endl;
				
				for(int i = fila1; i <= fila2; i++){
						
						for(int j = columna1; j <= columna2; j++){
								
								neighboorsunits.push_back(i*numColumnas + j);
								
							}
					
					}
				//~ cout << "size neigh " << neighboorsunits.size() << endl;
				
			//~ for(int j = 0; j < neighboorsunits.size(); j++)
				//~ {
					//~ cout << neighboorsunits[j] << endl;
				//~ }							
	}

int neighborhood::movimiento(int accion, int _estadoActual)
		{
			int fila = 0, columna = 0;
			int estadoSig = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			switch(accion)
				{
					case(0): ///Arriba
						if(fila > 0)
							fila--;
						break;
					case(1):
						if(columna < (numColumnas - 1))
							columna++;
						break;
					case(2):
						if(fila < (numFilas - 1))
							fila++;
						break;
					case(3):
						if(columna > 0)
							columna--;
						break;
				}
			estadoSig = (fila * numColumnas) + columna;
			
			return estadoSig;
		
		}
		
vector < vector < float > > neighborhood::devClusentrenados(){
	
		return clusters;
	
	}

///reciclar

//~ for (int i = 1; i <= radii; i++){
					 //~ 
					 //~ unidadActual = movimiento(0, unidadActual); ///Arriba
					 //~ 
					 //~ neighboors.push_back(unidadActual);
					 //~ 
				//~ }
			//~ 
			//~ for (int i = 1; i <= radii; i++){
					 //~ 
					 //~ unidadActual = movimiento(1, unidadActual); ///derecha
					 //~ neighboors.push_back(unidadActual);
					 //~ 
				//~ }
				//~ 
			//~ for (int i = 1; i <= (2*radii); i++){
					 //~ 
					 //~ unidadActual = movimiento(2, unidadActual); ///abajo
					 //~ neighboors.push_back(unidadActual);
					 //~ 
				//~ }
			//~ 
			//~ for (int i = 1; i <= (2*radii); i++){
					 //~ 
					 //~ unidadActual = movimiento(3, unidadActual); ///izquierdo
					 //~ neighboors.push_back(unidadActual);
					 //~ 
				//~ }
				//~ 
			//~ for (int i = 1; i <= (2*radii); i++){
					 //~ 
					 //~ unidadActual = movimiento(0, unidadActual); ///Arriba
					 //~ neighboors.push_back(unidadActual);
					 //~ 
				//~ }
				//~ 
			//~ for (int i = 1; i < radii; i++){
									 //~ 
					 //~ unidadActual = movimiento(1, unidadActual); ///Arriba					 
					 //~ neighboors.push_back(unidadActual);
					 					 //~ 
				//~ }
