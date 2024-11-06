//Ek Chacon
/// link del algoritmo iterative policy evaluation
///http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node41.html

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "ql.h"
#include <random>
#include <chrono>

using namespace std;

agente::agente(int _numFilas, int _numColumnas, int _numAcciones, int _numOptions){
			vector < float > valorOptionPorEstado;
			
			///* initialize random seed: */
			//~ srand (time(NULL));
			
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			// uniform_real_distribution
			default_random_engine generator (seed);
			uniform_real_distribution<double> distribution(0.0,1.0);
			//~ distribution(generator)
								
			numFilas = _numFilas;
			numColumnas = _numColumnas;
			numEstados = (_numFilas * _numColumnas);
			numAcciones = _numAcciones;
			numOptions = _numOptions;
			
			float a = -0.05;
			float b = 0.05;
			
			//~ distribution(generator)
			
			for(int i = 0; i < numEstados; i++)
				{
					if(i == noEstado(i)){
						for(int j = 0; j < numOptions; j++)
						{
							valorOptionPorEstado.push_back(0.0);
						}
						
						Qso.push_back(valorOptionPorEstado);
						
					}else{
						for(int j = 0; j < numOptions; j++)
						{
							valorOptionPorEstado.push_back(((b-a)*(distribution(generator)) + a));
							//~ valorOptionPorEstado.push_back(0.0);
						}
						
						Qso.push_back(valorOptionPorEstado);
					}
					valorOptionPorEstado.clear();
				}
			
			option("I0.cpp","option0.cpp","beta0.cpp");
			option("I1.cpp","option1.cpp","beta1.cpp");
			option("I2.cpp","option2.cpp","beta2.cpp");
			option("I3.cpp","option3.cpp","beta3.cpp");
			option("I4.cpp","option4.cpp","beta4.cpp");
			option("I5.cpp","option5.cpp","beta5.cpp");
			option("I6.cpp","option6.cpp","beta6.cpp");
			option("I7.cpp","option7.cpp","beta7.cpp");
			
			tablaProbabilidades("tabprob.cpp");
			
		}

int agente::devolverContExploracion(){
				return contExploracion;
			}
			
void agente::obtenerContExploracion(){
				 contExploracion = 0;
			}

int agente::stateAround(int accion, int _estadoActual){
			int fila = 0, columna = 0, auxfila = 0, auxcolumna = 0;
			int estadoSigReal = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			switch(accion)
				{
					case(0):
						if(fila > 0){
							if(columna > 0){
								fila--;
								columna--;
							}
						}
						break;
						
					case(1):
						if(fila > 0)
							fila--;
						break;
						
					case(2):
						if(fila > 0){
							if(columna < (numColumnas - 1)){
								fila--;
								columna++;
							}
						}
						break;
						
					case(3): 
						if(columna < (numColumnas - 1))
							columna++;
						break;
						
					case(4): 
						if(fila < (numFilas - 1)){
							if(columna < (numColumnas - 1)){
								fila++;
								columna++;
							}
						}
						break;
						
					case(5):
						if(fila < (numFilas - 1))
							fila++;
						break;
						
					case(6): 
						if(fila < (numFilas - 1)){
							if(columna > 0){
								fila++;
								columna--;
							}
						}
						break;
						
					case(7):
						if(columna > 0)
							columna--;
						break;
				}
				
			estadoSigReal = (fila * numColumnas) + columna;	
			
			return estadoSigReal;
				
		}
		
int agente::deNoEstadoToEstado(int _estadoSigDeSOM, int _optionsElegida, int _estadoActual){
	
		vector < int > statesAround;
		
		statesAround.clear();
		
		int auxEstadoSig = 0, auxAccion = 0;
	
		//Barrer todas las acciones alrededor
		for(int accion = 0; accion < 8; accion++){
				
				statesAround.push_back(stateAround(accion, _estadoSigDeSOM));
			
			}
		//~ cout << "statesAround: " << statesAround.size() << endl;
		//~ 
		//~ for(int i=0; i < statesAround.size(); i++)
			//~ {		
				//~ cout << statesAround[i] << " ";		
			//~ }
		
		for(int i = 0; i < statesAround.size(); i++){
			
				if(options[_optionsElegida].I[_estadoActual] = options[_optionsElegida].I[statesAround[i]]){
					
						auxEstadoSig = statesAround[i];
						auxAccion = i;
					}
			
			}
			accion8 = auxAccion;
		
		return auxEstadoSig;
	
	}
	
int agente::DevAccionDeNoestadoToEsatdo(){
	
		return accion8;
	
	}
	
		
int agente::sigueOTerminaOptionElegida(int _estadoSigDeSOM, int _optionElegida){
	
		int auxBeta;
	
		auxBeta = options[_optionElegida].beta[_estadoSigDeSOM];
		
		return auxBeta;
	
	}
		
