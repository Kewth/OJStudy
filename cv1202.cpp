#include <bits/stdc++.h>

long long input() { long long res; scanf("%lld",&res); return res; }

int main()
{
	int n = input() , sum = 0;
	for(int i=1;i<=n;i++)
		sum += input();
	printf("%d\n",sum);
}
