#include <bits/stdc++.h>
#define int long long

inline long long input() { long long res; scanf("%lld",&res); return res; }

const int maxn = 50020;
int mu[maxn] , s_mu[maxn] , f[maxn];
bool not_prime[maxn];
std::vector<int> prime;

void init()
{
	mu[1] = 1;
	not_prime[1] = true;
	for(int i=2;i<maxn;i++)
	{
		if(not not_prime[i])
			prime.push_back(i),
			mu[i] = -1;
		for(uint j=0;j<prime.size();j++)
		{
			int p = prime[j];
			if(i * p >= maxn) break;
			not_prime[i * p] = true;
			if(i % p == 0) break;
			mu[i * p] = mu[i] * -1;
		}
	}
	for(int i=1;i<maxn;i++)
		s_mu[i] = s_mu[i-1] + mu[i];
	for(int n=1;n<maxn;n++)
		for(int l=1,r;l<=n;l=r)
		{
			r = n / (n / l) + 1;
			f[n] += (r - l) * (n / l);
		}
}
 main()
{
	int q = input();
	init();
	/* for(int i=1;i<=10;i++) */
	/* 	printf("%d ",f[i]); */
	/* puts(""); */
	/* for(int i=1;i<=10;i++) */
	/* 	printf("%d ",mu[i]); */
	/* puts(""); */
	while(q --)
	{
		int n = input() , m = input();
		long long ans = 0;
		if(n > m) std::swap(n , m);
		for(int l=1,r;l<=n;l=r)
		{
			r = std::min(n / (n / l) , m / (m / l)) + 1;
			ans += (s_mu[r-1] - s_mu[l-1]) * f[n / l] * f[m / l];
			/* printf("%d-%d:%lld\n",l,r,ans); */
		}
		printf("%lld\n",ans);
	}
}
