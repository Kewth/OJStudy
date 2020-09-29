/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.09.25

 * Solution:
  考虑链的情况，可以随机选择两个点 X, Y ，然后把每个点 u 放进去询问一波，可以
拆成三个部分，三个部分分别排序即可，排序的 cmp 就是一个 Query 。
  推广到树，随机选两个点 X, Y 后把每个点 u 放进去询问一波，可以分成若干部分，
称 X - Y 路径上的点为主干点，每个点询问的结果就是其最近的主干点，主干点之间排
序就可以确定边，然后每个主干点划分为一个新的子问题，递归处理即可。
  虽然最坏复杂度是平方级别的，但是随机化后的期望复杂度似乎很优秀？证明待补。

 * Digression:

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
#include <vector>
#include <algorithm>
#include "meetings.h"
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;
typedef std::vector<int> vec;

void Answer (int x, int y) {
	/* debug("%d %d\n", x, y); */
	if (x > y) std::swap(x, y);
	Bridge(x, y);
}

const int maxn = 2020;
int N;
vec sub[maxn];
int lis[maxn];

void work (vec &v) {
	if (v.size() < 2) return;
	if (v.size() == 2) return Answer(v[0], v[1]);
	int X = v[0], Y = v[1];
	for (int i = 0; i < N; i ++) sub[i].clear();
	/* for (int u : v) debug(" %d", u); debug("\n"); */
	sub[X].push_back(X);
	sub[Y].push_back(Y);
	for (int u : v)
		if (u != X and u != Y) {
			int c = Query(X, Y, u);
			sub[c].push_back(u);
			/* debug("%d -> %d\n", u, c); */
		}
	int p = 0;
	for (int i = 0; i < N; i ++)
		if (sub[i].size() and i != X and i != Y)
			lis[++ p] = i;
	std::sort(lis + 1, lis + p + 1, [&] (int x, int y) {
				return Query(X, x, y) == x;
			});
	lis[0] = X;
	lis[p + 1] = Y;
	for (int i = 1; i <= p + 1; i ++) Answer(lis[i - 1], lis[i]);
	std::vector<vec> nv;
	for (int i = 0; i <= p + 1; i ++) nv.push_back(sub[lis[i]]);
	for (vec &n : nv)
		work(n);
}

void Solve (int n) {
	N = n;
	vec v((size_t)n);
	for (int i = 0; i < n; i ++) v[(size_t)i] = i;
	std::random_shuffle(v.begin(), v.end());
	work(v);
}
