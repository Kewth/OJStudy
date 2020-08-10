/*
 * Author: Kewth

 * Date:
  2020.08.04

 * Solution:
  后缀平衡树是个好东西。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 500005;
struct SGT {
	int lti, rti, prei;
	int size;
	ld key;
} pool[maxn];
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define pre pool[self.prei]
char s[maxn];

bool cmp (int a, int b) {
	if (s[a] != s[b]) { return s[a] < s[b]; }
	int A = pool[a].prei, B = pool[b].prei;
	return A == B ? a < b : pool[A].key < pool[B].key;
}

int tmp[maxn], tp;
void dfs (int now) {
	if (self.lti) dfs(self.lti);
	tmp[++ tp] = now;
	if (self.rti) dfs(self.rti);
}

int rebuild (int l, int r, ld L, ld R) {
	if (l > r) return 0;
	int mid = (l + r) >> 1, now = tmp[mid];
	self.key = (L + R) / 2;
	self.lti = rebuild(l, mid - 1, L, self.key);
	self.rti = rebuild(mid + 1, r, self.key, R);
	self.size = lt.size + rt.size + 1;
	return now;
}

void tryrebuild (int &now, ld l, ld r) {
	if (std::max(lt.size, rt.size) > self.size * 0.7) {
		tp = 0, dfs(now);
		now = rebuild(1, tp, l, r);
	}
}

void insert (int &now, int a, ld l, ld r) {
	if (!now) {
		now = a;
		self.size = 1;
		self.key = (l + r) / 2;
		return;
	}
	if (cmp(a, now)) insert(self.lti, a, l, self.key);
	else insert(self.rti, a, self.key, r);
	self.size = lt.size + rt.size + 1;
	tryrebuild(now, l, r);
}

int main () {
	pool[0].key = - 1e4792L; // XXX: 这都能忘？这都能忘？这都能忘？
	int n = read;
	for (int now = 2; now <= n; now ++) read(self.prei);
	scanf("%s", s + 1);
	int t = 0;
	// XXX: 下面的值域不能开成 inf ，否则做加法会爆
	for (int now = 1; now <= n; now ++) insert(t, now, - 1e2333L, 1e2333L);
	tp = 0, dfs(t);
	for (int i = 1; i <= tp; i ++) printf("%d ", tmp[i]);
	puts("");
}