void agente::actualizarQso( float _alfa, float _recompensa, float _gamma, int _estadoSiguiente, int _estadoActual, int _optionElegida, int _accionElegida){
		
		vector < int > optionsEnEstado;	///Las options disponibles en _estado
		
		Qso[_estadoActual][_optionElegida] = Qso[_estadoActual][_optionElegida] + _alfa * ( _recompensa + _gamma*( U(_estadoSiguiente, _optionElegida) ) - Qso[_estadoActual][_optionElegida] );
		
		for(int option = 0; option < numOptions; option++){
				
				if(options[option].I[_estadoActual] == 1){
						optionsEnEstado.push_back(option);
					}
			}
			
		for(int Option = 0; Option < optionsEnEstado.size(); Option++ ){
				
				if(optionsEnEstado[Option] != _optionElegida){
						///Comprobar consistencia de accion elegida con todas las options disponibles en el estado
						//~ cout << "accion de consistencia" << elegirAccionEnPoliticaOption(optionsEnEstado[Option], _estadoActual) << endl;
						if(elegirAccionEnPoliticaOption(optionsEnEstado[Option], _estadoActual) == _accionElegida){
							
							Qso[_estadoActual][optionsEnEstado[Option]] = Qso[_estadoActual][optionsEnEstado[Option]] + _alfa * ( _recompensa + _gamma*( U(_estadoSiguiente, optionsEnEstado[Option]) ) - Qso[_estadoActual][optionsEnEstado[Option]] );
						}
					}
					
			}
		
	}
	
void agente::observarRecompensaYEstadoSig(int accion, int _estadoActual, int _optionActual)
		{
			recompensaf(_estadoActual,accion, _optionActual);
		}
	
int agente::elegirAccionEnPoliticaOption(int _optionActual, int _estadoActual){
		float accionMax;
		int auxAccionMax;
	
		for(int accion = 0; accion < numAcciones; accion++ )
			{
				
				if(accion == 0){
						accionMax = options[_optionActual].pi[_estadoActual][accion];
						auxAccionMax = accion;
					}else{
						if(accionMax < options[_optionActual].pi[_estadoActual][accion]){
							
								accionMax = options[_optionActual].pi[_estadoActual][accion];
								auxAccionMax = accion;
							}
					}
					
			}
			
			return auxAccionMax;
	}
	
float agente::U(int _estado, int _optionElegida){
		float valorU;
		
	
		valorU = (1.0 - (options[_optionElegida].beta[_estado]))*(Qso[_estado][_optionElegida]) + (options[_optionElegida].beta[_estado])*(Qso[_estado][explotarOption(_estado)]);
		//~ cout << "mejor option de est sig: " << explotarOption(_estado) << endl;
		return valorU;
	}
		
void agente::observarRecompensaYEstadoSigOption(int _option, int _estadoActual){
			//~ cout << "option: " << _option << endl;
			rO_sOption( _estadoActual, _option);		
	}
	
void agente::rO_sOption(int _estadoActual, int _optionActual){
		
		float recompensa = 0.0;
		
		int accion, estadoActual, k = 0;
		
		if(options[_optionActual].I[_estadoActual] == 1){
			recomEstadoSig = _estadoActual;
			
			do{
				estadoActual = recomEstadoSig;
				
				accion = elegirAccionCorrectaONC(estadoActual, _optionActual);
			
				recompensaf(estadoActual, accion, _optionActual);
				
				k++;
				
				recompensa = recompensa + recomRecompensa * pow(0.9,(k-1)); ///Gamma = 0.9
			}while(options[_optionActual].beta[recomEstadoSig] == 0); ///si la prob de terminacion de option es cero entonces Continua. 
			
			optionRecompensa = recompensa;
			optionEstadoSig = recomEstadoSig;
			k_steps = k;
		}else{
			optionRecompensa = recompensa;
			optionEstadoSig = _estadoActual;
			k_steps = k;
		}
		//~ cout << "hey" << endl;
	}
	
float agente::devolverRecompensa()
	{
		return recomRecompensa;
	}
	
int agente::devolverEstadoSiguiente()
	{
		return recomEstadoSig;
	}
	
int agente::devolverK_Steps(){
		return k_steps;
	}
	
void agente::rA_sAUH(int _estadoActual, int accion){

			float recompensa;

			int fila = 0, columna = 0, auxfila = 0, auxcolumna = 0;
			int estadoSigReal = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			auxfila = _estadoActual / numColumnas;
			auxcolumna = _estadoActual % numColumnas;
			
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
				
			estadoSigReal = (fila * numColumnas) + columna;
			
			if(estadoSigReal == noEstado(estadoSigReal)){
					estadoSigReal = (auxfila * numColumnas) + auxcolumna;
				}
			
			if(estadoSigReal == 100)
				{
					optionRecompensa = 1.0;
					optionEstadoSig = estadoSigReal;
				}
				
			else{
					optionRecompensa = 0.0;
					optionEstadoSig = estadoSigReal;
				}
}
		
int agente::elegirOptionEnEstadoUsandoGreedy(float _egreedy, int _estado){			
	
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			// uniform_real_distribution
			default_random_engine generator (seed);
			uniform_real_distribution<double> distribution(0.0,1.0);
			
		if( distribution(generator) > _egreedy)
			{
				 //~ cout << "explotar" << endl;
				return  explotarOption(_estado);
			}
		else
			{
				 //~ cout << "explorar" << endl;
				 contExploracion++;
				 return  explorarOption(_estado);
			}
			
	}
	
