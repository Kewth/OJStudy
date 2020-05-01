#if 0
2020.04.30

后缀异或和异或上全局异或和后可以转为前缀异或和，用可持久化 01 Trie 树维护即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 600005, maxk = 30;
int ch[maxn * (maxk + 1)][2], size[maxn * (maxk + 1)], cp;
int tr[maxn];

int lain (int an, int x, int k) {
	int now = ++ cp;
	ch[now][0] = ch[an][0];
	ch[now][1] = ch[an][1];
	size[now] = size[an] + 1;
	if (k >= 0) {
		int t = x >> k & 1;
		ch[now][t] = lain(ch[now][t], x, k - 1);
	}
	return now;
}

int query (int a, int b, int x, int k) {
	if (k == -1) return 0;
	int t = x >> k & 1;
	if (size[ch[a][!t]] > size[ch[b][!t]])
		return 1 << k | query(ch[a][!t], ch[b][!t], x, k - 1);
	return query(ch[a][t], ch[b][t], x, k - 1);
}

int main () {
	int n = read, q = read, las = 0;
	for (int i = 1; i <= n; i ++) {
		tr[i] = lain(tr[i - 1], las, maxk - 1);
		las ^= int(read);
	}

	while (q --) {
		char o = read;
		if (o == 'A') {
			++ n;
			tr[n] = lain(tr[n - 1], las, maxk - 1);
			las ^= int(read);
		}
		if (o == 'Q') {
			int l = read, r = read, x = read;
			printf("%d\n", query(tr[r], tr[l - 1], las ^ x, maxk - 1));
		}
	}
}
