#include <bits/stdc++.h>

long long input() { long long res; scanf("%lld",&res); return res; }

const double eps = 1e-8;
int main()
{
	double x , y;
	scanf("%lf%lf",&x,&y);
	if(std::abs(x - y) < eps)
		puts("yes");
	else
		puts("no");
}
