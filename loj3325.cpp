/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.15

 * Solution:
 * 势能线段树

  这个区间取 max 不难想到势能线段树，但是要维护的是区间最大子段和，和区间和不同的是，将
区间的 min 都增加一个值，即使不超过 semin ，虽然通过记录最大子段和包含了多少 min 可以得
到该子段新的和，但是可能存在另一包含更多 min 的子段在修改后超过原有子段成为最大子段。

  为了处理这个问题，需要对于每个节点维护一个阈值 thr ，表示取 max 的值在不超过 thr 时最
大子段不会改变，一旦超过 thr ，最大子段就可能发生改变，从而要递归到两个儿子进行修改再上
传节点信息。

  将子段抽象出来，用三个值 sum, min, cnt 描述，分别表示子段和，子段最小值，子段中包含多
少所在线段树节点的最小值（注意不是 min 的数量）。然后按照普通的最大子段和维护四个子段：
最大前缀子段，最大后缀子段，最大子段，整体子段。这样便可以维护了，细节并不多，思路也比
较自然。

 * Digression:
  复杂度均摊两个 log ，可以看出由于阈值 thr 不超过 semin ，这个算法是严格不比普通的势能
线段树优的，但是复杂度事实上也不比它劣，证明还不会。

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

struct info {
	ll sum;
	int min, cnt;
	int count (int x) { return min == x ? cnt : 0; }
	void update (int x) { cnt = count(x); }
	void inc (int x) { sum += 1ll * x * cnt; min += x; }
};

info operator + (info a, info b) {
	info c = {a.sum + b.sum, std::min(a.min, b.min), a.cnt + b.cnt};
	if (a.min < b.min) c.cnt = a.cnt;
	if (b.min < a.min) c.cnt = b.cnt;
	return c;
}

const int maxn = 100000, Size = maxn * 4 + 10, inf = 1000000000;
info sl[Size], sr[Size], sm[Size], ss[Size];
int min[Size], semin[Size], thr[Size];
bool isleaf[Size];
#define ls (now << 1)
#define rs (now << 1 | 1)

int nowmin, nowtime;
info operator & (info a, info b) {
	a.update(nowmin);
	b.update(nowmin);
	int d = b.cnt - a.cnt;
	ll D = a.sum - b.sum;
	if (D > 0) {
		if (d > 0) nowtime = int(std::min<ll>(nowtime, D / d));
		return a;
	} else {
		D = -D, d = -d;
		if (d > 0) nowtime = int(std::min<ll>(nowtime, D / d));
		return b;
	}
}

void update (int now) {
	if (min[ls] < min[rs]) nowmin = min[ls], semin[now] = std::min(semin[ls], min[rs]);
	else nowmin = min[rs], semin[now] = std::min(semin[rs], min[ls]);
	nowtime = inf;
	ss[now] = ss[ls] + ss[rs];
	sl[now] = sl[ls] & (ss[ls] + sl[rs]);
	sr[now] = sr[rs] & (sr[ls] + ss[rs]);
	sm[now] = sm[ls] & sm[rs] & (sr[ls] + sl[rs]);
	min[now] = nowmin;
	thr[now] = std::min({semin[now], min[now] + nowtime, thr[ls], thr[rs]});
}

void init (int now, int x) {
	min[now] = x;
	semin[now] = inf;
	thr[now] = x < 0 ? 0 : inf;
	ss[now] = {x, x, 1};
	sm[now] = sl[now] = sr[now] = x < 0 ? info({0, inf, 0}) : info({x, x, 1});
}

void modi (int, int);
void push (int now) {
	if (min[now] > min[ls]) modi(ls, min[now]);
	if (min[now] > min[rs]) modi(rs, min[now]);
}

void modi (int now, int x) {
	if (x <= thr[now]) {
		sl[now].inc(x - min[now]);
		sr[now].inc(x - min[now]);
		sm[now].inc(x - min[now]);
		ss[now].inc(x - min[now]);
		min[now] = x;
		return;
	}
	if (isleaf[now]) init(now, x);
	else {
		min[now] = x;
		push(now);
		update(now);
	}
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R or x <= min[now]) return;
	if (l <= L and R <= r) return modi(now, x);
	int M = (L + R) >> 1;
	push(now);
	modify(ls, L, M, l, r, x);
	modify(rs, M + 1, R, l, r, x);
	update(now);
}

ll qsum, qans;
void query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) {
		qans = std::max({qans, sm[now].sum, qsum + sl[now].sum});
		qsum = std::max(ss[now].sum + qsum, sr[now].sum);
		return;
	}
	push(now);
	int M = (L + R) >> 1;
	query(ls, L, M, l, r);
	query(rs, M + 1, R, l, r);
}

void build (int now, int L, int R) {
	if (L == R) return isleaf[now] = 1, init(now, read);
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
	update(now);
}

int main () {
	int n = read, q = read;
	build(1, 1, n);
	while (q --) {
		int o = read, l = read, r = read;
		if (o == 0) modify(1, 1, n, l, r, read);
		if (o == 1) {
			qsum = qans = 0;
			query(1, 1, n, l, r);
			printf("%lld\n", qans);
		}
	}
}
