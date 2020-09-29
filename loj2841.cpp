/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.09.28

 * Solution:
  一个个加入点，维护当前所有联通块，加入一个点无非就是三种情况：
    1. 独立出来，联通块数量加一
	2. 与一个联通块相连，联通块数量不变
	3. 连接两个联通块，联通块数量减一
  第一种情况很 simple ，后面两种情况二分出与加入点相连的联通块即可。

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
#include <algorithm>
#include <vector>
#include "library.h"
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::vector<int> vec;

const int maxn = 2000;
vec qu;
vec G[maxn];
int n, sp = 0;
vec S[maxn];

bool link (int x, int y) {
	vec Q(n, 0);
	Q[x - 1] = Q[y - 1] = 1;
	return Query(Q) == 1;
}

int find_1 (int u) {
	int l = 1, r = sp;
	while (l < r) {
		int mid = (l + r) >> 1;
		vec tmpQ(n);
		tmpQ[u - 1] = 1;
		for (int i = 1; i <= mid; i ++)
			for (int x : S[i])
				tmpQ[x - 1] = 1;
		int dt = Query(tmpQ) - mid;
		if (dt == 0 or dt == -1)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int find_2 (int u) {
	int l = 1, r = sp;
	while (l < r) {
		int mid = (l + r) >> 1;
		vec tmpQ(n);
		tmpQ[u - 1] = 1;
		for (int i = 1; i <= mid; i ++)
			for (int x : S[i])
				tmpQ[x - 1] = 1;
		int dt = Query(tmpQ) - mid;
		if (dt == -1)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

inline bool right (int i, int u) {
	return S[i].size() == 1 or link(S[i].back(), u);
}

void Solve (int N) {
	n = N;
	vec Q(n);

	for (int u = 1, las = 0; u <= n; u ++) {
		Q[u - 1] = 1;
		int now = Query(Q);
		if (now == las + 1)
			S[++ sp] = {u};
		if (now == las) {
			int i = find_1(u);
			if (!right(i, u))
				std::reverse(S[i].begin(), S[i].end());
			S[i].push_back(u);
		}
		if (now == las - 1) {
			int i = find_1(u), j = find_2(u);
			if (!right(i, u))
				std::reverse(S[i].begin(), S[i].end());
			S[i].push_back(u);
			if (right(j, u))
				std::reverse(S[j].begin(), S[j].end());
			for (int x : S[j])
				S[i].push_back(x);
			for (int k = j; k < sp; k ++)
				S[k] = S[k + 1];
			-- sp;
		}
		las = now;
		/* for (int i = 1; i <= sp; i ++) { */
		/* 	for (int x : S[i]) */
		/* 		debug(" %d", x); */
		/* 	debug(" |"); */
		/* } */
		/* debug("\n"); */
	}

	/* if (sp != 1) debug("ERROR\n"); */
	Answer(S[1]);
}
