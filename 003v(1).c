#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include <iostream> 
using namespace std;
ofstream file("C:\\gor2\\file.txt");
double trap(int n)
{
	double *x, *y, F = 0, *E, Ek = 0;
	x = (double*)calloc(n, sizeof(double));//узлы
	y = (double*)calloc(n, sizeof(double));//значения
	E = (double*)calloc(n, sizeof(double));//погрешности
	for (int i = 0; i < n + 1; i++)
	{

		double k = i, vs, vs2;// вспомогательные переменные
		x[i] = ((3 * k) / n) + 1;// узлы
		vs = x[i] * x[i];
		vs2 = sqrt(1 + x[i] * x[i]);
		y[i] = vs*vs2;
		printf("f( %lf ) = %lf\n", x[i], y[i]);// вывод на экран
	}
	for (int i = 0; i < n; i++)
	{
		E[i] = -(6 * pow(x[i + 1], 4) + 9 * pow(x[i + 1], 2) + 2)*(x[i + 1] - x[i])*pow(x[i + 1] - x[i], 2) / (12.0*sqrt(pow(1 + x[i + 1] * x[i + 1], 3)));
		F += ((y[i] + y[i + 1]) / 2)*(x[i + 1] - x[i]);// приближение
		Ek += abs(E[i]);// суммарная погрешность
	}
	printf("%lf\n%lf\n", F, Ek);
	file << "приближение составным правилом трапеций  " << F << endl << "погрешность составного правила трапеций  " << Ek << endl;
	return Ek;
}
double gauss(double *x, double *a, int n)
{
	double I = 0;//приближение по Гауссу
	double *xx, *y, vs, vs2;//вспомогательные переменные
	xx = (double*)calloc(n, sizeof(double));
	y = (double*)calloc(n, sizeof(double));//значения
	for (int i = 0; i < n; i++)
	{
		xx[i] = 2.5 + 1.5*x[i];
		vs = xx[i] * xx[i];
		vs2 = sqrt(1 + xx[i] * xx[i]);
		y[i] = vs*vs2;
		I += a[i] *y[i];
	}
	file << "приближение по Гауссу  " << I << endl;
	return I;
}
void main()
{
	int k = 0;
	double *Ek, *ot, *I, *raz;
	Ek = (double*)calloc(6, sizeof(double));
	ot = (double*)calloc(6, sizeof(double));
	I = (double*)calloc(4, sizeof(double));
	raz = (double*)calloc(3, sizeof(double));
	file << "точное значение интеграла 67.3492" << endl;
	for (int i = 2; i < 129; i *= 2)
	{
		Ek[k] = trap(i);
		k++;
	}
	for (int i = 0; i< 6; i++)
	{
		ot[i] = Ek[i] / Ek[i + 1];
		file << " отношение между погрешностями " << i + 1 << " и " << i << " равно " << ot[i] << endl;
	}
	double *x, *y;
	int n = 8;
	x = (double*)calloc(n, sizeof(double));
	y = (double*)calloc(n, sizeof(double));
	x[0] = -0.5773502692;
	x[1] = -x[0];

	y[0] = 1.0;
	y[1] = y[0];
	file << "значение интеграла 0.140451" << endl;
	I[0] = gauss(x, y, 2);
	raz[0] = abs(I[0] - 0.140451);
	file << " разность " << raz[0] << endl;
	x[0] = -0.7745966692;
	x[1] = 0.0;
	x[2] = -x[0];

	y[0] = 0.5555555556;
	y[1] = 0.8888888889;
	y[2] = y[0];
	file << "значение интеграла 0.360711" << endl;
	I[1] = gauss(x, y, 3);
	raz[1] = abs(I[1] - 0.360711);
	file << " разность " << raz[1] << endl;
	x[0] = -0.8611363116;
	x[1] = -0.3399810436;
	x[2] = -x[1];
	x[3] = -x[0];

	y[0] = 0.3478548451;
	y[1] = 0.6521451549;
	y[2] = y[1];
	y[3] = y[0];
	file << "значение интеграла 0.510542" << endl;
	I[2] = gauss(x, y, 4);
	raz[2] = abs(I[2] - 0.510542);
	file << " разность " << raz[2] << endl;
	x[0] = -0.9602898565;
	x[1] = -0.7966664774;
	x[2] = -0.5255324100;
	x[3] = -0.1834346425;
	x[4] = -x[3];
	x[5] = -x[2];
	x[6] = -x[1];
	x[7] = -x[0];

	y[0] = 0.1012285363;
	y[1] = 0.2223810345;
	y[2] = 0.3137066459;
	y[3] = 0.3626837834;
	y[4] = y[3];
	y[5] = y[2];
	y[6] = y[1];
	y[7] = y[0];
	file << "значение интеграла 0.73345" << endl;
	I[4] = gauss(x, y, 8);
	raz[3] = abs(I[4] - 0.73345);
	file << " разность " << raz[3] << endl;
	for (int i = 0; i<3; i++)
		file << " отношение между разностями " << i + 1 << " и " << i << " равно " << raz[i] / raz[i + 1] << endl;
	file.close();
}
