//Ek Chacón

#ifndef QL_H
#define QL_H

#include <vector>
#include <stdio.h>

using namespace std;

class agente
{
	private:
		
		vector < vector < float > > Qso, tabProb;
		vector < float > Vk_1, Vk;
		
		int numFilas;
		int numColumnas;
		int numEstados;
		int numAcciones;
		int numOptions;
		int numAUH;
		int estadoSiguiente;
		int contExploracion;
		
		int recomEstadoSig;
		float recomRecompensa;
		
		int probEstadoSig;
		float probProb;
		
		///Option
		int optionEstadoSig, k_steps;
		float optionRecompensa;
		///------------------
		
		int accion8;
		
		struct option {
				
				vector < int > I;
				vector < vector < float > > pi;
				vector < float > beta;
				
			} auxOption;
			
		vector < option > options;
		
	public:
		///funciones de option
		
		agente(int _numFilas, int _numColumnas, int _numAcciones, int _numOptions);
		void option(const char * _I, const char * _op, const char * _beta);
		
			//Impresiones
		void imprimirOptionPi(int _posOption);
		void imprimirOptionI(int _posOption);
		void imprimirOptionBeta(int _posOption);
		void imprimirV();
		void imprimirTabProb();
			//-------------
			
		void tablaProbabilidades(const char * _tabprob);
		void recompensaf(int _estadoActual, int accion, int _optionActual);
		int elegirAccionCorrectaONC( int _estadoActual, int _optionActual);
		int elegirAccionEnEstadoUsandoGreedy(float _egreedy, int _estado);
		int explotar(int _estado, int _option);
		int explorar(int _estado);
		void observarRecompensaYEstadoSig(int _accionElegida, int _estadoActual, int _optionActual);
		float devolverRecompensa();
		int devolverEstadoSiguiente();
		//~ float maxAccionQsa(int _estadoSiguiente);
		void obtenerVectorFuncionValorEstado( vector < float > _v);
		void actualizarVk(int _estadoActual);
		float rO_s( int _estadoActual, int _optionActual);
		int noEstado(int _estado);
		float sumatoriaEstadosSiguientes(int _estadoActual, int _optionActual);
		vector < float > devolverVectorFuntionValorEstado();
		float pO_sSig(int _estadoActual,int _optionActual, int _estadoSig);
		int sigueOTerminaOptionElegida(int estadoSigDeSOM, int optionElegida);
		
		
		///funciones de accion
		float rA_s(int _estadoActual, int _accionActual);
		float sumatoriaEstadosSiguientesAccion(int _estadoActual, int accionActual);
		float pA_sSig(int _estadoActual, int accionActual,int estadoSig);
		int elegirAccionEnPoliticaOption(int optionElegida, int _estadoActual);
		
		///funciones de SMDP-qlearning
		void imprimirQso();
		int elegirOptionEnEstadoUsandoGreedy(float _egreedy, int _estado);
		int explotarOption(int _estado);
		int explorarOption(int _estado);
		void observarRecompensaYEstadoSigOption(int _optionElegida, int _estadoActual);
		void rA_sAUH(int _estadoActual, int accion);
		float devolverRecompensaOption();
		int devolverEstadoSiguienteOption();
		void rO_sOption(int _estadoActual, int _optionActual);
		void actualizarQso( float _alfa, float _recompensa, float _gamma, int _estadoSiguiente, int _estadoActual, int _optionElegida, int _accionElegida);
		int devolverK_Steps();
		float U(int _estado, int _optionElegida);
		
		///intra + som
		int DevAccionDeNoestadoToEsatdo();
		int deNoEstadoToEstado(int _estadoSigDeSOM, int _optionsElegida, int _estadoActual);
		int stateAround(int accion, int _estadoActual);
		int devolverContExploracion();
		void obtenerContExploracion();
};

class ambiente
{
	private:
		
		vector < float > v;
		
		int numEstados;
		int numAcciones;
		int numFilas, numColumnas;
		float recompensa;
		int estadoSiguiente;
	
	public:
	
		ambiente(int numfilas, int numcolumnas, int numAcciones);
		void imprimirV();
		int noEstado(int _estado);
		vector < float > devolverVectorFuntionValorEstado();
		void obtenerVectorFuncionValorEstado( vector < float > _v);
		
		float devolverRecompensa();
		int devolverEstadoSiguiente();
		void observarRecompensa(vector < float > _puntoXy);
		vector < float > devolverPosicionReal();
		vector < float > recibirAccion(vector < float > _puntoXy, int _accionElegida);
		
	};
	
class transductor
{
	private:
		
		int numFilas, numColumnas;
		vector < vector < float > > output;
		
	public:
	
		transductor(int _numfilas, int _numcolumnas);
		
		vector < vector < float > >   output3DNSensor(vector < float > _posicionReal);		
		vector < vector < float > > tamanoPasoBasadoEnpuntoXy( vector < float > _puntoXy, int _accionElegida);
	};
	
class Som
	{				
		
		vector < vector < float > > clusters, mIn;
		vector < float > D;
		int longExamples;
		//Intra-Option + SOM
		vector < float > puntoXy;
		
		public:
		
		Som(int _numclusters, int _longexamples);
		int inputPatterns(vector < vector < float > > _mIn);
		void training(int _longexamples, float _alpha, int _epoca, int _iteracion);
		int match();
		
		//Intra-Option + SOM
		vector < float > devolverPuntoXyActual();
	};

#endif
