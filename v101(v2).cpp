#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
using namespace std;
inline double f(double a)
{
	return cos(a);//искомая функция
}
inline double g(double a)
{
	return -sin(a);//первая производная
}
inline double h(double a)
{
	return -cos(a);//вторая производная
}
int func()// начальные данные
{
	int n;
	double *x, *y, u, o;
	cout << "write the number of nodes" << endl;
	cin >> n;
	x = (double*)calloc(n+1, sizeof(double));
	y = (double*)calloc(n+1, sizeof(double));
	cout << "write startpoint" << endl;
	cin >> x[0];
	cout << "write endpoint" << endl;
	cin >> x[n];
	ofstream file("H:\\gor\\input.txt");
	o = x[n] - x[0];
	for (int i = 0; i <= n; i++)
	{
		x[i] = x[0] + (o/n)*i;
		y[i] = f(x[i]);
		file << x[i] << " " << y[i] << endl;
	}
	file << g(x[0]) << " " << h(x[n]);
	file.close();
	return n;
}
void treep(int n)
{
	double *x, *y, A, B, *h, *u, *c, *M, *a, *b, *d;
	ifstream file("H:\\gor\\input.txt");
	x = (double*)calloc(n+1, sizeof(double));//узлы интерполяции
	y = (double*)calloc(n+1, sizeof(double));//значения в узлах
	h = (double*)calloc(n, sizeof(double));//шаг сетки слева
	u = (double*)calloc(n - 1, sizeof(double));
	c = (double*)calloc(n - 1, sizeof(double));
	M = (double*)calloc(n, sizeof(double));//столбец вторых производных
	a = (double*)calloc(n, sizeof(double));//прогоночные коеффиценты
	b = (double*)calloc(n, sizeof(double));
	d = (double*)calloc(n, sizeof(double));//разделенная разность
	for (int i = 0; i < n+1; i++)
		file >> x[i] >> y[i];
	file >> A >> B;
	file.close();
	for (int i = 0; i < n; i++)
		cout << x[i] << " " << y[i] << endl;
	for (int i = 1; i < n; i++)//прямой ход прогонки
		h[i] = x[i] - x[i - 1];
	for (int i = 1; i < n - 1; i++)//нахождение элементов матрицы
	{
		u[i] = h[i] / (h[i] + h[i + 1]);
		c[i] = 1 - u[i];
	}
	c[0] = 1;
	a[1] = -1.0*c[0] / 2.0;//находим прогоночные коеффиценты
	b[1] = 6.0 / h[1] * ((y[1] - y[0]) / (x[1] - x[0]) - A) / 2.0;
	for (int i = 2; i < n; i++)//прямой ход прогонки
	{
		d[i - 2] = 6.0*(((y[i]) - y[i - 1]) / (x[i] - x[i - 1]) - (y[i - 1] - y[i - 2]) / (x[i - 1] - x[i - 2])) / (x[i] - x[i - 2]);
		a[i] = -1.0*(c[i - 1] / (u[i - 1] * a[i - 1] + 2.0));
		b[i] = (d[i - 2] - u[i - 1] * b[i - 1]) / (u[i - 1] * a[i - 1] + 2.0);
	}
	M[n - 1] = B;
	for (int i = n - 2; i >= 0; i--)//обратный ход
		M[i] = a[i + 1] * M[i + 1] + b[i + 1];



	double l, M1, M2, M3, M4, *Y;
	int i = 0, j = 1;
	l = (x[n - 1] - x[0]) / 100.0;// шаг сетки графика
	Y = (double*)calloc(100, sizeof(double));//значение сплайна
	for (int i = 0; i < 100; i++)
	{
		double k = i, mx = k*l + x[0];
		if (k*l <= (x[j] - x[0]))// проверка на вхождение в многочлен сплайна
		{
			M1 = M[j - 1] * pow((x[j] - mx), 3) / (6.0*h[j]);//вспомогательные переменные
			M2 = M[j] * pow((mx - x[j - 1]), 3) / (6.0*h[j]);
			M3 = (y[j - 1] - (M[j - 1] * h[j] * h[j]) / 6.0)*(x[j] - mx) / h[j];
			M4 = (y[j] - M[j] * h[j] * h[j] / 6.0)*(mx - x[j - 1]) / h[j];
			Y[i] = M1 + M2 + M3 + M4;//значение сплайна в точке
		}
		else//переход к следующему многочлену
		{
			j++;
			i--;
		}
	}
	ofstream fout;//вывод результатов
	fout.open("H:\\gor\\output.txt");
	for (int i = 0; i < 100; i++)
		fout << x[0] + i*l << " " << Y[i] << endl;
	fout.close();
}

void main()
{
	int a;
	a = func();
	treep(a);
}
