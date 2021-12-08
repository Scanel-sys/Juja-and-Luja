#include <stdio.h>

void juja(int *luja_size, int luja[][100], int luja_marks[][100], int x, int y);

int main()
{
	int luja_hights[100][100];
	int luja_marks[100][100];
	int n;
	scanf_s("%d", &n);

	//getting hights in array
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &luja_hights[i][j]);
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			luja_marks[i][j] = 0;


	juja(&n, luja_hights, luja_marks, 0, 0);

	//printing marks of luja_marks
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("  %d  ",luja_marks[i][j]);
		}
		printf("\n");
	}
	



}

void juja(int *luja_size, int luja[][100], int luja_marks[][100], int x, int y)
{

}