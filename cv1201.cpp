#include <bits/stdc++.h>

long long input() { long long res; scanf("%lld",&res); return res; }

int main()
{
	int min_ = 1000000000 , max_ = -1000000000 , n = input();
	for(int i=1;i<=n;i++)
	{
		int x = input();
		min_ = std::min(x , min_);
		max_ = std::max(x , max_);
	}
	printf("%d %d\n",min_,max_);
}
