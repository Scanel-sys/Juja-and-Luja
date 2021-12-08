#include <stdio.h>

void Luja(int *luja_size, int luja[][100], int luja_marks[][100], int x, int y);

int main()
{
	int Luja_hights[100][100];
	int Luja_marks[100][100];
	int n;
	scanf_s("%d", &n);

	//getting hights in array
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &Luja_hights[i][j]);
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			Luja_marks[i][j] = 0;


	Luja(&n, Luja_hights, Luja_marks, 0, 0);

	//printing marks of Luja_marks
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("  %d  ",Luja_marks[i][j]);
		}
		printf("\n");
	}
	



}

void Luja(int *luja_size, int luja[][100], int luja_marks[][100], int x, int y)
{

}