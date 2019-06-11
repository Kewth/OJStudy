#if 0
2019.05.23

对于质数的限制，枚举 min(n, m) 以内的质数再钦定 gcd 。
莫比乌斯反演，得到
Ans = \sum_{p is Prime} \sum_{d=1}^{n/p} mu(d) (n/pd) (m/pd)
枚举 t = pd ，得到
Ans = \sum_{t=1}^n (n/t) (m/t) \sum_{p|t, p is Prime} mu(t/p)
前面一部分整除分块，后面一部分与 n, m 无关，用埃筛的思路预处理即可。
#endif
#include <cstdio>
#include <vector>
#include <cassert>

typedef long long lolong;
const int maxn = 10000001;
std::vector<int> Prime;
int mu[maxn];
int f[maxn];
bool not_prime[maxn];

void sieve(int n) {
	mu[1] = 1;
	for(int x = 2; x <= n; x ++) {
		if(not not_prime[x]) {
			Prime.push_back(x);
			mu[x] = -1;
		}
		for(size_t i = 0; i < Prime.size(); i ++) {
			int p = Prime[i];
			if(1ll * x * p > 1ll * n) break;
			not_prime[x * p] = true;
			if(not (x % p)) {
				mu[x * p] = 0;
				break;
			}
			mu[x * p] = mu[x] * mu[p];
		}
	}
	for(size_t i = 0; i < Prime.size(); i ++) {
		int p = Prime[i];
		for(int x = p; x < maxn; x += p)
			f[x] += mu[x / p];
	}
}

int main() {
	int T;
	scanf("%d", &T);
	sieve(maxn - 1);
	for(int i = 2; i < maxn; i ++)
		f[i] += f[i - 1];
	while(T --) {
		int n, m;
		scanf("%d %d", &n, &m);
		if(n > m) std::swap(n, m);
		lolong ans = 0;
		for(int l = 1, r; l <= n; l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			/* assert(n / l == n / r); */
			/* assert(m / l == m / r); */
			ans += lolong(n / l) * (m / l)
				* (f[r] - f[l - 1]);
		}
		printf("%lld\n", ans);
	}
}
