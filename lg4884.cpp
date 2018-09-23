#include <bits/stdc++.h>

inline long long input() { long long res ; scanf("%lld",&res); return res; }

typedef __int128 Num;

Num power(Num x,long long k,Num mod)
{
	Num res = 1;
	while(k)
	{
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main()
{
	Num K = input() , mod = input();
	K = (K * 9 + 1) % mod;
	Num sq = std::sqrt((long long)mod);
	Num A = power(10ll , mod - sq - 1 , mod) , a = 1;
	std::map<Num,Num> mp;
	for(long long i=0;i<=sq;i++)
	{
		if(mp.count(a * K % mod))
			mp[a * K % mod] = std::min(sq * i , mp[a * K % mod]);
		else
			mp[a * K % mod] = sq * i;
		/* printf("mp[%lld]=%d\n",a * K % mod,mp[a * K % mod]); */
		(a *= A) %= mod;
	}
	A = 10;
	a = 1;
	Num ans = 999900000000000000ll;
	for(long long i=0;i<=sq;i++)
	{
		if(mp.count(a) and power(A , mp[a]+i , mod) == K)
			ans = std::min(mp[a] + i , ans);
		/* printf("%lld\n",a); */
		(a *= A) %= mod;
	}
	/* printf("%lld\n",ans); */
	std::cout<<(long long)ans<<std::endl;
}
