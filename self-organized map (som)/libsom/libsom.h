///Ek Chacón

#ifndef som
#define som
#include <vector>

using namespace std;

class neighborhood
	{				
		
		vector < vector < float > > clusters, mIn;
		
		///updateclustersneighboors
		int numFilas;
		int numColumnas;
		int longExamples;
		int radii;
		vector < int > neighboorsunits;
		///------------------------
		
		///Cross Validation
		vector < vector < float > > train, test;
		vector < float > eficiencia;
		///------------------------
		
		public:
		
		neighborhood(int numfilas, int numcolumnas, int _longexamples, int _radii);
		void inputPatterns();
		void parameters(int _numclusters, int _longexamples);
		void training(int _fold, float _alpha, int _epoca, int _iteracion);
		void updateNeighbooringUnits(int indiceJ);
		int movimiento(int accion, int _estadoActual);
		vector < vector < float > > devClusentrenados();
		void divideTestTrain(int fold);
		void match();
		void imprimeEficiencia();
		
	};

#endif
