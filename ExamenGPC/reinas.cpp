#include "stdafx.h"
#include "reinas.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

long GLOBAL_cuantas = 0;
long GLOBAL_solEquiv = 0;

int *GLOBAL_g;

void cout2(string s) {
	cout << s << endl;
}

void impA(int p[], int n) {
	for (size_t i = 0; i < n; i++)
	{
		cout << " " << p[i];
	}
}

bool reinas(int p[], int n) {
	bool band = 1;
	int i = 0, j = 0;
	int difCont, difInd;
	while (band && (i<n)) {
		j = 0;
		while (band && (j < n)) {
			if (i == j)
				j++;
			difCont = abs(p[i] - p[j]);
			difInd = abs(i - j);
			if (difCont == difInd) {
				band = false;
			}
			j++;
		}
		i++;
	}
	return band;
}

//Clases de equivalencia
bool relaciones(int p[], int q[], int n)
{
	int k = 0;
	//R1
	while (k < n && q[k] == (n - 1 - p[k])) k++;
	if (k == n) return 1; else k = 0;

	//R2
	while (k < n && q[k] == p[(n - 1) - k]) k++;
	if (k == n) return 1; else k = 0;

	//R3
	while (k < n && n - 1 - k == q[p[(n - 1 - k)]]) k++;
	if (k == n) return 1; else k = 0;

	//R4
	while (k < n && n - 1 - k == q[abs(p[k]-(n-1))]) k++;
	if (k == n) return 1; else k = 0;

	//R5
	while (k < n && q[n - 1 - p[k]] == k) k++;
	if (k == n) return 1; else k = 0;

	//R6
	while (k < n && q[n - 1 - k] == (n - 1 - p[k])) k++;
	if (k == n) return 1; else k = 0;

	//R7
	bool ans = 0;
	while (k < n && q[p[k]] == (n - 1 - k)) k++;
	if (k == n) return 1;

	return 0;
}

//Guarda la permutación en su espacio en el arreglo
void guarda(int n, int p[])
{
	int k;
	long algo = (GLOBAL_cuantas - 1) * n;
	algo += n;
	for (k = 0; k < n; k++)
		*(GLOBAL_g + algo++) = p[k];
}

void imp(int n)
{
	long cual;
	int k;
	long algo = 0;
	for (cual = 1; cual <= GLOBAL_cuantas; cual++)
	{
		cout << cual << " => ";
		for (k = 0; k<n; k++)
			cout << *(GLOBAL_g + algo++) << " ";
		cout << endl;
	}
}

//COMPARA LA P CON LAS PERMUTACIONES GUARDADAS EN GLOBAL_G
//REGRESA EL NUMERO DE PERMUTACIÓN QUE ES EQUIVALENTE
int compara(int p[], int n) {
	int sol = 0;
	while (sol < (GLOBAL_cuantas * (n))) {
		//SI HAY EQUIVALENCIA, SE SALE 
		if (relaciones(p, GLOBAL_g + sol, n)) {
			return sol;
		}
		else {
			sol += n;
		}
	}
	return -1;
}

//ENCUENTRA LAS PERMUTACIONES Y CHECA SI ES UNA SOLUCIÓN DE N REINAS
void permut(int k, int n, int p[], int d[])
{
	int i, res;
	if (k == n)
	{
		if (reinas(p, n) == 1)
		{
			//Se guarda la primera permutación siempre
			if (GLOBAL_cuantas < 1) {
				guarda(n, p);
				GLOBAL_cuantas++;
			}
			else {
				//SI NO TIENE EQUIVALENTE
				res = compara(p, n);
				if (res == -1) {
					guarda(n, p);
					GLOBAL_cuantas++;
				}
				else {
					cout << GLOBAL_solEquiv << " =>";
					impA(p, n);
					cout << " EQUIVALENTE A SOL: " << ((res)/n) + 1 << endl;
					GLOBAL_solEquiv++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < n; i++)
			if (d[i])
				{
					p[i] = k;
					d[i] = 0;
					permut(k + 1, n, p, d);
					d[i] = 1;
				}
	}
}

long nfactn(int n)
{
	long r;
	r = n;
	while (n) r *= n--;
	return r;
}

#define N 8
int main_reinas(int argc, char * argv[])
{
	cout << "-----------------------------------------" << endl;
	cout << "       INICIA IMPRESION REINAS			  " << endl;
	cout << "-----------------------------------------" << endl;
	
	int i, n;
	n = N;
	clock_t t0, t1;
	float deltaT_seg;
	long espacio = nfactn(n);

	int *p = (int*)malloc(sizeof(int)*n);
	int *d = (int*)malloc(sizeof(int)*n);

	//Asignación de memoria
	if (!(GLOBAL_g = (int*)malloc(espacio * sizeof(int))))
	{
		cout << "No hay memoria, necesaria: " << espacio * sizeof(int) << "." << endl;
		return 1;
	}

	for (i = 0; i < n; i++)
		d[i] = 1;

	cout << "1.3" << endl;

	permut(0, n, p, d);

	cout << "SOLUCIONES REINAS: " << GLOBAL_cuantas + GLOBAL_solEquiv << endl;

	cout << endl;
	
	cout << "1.1" << endl;
	cout << "SOLUCIONES UNICAS: " << GLOBAL_cuantas << endl;
	imp(n);

	cout << endl;

	cout << "1.2" << endl;
	cout << "SOLUCIONES EQUIVALENTES: ";
	cout << GLOBAL_solEquiv << endl;

	cout << endl;
	
	cout << "=========================================" << endl;
	cout << "============= FIN DE REINAS =============" << endl;
	cout << "=========================================" << endl;

	return 1;
}
