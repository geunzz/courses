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
			//mesh와 그 주변에 있는 4개(중심이므로)의 mesh에 대한 coefficient를 계산
			//A행렬의 [해당mesh][주변mesh]항에 각각을 저장
		}
	}
	//area2-top
	for (j = 2; j < column; j++)
	{
		i = 0;
		//가장 위의 온도를 구하기 때문에 i=0 으로 고정
		A[column * i + j][column * i + j] = 2 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
		b[column * i + j] = q + ((2 * k*h * t_f) / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		//mesh와 그 주변에 있는 3개(윗부분이므로)의 mesh에 대한 coefficient를 계산
		//A행렬의 [해당mesh][주변mesh]항에 각각을 저장
	}
	//area3-bottom
	for (j = 2; j < column; j++)
	{
		//가장 아래의 온도를 구하기 때문에 i=(row-1) 로 고정
		i = row - 1;
		A[column * i + j][column * i + j] = (2 * k / pow(delta_x, 2.0)) + (k / pow(delta_y, 2.0)) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
		A[column * i + j][column * i + j - 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * i + j + 1] = -k / pow(delta_x, 2.0);
		A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
		b[column * i + j] = q + (2 * k*h * t_f) / (pow(delta_y, 2.0)*h + 2 * k*delta_y);
		//mesh와 그 주변에 있는 3개(아랫부분이므로)의 mesh에 대한 coefficient를 계산
		//A행렬의 [해당mesh][주변mesh]항에 각각을 저장
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
		//mesh와 그 주변에 있는 3개(오른쪽부분이므로)의 mesh에 대한 coefficient를 계산
		//A행렬의 [해당mesh][주변mesh]항에 각각을 저장
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
		//mesh와 그 주변에 있는 3개(왼쪽부분이므로)의 mesh에 대한 coefficient를 계산
		//A행렬의 [해당mesh][주변mesh]항에 각각을 저장
	}
	//area6-top & left
	i = 0;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);
	//mesh와 그 주변에 있는 2개(모서리부분이므로)의 mesh에 대한 coefficient를 계산
	//A행렬의 [해당mesh][주변mesh]항에 각각을 저장

	//area7-bottom & left
	i = row - 1;
	j = 1;
	A[column * i + j][column * i + j] = 3 * k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j + 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 2 * t_s * k / pow(delta_x, 2.0);
	//mesh와 그 주변에 있는 2개(모서리부분이므로)의 mesh에 대한 coefficient를 계산
	//A행렬의 [해당mesh][주변mesh]항에 각각을 저장

	//area8-top & right
	i = 0;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + (2 * k*h / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (2 * k*h / (pow(delta_x, 2.0)*h + 2 * k*delta_x));
	A[column * i + j][column * (i + 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * (1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y) + 1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x));
	//mesh와 그 주변에 있는 2개(모서리부분이므로)의 mesh에 대한 coefficient를 계산
	//A행렬의 [해당mesh][주변mesh]항에 각각을 저장

	//area9-bottom & right
	i = row - 1;
	j = column;
	A[column * i + j][column * i + j] = k / pow(delta_x, 2.0) + k / pow(delta_y, 2.0) + 2 * k*h*((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	A[column * i + j][column * (i - 1) + j] = -k / pow(delta_y, 2.0);
	A[column * i + j][column * i + (j - 1)] = -k / pow(delta_x, 2.0);
	b[column * i + j] = q + 2 * k*h * t_f * ((1 / (pow(delta_y, 2.0)*h + 2 * k*delta_y)) + (1 / (pow(delta_x, 2.0)*h + 2 * k*delta_x)));
	//mesh와 그 주변에 있는 2개(모서리부분이므로)의 mesh에 대한 coefficient를 계산
	//A행렬의 [해당mesh][주변mesh]항에 각각을 저장

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
	cin >> o;//error criteria를 계산하기 위한 숫자
	es = 0.5*pow(10, 2 - o);
	cout << endl;
	n = row*column;
	area(A, b, n, row, column);
	//A행렬과 b행렬 diagonally scaling
	//LU decomposition과는 다른 scaling 방법
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			A_s[i][j] = A[i][j] / A[i][i];
			b_s[i] = b[i] / A[i][i];
		}
	}
//scaled된 A행렬 A_s로부터 B행렬 계산
//A_s=[B]+[I]
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			if (i == j)//A_s의 diagonal항의 값이 빠져나온것이 B이므로 i=j이면 0입력
			{
				B[i][j] = 0;
			}
			else//나머지항은 A_s와 동일함
			{
				B[i][j] = A_s[i][j];
			}
		}
	}
	double largest_ea = 1;
	//아래 for구문으로 진입할 수 있도록 smallest_ea값을 es보다 큰 값(1)으로 설정
	for (m = 1; es < largest_ea; m++)
	{	
		//각 mesh의 approximation error의 평균값을 적용하여 es값과 비교함
		//[B]*{x}_i행렬 계산
		for (i = 1; i < n + 1; i++)
		{
			sum = 0;
			for (j = 1; j < n + 1; j++)
			{
				sum = sum + B[i][j] * x[j];
			}
			Bx[i] = sum;
		}
		//{b_s}-[B]*{x}_i계산하여 x에 입력
		for (i = 1; i < n + 1; i++)
		{
			temp[i] = x[i];//approximation error를 계산하기 위해 이전의 soluton을 temp에 저장
			x[i] = b_s[i] - Bx[i];
		}
		for (i = 1; i < n + 1; i++)
		{
			ea[i] = (x[i] - temp[i]) * 100 / x[i];//이전 solution과 이후 solution을 이용하여 ea계산 저장
		}
		//구해진 approximation error중에서 가장 작은 값을 선정
		//선정된 값을 smallest_ea로 대입
		largest_ea = ea[1];
		for (i = 1; i < n + 1; i++)
		{
			if (ea[i] > largest_ea)
			{
				largest_ea = ea[i];
			}
		}
	}
	//iteration에 따른 각 mesh의 온도값 계산 및 출력
	//es>average ea를 만족하는 iteration 횟수에 대한 approximation error를 출력
	for (i = 1; i < n + 1; i++)
	{
		cout << "approximation error of T[" << i << "] : " << ea[i] << " %" << endl;
		fout << "approximation error of T[" << i << "] : " << ea[i] << " %" << endl;
	}
	cout.setf(ios::fixed);
	cout.precision(3);
	//해당된 iteration 횟수에 대한 mesh 각각의 온도값을 출력
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
	cout << "신뢰할 수 있는 유효숫자의 수는 " << o << "번째 까지이며" << endl;
	cout << "이때 필요한 iteraion 횟수는 " << m << "회 입니다." << endl << endl;
	fout << largest_ea << endl;
	fout << "[Jacobi method]" << endl << endl;
	fout << "신뢰할 수 있는 유효숫자의 수는 " << o << "번째 까지이며" << endl;
	fout << "이때 필요한 iteraion 횟수는 " << m << "회 입니다." << endl << endl;
	return 0;
}