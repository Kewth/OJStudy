#include <bits/stdc++.h>

inline long long input() { long long res; scanf("%lld",&res); return res; }

const int maxn = 100050;
int f[maxn] , g[maxn];
int belong[maxn];
bool has[maxn];

int main()
{
	int n = input() , m = input() , K = input();
	for(int i=1;i<=n;i++)
		belong[i] = input();
	for(int i=1;i<=n;i++)
	{
		int bao = 0;
		memset(has , 0 , sizeof(has));
		g[i] = f[i] = 1000000000;
		for(int j=i;j;j--)
		{
			if(not has[belong[j]])
				bao ++;
			if(bao > K)
				break;
			has[belong[j]] = true;
			if(f[j-1] + 1 < f[i])
				g[i] = g[j-1] + bao,
				/* f[i] = f[j-1] + 1; */
			/* else if(f[j-1] + 1 == f[i]) */
				g[i] = std::min(g[j-1] + bao , g[i]);
		}
	}
	printf("%d\n%d\n",f[n],g[n]);
}