int agente::explotarOption(int _estado){
		float OptionMax;
		int argOptionMax;
		vector < int > optionsEnEstado;	///Las options disponibles en _estado
		
		for(int option = 0; option < numOptions; option++){
				
				if(options[option].I[_estado] == 1){
						optionsEnEstado.push_back(option);
					}
			}
	
		
		for(int mejorOption = 0; mejorOption < optionsEnEstado.size(); mejorOption++ ){
				
				if(mejorOption == 0){
						OptionMax = Qso[_estado][optionsEnEstado[mejorOption]];
						argOptionMax = optionsEnEstado[mejorOption];
					}else{
						if(OptionMax < Qso[_estado][optionsEnEstado[mejorOption]]){
							
								OptionMax = Qso[_estado][optionsEnEstado[mejorOption]];
								argOptionMax = optionsEnEstado[mejorOption];
							}
					}
					
			}
		//~ cout << "AUH: " << argOptionMax << endl;
		return argOptionMax;
	}
	
int agente::explorarOption(int _estado){
		
		int pos;
		int randOption;
		vector < int > optionsEnEstado;	///Las options disponibles en _estado
		
		for(int option = 0; option < numOptions; option++){
				
				if(options[option].I[_estado] == 1){
						optionsEnEstado.push_back(option);
					}
			}
			
		//~ for(int i = 0; i < optionsEnEstado.size(); i++)
		//~ {
			//~ cout << "optionsEnEstado: " << optionsEnEstado[i] << endl;
		//~ }
		
		pos = rand() % optionsEnEstado.size();
		randOption = optionsEnEstado[pos];
		optionsEnEstado.clear();
		//~ cout << "randOption: " << randOption << endl;
		return randOption;
		
	}
		
void agente::tablaProbabilidades(const char * _tabprob){
		
		vector <float> v;
		int x = 0;
		
		ifstream inTabprob(_tabprob);
		
		float valor;
		
		while((inTabprob >> valor))
		{
			///option
			v.push_back(valor);
			x++;
			if(x == 8)
				{
					tabProb.push_back(v);
					v.clear();
					x = 0;
				}
		}
		
	}
		
void agente::actualizarVk(int _estadoActual){
		///Options///
		float auxMaxOption = 0.0, maxOption = 0.0;
		int auxArgMaxOption = 0, argMaxOption = 0, cont = 0;
		
		
		for(int optionActual = 0; optionActual < numOptions; optionActual++)///Recorre todas las options
		{
			if ( (options[optionActual].I[_estadoActual] == 1) ) /// la option o(optionActual) es valida en s(estadoActual); || (options[optionActual].beta[_estadoActual] == 1)
			{
				maxOption = rO_s(_estadoActual, optionActual) + sumatoriaEstadosSiguientes(_estadoActual, optionActual);
				argMaxOption = optionActual;
				if (cont == 0){
					
					auxMaxOption = maxOption;
					auxArgMaxOption = argMaxOption;
				}else{
					
						if(auxMaxOption < maxOption){
								
								auxMaxOption = maxOption;
								auxArgMaxOption = argMaxOption;
							}
						
					}
			}
			cont++;
		}
		
		///Acciones///
		float auxMaxAccion, maxAccion;
		int auxArgMaxAccion, argMaxAccion;
		
		auxMaxAccion = auxMaxOption;		///Para facilitar la prog se asigna de una vez el valor de option a la variable accion;
		auxArgMaxAccion = auxArgMaxOption;
		
		
		for(int accionActual = 0 ; accionActual < numAcciones; accionActual++)
		{
			maxAccion = rA_s(_estadoActual, accionActual) + sumatoriaEstadosSiguientesAccion(_estadoActual, accionActual);
			argMaxAccion = accionActual;
			
			if(auxMaxAccion < maxAccion){
								
				auxMaxAccion = maxAccion;
				auxArgMaxAccion = argMaxAccion;
			}
		}

		Vk[_estadoActual] = auxMaxAccion;
	}

float agente::sumatoriaEstadosSiguientesAccion(int _estadoActual, int accionActual){
		
		float sumatoriaEstadosSig = 0.0;
		
		for(int estadoSig = 0; estadoSig < numEstados; estadoSig++)
			{
				if(estadoSig == noEstado(estadoSig))
					continue;
				else
					sumatoriaEstadosSig = sumatoriaEstadosSig + pA_sSig(_estadoActual, accionActual, estadoSig) * (Vk_1[estadoSig]);
			}
		return sumatoriaEstadosSig;
	}

float agente::pA_sSig(int _estadoActual, int accion, int estadoSig){
			
			float probabilidad;

			int fila = 0, columna = 0, auxfila = 0, auxcolumna = 0;
			int estadoSigReal = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			auxfila = _estadoActual / numColumnas;
			auxcolumna = _estadoActual % numColumnas;
			
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
				
			estadoSigReal = (fila * numColumnas) + columna;
			
			if(estadoSigReal == noEstado(estadoSigReal)){
					estadoSigReal = (auxfila * numColumnas) + auxcolumna;
				}
			
			if(estadoSigReal == estadoSig)
				{
					probabilidad = 1.0;
				}
				
			else{
					probabilidad = 0.0;
				}
		
		return probabilidad;
	}

