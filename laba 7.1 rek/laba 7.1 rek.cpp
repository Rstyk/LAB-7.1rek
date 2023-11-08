#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** a, const int rowCount, const int colCount, int i, int j);
void Sort(int** a, const int rowCount, const int colCount, int j0, int j1);
void Change(int** a, const int row1, const int row2, const int colCount, int i);
void Calc(int** a, const int rowCount, const int colCount, int i, int j, int& S, int& k);

int main()
{
	srand((unsigned)time(NULL));
	int Low = -8;
	int High = 42;
	int rowCount = 8;
	int colCount = 7;

	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];

	Create(a, rowCount, colCount, Low, High, 0, 0);
	Print(a, rowCount, colCount, 0, 0);

	Sort(a, rowCount, colCount, 0, 0);
	Print(a, rowCount, colCount, 0, 0);

	int S = 0;
	int k = 0;
	Calc(a, rowCount, colCount, 0, 0, S, k);
	cout << "S = " << S << endl;
	cout << "k = " << k << endl;
	Print(a, rowCount, colCount, 0, 0);

	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);
	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
		if (i < rowCount - 1)
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl << endl;
}

void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
	if ((a[i1][0] > a[i1 + 1][0])
		||
		(a[i1][0] == a[i1 + 1][0] &&
			a[i1][0] > a[i1 + 1][1])
		||
		(a[i1][0] == a[i1 + 1][0] &&
			a[i1][1] == a[i1 + 1][1] &&
			a[i1][2] < a[i1 + 1][2]))
		Change(a, i1, i1 + 1, colCount, 0);

	if (i1 < colCount - 2)
		Sort(a, rowCount, colCount, i0, i1 + 1);
	else
		if (i0 < colCount - 2)
			Sort(a, rowCount, colCount, i0 + 1, 0);
}

void Change(int** a, const int col1, const int col2, const int rowCount, int i)
{
	if (i == rowCount)
	{
		return;
	}
	int tmp = a[i][col1];
	a[i][col1] = a[i][col2];
	a[i][col2] = tmp;

	Change(a, col1, col2, rowCount, i + 1);
}

void Calc(int** a, const int rowCount, const int colCount, int i, int j, int& S, int& k)
{
	if (a[i][j] > 0 || !(i % 2 == 0 && j % 2 == 0))
	{
		S += a[i][j];
		k++;
		a[i][j] = 0;
	}
	if (j < colCount - 1)
		Calc(a, rowCount, colCount, i, j + 1, S, k);
	else
		if (i < rowCount - 1)
			Calc(a, rowCount, colCount, i + 1, 0, S, k);
}
