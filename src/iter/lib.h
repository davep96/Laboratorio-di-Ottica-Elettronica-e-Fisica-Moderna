using namespace std;

struct drop{
	double* dt1; // Lista dei tempi di caduta dV=0
	double* dt2; // Lista dei tempi di risalita dV>0
	double* dt3; // Lista dei tempi di ricaduta dV<0
	double* v1; // Lista velocità di caduta
	double mv1; // Velocità di caduta media
	double sv1; // Errore v1
	double* v2; // Lista velocità di risalita
	double mv2; // Velocità di risalita media
	double sv2; // Errore v2
	double* v3; // Lista velocità di ricaduta
	double mv3; // Velocità di ricaduta media
	double sv3; // Errore v3
	double* r; // Lista Raggi
	double* sr; // Errore r
	double mr; // Raggio medio
	double msr; // Errore medio del raggio
	double* Q; // Lista cariche
	double* sQ; // Errori delle cariche
};

struct measure{
	double value;
	double error;
	int classnum;
	int number;
};