float agente::rA_s(int _estadoActual, int accion){

			float recompensa;

			int fila = 0, columna = 0, auxfila = 0, auxcolumna = 0;
			int estadoSigReal = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			auxfila = _estadoActual / numColumnas;
			auxcolumna = _estadoActual % numColumnas;
			
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
				
			estadoSigReal = (fila * numColumnas) + columna;
			
			if(estadoSigReal == noEstado(estadoSigReal)){
					estadoSigReal = (auxfila * numColumnas) + auxcolumna;
				}
			
			if(estadoSigReal == 126)
				{
					recompensa = 1.0;
				}
				
			else{
					recompensa = 0.0;
				}
		return recompensa;
}
	
float agente::rO_s(int _estadoActual, int _optionActual){
		
		float recompensa = 0.0;
		
		int accion, estadoActual, k = 0;
		
		recomEstadoSig = _estadoActual;
		
		do{
			estadoActual = recomEstadoSig;
			
			accion = elegirAccionCorrectaONC(estadoActual, _optionActual);
		
			recompensaf(estadoActual, accion, _optionActual);
			
			k++;
			
			recompensa = recompensa + recomRecompensa * pow(0.9,(k-1)); ///Gamma = 0.9
		}while(options[_optionActual].beta[recomEstadoSig] == 0); ///si la prob de terminacion de option es cero entonces Continua. 
		
		return recompensa;
		
	}

float agente::sumatoriaEstadosSiguientes(int _estadoActual, int _optionActual){
		
		float sumatoriaEstadosSig = 0.0;
		
		for(int estadoSig = 0; estadoSig < numEstados; estadoSig++)
			{
				if(estadoSig == noEstado(estadoSig))
					continue;
				else if (options[_optionActual].I[estadoSig] == 0){
						if (options[_optionActual].beta[estadoSig] == 1)
							sumatoriaEstadosSig = sumatoriaEstadosSig + pO_sSig(_estadoActual,_optionActual,estadoSig) * (Vk_1[estadoSig]);
						else
							continue;
					}
				else 
					sumatoriaEstadosSig = sumatoriaEstadosSig + pO_sSig(_estadoActual,_optionActual,estadoSig) * (Vk_1[estadoSig]);
			}
			
		
		return sumatoriaEstadosSig;
	}		
	
float agente::pO_sSig(int _estadoActual, int _optionActual,int _estadoSig){
		float probTerminacionOption;
		
		if(options[_optionActual].beta[_estadoSig] == 1)
			probTerminacionOption = tabProb[_estadoActual][_optionActual];
		else
			probTerminacionOption = 0.0;
		
		return probTerminacionOption;
	}
	
void agente::recompensaf(int _estadoActual, int accion, int _optionActual){
			int fila = 0, columna = 0, auxfila = 0, auxcolumna = 0;
			int estadoSigReal = 0;
			
			fila = _estadoActual / numColumnas;
			columna = _estadoActual % numColumnas;
			
			auxfila = _estadoActual / numColumnas;
			auxcolumna = _estadoActual % numColumnas;
			
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
				
			estadoSigReal = (fila * numColumnas) + columna;
			
			if(estadoSigReal == noEstado(estadoSigReal)){
					estadoSigReal = (auxfila * numColumnas) + auxcolumna;
				}
			
			if(estadoSigReal == 100)
				{
					recomRecompensa = 1.0;
					recomEstadoSig = estadoSigReal;
				}
				
			else{
					recomRecompensa = 0.0;
					recomEstadoSig = estadoSigReal;
				}
				
		}
		
void agente::option(const char * _I, const char * _op, const char * _beta){
		
		vector <float> v;
		int x = 0;
		
		ifstream inOp(_op);
		ifstream inI(_I);
		ifstream inBeta(_beta);
		
		float valorx;
		float valory;
		float valorz;
		
		while((inI >> valory ))
		{
			///Conjunto de estados iniciales
			
			auxOption.I.push_back(valory);
		}

		while((inOp >> valorx))
		{
			///option
			v.push_back(valorx);
			x++;
			if(x == 4)
				{
					auxOption.pi.push_back(v);
					v.clear();
					x = 0;
				}				
		}
		
		while((inBeta >> valorz ))
		{
			///Conjunto de estados iniciales
			
			auxOption.beta.push_back(valorz);
		}
		
		options.push_back(auxOption);
		
		auxOption.I.clear();
		auxOption.pi.clear();
		auxOption.beta.clear();
	}
	
void agente::imprimirQso(){
	
			cout << endl <<  "Valores Qso" << endl;
			
			for(int i=0; i < Qso.size(); i++)
			{
				cout << endl << i << " : \t";
				
				for(int j=0; j < numOptions; j++)
				{
					cout << Qso[i][j] << " ";
				}
			}
			cout << endl;
		}
		
void agente::imprimirOptionPi(int _posOption){
	
			cout << endl <<  "Valores pi" << endl;
			
			for(int i=0; i < options[_posOption].pi.size(); i++)
			{
				cout << endl << i << " : \t";
				
				for(int j=0; j < numAcciones; j++)
				{
					cout << options[_posOption].pi[i][j] << " ";
				}
			}
			cout << endl;
		}
		
void agente::imprimirTabProb(){
	
			cout << endl <<  "Valores pi" << endl;
			
			for(int i=0; i < tabProb.size(); i++)
			{
				cout << endl << i << " : \t";
				
				for(int j=0; j < numOptions; j++)
				{
					cout << tabProb[i][j] << " ";
				}
			}
			cout << endl;
		}

