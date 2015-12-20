#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
class Expression {
public:
	virtual Expression * diff() = 0;
	virtual void print() = 0;
	virtual	Expression* copy() = 0;
	Expression() {}
};
class Number :public Expression
{
	double data;
public:
	Number(double a)
	{
		data = a;
	}
	Expression * diff()
	{
		Number* ret = new Number(0);
		return (Expression*)ret;
	}
	Expression* copy()
	{
		Number* ret = new Number(this->data);
		return (Expression*)ret;
	}
	void print()
	{
		cout << data;
	}
	~Number()
	{
		delete(&data);
	}

};
class Variable :public Expression
{
	char per;
public:
	Variable(char a)
	{
		per = a;
	}
	Expression * diff()
	{
		Number* ret = new Number(1);
		return (Expression*)ret;
	}
	Expression* copy()
	{
		Variable* ret = new Variable(this->per);
		return (Expression*)ret;
	}
	void print()
	{
		cout << per;
	}
	~Variable()
	{
		delete(&per);
	}
};
class Add :public Expression {
public:
	Expression	*e1;
	Expression *e2;
	Expression * diff()
	{
		Expression * ex = (Expression*)new Add(e1->diff(), e2->diff());
		return ex;
	}
	Add(Expression * a1, Expression * a2)
	{
		this->e1 = a1;
		this->e2 = a2;
	}
	Expression* copy()
	{
		return 0;
	}
	void print()
	{
		cout << "(";
		e1->print();
		cout << " + ";
		e2->print();
		cout << ")";
	}
};
class Sub :public Expression
{
public:
	Expression	*e1;
	Expression *e2;
	Expression * diff()
	{
		Expression * ex = (Expression*)new Sub(e1->diff(), e2->diff());
		return ex;
	}

