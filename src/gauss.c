#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */

int eliminate(Matrix *mat, Matrix *b)
{
	int wiersze = mat->r;
	int kolumny = mat->c + b->c;

	//double macierz[wiersze][kolumny]
	double **macierz = (double**)malloc(wiersze * sizeof(double*));
	for (int i = 0; i < wiersze; i++) {
		macierz[i] = (double*)malloc(kolumny * sizeof(double));
	}

	//tworzy rozszerzona macierz
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
	//eliminacja
	for(int i = 0; i < wiersze - 1; i++)
	{
		p_select(macierz, wiersze, kolumny, i);

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
	//zamienia oryginalna macierz
	for(int w = 0; w < wiersze; w++)
	{
		for(int k = 0; k < kolumny; k++)
		{
			if(k + 1 == kolumny)
			{
				b->data[w][0] = macierz[w][k];
			}
			else mat->data[w][k] = macierz[w][k];
		}
	}
	for (int i = 0; i < wiersze; i++)
		free(macierz[i]);
	free(macierz);

	return 0;
}

void p_select(double **macierz, int rows, int cols, int diag) {
	//wybiera największy element w kolumnie i zamienia miejscami

	int max_index = diag;
	double max_val = fabs(macierz[diag][diag]);

	for (int i = diag; i <= rows - 1; i++) {
		if (max_val < fabs(macierz[i][diag])) {
			max_index = i;
			max_val = fabs(macierz[i][diag]);
		}
	}

	if (max_index == diag) 
		return;

	double tmp_val;
	for( int i = 0; i < cols; i++) {

		tmp_val = macierz[diag][i];
		macierz[diag][i] = macierz[max_index][i];
		macierz[max_index][i] = tmp_val;
	}
}