void agente::imprimirOptionI(int _posOption){
			
			cout << endl <<  "Conjunto de estados iniciales" << endl;
			int columna = 0;
			for(int i=0; i < options[_posOption].I.size(); i++)
			{
					if(columna == 13){
							cout << endl;
							columna = 0;
						}
					cout << options[_posOption].I[i] << "\t";
					columna++;
			}
			cout << endl;
		}
		
void agente::imprimirOptionBeta(int _posOption){
			
			cout << endl <<  "Condicion de terminacion beta" << endl;
			int columna = 0;
			for(int i=0; i < options[_posOption].beta.size(); i++)
			{
					if(columna == 13){
							cout << endl;
							columna = 0;
						}
				//~ cout << endl << i << " : \t";
					cout << options[_posOption].beta[i] << "\t";
					columna++;
			}
			cout << endl;
		}
		
void agente::imprimirV(){
			
			//~ cout << endl <<  "Imprimir V de robot" << endl;
			int columna = 0;
			for(int i=0; i < Vk_1.size(); i++)
			{
					if(columna == 13){
							cout << endl;
							columna = 0;
						}
					cout << Vk_1[i] << "\t";
					columna++;
			}
			cout << endl;
		}
	
int agente::elegirAccionCorrectaONC( int _estadoActual, int _optionActual){
		
		int auxAccion, mejorAccion;
		
		
		if( ((float)rand()/RAND_MAX) < (2.0/3.0) )
			{
				/// cout << "explotar" << endl;
				probProb = (2.0/3.0);
				
				return  explotar(_estadoActual, _optionActual);
			}
		else
			{
				 /// cout << "explorar" << endl;
				mejorAccion = explotar(_estadoActual, _optionActual);
				
				do{
					
					
					auxAccion = explorar(_estadoActual);
				
				}while(auxAccion == mejorAccion);
				
				probProb = (1.0/9.0);
				return auxAccion;
			}					
	}
		
int agente::explotar(int _estadoActual, int _optionActual){
		float accionMax;
		int auxAccionMax;
	
		for(int accion = 0; accion < numAcciones; accion++ )
			{
				
				if(accion == 0){
						accionMax = options[_optionActual].pi[_estadoActual][accion];
						auxAccionMax = accion;
					}else{
						if(accionMax < options[_optionActual].pi[_estadoActual][accion]){
							
								accionMax = options[_optionActual].pi[_estadoActual][accion];
								auxAccionMax = accion;
							}
					}
					
			}
			
			return auxAccionMax; ///Devuelve la mejor accion en pi de option
	}
	
int agente::explorar(int _estado){
		
		return rand() % numAcciones;
		
	}

	
//~ float agente::maxAccionQsa(int _estadoSiguiente){
		//~ float accionMax;
		//~ int auxAccionMax;
	//~ 
		//~ for(int accion = 0; accion < numAcciones; accion++ )
			//~ {
				//~ 
				//~ if(accion == 0){
						//~ accionMax = Qsa[_estadoSiguiente][accion];
						//~ auxAccionMax = accion;
					//~ }else{
						//~ if(accionMax < Qsa[_estadoSiguiente][accion]){
							//~ 
								//~ accionMax = Qsa[_estadoSiguiente][accion];
								//~ auxAccionMax = accion;
							//~ }
					//~ }
					//~ 
			//~ }
			//~ 
			//~ return accionMax;
	//~ }
	
void agente::obtenerVectorFuncionValorEstado( vector < float > _v)
	{
		Vk_1 = _v;
		Vk = _v;
	}
	
vector < float > agente::devolverVectorFuntionValorEstado()
	{
		return Vk;
	}
	
