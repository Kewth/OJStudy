/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.17

 * Solution:
  很自然的一个做法：随机撒点 + 线段树 + odt 。很套路，略，注意不要使用 rand() 。

 * Digression:
  知道 rand 弱，却实在没想到 rand 可以这么弱。

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
#include <set>
#include <random>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 150005;
struct Tree {
	int lti, rti;
	ll sum, tag;
} pool[maxn * 90];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
int seg[maxn];

void add (int &now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (!now) now = ++ pp;
	self.sum += x * (std::min(R, r) - std::max(L, l) + 1);
	if (l <= L and R <= r) return self.tag += x, void();
	int M = (L + R) >> 1;
	add(self.lti, L, M, l, r, x);
	add(self.rti, M + 1, R, l, r, x);
}

ll query (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !now) return 0;
	if (l <= L and R <= r) return self.sum;
	ll res = self.tag * (std::min(R, r) - std::max(L, l) + 1);
	int M = (L + R) >> 1;
	res += query(self.lti, L, M, l, r);
	res += query(self.rti, M + 1, R, l, r);
	return res;
}

struct Node {
	int l, r;
	mutable int x;
	Node (int l, int r, int x): l(l), r(r), x(x) { }
};
bool operator < (Node a, Node b) {
	return a.r < b.r;
}

std::set<Node> odt;
typedef std::set<Node>::iterator iter;

iter split (int r) {
	iter it = odt.lower_bound(Node(1, r, 0));
	if (it -> r == r) return it;
	Node a(it -> l, r, it -> x), b(r + 1, it -> r, it -> x);
	odt.erase(it);
	odt.insert(b);
	return odt.insert(a).first;
}

int ans[10], ap;

int main () {
	int n = read, q = read, p = read;

	odt.insert(Node(0, 0, 0));
	for (int i = 1; i <= n; i ++) {
		int x = read;
		add(seg[x], 1, n, i, i, 1);
		odt.insert(Node(i, i, x));
	}

	std::mt19937 engine;

	while (q --) {
		int o = read;

		if (o == 1) {
			int l = read, r = read, x = read;
			iter end = ++ split(r), begin = ++ split(l - 1);
			for (iter it = begin; it != end; ++ it)
				add(seg[it -> x], 1, n, it -> l, it -> r, -1);
			odt.erase(begin, end);
			odt.insert(Node(l, r, x));
			add(seg[x], 1, n, l, r, 1);
		}

		if (o == 2) {
			int l = read, r = read;
			std::uniform_int_distribution<int> Rand(l, r);
			ap = 0;
			for (int k = 0; k < 60; k ++) {
				int i = l + Rand(engine) % (r - l + 1);
				int x = odt.lower_bound(Node(1, i, 0)) -> x;
				bool diff = 1;
				for (int j = 1; j <= ap; j ++)
					diff &= x != ans[j];
				if (diff and query(seg[x], 1, n, l, r) * 100 >= (r - l + 1) * p)
					ans[++ ap] = x;
			}
			printf("%d", ap);
			for (int i = 1; i <= ap; i ++) printf(" %d", ans[i]);
			puts("");
		}
	}
}
