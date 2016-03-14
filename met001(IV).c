#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
inline double f(double a)
{
	cos(a);
}
double treep()
{
	int n;
	double *x, *y, A, B, h0, h1, a, b, c, *kk, *ll, *spc, *spb, *spd;
	string a;
	a = "C:\\gor3\\input.txt";
	ifstream file(a.c_str());
	file >> n;
	x = (double*)calloc(n, sizeof(double));//узлы интерполяции
	y = (double*)calloc(n, sizeof(double));//значения в узлах
	kk = (double*)calloc(n - 1, sizeof(double));//прогоночные коэффиценты
	ll = (double*)calloc(n - 1, sizeof(double));
	spc = (double*)calloc(n, sizeof(double));//коэффиценты сплайна
	spb = (double*)calloc(n, sizeof(double));
	spd = (double*)calloc(n, sizeof(double));
	for (int i = 0; i < n; i++)
		file >> x[i] >> y[i];
	file >> A >> B;// надо придумать где их вообще использовать то
	file.close();
	for (int i = 1; i < n - 1; i++)//прямой ход прогонки
	{
		h0 = x[i] - x[i - 1];//шаг сетки слева
		h1 = x[i+1] - x[i];//шаг сетки справа
		a = 2.0*(h0 + h1);
		b = 6.0*((y[+1] - y[i]) / h1 - (y[i] - y[i - 1]) / h0);
		c = h0*kk[i-1]+a;
		kk[i] = -h1 / c;//прогоночные кожффиценты
		ll[i] = b - h0*ll[i - 1] / c;//прогоночные коэффиценты
	}
	spc[n-1]= (b - h0*ll[i - 2]) / (a + h0*kk[i - 2]);
	for (int i = n - 2; i > 0; i--)//обратный ход прогонки
	{
		spc[i]= kk[i] *spline[i+1] +ll[i];
	}
	free(kk);
	free(ll);
	for (int i = 0; i < n - 1; i++)
	{
		spb[i] = h0*(2.0spc[i] + spc[i + 1]) / 6.0 + (y[i] - y[i - 1]) / h0;
		spd[i] = (spc[i] - spc[i - 1]) / h0;
	}
	// тут вроде что то типо построения сплайна или хотя бы возврата найденных коэффицентов должно быть но я пока не придумал как
	//и главное вообще зачем(и куда)
}
double proof(double *x, double *y)// была какая то крутая задумка но я ее забыл
{
	int i;
	y[i] = f(x[i]);
}
void main()// дооформить бы
{

}
