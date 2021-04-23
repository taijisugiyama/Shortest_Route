#include<iostream>
#include<string>
#include<list>
#include<iomanip>
using namespace std;
#include<fstream>
class wghtgraph
{
public:
	double **parent;
	int k;
	list<double> *p;
	string *city;
	double **M;
	int size;
	wghtgraph()
	{
		size = 0;
	}
	void matrixform()
	{
		fstream input;
		input.open("map.txt");
		if (!input)
		{
			cout << "ERROR the file not found" << endl;
			return;
		}
		input >> size;
		city = new string[size];
		M = new double *[size];
		for (int i = 0; i < size; i++)
		{
			M[i] = new double[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i != j)
					M[i][j] = INFINITY;
				else if (i == j)
					M[i][j] = 0;
			}
		}
		double  wght;
		char check;
		int vertex=0,adjvertex;
		while (!input.eof())
		{
			input.ignore();
			getline(input, city[vertex], '\t');
			input >> adjvertex;
			if (adjvertex != -999)
				input >> wght;
			while (adjvertex != -999)
			{
				M[vertex][adjvertex] = wght;
				input >> adjvertex;
				if (adjvertex != -999)
					input >> wght;
			}
			vertex++;
			check = input.peek();
			if (check == ' ')
				input.ignore();
		}
	}

	void shortestpath()
	{
		double **Dummy;
		Dummy = new double *[size];
		for (int i = 0; i < size; i++)
			Dummy[i] = new double [size];
		parent = new double *[size];
		for (int i = 0; i < size; i++)
			parent[i] = new double[size];
		for (int i = 0; i < size;i++)
		for (int j = 0; j < size; j++)
		{
			parent[i][j] = 0;
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				Dummy[i][j] = M[i][j];
		}
		for (int k = 0; k < size;k++)
		for (int i = 0; i < size;i++)
		for (int j = 0; j < size; j++)
		{
			if (Dummy[i][j]>Dummy[i][k] + Dummy[k][j])
			{
				Dummy[i][j] = Dummy[i][k] + Dummy[k][j];
				parent[i][j] = k;
			}
		}
		string city1, city2;
		int numi, numj;
		cout << "Enter your start point (city)" << endl;
		cin >> city1;
		numi = translator(city1);
		cout << "Enter your destination" << endl;
		cin >> city2;
		numj = translator(city2);
		cout << "Your minimum distance " << Dummy[numi][numj] <<"km"<< endl;
		cout << "YOUR PATH  " << endl;
		path(numi, numj);
	}
	void path(int i,int j)
	{

		k = parent[i][j];
		if (k == 0)
			return;
		path(i, k);
			cout <<city[k] << "->";
	// 	path(k, j);
	}
	int translator(string city3)
	{
		while (1)
		{
			for (int i = 0; i < size; i++)
			{
				if (city[i] == city3)
				{
					return i;
				}
			}
			cout << "City not found enter again" << endl;
			cin >> city3;
		}
	}
	void display(double **M)
	{
		cout << "   ";
		for (int i = 0; i < size; i++)
		{
			cout << i << "  ";
		}
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i << "  ";
			for (int l = 0; l < size; l++)
			{
				cout << M[i][l] << "  ";
			}
			cout << endl;
		}
	}

};
void main()
	{
		wghtgraph obj;
		int num;
		obj.matrixform();
				obj.shortestpath();
				cout << endl;
}