	Sub(Expression * a1, Expression * a2)
	{
		this->e1 = a1;
		this->e2 = a2;
	}
	Expression* copy()
	{
		return 0;
	}
	void print()
	{
		cout << "(";
		e1->print();
		cout << " - ";
		e2->print();
		cout << ")";
	}
};
class Mul :public Expression
{
public:
	Expression * e1;
	Expression * e2;
	Expression * diff()
	{
		Expression * ex = (Expression*)new Mul(e1->diff(), e2);
		Expression * ex1 = (Expression*)new Mul(e1, e2->diff());
		Expression *ex2 = (Expression*)new Add(ex, ex1);
		return ex2;
	}
	Mul(Expression * a1, Expression * a2)
	{
		e1 = a1->copy();
		e2 = a2->copy();
	}
	Expression* copy()
	{
		return new Mul(this->e1, this->e2);
	}
	void print()
	{
		cout << "(";
		e1->print();
		cout << " * ";
		e2->print();
		cout << ")";
	}
};
class Div :public Expression
{
public:
	Expression * e1;
	Expression * e2;
	Expression * diff()
	{
		Expression * ex = (Expression*)new Mul(e1->diff(), e2);
		Expression * ex1 = (Expression*)new Mul(e1, e2->diff());
		Expression *ex2 = (Expression*)new Sub(ex, ex1);
		Expression *ex3 = (Expression*)new Mul(e2, e2);
		Expression *ex4 = (Expression*)new Div(ex2, ex3);
		return ex4;
	}
	Div(Expression * a1, Expression * a2)
	{
		this->e1 = a1;
		this->e2 = a2;
	}
	Expression* copy()
	{
		return 0;
	}
	void print()
	{
		cout << "(";
		e1->print();
		cout << " / ";
		e2->print();
		cout << ")";
	}
};
class Sin :public Expression
{
public:
	Expression * e1;
	Expression * e2;
	Expression * diff();
	Sin(Expression * a1)
	{
		this->e1 = a1;
	}
	Expression* copy()
	{
		return 0;
	}
	void print()
	{
		cout << "sin(";
		e1->print();
		cout << ")";
	}
};
class Cos :public Expression
{
public:
	Expression * e1;
	Expression * diff();
	Cos(Expression * a1)
	{
		this->e1 = a1;
	}
	Expression* copy()
	{
		return 0;
	}
	void print()
	{
		cout << "cos(";
		e1->print();
		cout << ")";
	}
};
Expression * Cos::diff()
{
	Number* ret = new Number(-1);
	Expression *ex = (Expression*)new Mul((Expression*)ret, e1);
	Expression * ex1 = (Expression*)new Sin(ex);
	return ex1;
}
Expression * Sin::diff()
{
	Expression * ex;
	if (e1->diff() == 0)
		ex = (Expression*)new Number(0);
	else
		ex = (Expression*)new Cos(e1);
	return ex;
}
Expression * read_expression(char * a)
{
	Expression *e;
	int i, ss = 0;
	int n = strlen(a);
	int c = 0, sign = 0;
	char *b, *se;
	b = (char*)calloc(n - 3, sizeof(char));
	se = (char*)calloc(n, sizeof(char));
	i = 0;
	if (a[i] == '(')
	{
		for (i = 0; i < n - 1; i++)
			se[i] = a[i + 1];
		read_expression(se);
	}
	else
		if (a[i] >= 'a' && a[i] <= 'z')
			if (a[i] == 's' || a[i] == 'c')
			{
				if (a[++i] == 'i')
				{
					for (int k = 0; k < n - 3; i++)
						a[k] = a[i + 3];
					e = new Sin(read_expression(a));
				}
				if (a[i + 1] == 'o')
				{
					for (int k = 0; k < n - 3; i++)
						a[k] = a[i + 3];
					e = new Cos(read_expression(a));
				}
				else
					goto point2;
			}
			else
				goto point1;
	while (a[i] >= '0' && a[i] <= '9')
	{
		c = 10 * c + a[i];
		i++;
	}
point1:
point2:
	switch (a[i])
	{
	case '+':
	{
		for (int k = 0; k < n - 3; i++)
			b[k] = a[i + 1];
		e = new Add(new Variable(a[i - 1]), read_expression(b));
		break;
	}
	case '-':
	{
		for (int k = 0; k < n - 3; i++)
			b[k] = a[i + 1];
		e = new Sub(new Variable(a[i - 1]), read_expression(b));
		break;
	}
	case'*':
	{
		for (int k = 0; k < n - 3; i++)
			b[k] = a[i + 1];
		e = new Mul(new Variable(a[i - 1]), read_expression(b));
		break;
	}
	case '/':
	{
		for (int k = 0; k < n - 3; i++)
			b[k] = a[i + 1];
		e = new Div(new Variable(a[i - 1]), read_expression(b));
		break;
	}
	case ')':
	{
		e = new Variable(a[i - 1]);
		break;
	}
	default:
		cout << "error" << endl;
		exit(1);
	}
	return e;
}

void main() {
	char x = 'y';
	/*Expression *e = (Expression*)new Add((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e1 = (Expression*)new Sub((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e2 = (Expression*)new Mul((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e3 = (Expression*)new Div((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e4 = (Expression*)new Sin((Expression*)new Variable(x));*/
	Expression *e5 = read_expression("((x+1)*x)");
	e5->print();
	/*e->print();
	cout << "\n";
	e1->print();
	cout << "\n";
	e2->print();
	cout << "\n";
	e3->print();
	cout << "\n";
	e4->print();
	cout << "\n";
	Expression *de = e->diff();
	Expression *de1 = e1->diff();
	Expression *de2 = e2->diff();
	Expression *de3 = e3->diff();
	Expression *de4 = e4->diff();
	cout << "\n";
	de->print();
	cout << "\n";
	de1->print();
	cout << "\n";
	de2->print();
	cout << "\n";
	de3->print();
	cout << "\n";
	de4->print();
	cout << "\n";
	free(e);
	free(de);*/
	system("pause");
}
