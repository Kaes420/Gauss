#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b)
{
	int wiersze = mat->r;
	int kolumny = mat->c + b->c;

	double macierz[wiersze][kolumny];

	for(int w = 0; w < wiersze; w++)
	{
		for(int k = 0; k < kolumny; k++)
		{
			if(k + 1 == kolumny)
			{
				macierz[w][k] = b->data[w][0];
			}
			else macierz[w][k] = mat->data[w][k];
		}
	}

	for(int i = 0; i < wiersze - 1; i++)
	{
		double A = macierz[i][i];
		if(A == 0) return 1;

		int x = i + 1;
		while (x < wiersze)
		{
			double B = macierz[x][i];
			double iloraz = B / A;

			for(int k = 0; k < kolumny; k++)
			{
				macierz[x][k] -= macierz[i][k] * iloraz;
			}

			x++;
		}
	}

	for(int w = 0; w < wiersze; w++)
	{
		for(int k = 0; k < kolumny; k++)
		{
			if(k + 1 == kolumny)
			{
				b->data[w][1] = macierz[w][k];
			}
			else mat->data[w][k] = macierz[w][k];
		}
	}

	return 0;
}

