#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;
int main()
{
	double A[105][105] = { 0 };
	double b[105] = { 0 };
	double n = 100;
	int column = 10, row = 10;
	double k = 80;
	double h = 20000;
	double q = 2000000000;
	double t_f = 300, t_s = 500;

	double delta_x = 0.005 / column;
	double delta_y = 0.02 / row;
	int i, j;
	//area1-center
	for (i = 1; i < (row - 1); i++)
	{
		for (j = 2; j < column; j++)
		{
			A[10 * i + j][10 * i + j] = 2 * k * (1 / pow(delta_x, 2.0) + 1 / pow(delta_y, 2.0));
			A[10 * i + j][10 * i + j - 1] = -k / pow(delta_y, 2.0);
			A[10 * i + j][10 * i + j + 1] = -k / pow(delta_y, 2.0);
			A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_x, 2.0);
			A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_x, 2.0);
			b[10 * i + j] = q;
		}
	}
	//area2-top
	for (j = 2; j < column; j++)
	{
		i = 0;
		//가장 위의 온도를 구하기 때문에 i=0 으로 고정
		A[10 * i + j][10 * i + j] = 2 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[10 * i + j][10 * i + j - 1] = -k / pow(delta_x, 2.0);
		A[10 * i + j][10 * i + j + 1] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_y, 2.0);
		b[10 * i + j] = q + 2 * k*h * t_f / pow(delta_y, 2.0)*h + 2 * k*delta_y;
	}
	//area3-bottom
	for (j = 2; j < column; j++)
	{
		//가장 아래의 온도를 구하기 때문에 i=(row-1) 로 고정
		i = row - 1;
		A[10 * i + j][10 * i + j] = (2 * k / pow(delta_x, 2.0)) + (k / pow(delta_y, 2.0)) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[10 * i + j][10 * i + j - 1] = -k / pow(delta_x, 2.0);
		A[10 * i + j][10 * i + j + 1] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_y, 2.0);
		b[10 * i + j] = q + 2 * k*h * t_f / pow(delta_y, 2.0)*h + 2 * k*delta_y;
	}
	//area4-right
	for (i = 0; i < row; i++)
	{
		j = column;
		A[10 * i + j][10 * i + j] = 2 * k / pow(delta_y, 2.0) + k / pow(delta_x, 2.0) + 2 * k*h / (pow(delta_x, 2.0)*h + 2 * k*delta_x);
		A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * i + (j - 1)] = -k / pow(delta_x, 2.0);
		b[10 * i + j] = q + (2 * k*h * t_f / (h*pow(delta_x, 2.0) + 2 * k*delta_x));
	}
	//area5-left
	for (i = 1; i < (row - 1); i++)
	{
		j = 1;
		A[10 * i + j][10 * i + j] = (3 * k / pow(delta_x, 2.0)) + (2 * k / pow(delta_y, 2.0));
		A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_y, 2.0);
		A[10 * i + j][10 * i + (j + 1)] = -k / pow(delta_x, 2.0);
		b[10 * i + j] = q + (t_s * 2 * k / pow(delta_x, 2.0));
	}
	//area6-top & left
	i = 0;
	j = 1;
	A[10 * i + j][10 * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[10 * i + j][10 * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[10 * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*h*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);

	//area7-bottom & left
	i = row - 1;
	j = 1;
	A[10 * i + j][10 * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[10 * i + j][10 * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[10 * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*h*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);

	//area8-top & right
	i = 0;
	j = column;
	A[10 * i + j][10 * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h*(1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	A[10 * i + j][10 * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[10 * i + j][10 * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[10 * i + j] = q + 2 * k*h * t_f * (1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x));

	//area9-bottom & right
	i = row - 1;
	j = column;
	A[10 * i + j][10 * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + 2 * k*h*((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	A[10 * i + j][10 * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[10 * i + j][10 * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[10 * i + j] = q + 2 * k*h * t_f * ((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
		//fout << setw(8) << A[i][j];
			cout << setw(8) << A[i][j];
		}
		cout << endl;
	}
	for (i = 1; i < n + 1; i++)
	{
		cout << b[i] << endl;
	}
	return 0;
}