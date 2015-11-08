#include <stdio.h>
#include <iostream> 
#include <cmath>
#include <conio.h>
#include<fstream>
#include<string>
using namespace std;
#define pi 3.1415926535
double * write(double *s1, int n, int cheb)
{
	char name;
	string a;
	int k;
	double v = 0, z = n, *bliy;
		bliy = (double*)calloc(90, sizeof(double));
		int l;
		if(n==1)
			l=0;
		if(n==3)
			l=1;
		if(n==9)
			l=2;
	name = 48+l;
	a="C:\\gor\\file";
	if(cheb!=0)
		a+="4eb";
	a+=name;
	a+=".txt";
	ofstream file(a.c_str());
	for (z = 0; z <= 9; z += 0.1)
	{
		k = z*10;
		for (int i = n; i >= 0; i--)
			if (i != 0)
			{
				v += s1[i] * pow(z, i);
			}
			else
			{
				v += s1[i];
			}
		bliy[k] = v;
		file << z << ' ' << bliy[k]<< endl;
		v = 0;
	}
	file.close();
	return bliy;
}
void AbPog(double * bliy, double * y, int i, int f){
	double *pog, z;
	char name;
	string a, a2;
	pog = (double*)calloc(90, sizeof(double));

	name = 48+i;
	a="C:\\gor\\pogr";
	a2="C:\\gor\\bliypog";
	if(f!=0)
	{
		a+="4eb";
		a2+="4eb";
	}
	a+="4-";
	a2+="4-";
	a+=(name+1);
	a2+=(name+1);
	a+=".txt";
	a2+=".txt";
	ofstream file(a.c_str());
	ofstream file2(a2.c_str());
	ofstream file3("C:\\gor\\file7.txt");
	for (int k = 0; k<91; k++)
	{
		double t = k;
		t = t / 10;
		file2 << t << ' ' << bliy[k] << endl;
		file3 << t << ' ' << y[k] << endl;
	}
	for (int k = 0; k<91; k++)
	{
		if (bliy[k]>y[k])
			pog[k] = bliy[k] - y[k];
		else
			pog[k] = y[k] - bliy[k];
		double kk = k;
		z = kk / 10;
		file << z << ' ' << pog[k] << endl;
	}
	file.close();
	file2.close();
	file3.close();
}
double * realgraph()
{
	double *to4y, i = 0;
	to4y = (double*)calloc(90, sizeof(double));
	int k;
	ofstream file("C:\\gor\\file4.txt");
	for (i = 0; i < 9; i += 0.1)
	{
		k = 10 * i;
		to4y[k] = 3.0 * sin((3.0 * i) / 4.0) + 0.1;
		file << i << " " << to4y[k] << endl;
	}
	file.close();
	return to4y;
}
double * work(int n, int cheb){
		int l;
		if(n==1)
			l=0;
		if(n==3)
			l=1;
		if(n==9)
			l=2;
		string a="C:\\gor\\output";
		if(cheb!=0)
			a+="4eb";
		a+=l;
		a+=".txt";
	ofstream file(a.c_str());
	int c;
	double *y, *x, **s, *s1, *g, z, *bliy;
	y = (double*)calloc(n + 2, sizeof(double));
	x = (double*)calloc(n + 2, sizeof(double));
	s1 = (double*)calloc(n*n + 10, sizeof(double));
	g = (double*)calloc(n*n + 10, sizeof(double));
	s = (double**)calloc(n*n + 10, sizeof(double*));
	bliy = (double*)calloc(90, sizeof(double));
	for (int i = 0; i < n*n + 10; i++)
	{
		s[i] = (double*)calloc(n*n + 10, sizeof(double));
	}
	if(cheb==0)
		for (int i = 0; i < n + 1; i++)
		{
			x[i] = i*(9 / (n));
			y[i] = 3 * sin((3 * x[i]) / 4) + 0.1;
		}
	else
		for (int i = 0; i < n + 1; i++)
		{
			x[i] = (9 * cos((2 * i + 1)*pi / (2 * n + 2)) + 9) / 2;
			y[i] = 3 * sin((3 * x[i]) / 4) + 0.1;
		}
	cout << endl <<endl << endl;
	for (int i = 0; i < 10; i++)
	{
		g[i] = 0;
		s1[i] = 0;
		for (int j = 0; j < n*n + 10; j++)
		{
			s[i][j] = 0;
			s[i][1] = 1;
		}
	}
	for (int k = 0; k < n + 1; k++)
	{
		c = 1;
		z = 1;
		for (int i = 0; i < n + 1; i++)
		{
			if (i != k)
			{
				if (c == 1)
				{
					s[k][0] = -x[i];
				}

				else
				{
					s[k][c] = 1;
					for (int j = c - 1; j != 0; j--)
					{
						s[k][j] = g[j - 1] - x[i] * g[j];
					}
					s[k][0] = g[0] * (-x[i]);

				}
				for (int r = 0; r < n + 1; r++)
				{
					g[r] = s[k][r];
				}
				c++;
				z *= -(x[k] - x[i]);
			}
		}
		for (int r = 0; r < n + 1; r++)
		{
			s[k][r] *= -(y[k] / z);
			s1[r] += s[k][r];
		}
	}
	cout << "L="<< s1[n]<< "x^"<< n;
	file << s1[n] << "x^" << n;
	for (int t = n - 1; t >= 1; t--)
	{
		if (s1[t] > 0)
		{
			cout << "+" << s1[t] << "x^" << t;
			file << "+" << s1[t] << "x^" << t;
		}
		else
		{
			cout << "-" << -s1[t] << "x^" << t;
			file << "-" << -s1[t] << "x^" << t;
		}
	}
	if (s1[0] > 0)
	{
		cout << "+" << s1[0]<< endl;
		file << "+" << s1[0]<< endl;
	}
	else
	{
		cout << "-" << -s1[0]<< endl;
		file << "-" << -s1[0]<< endl;
	}
	file.close();
	double w = 1, R;
	for (int i = 0; i<n; i++)
		if (n % 2 == 1)
		{
			w *= 0 - x[i];
		}
		else
		{
			w *= (pi / 2) - x[i];
		}
	R = 3 * pow(3 / 4, n)*w;
	cout << " " << R;
		//bliy = write(s1, n, cheb);
	//return bliy;
	return s1;
}
int main()
{
	int N[3] = { 1, 3, 9};
	double *y, ***Bliy, *s1;
	y = (double*)calloc(91, sizeof(double));
	Bliy = (double***)calloc(2, sizeof(double**));
	s1 = (double*)calloc(3, sizeof(double));
	for (int k = 0; k<3; k++)
		Bliy[k] = (double**)calloc(2, sizeof(double*));
	for (int k = 0; k<3; k++)
		for (int z = 0; z<90; z++)
			Bliy[k][z] = (double*)calloc(90, sizeof(double));
	for (int f = 0; f<2; f++)
		for (int i = 0; i<3; i++)
		{
			s1=work(N[i], f);
			Bliy[f][i]=write(s1, N[i], f);
		}
	char *name;
	string *a;
	name=(char*)calloc(3, sizeof(char));
	a=(string*)calloc(3, sizeof(string));
	for(int f=0;f<2;f++)
		for(int i=0;i<3;i++)
		{
			name[i] = 48+i;
			a[i]="C:\\gor\\bliy";
			if(f!=0)
				a[i]+="4eb";
			a[i]+=name[i];
			a[i]+=".txt";
			ofstream file(a[i].c_str());
			for (int z = 0; z<91; z++)
			{
				double k = z;
				k = k / 10;
				file << k << ' ' << Bliy[f][i][z] << endl;
			}
		file.close();
		}
	y = realgraph();
	ofstream file("C:\\gor\\to4y.txt");
	for (int z = 0; z<91; z++)
	{
		double k = z;
		k = k / 10;
		file << k << " " << y[z]<< endl;
	}
	for (int f = 0; f<2; f++)
		for (int i = 0; i<3; i++)
			AbPog(Bliy[f][i], y, i, f);
}

/*output// полином Лагранжа
output4eb// полином Лагранжа по чебышевским точкам
file//приближение по Лагранжу
file4//точное
file5//ось - OX
file6//приближение в AbPog
file7//точное в AbPog
file4eb// приближение через чебышевские
bliy//приближение в main
to4y// точное значение в main
file4-// погрешность приближения
file4eb4-//погрешность с чебышевскими
*/
