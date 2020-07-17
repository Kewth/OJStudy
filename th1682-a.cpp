/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.16

 * Solution:
  把问题抽象到图论上，把每个妹子看做连接 (a, b) 的边，不难发现任意时刻的答案就是每个联
通块的 min(|V|, |E|) 的和。如果只有 push 操作，并查集维护即可，考虑到 pop 操作，就可以
用 LCT 动态维护这张图。
  然而有更有意思的做法，类比 rayment 出的《蚯蚓》一题，把队列始终分为左右两部分，右边
一部分只有加点，左边一部分只有删点，由于删点难以维护，不妨始终保证左边一部分的大小足够
小，在每次询问的时候暴力加入左边一部分的所有点。而当左边一部分删干净的时候就需要暴力重
构，不难发现左边部分的大小限定在根号时复杂度最优。

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int ex[maxn], ey[maxn];
int fa[maxn], size[maxn], sum[maxn];
int stx[maxn], sty[maxn], sp;

inline int find (int x) {
	while (fa[x] != x) x = fa[x];
	return x;
}

int ans;
inline int get (int x) { return std::min(size[x], sum[x]); }

void clear (int n) {
	for (int i = 1; i <= n; i ++) {
		fa[i] = i;
		size[i] = 1;
		sum[i] = 0;
	}
	ans = sp = 0;
}

void add (int x, int y) {
	x = find(x), y = find(y);
	if (size[x] > size[y]) std::swap(x, y);
	++ sp;
	stx[sp] = x, sty[sp] = y;
	if (x == y) {
		ans -= get(x);
		++ sum[x];
		ans += get(x);
		return;
	}
	ans -= get(x) + get(y);
	fa[x] = y;
	size[y] += size[x];
	sum[y] += sum[x] + 1;
	ans += get(y);
}

void undo () {
	int x = stx[sp], y = sty[sp];
	-- sp;
	if (x == y) {
		ans -= get(x);
		-- sum[x];
		ans += get(x);
		return;
	}
	ans -= get(y);
	sum[y] -= sum[x] + 1;
	size[y] -= size[x];
	fa[x] = x;
	ans += get(x) + get(y);
}

int main () {
	int n = read, q = read, typ = read, off = 0, L = 1, M = 0, R = 0;
	clear(n);

	while (q --) {
		int o = (read + off) & 1;

		if (o == 0) {
			if (L ++ > M) {
				clear(n);
				M = std::min(L + 400, R);
				for (int i = M + 1; i <= R; i ++)
					add(ex[i], ey[i]);
			}
		}

		if (o == 1) {
			++ R;
			ex[R] = 1 + (read + off) % n;
			ey[R] = 1 + (read + off) % n;
			add(ex[R], ey[R]);
		}

		for (int i = L; i <= M; i ++)
			add(ex[i], ey[i]);
		printf("%d\n", ans);
		off = ans * typ;
		for (int i = L; i <= M; i ++)
			undo();
	}
}
