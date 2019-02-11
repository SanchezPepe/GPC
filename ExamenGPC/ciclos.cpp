#include "stdafx.h"
#include "ciclos.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

double *GLOBAL_mC;
int *GLOBAL_permCostoMin;
double GLOBAL_min = 0;
int GLOBAL_numP = 0;
int GLOBAL_permDif = 1;

void guardaC(int n, int p[])
{
	int k;
	long algo = (GLOBAL_numP - 1) * n;
	algo += n;
	for (k = 0; k < n; k++)
		*(GLOBAL_permCostoMin + algo++) = p[k];
}

double costoCiclo(int p[], int n) {
	double cost = 0;
	double *pr = GLOBAL_mC;
	int ind = 0;
	for (int i = 0; i < n; i++)
	{
		cost += *(pr + (p[i] * n) + i);
	}
	return cost;
}

void impSol(int n)
{
	long cual;
	int k;
	long algo = 0;
	for (cual = 1; cual <= GLOBAL_numP; cual++)
	{
		cout << cual << " => ";
		for (k = 0; k < n; k++) {
			cout << *(GLOBAL_permCostoMin + algo++) << " ";
		}
		cout << "=> COSTO: " << costoCiclo((GLOBAL_permCostoMin + algo - n), n) << endl;
	}
}

void impAr(int p[], int n) {
	cout << " ";
	for (size_t i = 0; i < n; i++)
	{
		cout << p[i] << " ";
	}
	cout << "COSTO: " << costoCiclo(p, n);
	cout << endl;

}

void imprimeCostos(int n)
{
	int i, j;
	double *po = GLOBAL_mC;
	cout << "MATRIZ DE COSTOS PARA n= " << n << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << ' ' << *(po++);
		cout << endl;
	}
}

void asignaMatrizCostos(int n)
{
	int i, j;
	double *pt = GLOBAL_mC;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++)
			*(pt++) = (i == j) ? 10 + rand() % 90 : 10.0 * i + j;
	}
}

long factorial(int n)
{
	long r;
	r = n;
	n--;
	while (n) r *= n--;
	return r;
}

//EJ 1.3
bool equiv(int u[], int v[], int n) {
	int i = 0, j = 0, k = 0;
	while (j < n && u[i] != v[j]) {
		j++;
	}
	while (k < n && u[i] == v[j]) {
		if (i == n - 1) i = 0;
		else i++;
		if (j == n - 1) j = 0;
		else j++;
		k++;
	}
	if (k == n) return 1;
	else return 0;
}

bool buscaEquiv(int p[], int n) {
	int sol = 0;
	while (sol < (GLOBAL_numP * (n))) {
		//SI HAY EQUIVALENCIA, SE SALE 
		if (equiv(p, GLOBAL_permCostoMin + sol, n)) {
			return 1;
		}
		else {
			sol += n;
		}
	}
	return 0;
}

void permuta(int k, int n, int p[], int d[])
{
	int i;
	double c = 0;
	if (k == n)
	{
		cout << GLOBAL_permDif << " =>";
		GLOBAL_permDif++;
		impAr(p, n);
		c = costoCiclo(p, n);
		//Se guarda el primero o si el costo es igual y no tiene equivalente
		if (GLOBAL_numP == 0 || c == GLOBAL_min && !buscaEquiv(p, n)) {
			guardaC(n, p);
			GLOBAL_min = c;
			GLOBAL_numP++;
		}
		else if (c < GLOBAL_min) {
			//Si hay un ciclo más económico borra las soluciones que ya tenía
			//Para que el índice a guardar sea i = 0
			GLOBAL_numP = 0;
			guardaC(n, p); //Sobre escribe la primera permutación
			GLOBAL_min = c;
			GLOBAL_numP = 1;
		}
	}
	else
	{
		for (i = 0; i < n; i++)
			if (d[i])
			{
				p[i] = k;
				d[i] = 0;
				permuta(k + 1, n, p, d);
				d[i] = 1;
			}
	}
}

int main_ciclos(int argc, char** argv)
{
	int n = 4;
	GLOBAL_mC = (double*) malloc( n * n * sizeof(double)); // no me preocupo por el espacio...
	GLOBAL_permCostoMin = (int*)malloc(n * factorial(n) * sizeof(int));
	
	int *p = (int*)malloc(sizeof(int)*n);
	int *d = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) d[i] = 1;

	asignaMatrizCostos(n);

	cout << "-----------------------------------------" << endl;
	cout << "       INICIA IMPRESION DE CICLOS" << endl;
	cout << "-----------------------------------------" << endl;

	imprimeCostos(n);

	cout << endl;

	cout << "1.1" << endl;

	cout << "PERMUTACIONES DIFERENTES: " << endl;

	permuta(0, n, p, d);

	cout << endl;

	cout << "1.2" << endl;

	cout << "PERMUTACIONES COSTO MINIMO" << endl;

	impSol(n);

	cout << "=========================================" << endl;
	cout << "============= FIN DE CICLOS =============" << endl;
	cout << "=========================================" << endl << endl;

	return 1;
}
