#include <bits/stdc++.h>

inline long long input() { long long res ; scanf("%lld",&res); return res; }

int find(int x,int *fa)
{
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x] , fa);
}

inline void add(int x,int y,int *fa)
{
	x = find(x , fa);
	y = find(y , fa);
	fa[x] = y;
}

bool together(int x,int y,int *fa)
{
	x = find(x , fa);
	y = find(y , fa);
	return x == y;
}

int main()
{
	int n = input() , q = input();
	int *fa = new int [n + 1];
	for(int i=1;i<=n;i++)
		fa[i] = i;
	while(q --)
	{
		int typ = input() , x = input() , y = input();
		if(typ == 1)
			add(x , y , fa);
		else
			together(x , y , fa) ? puts("Y") : puts("N");
	}
}
