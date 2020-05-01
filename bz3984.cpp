#if 0
2020.05.01

  将序列差分，那么区间异或就是单点异或两个位置，区间赋值就是把一段区间删掉然后单点异或
两个位置，单点异或同样可以看做先删后加，线性基动态加入一个数是很方便的，问题瓶颈在于动
态删除一个数。
  算是个 trick 吧，bitset 维护每个向量可以被原来哪些向量表示，每次做异或的同时对这个位
置集合进行异或即可。那么假设要删除第 i 个向量，就找到一个被 i 表示的向量，优先找非基向
量，否则找对应位最小的基向量。然后把其他所有被 i 表示的向量异或上当前这个向量，操作完
后，该向量就是唯一一个被 i 表示的向量，把它删掉即可，如果它是基向量，就同时在线性基里
删除，复杂度 O(n^2/W) 。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 2048;
typedef long long ll;
typedef unsigned long long ull;
typedef std::bitset<maxn> bs;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator bs () {
		static char s[2048];
		bs x;
		scanf("%s", s);
		for (int i = 0; s[i]; i ++)
			if (s[i] == '1')
				x.set(i);
		return x;
	}
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

bs a[maxn];
bs v[maxn], from[maxn];
int isbas[maxn];
int bas[maxn];

void insert (int pi, int m) {
	for (int k = 0; k < m; k ++)
		if (v[pi].test(k)) {
			if (bas[k]) {
				v[pi] ^= v[bas[k]];
				from[pi] ^= from[bas[k]];
			}
			else {
				bas[k] = pi;
				isbas[pi] = k;
				return;
			}
		}
	isbas[pi] = -1;
}

int erase (int id, int n) {
	int pi = 0;
	isbas[0] = -2;
	auto priority = [] (int i) { return isbas[i] == -1 ? 1000000000 : isbas[i]; };
	for (int i = 1; i <= n; i ++)
		if (from[i].test(id) and priority(i) > priority(pi))
			pi = i;
	if (!pi) return 0; // impossible if id <= n
	for (int i = 1; i <= n; i ++)
		if (i != pi and from[i].test(id)) {
			v[i] ^= v[pi];
			from[i] ^= from[pi];
		}
	/* debug("erase %d (%d %d %d)(%d %d %d)\n", */
	/* 		pi, bas[0], bas[1], bas[2], isbas[1], isbas[2], isbas[3]); */
	if (isbas[pi] != -1) bas[isbas[pi]] = 0, isbas[pi] = -1;
	return pi;
}

void Xor (int id, bs x, int n, int m) {
	if (x.none()) return;
	int pi = erase(id, n);
	/* debug("erase %d\n", pi); */
	/* for (int i = 1; i <= n; i ++) { */
	/* 	for (int k = 0; k < m; k ++) */
	/* 		debug("%d", v[i].test(k)); */
	/* 	debug(" (%d) ", isbas[i]); */
	/* 	for (int j = 1; j <= n; j ++) */
	/* 		debug("%d", from[i].test(j)); */
	/* 	debug("\n"); */
	/* } */
	/* debug("\n"); */
	if (!pi) return;
	v[pi] ^= x;
	insert(pi, m);
}

int main () {
	int n = read, m = read, q = read;
	std::fill(isbas, isbas + n + 1, 0);
	for (int i = 1; i <= n; i ++) {
		read(a[i]);
		v[i] = a[i] ^ a[i - 1];
		from[i].set(i);
		insert(i, m);
	}

	while (q --) {
		int o = read;
		if (o == 1) {
			int l = read, r = read;
			bs x = read;
			Xor(l, x, n, m);
			Xor(r + 1, x, n, m);
			for (int i = l; i <= r; i ++)
				a[i] ^= x;
		}
		if (o == 2) {
			int l = read, r = read;
			bs x = read;
			Xor(l, a[l] ^ x, n, m);
			for (int i = l + 1; i <= r; i ++)
				Xor(i, a[i] ^ a[i - 1], n, m);
			Xor(r + 1, a[r] ^ x, n, m);
			for (int i = l; i <= r; i ++)
				a[i] = x;
		}
		if (o == 3) {
			bs ans;
			for (int k = 0; k < m; k ++)
				if (!ans.test(k) and bas[k])
					ans ^= v[bas[k]];
			for (int k = 0; k < m; k ++)
				printf("%d", ans.test(k));
			puts("");
		}
	}
}
