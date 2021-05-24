#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;
void area(double A[105][105], double b[101], int n, int row, int column)
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
	fstream fout("result.txt");
	cout.setf(ios::fixed);
	cout.precision(15);
	int row, column;
	int i, j, k, n, m, o;
	double x[105] = { 0 }, A[105][105] = { 0 }, L[105][105] = { 0 }, b[105] = { 0 }, s[105] = { 0 }, A_s[105][105] = { 0 }, b_s[105] = { 0 };
	//x[n] : solution
	//A,b : system matrix
	//A_s : scailed A
	//b_s : scailed b
	double Z[105][105] = {}, U[105][105] = { 0 }, Ux[105], bUx[105], suml, sum, iminus, temp[105], ea[105] = { 100 }, es;
	//Z : inverse of [L+I]
	//U : upper matrix of A_s
	//L : lower matrix of A_s
	cout << "please put in number of rows" << endl;
	cin >> row;
	cout << "please put in number of columns" << endl;
	cin >> column;
	cout << "please input your desired sginificant number" << endl;
	cin >> o;//error criteria�� ����ϱ� ���� ����
	es = 0.5*pow(10, 2 - o);
	cout << endl;
	n = row*column;
	cout << endl;
	area(A, b, n, row, column);
	//A��İ� b��� scaling
	//LU decomposition���� �ٸ� scaling ���
	//diagonal element�� scaling
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			A_s[i][j] = A[i][j] / A[i][i];
			b_s[i] = b[i] / A[i][i];
		}
	}
	//[L+I]��� ����, ���ǻ� L��ķ� ǥ��
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (i == j)
			{
				L[i][j] = 1;
			}
			else if (i > j)
			{
				L[i][j] = A_s[i][j];
			}
	//L����� �ʱ⿡ 0���� �����Ǿ��ֱ� ������ ���� 0���� ���� ����
		}
	}
	cout << endl;

	//L+i�� ����� Z�� ���
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (i == j)
			{
				Z[i][j] = 1;//determinant�� 1�̹Ƿ� 1/det(L+i)�� 1�̵�
			}
			else if (i < j)
			{
				Z[i][j] = 0.0;
			}
		}
	}
	for (j = 1; j < n + 1; j++)
	{
		for (i = 1; i < n + 1; i++)
		{
			if (i > j)
			{
				suml = 0.0;
				iminus = i - 1;
				for (k = 1; k < iminus + 1; k++)
				{
					suml = suml + L[i][k] * Z[k][j];
				}
				Z[i][j] = -1*(suml / L[i][i]);
			}
		}
	}
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (i == j || i > j)
			{
				U[i][j] = 0;
			}
			else if (i < j)
			{
				U[i][j] = A_s[i][j];
			}
		}
	}
	//m�� ���� iteration Ƚ���� ����
	double largest_ea = 1;
	//�Ʒ� for�������� ������ �� �ֵ��� smallest_ea���� es���� ū ��(1)���� ����
	for (m = 1; es < largest_ea; m++)
	{
		//[U]*{x}���
		for (i = 1; i < n + 1; i++)
		{
			sum = 0;
			for (j = 1; j < n + 1; j++)
			{
				sum = sum + U[i][j] * x[j];
				//cout << Ux[m][j] << endl;
			}
			Ux[i] = sum;
		}

		//{b_s}-[u]*{x}���
		for (i = 1; i < n + 1; i++)
		{
			bUx[i] = b_s[i] - Ux[i];
		}
		//([I]+[L])�� ����� * [{b_s}-[u]*{x}]���
		for (i = 1; i < n + 1; i++)
		{
			sum = 0;
			temp[i] = x[i];
			for (j = 1; j < n + 1; j++)
			{
				sum = sum + Z[i][j] * bUx[j];
			}
			x[i] = sum;
		}
		//approximation error�� ���
		for (i = 1; i < n + 1; i++)
		{
			ea[i] = (x[i] - temp[i]) * 100 / x[i];
		}
		//������ approximation error�߿��� ���� ���� ���� ����
		//������ ���� smallest_ea�� ����
		largest_ea =ea[1];
		for (i = 1; i < n + 1; i++)
		{
			if (ea[i] > largest_ea)
			{
				largest_ea = ea[i];
			}
		}
	}
	//iteration�� ���� �� mesh�� �µ��� ��� �� ���
	//es>average ea�� �����ϴ� iteration Ƚ���� ���� approximation error�� ���
	for (i = 1; i < n + 1; i++)
	{
		cout << "approximation error of T[" << i << "] : " << ea[i] << " %"<<endl;
		fout << "approximation error of T[" << i << "] : " << ea[i] << " %" << endl;
	}
	cout.setf(ios::fixed);
	cout.precision(3);
	cout << endl;
	cout << "[temperature of each mesh element]" << endl << endl;
	//�ش�� iteration Ƚ���� ���� mesh ������ �µ����� ���
	for (i = 1; i < n + 1; i++)
	{
		cout << setw(9) << x[i];
		fout << setw(9) << x[i];
		if (i%column == 0)
		{
			cout << endl;
			fout << endl;
		}
	}
	cout << endl;
	cout << "[Gauss-seidel method]" << endl << endl;
	cout << "�ŷ��� �� �ִ� ��ȿ������ ���� " << o << "��° �����̸�" << endl;
	cout << "�̶� �ʿ��� iteration Ƚ���� " << m << "ȸ �Դϴ�." << endl << endl;
	fout << "[Gauss-seidel method]" << endl << endl;
	fout << "�ŷ��� �� �ִ� ��ȿ������ ���� " << o << "��° �����̸�" << endl;
	fout << "�̶� �ʿ��� iteraion Ƚ���� " << m << "ȸ �Դϴ�." << endl << endl;
	return 0;
}