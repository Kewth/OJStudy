/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
  考虑一个离线做法：按边权从小到大加边随着时间推移对每个点 x 维护 f[x] 表示该点到 1 的
合法路径的最小边权的最大值，那么通过 f[x] 可以很简单地回答询问。
  而这个离线做法可以很容易地扩展到在线，由于强制在线的仅仅是询问，所有边仍然可以离线下
来，把边从小到大加到图里同时对 x 开一个 vector 记录每次发生改变时的 f[x] ，对于询问直接
在 vector 上二分得到对应时刻的 f 即可。
  那么问题来了，如果强制在线动态加入边权不单调的边该如何处理？

 * Digression:
  感觉不止蓝啊，是我菜了么 QwQ 。

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
std::vector<par> t[maxn];
int f[maxn];

int main () {
	int n = read, m = read, q = read, o = read;
	for (int i = 1; i <= n; i ++)
		t[i].push_back(par(0, 0));
	for (int i = 1; i <= m; i ++) {
		int x = read, y = read;
		f[x] = y == 1 ? i : std::max(f[x], f[y]);
		t[x].push_back(par(i, f[x]));
	}
	for (int i = 1; i <= n; i ++)
		t[i].push_back(par(m + 2, 0));
	int sum = 0;
	while (q --) {
		int x = read, l = read, r = read;
		if (o) x ^= sum, l ^= sum, r ^= sum;
		par p = *(-- std::lower_bound(t[x].begin(), t[x].end(), par(r + 1, 0)));
		if (x == 1 or p.second >= l) puts("1"), ++ sum;
		else puts("0");
	}
}
