/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.12

 * Solution:
  直接 KDT 维护，2DT 的矩形查询复杂度最坏 O(n^0.5) 。

 * Digression:
  几百年没写 KDT 了，刷刷找手感。
  0 号点的 min 要赋值为 inf ，否则节点的矩形区域会维护错，只 T 不 WA ，巨难调。

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
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 200005;
struct KDT {
	int size;
	int val, sum;
	int p[2], min[2], max[2];
	int lti, rti;
} pool[maxn];
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

inline void update (int now) {
	self.size = lt.size + rt.size + 1;
	self.sum = lt.sum + rt.sum + self.val;
	for (int i = 0; i < 2; i ++) {
		self.min[i] = std::min({self.p[i], lt.min[i], rt.min[i]});
		self.max[i] = std::max({self.p[i], lt.max[i], rt.max[i]});
	}
}

int cmp_d;
inline bool cmp (int a, int b) {
	if (pool[a].p[cmp_d] == pool[b].p[cmp_d])
		return a < b;
	return pool[a].p[cmp_d] < pool[b].p[cmp_d];
}

int tmp[maxn], tp;
void maketmp (int now) {
	if (self.lti) maketmp(self.lti);
	tmp[++ tp] = now;
	if (self.rti) maketmp(self.rti);
}
int rebuild (int l, int r, int d) {
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	cmp_d = d;
	std::nth_element(tmp + l, tmp + mid, tmp + r + 1, cmp);
	int now = tmp[mid];
	self.lti = rebuild(l, mid - 1, d ^ 1);
	self.rti = rebuild(mid + 1, r, d ^ 1);
	update(now);
	return now;
}

void tryrebuild (int &now, int d) {
	if (std::max(lt.size, rt.size) > self.size * 0.725) {
		tp = 0;
		maketmp(now);
		now = rebuild(1, tp, d);
	}
}

void insert (int &now, int an, int d) {
	if (!now) return now = an, void();
	cmp_d = d;
	if (cmp(an, now)) insert(self.lti, an, d ^ 1);
	else insert(self.rti, an, d ^ 1);
	update(now);
	tryrebuild(now, d);
}

int TOT;
int lp[2], rp[2];
int query (int now) {
	if (!now) return 0;
	/* if (rp[0] < self.min[0]) debug("1\n"); */
	/* if (lp[0] > self.max[0]) debug("2\n"); */
	/* if (rp[1] < self.min[1]) debug("3\n"); */
	/* if (lp[1] > self.max[1]) debug("%d %d\n", lp[1], self.max[1]); */
	if (rp[0] < self.min[0] or lp[0] > self.max[0] or
			rp[1] < self.min[1] or lp[1] > self.max[1])
		return 0;
	++ TOT;
	if (lp[0] <= self.min[0] and self.max[0] <= rp[0] and
			lp[1] <= self.min[1] and self.max[1] <= rp[1])
		return self.sum;
	int res = query(self.lti) + query(self.rti);
	if (lp[0] <= self.p[0] and self.p[0] <= rp[0] and
			lp[1] <= self.p[1] and self.p[1] <= rp[1])
		res += self.val;
	return res;
}

int main () {
	// XXX: 没加这个 T 了一年
	pool[0].min[0] = pool[0].min[1] = read;
	int p = 0, kdt = 0, ans = 0;
	while (1) {
		int o = read;
		if (o == 1) {
			int now = ++ p;
			for (int i = 0; i < 2; i ++)
				self.p[i] = self.min[i] = self.max[i] = read ^ ans;
			self.size = 1;
			self.val = self.sum = read ^ ans;
			self.lti = self.rti = 0;
			insert(kdt, now, 0);
		}
		if (o == 2) {
			read(lp[0], lp[1], rp[0], rp[1]);
			lp[0] ^= ans;
			lp[1] ^= ans;
			rp[0] ^= ans;
			rp[1] ^= ans;
			printf("%d\n", ans = query(kdt));
		}
		if (o == 3) break;
		/* ans = 0; */
	}
	debug("%d\n", TOT);
}
