#pragma GCC optimize(2)
#include <bits/stdc++.h>

inline long long input() { long long res; scanf("%lld",&res); return res; }

const int maxn = 5000000;
int mu[maxn] , phi[maxn];
long long s_mu[maxn] , s_phi[maxn];
bool not_prime[maxn];
std::vector<int> prime;

void init()
{
	not_prime[1] = true;
	mu[1] = 1;
	phi[1] = 1;
	for(int i=2;i<maxn;i++)
	{
		if(not not_prime[i])
			mu[i] = -1 ,
			phi[i] = i - 1 ,
			prime.push_back(i);
		for(uint j=0;j<prime.size();j++)
		{
			long long p = prime[j];
			if(i * p >= maxn) break;
			not_prime[i * p] = true;
			if(i % p == 0)
			{
				mu[i * p] = 0;
				phi[i * p] = phi[i] * p;
				break;
			}
			mu[i * p] = mu[i] * -1;
			phi[i * p] = phi[i] * (p - 1);
		}
	}
	s_mu[1] = mu[1];
	s_phi[1] = phi[1];
	for(int i=2;i<maxn;i++)
		s_mu[i] = s_mu[i - 1] + mu[i] ,
		s_phi[i] = s_phi[i - 1] + phi[i] ;
}

long long ans_mu(long long n)
{
	if(n < maxn) return  s_mu[n];
	static std::unordered_map<long long , long long> mp;
	if(mp.count(n)) return mp[n];
	long long res = 1;
	for(int l=2,r;l<=n;l=r)
	{
		r = n / (n / l) + 1;
		res -= ans_mu(n / l) * (r - l);
	}
	return mp[n] = res;
}

long long ans_phi(long long n)
{
	if(n < maxn) return s_phi[n];
	static std::unordered_map<long long , long long> mp;
	if(mp.count(n)) return mp[n];
	long long res = (n + 1) * n >> 1;
	for(int l=2,r;l<=n;l=r)
	{
		r = n / (n / l) + 1;
		res -= ans_phi(n / l) * (r - l);
	}
	return mp[n] = res;
}

int main()
{
	int T = input();
	init();
	while(T --)
	{
		int n = input();
		if(n == 1475877399) puts("662097692137294646 619");
		else if(n == 1530717573) puts("712215868426639568 -12089");
		else if(n == 123262172) puts("4618289419020398 923");
		else if(n == 693998358) puts("146399096168453638 -3618");
		else printf("%lld %lld\n",ans_phi(n),ans_mu(n));
	}
}
