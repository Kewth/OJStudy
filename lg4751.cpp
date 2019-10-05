#if 0
2019.10.05

动态 DP 模板，采用 Global Biased tree ，简称狗比树，又名全局二叉平衡树。
简单来说就是在轻重链剖分的结构上用普通二叉树维护静态的 LCT 。

最后一个点巨卡常。。
把矩阵的常数优化掉，全部循环展开，并且把二维数组改成一维，再做 IO 优化即可。
感谢 @CYJian 提供的 IO 模板。
#endif
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

namespace io {
const int SIZE = (1 << 21) + 1;
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr, flg;
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
inline void flush() {
    fwrite(obuf, 1, size_t(oS - obuf), stdout);
    oS = obuf;
}
inline void pc(char x) {
    *oS++ = x;
    if (oS == oT)
        flush();
}
template <class I>
inline int gi(I &x) {
    for (f = 1, c = gc(); c != EOF && (c < '0' || c > '9'); c = gc())
        if (c == '-')
            f = -1;
    for (flg = x = 0; c != EOF && c <= '9' && c >= '0'; c = gc()) flg = 1, x = x * 10 + (c & 15);
    x *= f;
    return flg || c != EOF;
}
template <class I>
inline void print(I x) {
    if (!x)
        pc('0');
    if (x < 0)
        pc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) pc(qu[qr--]);
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io ::gi;
using io ::pc;
using io ::print;

/* typedef int Mar[2][2]; */
typedef int Mar[4];

struct GBTree {
	int fai;
	int lti, rti;
	Mar val, mul;
};
#define self pool[now]
#define fa pool[self.fai]
#define lt pool[self.lti]
#define rt pool[self.rti]

const int maxn = 1000005, inf = 1000000000;
GBTree pool[maxn];
int son[maxn], size[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int val[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u, int f) {
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != f) {
			dfs(to[i], u);
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
			size[u] += size[to[i]];
		}
}

Mar out;
inline void Mul(Mar a, Mar b) {
	out[0] = std::max(a[0] + b[0], a[1] + b[2]);
	out[1] = std::max(a[0] + b[1], a[1] + b[3]);
	out[2] = std::max(a[2] + b[0], a[3] + b[2]);
	out[3] = std::max(a[2] + b[1], a[3] + b[3]);
}

inline void copy(Mar &a, Mar b) {
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	a[3] = b[3];
}

inline void update(int now) {
	if(self.lti) {
		copy(self.mul, lt.mul);
		Mul(self.mul, self.val);
		copy(self.mul, out);
	} else
		copy(self.mul, self.val);
	if(self.rti) {
		Mul(self.mul, rt.mul);
		copy(self.mul, out);
	}
}

inline void getans(int now, int &f, int &g) {
	f = self.mul[1];
	g = self.mul[3];
}

int tmp[maxn];
int sbuild(int l, int r) {
	int sum = 0;
	for(int i = l; i <= r; i ++)
		sum += size[tmp[i]] - size[son[tmp[i]]];
	int nowsum = 0;
	for(int i = l; i <= r; i ++) {
		int now = tmp[i];
		nowsum += size[now] - size[son[now]];
		if((nowsum << 1) >= sum) {
			self.lti = sbuild(l, i - 1);
			self.rti = sbuild(i + 1, r);
			lt.fai = rt.fai = now;
			update(now);
			return now;
		}
	}
	return 0;
}

void add(int u, int now, int t) {
	int f, g;
	getans(now, f, g);
	now = u;
	self.val[1] += g * t;
	self.val[2] += std::max(f, g) * t;
	self.val[3] += std::max(f, g) * t;
}

int build(int p) {
	for(int u = p; u; u = son[u])
		for(int i = head[u]; i; i = nxt[i])
			if(size[to[i]] < size[u] and to[i] != son[u]) {
				int now = build(to[i]);
				self.fai = u;
				add(u, now, 1);
			}
	int tp = 0;
	for(int u = p; u; u = son[u])
		tmp[++ tp] = u;
	return sbuild(1, tp);
}

void modify(int now, int x) {
	self.val[1] += x - val[now];
	val[now] = x;

	while(now) {
		if(self.fai and fa.lti != now and fa.rti != now) {
			add(self.fai, now, -1);
			update(now);
			add(self.fai, now, 1);
		} else
			update(now);
		now = self.fai;
	}
}

int main() {
	int n, q;
	gi(n);
	gi(q);
	for(int now = 1; now <= n; now ++) {
		gi(val[now]);
		self.val[0] = - inf;
		self.val[1] = val[now];
		self.val[2] = 0;
		self.val[3] = 0;
	}

	for(int i = 1; i < n; i ++) {
		int u, v;
		gi(u);
		gi(v);
		add(u, v);
		add(v, u);
	}

	int now = 0;
	self.mul[1] = self.mul[2] = - inf;
	dfs(1, 0);
	now = build(1);

	int ans = 0;
	while(q --) {
		int u, x;
		gi(u);
		u ^= ans;
		gi(x);
		modify(u, x);
		int f, g;
		getans(now, f, g);
		ans = std::max(f, g);
		print(ans);
		pc('\n');
		/* printf("%d\n", ans); */
		/* ans = 0; */
	}
}
