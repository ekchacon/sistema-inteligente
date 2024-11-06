///Ek Chacón

/// cd Escritorio/3er\ Semestre/Seminario\ de\ tesis\ II/somunit2updaten13x13/sinsensor/someucli/prueba/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include "../libsom/libsom.h"

using namespace std;

main ()
{						
	vector < vector < float > > clusentrenados;
	ofstream myfile;
	
	///1) Inicializar Pesos (Se hace internamente en la funcion clusters)
	///   Definir parametros de vecindario
	///	  Definir parámetro de velocidad de aprendizaje
	
	//Parametros de vecindario
	int radio = 3;
	int numclusters = 2500, longexamples = 2; 	///Número de clusters y longitud de ejemplos
	int numfilas = pow(numclusters,(1.0/2.0));
	int numcolumnas = pow(numclusters,(1.0/2.0));
		
	//Parametro de volocidad de aprendizaje
	float alpha = 0.1; //originalmente alpha = 0.6, alpha con 4 ceros el mejor
	
	//Epoca
	
	int epoca = 10;
					
	neighborhood neighborhood1(numfilas, numcolumnas, longexamples, radio);
	
	neighborhood1.inputPatterns(); ///Entrada de patrones
										///~ 1 1 0 0 
										///~ 1 0 0 0 
										///~ 0 0 0 1 
		neighborhood1.parameters(numclusters, longexamples); // Inicialización pesos									///~ 0 0 1 1 

	for(int fold = 1; fold < 7; fold++) // 6-fold Cross Validation //NECESARIAMENTE DE 1 A 7, SON 6-FOLD
		{
	
		
			
			neighborhood1.divideTestTrain(fold);
			
			for(int i = 0; i < epoca; i++) ///Numclusters es igual al numero de vectores de entrada  epoca
				{
					
					neighborhood1.training( fold, alpha, epoca, i);
					alpha = 0.5*(alpha);
							
				}
				
					///Division entre test y train----------------------
					if(fold == 6){
						clusentrenados = neighborhood1.devClusentrenados();
														//~ 
						myfile.open("clustersentranados.cpp");
						for(unsigned int i = 0; i < clusentrenados.size(); i++)
						{
							for(int j = 0; j < longexamples; j++)
								{							
									myfile << fixed << clusentrenados[i][j] << " ";
								}					
								myfile << endl;
						}
						myfile.close();
						}
					///-------------------------------------------------
					
				neighborhood1.match();
			cout << "fold: " << fold << endl;
		}
		
		neighborhood1.imprimeEficiencia();
}