int agente::noEstado(int _estado){
		
		if( (0 <= _estado) && (_estado <= 12 ) )
			return _estado;
		if( (156 <= _estado) && (_estado <= 168 ) )
			return _estado;
		if( (_estado % 13) == 0 )
			return _estado;
		if( (_estado % 13) == 12 )
			return _estado;
		if( (_estado % 13) == 6 )
			{
				if((_estado == 45)||_estado == 136)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
		if( (79 <= _estado) && (_estado <= 83 ) )
			{
				if(_estado == 80)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
		if( (98 <= _estado) && (_estado <= 102 ) )
			{
				if(_estado == 100)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
	}


ambiente::ambiente(int _numfilas, int _numcolumnas, int _numAcciones)
	{
		
		///* initialize random seed: */
		//~ srand (time(NULL));
		
		numEstados = _numfilas * _numcolumnas;
		numAcciones = _numAcciones;
		numFilas = _numfilas;
		numColumnas = _numcolumnas;
		
		for(int i = 0; i < numEstados; i++)
				{
					if(i == noEstado(i))
						v.push_back(7.0);
					else
						if(i == 126)
							v.push_back(1.0);
						else
							v.push_back(0.0);
				}			
	}
	
vector < float > ambiente::recibirAccion(vector < float > _puntoXy, int _accionElegida){
			
		vector < float > posicionReal;	
		
		float x, y, xDecimal, yDecimal, a, b, c, fila, columna;
	
		x = _puntoXy[0];
		y = _puntoXy[1];
		
		xDecimal = x-(long)x;
		yDecimal = y-(long)y;
		
		//~ cout << "x: " << x << endl;
		//~ cout << "y: " << y << endl;
		
		//~ cout << "xDecimal: " << xDecimal << endl;
		//~ cout << "yDecimal: " << yDecimal << endl;
		
				
					int filaA = _puntoXy[1], columnaA = _puntoXy[0];
					
					switch(_accionElegida)
						{
							case(0): ///Arriba
								if(filaA > 0){
									
										//valor de a
										if(xDecimal < 0.5){
											
												a = 0.5 - xDecimal;
												x = x + a;
											
											}else{
											
												a = xDecimal - 0.5;
												x = x - a;
											}
											
										b = yDecimal + 0.5;
										
										y = y - b;
									
									}
									
								break;
							case(1):
								if(columnaA < (numColumnas - 1)){
									
										if(yDecimal < 0.5){
											
												a = 0.5 - yDecimal;
												y = y + a;
											
											}else{
												
												a = yDecimal - 0.5;
												
												y = y - a;
												
											}
											
											b = (1.0 - xDecimal) + 0.5;
											
											x = x + b;
									
									}
									
								break;
							case(2):
								if(filaA < (numFilas - 1)){
									
										//valor de a
										if(xDecimal < 0.5){
											
												a = 0.5 - xDecimal;
												x = x + a;
											
											}else{
											
												a = xDecimal - 0.5;
												x = x - a;
											}
											
										b = (1.0 - yDecimal) + 0.5;
										
										y = y + b;
									
									}									
								break;
							case(3):
								if(columnaA > 0){
									
										if(yDecimal < 0.5){
											
												a = 0.5 - yDecimal;
												
												y = y + a;
											
											}else{
													
												a = yDecimal - 0.5;
												
												y = y -a;
											}
											
											b = xDecimal + 0.5;
											
											x = x - b;
									
									}
									
								break;
						}
					
		c = pow(( pow(a,2.0) + pow(b,2.0) ),0.5);
		
		//~ cout << "Distancia s a s': " << c << endl;
					
		//~ cout << "x: " << x << endl;
		//~ cout << "y: " << y << endl;
		//Empieza en estado 14
	
		posicionReal.push_back(x);
		posicionReal.push_back(y);
		
		return posicionReal;
	
	}
	
vector < float > ambiente::devolverPosicionReal(){
	
		float x = 1.5, y = 1.5;
		
		vector < float > posicion;
		
		posicion.push_back(x);
		posicion.push_back(y);
		
		return posicion;
	
	}
	
void ambiente::observarRecompensa(vector < float > _puntoXy){
	
		int x,y, estado;
	
		x = _puntoXy[0];
		y = _puntoXy[1];
		
		estado = (y*13 + x);
		
		//~ cout << "estado: " << estado << endl;
	
		if(estado == 100)
				{
					recompensa = 1.0;
					estadoSiguiente = estado;
					
				}else{
					recompensa = 0.0;					
					estadoSiguiente = estado;
				}
	
	}
	
float ambiente::devolverRecompensa()
	{
		return recompensa;
	}

int ambiente::devolverEstadoSiguiente()
	{
		return estadoSiguiente;
	}


void ambiente::imprimirV(){
			
			//~ cout << endl <<  "Imprimir V" << endl;
			int columna = 0;
			for(int i=0; i < v.size(); i++)
			{
					if(columna == 13){
							cout << endl;
							columna = 0;
						}					
						printf("%2.2f",v[i]); cout << "\t";
					columna++;
			}
			cout << endl;
		}

int ambiente::noEstado(int _estado){
		
		if( (0 <= _estado) && (_estado <= 12 ) )
			return _estado;
		if( (156 <= _estado) && (_estado <= 168 ) )
			return _estado;
		if( (_estado % 13) == 0 )
			return _estado;
		if( (_estado % 13) == 12 )
			return _estado;
		if( (_estado % 13) == 6 )
			{
				if((_estado == 45)||_estado == 136)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
		if( (79 <= _estado) && (_estado <= 83 ) )
			{
				if(_estado == 80)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
		if( (98 <= _estado) && (_estado <= 102 ) )
			{
				if(_estado == 100)
					{
						_estado++;
						return _estado;
					}
				else
					return _estado;
			}
	}
	
vector < float > ambiente::devolverVectorFuntionValorEstado()
	{
		return v;
	}
	
void ambiente::obtenerVectorFuncionValorEstado( vector < float > _v)
	{
		v = _v;
	}

transductor::transductor(int _numfilas, int _numcolumnas){

			//~ srand (time(NULL));
				
			numFilas = _numfilas;
			numColumnas = _numcolumnas;
			output.clear();
		
		}
	
vector < vector < float > >  transductor::tamanoPasoBasadoEnpuntoXy( vector < float > _puntoXy, int _accionElegida){
		
		vector < vector < float > >  Mejemplos;
		vector < float > Vejemplos;	
		
		float x, y, xDecimal, yDecimal, a, b, c, fila, columna;
	
		x = _puntoXy[0];
		y = _puntoXy[1];
		
		xDecimal = x-(long)x;
		yDecimal = y-(long)y;
		
		//~ cout << "x: " << x << endl;
		//~ cout << "y: " << y << endl;
		
		//~ cout << "xDecimal: " << xDecimal << endl;
		//~ cout << "yDecimal: " << yDecimal << endl;
		
				
					int filaA = _puntoXy[1], columnaA = _puntoXy[0];
					
					switch(_accionElegida)
						{
							case(0): ///Arriba
								if(filaA > 0){
									
										//valor de a
										if(xDecimal < 0.5){
											
												a = 0.5 - xDecimal;
												x = x + a;
											
											}else{
											
												a = xDecimal - 0.5;
												x = x - a;
											}
											
										b = yDecimal + 0.5;
										
										y = y - b;
									
									}
									
								break;
							case(1):
								if(columnaA < (numColumnas - 1)){
									
										if(yDecimal < 0.5){
											
												a = 0.5 - yDecimal;
												y = y + a;
											
											}else{
												
												a = yDecimal - 0.5;
												
												y = y - a;
												
											}
											
											b = (1.0 - xDecimal) + 0.5;
											
											x = x + b;
									
									}
									
								break;
							case(2):
								if(filaA < (numFilas - 1)){
									
										//valor de a
										if(xDecimal < 0.5){
											
												a = 0.5 - xDecimal;
												x = x + a;
											
											}else{
											
												a = xDecimal - 0.5;
												x = x - a;
											}
											
										b = (1.0 - yDecimal) + 0.5;
										
										y = y + b;
									
									}									
								break;
							case(3):
								if(columnaA > 0){
									
										if(yDecimal < 0.5){
											
												a = 0.5 - yDecimal;
												
												y = y + a;
											
											}else{
													
												a = yDecimal - 0.5;
												
												y = y -a;
											}
											
											b = xDecimal + 0.5;
											
											x = x - b;
									
									}
									
								break;
						}
					
		c = pow(( pow(a,2.0) + pow(b,2.0) ),0.5);
		
		//~ cout << "Distancia s a s': " << c << endl;
					
		//~ cout << "x: " << x << endl;
		//~ cout << "y: " << y << endl;
		//Empieza en estado 14
	fila = y;			///initialization
	columna = x;		///initialization
	
	//Empieza en estado 100
	//~ float	fila = 7.5;			///initialization
	//~ float	columna = 9.5;		///initialization
	
	Mejemplos.clear();
	Vejemplos.clear();
	
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();	
	default_random_engine generator (seed);
	
	
	normal_distribution < float > sx1(columna,0.1413859965), sy1(fila,0.1413859965);
	normal_distribution < float > sx2(columna,0.0706929982), sy2(fila,0.0706929982);
	normal_distribution < float > sx3(columna,0.0353464991), sy3(fila,0.0353464991);
	
	//~ cout << "sx1 " << sx1(generator) << " sy1 " << sy1(generator) << endl;
	//~ cout << "sx2 " << sx2(generator) << " sy2 " << sy2(generator) << endl;
	//~ cout << "sx3 " << sx3(generator) << " sy3 " << sy3(generator) << endl;
	//~ return miu(generator);
	for(int i = 0; i < 1; i++){
		
			Vejemplos.push_back(sx1(generator));
			Vejemplos.push_back(sy1(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
			//~ 
			Vejemplos.push_back(sx2(generator));
			Vejemplos.push_back(sy2(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
			
			Vejemplos.push_back(sx3(generator));
			Vejemplos.push_back(sy3(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
		}
	
	//~ for(unsigned int i = 0; i < Mejemplos.size(); i++)
		//~ {
			//~ for(int j = 0; j < 2; j++)
				//~ {
					 //~ cout << Mejemplos[i][j] << " ";
				//~ }	
				//~ cout << endl;
		//~ }
		
		return Mejemplos;			
	}
	
vector < vector < float > >  transductor::output3DNSensor(vector < float > _posicionReal){
	
	//Empieza en estado 14
	float	columna = _posicionReal[0];			///initialization
	float	fila = _posicionReal[1];		///initialization
	
	//Empieza en estado 100
	//~ float	fila = 7.5;			///initialization
	//~ float	columna = 9.5;		///initialization
	
	vector < vector < float > > Mejemplos;
	vector < float > Vejemplos;
	
	Mejemplos.clear();
	Vejemplos.clear();
		
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();	
	default_random_engine generator (seed);
	
	
	normal_distribution < float > sx1(columna,0.0), sy1(fila,0.0);
	normal_distribution < float > sx2(columna,0.0), sy2(fila,0.0);
	normal_distribution < float > sx3(columna,0.0), sy3(fila,0.0);
	
	//~ cout << "sx1 " << sx1(generator) << " sy1 " << sy1(generator) << endl;
	//~ cout << "sx2 " << sx2(generator) << " sy2 " << sy2(generator) << endl;
	//~ cout << "sx3 " << sx3(generator) << " sy3 " << sy3(generator) << endl;
	//~ return miu(generator);
	for(int i = 0; i < 1; i++){
		
			Vejemplos.push_back(sx1(generator));
			Vejemplos.push_back(sy1(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
			//~ 
			Vejemplos.push_back(sx2(generator));
			Vejemplos.push_back(sy2(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
			
			Vejemplos.push_back(sx3(generator));
			Vejemplos.push_back(sy3(generator));
			
			Mejemplos.push_back(Vejemplos);
			Vejemplos.clear();
		}
	
	//~ for(unsigned int i = 0; i < Mejemplos.size(); i++)
		//~ {
			//~ for(int j = 0; j < 2; j++)
				//~ {
					 //~ cout << Mejemplos[i][j] << " ";
				//~ }	
				//~ cout << endl;
		//~ }
		
		return Mejemplos;
	
}

Som::Som(int _numclusters, int _longexamples)
	{
		//~ srand(time(0));
		vector < float > cluster;
		longExamples = _longexamples;
		///Inicialización de pesos
		//~ for(unsigned int i = 0; i < _numclusters; i++)
		//~ {
			//~ for(int j = 0; j < _longexamples; j++)
				//~ {
					 //~ cluster.push_back((((double)rand()/RAND_MAX)));
				//~ }	
				//~ clusters.push_back(cluster);
				//~ cluster.clear();								
		//~ }
		
		int x = 0;

		ifstream in("clusentrenados.cpp");
		float valor;

		while(in >> valor)
		{
			cluster.push_back(valor);
			x++;
			if(x == longExamples)
				{
					clusters.push_back(cluster);
					cluster.clear();
					x = 0;
				}
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
		
		//~ cout << "Clusters entrendos" << endl<< endl;
		//~ 
		//~ for(unsigned int i = 0; i < _numclusters; i++)
		//~ {	cout << i <<": " ;
			//~ for(int j = 0; j < _longexamples; j++)
				//~ {
					//~ cout << clusters[i][j] << " ";
				//~ }
				//~ cout << endl;
		//~ }
		
	}
	
vector < float > Som::devolverPuntoXyActual(){
	
		return puntoXy;
	
	}

int Som::inputPatterns(vector < vector < float > > _mIn)
	{
		//~ srand(time(0));
		//~ vector < double > v;
		//~ 
		//~ int x = 0;
//~ 
		//~ ifstream in("dataset.cpp");
		//~ double valor;
//~ 
		//~ while(in >> valor)
		//~ {
			//~ v.push_back(valor);
			//~ x++;
			//~ if(x == longExamples)
				//~ {
					//~ mIn.push_back(v);
					//~ v.clear();
					//~ x = 0;
				//~ }
		//~ }
		
		mIn = _mIn;
		
		return match();
		//~ 
		//~ cout << "ejemplo de entreda" << endl<< endl;
		//~ 
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




void Som::training(int _longexamples, float _alpha, int _epoca, int _iteracion)
	{
		float sumaD = 0.0, Djmenor;
		int indiceJ = 0;
		
		for(int x = 0; x < mIn.size();x++)	///Recorre todas las x de entrada
			{
				for(int j = 0; j < clusters.size();j++)
					{
						for(int i = 0; i < _longexamples; i++)
						{
							sumaD += pow((clusters[j][i] - mIn[x][i]),2);
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
					
				
				for(int i = 0; i < _longexamples; i++)
					{
						clusters[indiceJ][i] = clusters[indiceJ][i] + _alpha*((mIn[x][i])-(clusters[indiceJ][i]));
					}																				
					
					//~ if(x == 3){
						//~ for(unsigned int i = 0; i < w.size(); i++)
						//~ {
							//~ for(int j = 0; j < _longexamples; j++)
								//~ {
									//~ cout << w[i][j] << " ";
								//~ }
								//~ cout << endl;
						//~ }
					//~ }					
			}			
		
		if(_iteracion == (_epoca-1)){
				for(unsigned int i = 0; i < clusters.size(); i++)
				{
					for(int j = 0; j < _longexamples; j++)
						{
							cout << clusters[i][j] << " ";
						}
						cout << endl << endl;
				}
			}					
	}

int Som::match(){
		
		vector<int> clusganadorfinal (clusters.size(),0);
		
		puntoXy.clear();
		
		float sumaD = 0.0, Djmenor, sumVecx = 0.0, sumVecy = 0.0, clusMayor;
		int indiceJ, indiceI,  X = 0, Y = 0;
		
		for(int x = 0; x < mIn.size();x++)	///Recorre todas las x de entrada
			{
				for(int j = 0; j < clusters.size();j++)
					{
						for(int i = 0; i < longExamples; i++)
						{
							sumaD += pow((clusters[j][i] - mIn[x][i]),2);
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
				clusganadorfinal[indiceJ] = clusganadorfinal[indiceJ] + 1;												
			}
		
		//~ for(int  i = 0; i < clusganadorfinal.size(); i++){
						//~ cout << clusganadorfinal[i] << endl;
					//~ }
					
			for(int  i = 0; i < clusganadorfinal.size(); i++){
						if(i == 0)
							{
								clusMayor = clusganadorfinal[i];
								indiceI = i;
							}
						
						if(clusMayor < clusganadorfinal[i]){
								clusMayor = clusganadorfinal[i];
								indiceI = i;
							}
					}
		///cout << "cluster ganador: " << indiceI << endl << endl;
			
			///cout << "x: " << clusters[indiceI][0] << endl << endl;
			///cout << "y: " << clusters[indiceI][1] << endl << endl;
			
			X = clusters[indiceI][0];
			Y = clusters[indiceI][1];
			
			puntoXy.push_back(clusters[indiceI][0]);
			puntoXy.push_back(clusters[indiceI][1]);
			
			///cout << "estado: " << (Y*13 + X) << endl << endl;
			
			return (Y*13 + X);
			
	}
