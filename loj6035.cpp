/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
  设 a[i] 表示洗 i 件衣服的最小时间花费，同理有 b[i] 对应烘干。稍加观察可以发现答案
就是 max(a[i] + b[n + i - 1]) ，用堆模拟贪心求出 {a} 和 {b} 即可。

 * Digression:
  似乎本质上是要选排列 p ，最小化 max(a[p[i]] + b[n + i - 1]) ，根据排序不等式就能
直接得到上述的结论。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
ll a[maxn], b[maxn];

int main () {
	int n = read, an = read, bn = read;
	std::priority_queue<par, std::vector<par>, std::greater<par> > qa, qb;
	for (int i = 1; i <= an; i ++) {
		int x = read;
		qa.push(par(x, x));
	}
	for (int i = 1; i <= bn; i ++) {
		int x = read;
		qb.push(par(x, x));
	}

	for (int i = 1; i <= n; i ++) {
		par p; {
			p = qa.top();
			qa.pop();
			a[i] = p.first;
			p.first += p.second;
			qa.push(p);
		} {
			p = qb.top();
			qb.pop();
			b[i] = p.first;
			p.first += p.second;
			qb.push(p);
		}
	}

	ll ans = 0;
	for (int i = 1; i <= n; i ++)
		ans = std::max(ans, a[i] + b[n - i + 1]);
	printf("%lld\n", ans);
}
