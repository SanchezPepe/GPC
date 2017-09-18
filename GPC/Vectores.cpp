// Vectores.cpp: define el punto de entrada de la aplicación de consola.
// Preprocesador
#include "stdafx.h"
//Stream: flujo de datos. Los construimos con archivos o cadenas de texto.
// Entrada Cin
// Salida Cout
#include <iostream>
//f (file stream)
#include <fstream>
//str(string)
#include <strstream>
//namespace
using namespace std;

class clsVector3D
{
private:
	double dbl_x, dbl_y, dbl_z;
public:
	clsVector3D()
	{
		dbl_x = dbl_y = dbl_z = 0.0;
	}
	void x(double unX) { dbl_x = unX; }
	double x() { return dbl_x; }

	void y(double unY) { dbl_y = unY; }
	double y() { return dbl_y; }

	void z(double unZ) { dbl_z = unZ; }
	double z() { return dbl_z; }



	friend ostream& operator <<(ostream& os, clsVector3D& p)
	{
		os << "( " << p.x() << "," << p.y() << "," << p.z() << " )";
		return os;
	}


	friend clsVector3D operator +(clsVector3D a, clsVector3D b)
	{
		clsVector3D s;
		s.x(a.x() + b.x());
		s.y(a.y() + b.y());
		s.z(a.z() + b.z());

		return s;
	}



	friend clsVector3D operator * (double esc, clsVector3D v)
	{
		clsVector3D w;

		w.x(esc * v.x());
		w.y(esc * v.y());
		w.z(esc * v.z());

		return w;
	}



	friend clsVector3D operator * (clsVector3D v, double esc)
	{
		return esc * v;
	}



	// EJER 1) operador de entrada del clsVector3D:
	friend istream& operator >>(istream& is, clsVector3D& v)
	{
		v.formato(&is, 1);
		return is;
	}

	void agregaAlFinal(double dato, int num) {
		switch (num) {
		case 1: x(dato);
			break;
		case 2: y(dato);
			break;
		case 3: z(dato);
			break;
		}

	}
	//Dos opciones usar metodo v.x(n) o dbl_x = n
	void formato(istream *f, int num) {
		enum edo { S0, S1, S2, S3, S4, SF, SError };
		enum edo s = S0;
		char c;
		double n;

		while ((s != SF) && (s != SError)) {
			(*f).get(c);

			if ((*f).eof()) c = '\0';

			switch (s)
			{
			case S0:if (c == '[')
				s = S1;
					else
						s = SError;
				break;

			case S1:
				if (c == '(')
				{
					(*f) >> n;
					s = S2;
				}
				else
					if (c == ']')
						s = SF;
					else
						s = SError;
				break;

			case S2:if (c == ')')
			{
				s = S3;
				agregaAlFinal(n, num++);

			}
					else
						s = SError;
				break;

			case S3:if (c == ']')
				s = SF;
					else
						if (c == ',')
							s = S4;
						else
							s = SError;
				break;

			case S4:
				if (c == '(')
				{
					(*f) >> n;
					s = S2;
				}
				else
					s = SError;
				break;
			}
		}

		if (s == SF)
			cout << "todo ok\n";
		else
		{
			cout << "error en la cadena\n";
			throw 5;
		}

	}



	// EJER 2) operador Producto Cruz de dos clsVector3D
	friend clsVector3D operator *(clsVector3D& a, clsVector3D& b)
	{
		clsVector3D w;

		w.x(a.y()*b.z() - b.y()*a.z());
		w.y(b.x()*a.z() - a.x()*b.z());
		w.z(a.x()*b.y() - a.y()*b.x());
		return w;
	}

	// Extra idea Emiliano
	friend clsVector3D operator -(clsVector3D& a, clsVector3D& b)
	{
		clsVector3D w;

		w.x(a.x() - b.x());
		w.y(a.y() - b.y());
		w.z(a.z() - b.z());
		return w;
	}

};



// =============================================
class clsPlano3D
{
private:
	double dbl_A, dbl_B, dbl_C, dbl_D; // representa el plano Ax + By + Cz + D = 0.
public:
	clsPlano3D()
	{
		dbl_A = dbl_B = dbl_C = dbl_D = 0.0;
	}

	// EJER 3)  Construir el plano a partir de los tres puntos v1, v2 y v3.
	clsPlano3D(clsVector3D v1, clsVector3D v2, clsVector3D v3)
	{
		clsVector3D a, b, c;
		double d;
		a = v1 - v2;
		b = v3 - v2;

		cout << a << endl;
		cout << b << endl;

		c = operator*(a, b);

		cout << c << endl;

		//Asignar valores
		A(c.x());
		B(c.y());
		C(c.z());

		cout << A() << endl;

		d = -(A()*v2.x() + B()*v2.y() + C()*v2.z());

		D(d);

		cout << d << endl;

	}

	void A(double unA) { dbl_A = unA; }
	double A() { return dbl_A; }

	void B(double unB) { dbl_B = unB; }
	double B() { return dbl_B; }

