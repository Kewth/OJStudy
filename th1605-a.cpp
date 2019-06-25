#if 0
2019.06.25

i, j, k 为等差数列等价于 ik = jj 。
枚举 i, k 的话，(i, k) 的贡献为 ik 是否是完全平方数。
枚举 i, k 的 gcd d ，那么 (d, i, k) 的贡献为 i, k 互质且 ik 为完全平方数。
若 i, k 互质则 i, k 没有公共质因数，
但 ik 为完全平方数，这要求 i, k 都是完全平方数。
那么枚举 i, k 的二次方根，(d, i, k) 的贡献为 i^2, k^2 互质，即 i, k 互质。
这个时候互质关系可以用欧拉函数表示，于是得到了最终的式子：
\sum_{d=1}^n (2 \sum_{i=1}^{\sqrt{n/d}} \phi(i) - 1)
整除分块即可。
#endif
#include <cstdio>
#include <vector>
#include <cmath>

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 10000000;
bool not_prime[maxn];
std::vector<int> Prime;
lolong phi[maxn];

void sieve(int n) {
	phi[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(not not_prime[i]) {
			Prime.push_back(i);
			phi[i] = i - 1;
		}
		for(int p : Prime) {
			if(1ll * p * i > n) break;
			not_prime[p * i] = true;
			if(i % p == 0) {
				phi[p * i] = p * phi[i];
				break;
			}
			phi[p * i] = phi[p] * phi[i];
		}
	}
}

int main() {
	lolong n = input(), ans = 0;
	int m = int(sqrt(n));
	sieve(m);
	for(int i = 1; i <= m; i ++)
		phi[i] += phi[i - 1];
	for(lolong l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans += ((phi[int(sqrt(n / l))] << 1) - 1) * (r - l + 1);
		/* printf("%lld-%lld: %lld\n", l, r, ans); */
	}
	printf("%lld\n", ans);
}
