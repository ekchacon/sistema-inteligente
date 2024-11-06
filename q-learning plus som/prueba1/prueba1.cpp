//~ //Ek Chacón

///cd Escritorio/3er\ Semestre/Procesos\ de\ decisión\ semi-Marcok/11-intraoptions/prueba1/

#include <iostream>
#include <fstream> 
#include <random> 
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "../qllib/ql.h"
#include <cmath>

using namespace std;

const int numFilas = 13;
const int numColumnas = 13;
const int numAcciones = 4, numOptions = 8;
const int numEstados = numFilas * numColumnas;
int estadoInicial, estadoActual, estadoSiguiente, k_steps, estadoSigDeSOM;
int optionElegida, accionElegida, accionSiguiente, numEpisodios = 1000, numPasos = 10, pasos, betaOption, switchOption, exploracion;
float recompensa;
const float _egreedy = 0.1, _alfa = 0.25, _gamma = 1.0;
vector < float > posicionReal, tempPosicionReal;
vector < vector < float > > output3Sensor;

///Parametros Self-Organizing Map Entrenado	----------------------------
	//Parametros de vecindario
int numclusters = 2500, longexamples = 2; 	///Número de clusters y longitud de ejemplos
			
main ()
	{		
			
			///parametros experimento
				vector < vector < float > > Mpasos, MswitchOption, Mexploracion;
				vector < float > Vpasos, VswitchOption, Vexploracion;
			
				///instanciacion de un archivo
				ofstream myfile;
			///________________________
			//~ mundo.imprimirV();
			
			//~ robot.imprimirQso();
			for( int Experimento = 0; Experimento < 1; Experimento++)
				{
										
					ambiente mundo(numFilas, numColumnas, numAcciones);
			
					agente robot(numFilas,numColumnas,numAcciones, numOptions);
					
					transductor Sensor(numFilas, numColumnas);
					
					Som Som(numclusters, longexamples);
					
					///Repeat for each Episode
					 for(int episodio = 0; episodio < numEpisodios; episodio++)//numEpisodios
					 {
						posicionReal = mundo.devolverPosicionReal();
						
						do{ 
							output3Sensor = Sensor.output3DNSensor(posicionReal);
												
							estadoActual  = Som.inputPatterns(output3Sensor); ///Som recibe datos de los sensores.  ///Hace una estimación del estado del ambiente
						}while(estadoActual == robot.noEstado(estadoActual));
						
						pasos = 0;
						betaOption = 1;
						switchOption = 0;
						robot.obtenerContExploracion();
						//~ 
						//~ cout << "Episodio: " << episodio << endl << endl;
						///Repeat for each step of episode
							do
							{
								
								if( (pasos == 0) || (betaOption == 1) ){	//Esencia de intra-options: se sigue una option mientras se aprende de otros, off-policy
									//~ cout <<"o e: " << optionElegida << endl;						
									optionElegida = robot.elegirOptionEnEstadoUsandoGreedy(_egreedy, estadoActual);/// 
									switchOption++;
									 
									}
								//~ cout <<"o e: " << optionElegida << endl;						
								accionElegida = robot.elegirAccionEnPoliticaOption(optionElegida, estadoActual);
								//~ cout <<"a e: " << accionElegida << endl;
								
								do{
									
								tempPosicionReal = mundo.recibirAccion(posicionReal,accionElegida);
								
								output3Sensor = Sensor.output3DNSensor(tempPosicionReal);
								
								estadoSigDeSOM  = Som.inputPatterns(output3Sensor);
									
									//~ if(estadoSigDeSOM == robot.noEstado(estadoSigDeSOM)){	//Para asurar que el estadoSig no sea un estado con muro.
											//~ 
											//~ estadoSigDeSOM = robot.deNoEstadoToEstado(estadoSigDeSOM, optionElegida, estadoActual); ///Devuelve un estado cercano al estado anterior, se hizo a base del conjunto de estados iniciales
																						//~ 
								//~ 
											//~ cout << "Nestea" << endl;
										//~ }
								
								 }while(estadoSigDeSOM == robot.noEstado(estadoSigDeSOM));
								 
								posicionReal = tempPosicionReal;
								 
								mundo.observarRecompensa(posicionReal);
								
								recompensa = mundo.devolverRecompensa(); 
								
								//~ estadoSiguiente = mundo.devolverEstadoSiguiente();
							
								//~ cout << "  " << estadoActual << "--" << estadoSiguiente << "--" << estadoSigDeSOM << endl;
								
								//~ cout << "edo sig: " << estadoSiguiente << endl;
								
								//~ if(estadoSiguiente == estadoSigDeSOM){
									//~ 
									//~ }else{
											//~ cout << "edo sig: " << estadoSiguiente << endl;
											//~ cout << "edo sigSOM: " << estadoSigDeSOM << endl;
											//~ break;
										//~ }
															
								pasos++;
								// if(episodio == (numEpisodios-1))	{cout << "paso: " << pasos << "  estadoActual: " << estadoActual << "  OptionElegida: " << optionElegida << "  estadoSiguiente" << estadoSiguiente << "  recompensa: " << recompensa << endl;}
								robot.actualizarQso(_alfa,recompensa,_gamma,estadoSigDeSOM, estadoActual, optionElegida, accionElegida);
								
								betaOption = robot.sigueOTerminaOptionElegida(estadoSigDeSOM,optionElegida); //Esencia de intra-options:
								
								estadoActual = estadoSigDeSOM;
								//~ if(estadoActual == 100) cout << "pasos: " << pasos << endl;
							 }while(estadoActual != 100);
							 //~ cout << "SW Op: " << switchOption << endl;
							 Vpasos.push_back(pasos);
							 VswitchOption.push_back(switchOption);
							 Vexploracion.push_back(robot.devolverContExploracion());
							 //~ cout << "SW Op: " << switchOption << endl;
					}
					
					Mpasos.push_back(Vpasos);
					Vpasos.clear();
					MswitchOption.push_back(VswitchOption);								
					VswitchOption.clear();
					Mexploracion.push_back(Vexploracion);
					Vexploracion.clear();
					// if ((promE == 25) || (promE == 50) || (promE == 75))
						// cout << "..." << endl;
					cout << "Experimento: " << Experimento << endl;
				}
				
				myfile.open("Mpasos.cpp");
				for(int i = 0; i < Mpasos.size(); i++)
				{
					//~ // myfile << (i) << " ";
					for(int j = 0; j < numEpisodios; j++)
					{
						myfile << fixed << Mpasos[i][j] << " ";
					}
					myfile << endl;
				}
					myfile.close();
					
				myfile.open("MswitchOption.cpp");
				for(int i = 0; i < MswitchOption.size(); i++)
				{
					//~ // myfile << (i) << " ";
					for(int j = 0; j < numEpisodios; j++)
					{
						myfile << fixed << MswitchOption[i][j] << " ";
					}
					myfile << endl;
				}
					myfile.close();
					
				myfile.open("ContExploracion.cpp");
				for(int i = 0; i < Mexploracion.size(); i++)
				{
					//~ // myfile << (i) << " ";
					for(int j = 0; j < numEpisodios; j++)
					{
						myfile << fixed << Mexploracion[i][j] << " ";
					}
					myfile << endl;
				}
					myfile.close();
			//~ 
			 //~ robot.imprimirQso();
	}