	void C(double unC) { dbl_C = unC; }
	double C() { return dbl_C; }

	void D(double unD) { dbl_D = unD; }
	double D() { return dbl_D; }

	// EJER 4) Impresión del plano A * x + B * y + c * z + D = 0.
	friend ostream& operator <<(ostream& os, clsPlano3D& p)
	{
		os << p.A() << " * x + " << p.B() << " * y + " << p.C() << " * z + " << p.D() << " = 0 " << endl;
		return os;
	}



	// EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
	friend istream& operator >>(istream& is, clsPlano3D& p)
	{
		p.formato3(&is, 1);
		return is;
	}


	void agrega(double dato, int num) {
		switch (num) {
		case 1: A(dato);
			break;
		case 2: B(dato);
			break;
		case 3: C(dato);
			break;
		case 4: D(dato);
			break;
		}
	}


	void formato3(istream *f, int num) {
		enum edo { S0, S1, S2, S3, S4, S5, SF, SError };
		enum edo s = S0;
		char c;
		double n;
		(*f) >> n;
		while ((s != SF) && (s != SError)) {
			(*f).get(c);
			if ((*f).eof()) c = '\0';
			switch (s)
			{
			case S0:
				if (c == '*')
					s = S1;

				else
					if (c == '=')
						s = S3;

					else
						s = SError;

				break;

			case S1:if (c == 'x' || c == 'y' || c == 'z') {
				agrega(n, num);
				num++;
				s = S2;
			}
					else
						s = SError;
				break;

			case S2:if (c == '+' || c == '-') {
				(*f) >> n;
				if (c == '-')
					n = n*(-1);
				s = S0;
			}
					else
						if (c == '=') {
							s = S3;
							num--;
						}

						else
							s = SError;

				break;

			case S3:if (c == '0') {
				agrega(n, num);
				s = SF;
			}
					else
						s = SError;
				break;
			}
		}

		if (s == SF)
			cout << "Buen camino\n";
		else
		{
			cout << "Error en la cadena\n";
			throw 5;
		}

	}

	friend double det(clsVector3D h1, clsVector3D h2, clsVector3D h3) {
		double d, compx, compy, compz;
		compx = h1.x() * ((h2.y() * h3.z()) - (h2.z() * h3.y()));
		compy = h1.y() * ((h2.x() * h3.z()) - (h2.z() * h3.x()));
		compz = h1.z() * ((h2.x() * h3.y()) - (h2.y() * h3.x()));

		d = compx - compy + compz;
		return d;

	}

	friend clsVector3D planoVector(clsPlano3D p) {
		clsVector3D v;
		v.x(p.A());
		v.y(p.B());
		v.z(p.C());

		return v;
	}


	friend double cram(clsVector3D a, clsVector3D b, clsVector3D c, clsVector3D sol, char lugar) {
		double res;

		switch (lugar)
		{
		case 'x':
			a.x(sol.x());
			b.x(sol.y());
			c.x(sol.z());
			break;
		case 'y':
			a.y(sol.x());
			b.y(sol.y());
			c.y(sol.z());
			break;
		case 'z':
			a.z(sol.x());
			b.z(sol.y());
			c.z(sol.z());
			break;
		}

		res = det(a, b, c);
		return res;
	}


	// EJER 6) Obtener el punto que resulta de la intersección de tres planos
	friend clsVector3D interseccion(clsPlano3D P1, clsPlano3D P2, clsPlano3D P3)
	{
		// Regresa interseccion de planos
		clsVector3D inter, a, b, c, sol;
		double d, dx, dy, dz;

		//Encontrar D
		//Transformar plano en vector
		a = planoVector(P1);
		b = planoVector(P2);
		c = planoVector(P3);

		//Determinante
		//TRAMPA -1
		d = det(a, b, c)*-1;
		cout << d << endl;

		//asignar valores de sol
		sol.x(P1.D());
		sol.y(P2.D());
		sol.z(P3.D());

		//Encontrar valores de intersección
		dx = (cram(a, b, c, sol, 'x')) / d;
		dy = (cram(a, b, c, sol, 'y')) / d;
		dz = (cram(a, b, c, sol, 'z')) / d;

		inter.x(dx);
		inter.y(dy);
		inter.z(dz);

		return inter;
	}
};
// =============================================



int main()
{
	clsVector3D a, b, c, d, a1;
	clsPlano3D x, y, z;

	istrstream sin("2*x-1*y+6*z-10=0");
	sin >> x;
	cout << x << endl;
	a = planoVector(x);
	cout << a << endl;

	istrstream sin2("-3*x+4*y-5*z-11=0");
	sin2 >> y;
	cout << y << endl;
	b = planoVector(y);
	cout << b << endl;

	istrstream sin3("8*x-7*y-9*z-12=0");
	sin3 >> z;
	cout << z << endl;
	c = planoVector(z);
	cout << c << endl;

	double d1 = det(a, b, c);
	cout << d1;

	a1 = interseccion(x, y, z);
	cout << a1 << endl;


	char car;
	cin >> car;

	return 0;
}