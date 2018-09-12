#include <bits/stdc++.h>

inline long long input() { long long res; scanf("%lld",&res); return res; }

const int maxn = 101;
const double eps = 1e-7;
double M[maxn][maxn+1];

void debug(int n)
{
	/* return ; */
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n+1;j++)
				printf("%.3lf ",M[i][j]);
	puts("-----");
}

int main()
{
	int n = input();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			M[i][j] = input();
	for(int i=1;i<=n;i++)
	{
		if(std::abs(M[i][i]) < eps)
			for(int j=i+1;j<=n;j++)
				if(std::abs(M[j][i]) >= eps)
				{
					for(int k=1;k<=n+1;k++)
						std::swap(M[i][k] , M[j][k]);
					break;
				}
		if(std::abs(M[i][i]) < eps)
		{
			puts("No Solution");
			return 0;
		}
		for(int j=1;j<=n+1;j++)
			if(i != j)
				M[i][j] /= M[i][i];
		M[i][i] = 1;
		debug(n);
		for(int j=i+1;j<=n;j++)
		{
			for(int k=i+1;k<=n+1;k++)
				M[j][k] -= M[j][i] * M[i][k];
			M[j][i] = 0;
			if(std::abs(M[j][j]) < eps)
			{
				for(int k=j+1;k<=n;k++)
					if(std::abs(M[k][j]) >= eps)
					{
						for(int l=1;l<=n+1;l++)
							std::swap(M[j][l] , M[k][l]);
						break;
					}
				if(std::abs(M[j][j]) < eps)
				{
					puts("No Solution");
					return 0;
				}
				j--;
				continue;
			}
		}
		debug(n);
	}
	for(int i=n;i;i--)
	{
		for(int j=1;j<i;j++)
		{
			M[j][n+1] -= M[i][n+1] * M[j][i];
			M[j][i] = 0;
		}
		debug(n);
	}
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",M[i][n+1]);
}
