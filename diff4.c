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
	Number(string a)
	{
		char * b;
		b = (char*)calloc(10, sizeof(char));
		data = atof(strcpy(b, a.c_str()));
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
		//e1 = a1->copy();
		//e2 = a2->copy();
		this->e1 = a1;
		this->e2 = a2;
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
Expression * read_expression(string s)
{
	if (s[0] == '(')
	{
		int vlozhennost = 0;
		int i = 0;
		while (true)
		{
			i++;
			if (s[i] == '(') vlozhennost++;
			else if (s[i] == ')') vlozhennost--;
			if (vlozhennost == 0)
			{
				int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
				if (s[i] == ')')
				{
					pos1 = 1;
					pos2 = i;
					pos3 = i + 2;
					pos4 = s.length() - 2;
				}
				else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == ' / ')
				{
					//первая часть является константой или переменной
					pos1 = 1;
					pos2 = i - 1;
					pos3 = i + 1;
					pos4 = s.length() - 2;
					i--;
				}
				else continue;
				string s1 = s.substr(pos1, pos2 - pos1 + 1);
				string s2 = s.substr(pos3, pos4 - pos3 + 1);
				Expression* e1 = read_expression(s1);
				Expression* e2 = read_expression(s2);
				switch (s[i + 1]) {
				case '+': return new Add(e1, e2);
				case '-': return new Sub(e1, e2);
				case '*': return new Mul(e1, e2);
				case '/': return new Div(e1, e2);
				}
			}
		}
	}
	int kk = 1;
	if (int(s.find("-")) != -1)
		kk = -1;
	if (int(s.find("cos")) != -1)
	{
		if (kk == 1)
		{
			string s1 = s.substr(4, s.length() - 3);
			Expression* e1 = new Cos(read_expression(s1));
			return e1;
		}
		else
		{
			string s1 = s.substr(5, s.length() - 3);
			Expression* e = new Cos(read_expression(s1));
			Expression* e0 = new Number(-1);
			Expression* e4 = new Mul(e0, e);
			return e4;
		}
	}
	else if (int(s.find("sin")) != -1)
	{
		if (kk == 1)
		{
			string s1 = s.substr(4, s.length() - 3);
			Expression* e1 = new Sin(read_expression(s1));
			return e1;
		}
		else
		{
			string s1 = s.substr(5, s.length() - 3);
			Expression* e = new Sin(read_expression(s1));
			Expression* e0 = new Number(-1);
			Expression* e4 = new Mul(e0, e);
			return e4;
		}
	}
	if (s.front() >= '0' && s.front() <= '9')
		if (kk == 1)
		{
		Expression* e1 = new Number(s);
		return e1;
		}
		else
		{
			Expression* e1 = new Number('-' + s);
			return e1;
		}
	else if (s.front() >= 'a' && s.front() <= 'z')
		if (kk == 1)
		{
		Expression* e1 = new Variable(s.front());
		return e1;
		}
		else
		{
			Expression* e = new Variable(s.front());
			Expression* e0 = new Number(-1);
			Expression* e1 = new Mul(e0, e);
			return e1;
		}
	else
	{
		cout << "error" << endl;
		exit(1);
	}
}
void main() {
	char x = 'y';
	/*Expression *e = (Expression*)new Add((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e1 = (Expression*)new Sub((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e2 = (Expression*)new Mul((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e3 = (Expression*)new Div((Expression*)new Number(1), (Expression*)new Variable(x));
	Expression *e4 = (Expression*)new Sin((Expression*)new Variable(x));*/
	Expression *e5 = read_expression("((x+1)*x)");
	Expression *de = e5->diff();
	//e5->print();
	de->print();
	file
	fout<< 
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
