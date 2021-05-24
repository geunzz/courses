#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;
void area(double A[105][105], double b[101], int n, int row, int column)
{
	double k = 80;//(W/m*K)
	double h = 20000;//(W/m^2)
	double q = 2000000000;//(W/m^3)
	double t_f = 300, t_s = 500;//(kelvin)
	//t_f=temperature of fluid, t_s=temperature of surface(wall)
	double delta_x = 0.005 / column;
	double delta_y = 0.02 / row;
	int i, j;
	//area1-center
	for (i = 1; i < (row - 1); i++)
	{//i=row 
		for (j = 2; j < column; j++)
		{   //j=column
			A[column * i + j][column * i + j] = 2 * k * (1 / pow(delta_x, 2.0) + 1 / pow(delta_y, 2.0));
			A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
			A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
			A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
			A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
			b[column * i + j] = q;
			//mesh�� �� �ֺ��� �ִ� 4��(�߽��̹Ƿ�)�� mesh�� ���� coefficient�� ���
			//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����
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
		//mesh�� �� �ֺ��� �ִ� 3��(���κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
		//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����
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
		//mesh�� �� �ֺ��� �ִ� 3��(�Ʒ��κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
		//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����
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
		//mesh�� �� �ֺ��� �ִ� 3��(�����ʺκ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
		//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����
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
		//mesh�� �� �ֺ��� �ִ� 3��(���ʺκ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
		//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����
	}
	//area6-top & left
	i = 0;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);
	//mesh�� �� �ֺ��� �ִ� 2��(�𼭸��κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
	//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����

	//area7-bottom & left
	i = row - 1;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);
	//mesh�� �� �ֺ��� �ִ� 2��(�𼭸��κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
	//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����

	//area8-top & right
	i = 0;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (2 * k*h / (pow(delta_x, 2.0)*h + 2 * k*delta_x));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * (1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x));
	//mesh�� �� �ֺ��� �ִ� 2��(�𼭸��κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
	//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����

	//area9-bottom & right
	i = row - 1;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + 2 * k*h*((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * ((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	//mesh�� �� �ֺ��� �ִ� 2��(�𼭸��κ��̹Ƿ�)�� mesh�� ���� coefficient�� ���
	//A����� [�ش�mesh][�ֺ�mesh]�׿� ������ ����

}
int main()
{
	fstream fout("result.txt");
	cout.setf(ios::fixed);
	cout.precision(15);
	int i, j, m, n, o,row, column;//n=size of matrix
	double A[105][105] = { 0 }, b[105] = { 0 }, A_s[105][105] = { 0 }, b_s[105] = { 0 };
	//A,b : calculated by upper function
	//A_s, b_s :scaled A and b matrix
	double B[105][105] = { 0 }, x[105] = { 0 }, Bx[105] = { 0 }, temp[105] = { 0 }, ea[105] = { 10 }, sum, es;
	cout << "please put in number of rows" << endl;
	cin >> row;
	cout << "please put in number of columns" << endl;
	cin >> column;
	cout << "please input your desired sginificant number" << endl;
	cin >> o;//error criteria�� ����ϱ� ���� ����
	es = 0.5*pow(10, 2 - o);
	cout << endl;
	n = row*column;
	area(A, b, n, row, column);
	//A��İ� b��� diagonally scaling
	//LU decomposition���� �ٸ� scaling ���
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			A_s[i][j] = A[i][j] / A[i][i];
			b_s[i] = b[i] / A[i][i];
		}
	}
//scaled�� A��� A_s�κ��� B��� ���
//A_s=[B]+[I]
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (i == j)//A_s�� diagonal���� ���� �������°��� B�̹Ƿ� i=j�̸� 0�Է�
			{
				B[i][j] = 0;
			}
			else//���������� A_s�� ������
			{
				B[i][j] = A_s[i][j];
			}
		}
	}
	double largest_ea = 1;
	//�Ʒ� for�������� ������ �� �ֵ��� smallest_ea���� es���� ū ��(1)���� ����
	for (m = 1; es < largest_ea; m++)
	{	
		//�� mesh�� approximation error�� ��հ��� �����Ͽ� es���� ����
		//[B]*{x}_i��� ���
		for (i = 1; i < n + 1; i++)
		{
			sum = 0;
			for (j = 1; j < n + 1; j++)
			{
				sum = sum + B[i][j] * x[j];
			}
			Bx[i] = sum;
		}
		//{b_s}-[B]*{x}_i����Ͽ� x�� �Է�
		for (i = 1; i < n + 1; i++)
		{
			temp[i] = x[i];//approximation error�� ����ϱ� ���� ������ soluton�� temp�� ����
			x[i] = b_s[i] - Bx[i];
		}
		for (i = 1; i < n + 1; i++)
		{
			ea[i] = (x[i] - temp[i]) * 100 / x[i];//���� solution�� ���� solution�� �̿��Ͽ� ea��� ����
		}
		//������ approximation error�߿��� ���� ���� ���� ����
		//������ ���� smallest_ea�� ����
		largest_ea = ea[1];
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
		cout << "approximation error of T[" << i << "] : " << ea[i] << " %" << endl;
		fout << "approximation error of T[" << i << "] : " << ea[i] << " %" << endl;
	}
	cout.setf(ios::fixed);
	cout.precision(3);
	//�ش�� iteration Ƚ���� ���� mesh ������ �µ����� ���
	cout << endl;
	cout << "[temperature of each mesh element]" << endl << endl;
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
	cout << "[Jacobi method]" << endl << endl;
	cout << "�ŷ��� �� �ִ� ��ȿ������ ���� " << o << "��° �����̸�" << endl;
	cout << "�̶� �ʿ��� iteraion Ƚ���� " << m << "ȸ �Դϴ�." << endl << endl;
	fout << largest_ea << endl;
	fout << "[Jacobi method]" << endl << endl;
	fout << "�ŷ��� �� �ִ� ��ȿ������ ���� " << o << "��° �����̸�" << endl;
	fout << "�̶� �ʿ��� iteraion Ƚ���� " << m << "ȸ �Դϴ�." << endl << endl;
	return 0;
}