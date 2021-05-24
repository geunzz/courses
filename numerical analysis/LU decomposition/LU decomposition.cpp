#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
void area(double A[105][105], double b[105], int n, int row, int column)
{
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
			A[column * i + j][column * i + j] = 2 * k * (1 / pow(delta_x, 2.0) + 1 / pow(delta_y, 2.0));
			A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
			A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
			A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
			A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
			b[column * i + j] = q;
		}
	}
	//area2-top
	for (j = 2; j < column; j++)
	{
		i = 0;
		//���� ���� �µ��� ���ϱ� ������ i=0 ���� ����
		A[column * i + j][column * i + j] = 2 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
		b[column * i + j] = q + ((2 * k*h * t_f) / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	}
	//area3-bottom
	for (j = 2; j < column; j++)
	{
		//���� �Ʒ��� �µ��� ���ϱ� ������ i=(row-1) �� ����
		i = row - 1;
		A[column * i + j][column * i + j] = (2 * k / pow(delta_x, 2.0)) + (k / pow(delta_y, 2.0)) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
		b[column * i + j] = q + (2 * k*h * t_f) / (pow(delta_y, 2.0)*h + 2 * k*delta_y);
	}
	//area4-right
	for (i = 0; i < row; i++)
	{
		j = column;
		A[column * i + j][column * i + j] = 2 * k / pow(delta_y, 2.0) + k / pow(delta_x, 2.0) + 2 * k*h / (pow(delta_x, 2.0)*h + 2 * k*delta_x);
		A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
		A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
		A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
		b[column * i + j] = q + (2 * k*h * t_f / (h*pow(delta_x, 2.0) + 2 * k*delta_x));
	}
	//area5-left
	for (i = 1; i < (row - 1); i++)
	{
		j = 1;
		A[column * i + j][column * i + j] = (3 * k / pow(delta_x, 2.0)) + (2 * k / pow(delta_y, 2.0));
		A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
		A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
		A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
		b[column * i + j] = q + (t_s * 2 * k / pow(delta_x, 2.0));
	}
	//area6-top & left
	i = 0;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);

	//area7-bottom & left
	i = row - 1;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);

	//area8-top & right
	i = 0;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (2 * k*h / (pow(delta_x, 2.0)*h + 2 * k*delta_x));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * (1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x));

	//area9-bottom & right
	i = row - 1;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + 2 * k*h*((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * ((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));

}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(3);
	int i, j, k, n, q;
	int row;
	int column;
	double A[105][105] = { 0 }, b[105] = { 0 }, s[105] = { 0 }, x[105], factor, sum, er = 0, tol = 0.000000001;
	cout << "please put in number of rows" << endl;
	cin >> row;
	cout << endl;
	cout << "please put in number of columns" << endl;
	cin >> column;
	cout << endl;
	n = row*column;
	cout << endl;
	area(A, b, n, row, column);

	for (k = 1; k < n; k++)//n-1�ױ��� elimination
	{
		//scaling : ��ü ������ �� �� ����� ������ ���� s�� ����
		for (i = 1; i < n + 1; i++)
		{
			s[i] = abs(A[i][i]);
			for (j = 2; j < n + 1; j++)
			{
				if (abs(A[i][j]) > s[i])
				{
					s[i] = abs(A[i][j]);
				}
			}
		}

		//pivot : ������ s���� �̿��Ͽ� pivot
		double big, dummy;
		int ii, p;
		p = k;
		big = abs(A[k][k]) / s[k];
		for (ii = k + 1; ii < n + 1; ii++)
		{
			dummy = abs(A[ii][k] / s[ii]);
			if (dummy > big)
			{
				big = dummy;
				p = ii;
				if (p != k)
				{
					for (q = k; q < n + 1; q++)
					{
						dummy = A[k][q];
						A[k][q] = A[p][q];
						A[p][q] = dummy;
					}
					dummy = b[k];
					b[k] = b[p];
					b[p] = dummy;

					dummy = s[k];
					s[k] = s[p];
					s[p] = dummy;
				}
			}
		}
		if (abs(A[k][k] / s[k]) < tol)
			//diagonal�� tol(0�� �ſ� ����� ����)���� ���� ��� singular matrix�̹Ƿ� ������ ��������
		{
			er = -1;
			cout << "sigular matrix : A_" << k << k << "  value is :" << A[k][k] / s[k] << endl;
			break;
		}
		for (i = k + 1; i < n + 1; i++)
		{
			factor = A[i][k] / A[k][k];
			A[i][k] = factor;
			//cout << "factor:" << factor;
			for (j = k + 1; j < n + 1; j++)
			{
				A[i][j] = A[i][j] - factor*A[k][j];
			}
		}
		if (abs(A[k][k] / s[k]) < tol)
		{
			er = -1;
		}
	}
	//er=-1�� �ƴ� ���(singular matrix�� �ƴѰ��) substitute�� ����
	if (er != -1)
	{
		//forward substitute
		for (i = 2; i < n + 1; i++)
		{
			sum = b[i];
			for (j = 1; j < i; j++)
			{
				sum = sum - A[i][j] * b[j];
			}
			b[i] = sum;
		}
		//backward substitute
		x[n] = (b[n] / A[n][n]);
		for (i = n - 1; i > 0; i--)
		{
			sum = 0;
			for (j = i + 1; j < n + 1; j++)
			{
				sum = sum + A[i][j] * x[j];
			}
			x[i] = (b[i] - sum) / A[i][i];
		}
	}
			else//er=-1�� ��� (singular matrix�� ���) substitute�� �������� ����
			{
				cout << "singular matrix" << endl;
			}

	//x(solution)���
	cout << "[temperature of each mesh element]" << endl << endl;

	for (i = 1; i < n + 1; i++)
	{			
		cout << setw(9) << x[i];
		if (i%column == 0)
			{
			cout << endl;
		}
	}
	cout << endl;
		return 0;
	}
