#if 0
2020.01.04

数列可分为两部分：左边一部分排过序的，右边一部分在上次排序后插入的。
对于修改，记全局 tag 。
分别维护这两部分。

左边用 01 Trie 树维护，记一个标记 tritag 表示上次排序时的 tag 。
那么询问这部分的前缀和就根据 tritag 在 01 Trie 树上跑，
每个点记录经过它的数字个数 size 以及经过它的数字个数的每个二进制位个数。
这样就可以根据 tag 计算答案。

右边直接维护前缀和，准确来讲是每个二进制位 1 的个数的前缀和。

这样询问拆成前缀和就很好处理了，排序的时候直接将右边的部分全部扔到左边并更新 tritag 标记即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005, maxk = 30;
int seq[maxn][maxk], sp;
int ch[maxn * maxk][2], size[maxn * maxk], tri[maxn * maxk][maxk], cp = 1;
int tag, tritag;

ll seq_query(int *a, int tot) {
	ll sum = 0;
	for(int k = 0; k < maxk; k ++)
		if(tag >> k & 1) sum += (1ll << k) * (tot - a[k]);
		else sum += (1ll << k) * a[k];
	return sum;
}

ll seq_insert(int *a, int *base, int x) {
	ll sum = 0;
	for(int k = 0; k < maxk; k ++)
		a[k] = base[k] + (x >> k & 1);
	return sum;
}

ll trie_query(int n) {
	int now = 1;
	ll sum = 0;
	for(int k = maxk - 1; k >= 0; k --) {
		int lt = ch[now][tritag >> k & 1], rt = ch[now][!(tritag >> k & 1)];
		if(n <= size[lt]) {
			now = lt;
		}
		else {
			n -= size[lt];
			sum += seq_query(tri[lt], size[lt]);
			now = rt;
		}
	}
	ll fuck = seq_query(tri[now], size[now]);
	if(size[now]) sum += fuck * n / size[now];
	return sum;
}

void trie_insert(int x) {
	int now = 1;
	for(int k = maxk - 1; k >= 0; k --) {
		++ size[now];
		seq_insert(tri[now], tri[now], x);
		int &to = ch[now][x >> k & 1];
		if(!to) to = ++ cp;
		now = to;
	}
	++ size[now];
	seq_insert(tri[now], tri[now], x);
}

void insert(int x) {
	++ sp;
	seq_insert(seq[sp], seq[sp - 1], x ^ tag);
}

ll query(int n) {
	if(n <= size[1]) return trie_query(n);
	return trie_query(size[1]) + seq_query(seq[n - size[1]], n - size[1]);
}

void modify(int x) {
	tag ^= x;
}

void sort() {
	while(sp) {
		int x = 0;
		for(int k = 0; k < maxk; k ++)
			if(seq[sp][k] != seq[sp - 1][k])
				x |= 1 << k;
		trie_insert(x);
		-- sp;
	}
	tritag = tag;
}

int main() {
	int n = read;
	while(n --) insert(read);
	int q = read;
	while(q --) {
		int op = read;
		if(op == 1) insert(read);
		if(op == 2) {
			ll tmp = query(read - 1);
			printf("%lld\n", query(read) - tmp);
		}
		if(op == 3) modify(read);
		if(op == 4) sort();
	}
}
