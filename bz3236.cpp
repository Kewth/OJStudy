#pragma GCC optimize(3)
#if 0
2020.01.13

猛然意识到 k 维偏序可以离线解决不带修改的 k 维数点问题。
并且复杂度比 k 层树套树要优秀一个 log 。
但不知道为什么根号 log 的莫队加树状数组跑得能飞快，过 1e6 什么鬼？

有个 yy 出来的优化，当询问很多但数很少的时候，
直接将所有询问点和数点放一起做偏序 log 里面的数会很大，是 q + n 的。
可以每 k 个询问就和所有数点放一起做偏序，这样 log 里面的数就是 n + k 的。
但是 log 的系数会是 q / k (k + n) 而不是 q n ，找到平衡位置即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[64 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 100005, maxq = 1000005;
struct Dot {
	int x, y, z, id, t;
};
int ans1[maxq], ans2[maxq];
int pre[maxn];
Dot fuck[maxq * 4 + maxn], tmp[maxq * 4 + maxn];
int bit[maxn];

inline void modify(int p, int x) {
	for(int k = p + 1; k < maxn; k += k & -k)
		bit[k] += x;
}

inline int query(int p) {
	int res = 0;
	for(int k = p + 1; k; k -= k & -k)
		res += bit[k];
	return res;
}

void cdq(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);

	int p1 = l, p = 0, tot = 0;
	for(int i = mid + 1; i <= r; i ++) {
		while(p1 <= mid and fuck[p1].y < fuck[i].y) {
			tmp[++ p] = fuck[p1 ++];
			if(!tmp[p].id) {
				modify(tmp[p].z, 1);
				++ tot;
			}
		}
		tmp[++ p] = fuck[i];
		if(tmp[p].id and tot) {
			ans1[tmp[p].id] += tmp[p].t * tot;
			ans2[tmp[p].id] += tmp[p].t * query(tmp[p].z - 1);
		}
	}

	for(int i = l; i < p1; i ++)
		if(!fuck[i].id)
			modify(fuck[i].z, -1);
	std::copy(fuck + p1, fuck + mid + 1, tmp + p + 1);
	std::copy(tmp + 1, tmp + r - l + 2, fuck + l);
}

char buffer[64 * 1024 * 1024], *s = buffer;
char stack[64], *sp = stack;
void print(int x, char en) {
	if(x == 0) *(s ++) = '0';
	else {
		while(x) *(++ sp) = '0' + x % 10, x /= 10;
		while(sp != stack) *(s ++) = *(sp --);
	}
	*(s ++) = en;
}

bool cmp(Dot a, Dot b) {
	if(a.x == b.x)
		return a.y == b.y ? a.z < b.z : a.y < b.y;
	return a.x < b.x;
}

Dot first[maxn];
int main() {
	int n = read, q = read, p = 0;
	for(int i = 1; i <= n; i ++) {
		int a = read;
		first[i] = {i << 1, a, pre[a], 0, 0};
		pre[a] = i;
	}

	int K = n * 3;
	for(int i = 1; i <= q; i ++) {
		int l = read, r = read, a = read, b = read;
		fuck[++ p] = {r << 1 | 1, b + 1, l, i, 1};
		fuck[++ p] = {r << 1 | 1, a, l, i, -1};
		fuck[++ p] = {l * 2 - 1, b + 1, l, i, -1};
		fuck[++ p] = {l * 2 - 1, a, l, i, 1};
		if((i % K == 0 and q - i + 1 >= K / 2) or i == q) {
			for(int j = 1; j <= n; j ++)
				fuck[++ p] = first[j];
			std::sort(fuck + 1, fuck + p + 1, cmp);
			cdq(1, p);
			p = 0;
		}
	}

	for(int i = 1; i <= q; i ++) {
		print(ans1[i], ' ');
		print(ans2[i], '\n');
	}

	fwrite(buffer, 1, size_t(s - buffer), stdout);
}
