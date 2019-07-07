#if 0
2019.07.06

发现新玩法，询问只有 1000 ，原始序列是 1 到 n ，利用好这两个性质。
对于修改操作，考虑对后面询问的影响，
由于只修改一个点，影响是可以算 gcd 暴力算出来的。
那么修改操作存下来，询问操作暴力考虑每个修改的影响，q^2 logn 。
那么问题转换为对与询问操作求原始数列 1 ~ n 的答案，没有修改操作。
枚举 p 的因子 d ，根据容斥，算出 x ~ y 中 d 的倍数和乘上 mu[d] 即可，
怎么算？用 1 ~ y 减去 1 ~ x ，而 1 ~ k 中 d 的倍数和可以容易 O(1) 得出。
#endif
#include <cstdio>
#include <vector>

typedef long long lolong;
typedef std::pair<int, int> par;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 400005, maxq = 1005;
int a[maxn];
int mu[maxn];

inline void init(int x) {
	int &tg = mu[x];
	tg = 1;
	for(int p = 2; p * p <= x; p ++)
		if(x % p == 0) {
			tg *= -1;
			x /= p;
			if(x % p == 0) {
				tg = 0;
				return;
			}
		}
	if(x > 1)
		tg *= -1;
}

int gcd(int x, int y) {
	if(! y) return x;
	return gcd(y, x % y);
}

int main() {
	int T = input();
	for(int i = 0; i < maxn; i ++) {
		a[i] = i;
		init(i);
	}
	while(T --) {
		int n = input(), q = input();
		std::vector<par> modidy;
		while(q --) {
			int op = input(), x = input(), y = input();
			if(op == 1) {
				int p = input();
				lolong ans = 0;
				x --;
				for(int d = 1; d * d <= p; d ++)
					if(p % d == 0) {
						int dd = d;
						ans += 1ll * (1 + y / dd) * (y / dd) / 2 * dd * mu[dd];
						ans -= 1ll * (1 + x / dd) * (x / dd) / 2 * dd * mu[dd];
						if(d * d == p) break;
						dd = p / d;
						ans += 1ll * (1 + y / dd) * (y / dd) / 2 * dd * mu[dd];
						ans -= 1ll * (1 + x / dd) * (x / dd) / 2 * dd * mu[dd];
					}
				x ++;
				for(size_t k = 0; k < modidy.size(); k ++) {
					par pr = modidy[k];
					if(x <= pr.first && pr.first <= y) {
						if(gcd(a[pr.first], p) == 1)
							ans -= a[pr.first];
						a[pr.first] = pr.second;
						if(gcd(a[pr.first], p) == 1)
							ans += a[pr.first];
					}
				}
				for(size_t k = 0; k < modidy.size(); k ++) {
					par pr = modidy[k];
					a[pr.first] = pr.first;
				}
				printf("%lld\n", ans);
			} if(op == 2)
				modidy.push_back(par(x, y));
		}
	}
}
