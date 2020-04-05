#if 0
2020.04.05

再多点时间就能做出 D 啦。。。

首先每次删除一定删一段极大的串，那么把串分为若干段，每段是能删除的极大的串。
每次删除一个段后，可以发现两边的段可能可以合并为一个段，这样就通过一次操作使得段数减小了二。
如何删段最优？段没有什么直接的性质，考虑两个段之间的“间隙”，每个间隙是由相邻且相等的两个字符组成的。
由于始终有 段数 = 间隙数 + 1 ，可以考虑用最少的操作次数删掉所有间隙。

可以发现删间隙有两个操作：
1) 删掉两个相邻且不相等的间隙
2) 删掉任意一个间隙
记不同种类间隙数量的最大值和总和分别为 max 和 sum ，根据这两个操作不能得出删掉间隙需要的最小操作次数为：
max(ceil(sum / 2), max).

求方案，从左到右扫每个间隙，用栈维护当前还没有被删的间隙，对于当前扫到的间隙，
如果它与栈顶不相等且删掉它和栈顶会使得上式减小就删且出栈，否则入栈。
最后栈里面一定是相等的若干间隙，依次删除即可。

由于方案输出的是相对位置，可以利用线段树把绝对位置转换为相对位置。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
char s[maxn], t[maxn];
int pos[maxn];
int tot[26];
int ansx[maxn], ansy[maxn], ap;
int seg[maxn << 2], tag[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

int query (int now, int L, int R, int l, int r, bool c) {
	if (r < L or l > R) return 0;
	c |= tag[now];
	if (l <= L and R <= r) return c ? R - L + 1 : seg[now];
	int M = (L + R) >> 1;
	return query(ls, L, M, l, r, c) +
		query(rs, M + 1, R, l, r, c);
}

void modify (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return tag[now] = 1, seg[now] = R - L + 1, void();
	int M = (L + R) >> 1;
	modify(ls, L, M, l, r);
	modify(rs, M + 1, R, l, r);
	seg[now] = tag[now] ? R - L + 1 : seg[ls] + seg[rs];
}

int n;
void erase (int l, int r) {
	/* debug("%d %d\n", l, r); */
	++ ap;
	ansx[ap] = l - query(1, 1, n, 1, l - 1, 0);
	ansy[ap] = r - query(1, 1, n, 1, r, 0);
	modify(1, 1, n, l, r);
}

int f () {
	int sum = 0, max = 0;
	for (int c = 0; c < 26; c ++) max = std::max(max, tot[c]);
	for (int c = 0; c < 26; c ++) sum += tot[c];
	return std::max(max, (sum + 1) >> 1);
}

int main() {
	int T = read, shit = 0;
	while (T --) {
		++ shit;
		scanf("%s", s + 1);
		n = int(strlen(s + 1));

		ap = 0;
		std::fill(seg + 1, seg + n * 4 + 1, 0);
		std::fill(tag + 1, tag + n * 4 + 1, 0);
		std::fill(tot, tot + 26, 0);

		for (int i = 1; i < n; i ++)
			if (s[i] == s[i + 1])
				++ tot[s[i] - 'a'];

		int m = 0, now = f();
		for (int i = 1; i < n; i ++)
			if (s[i] == s[i + 1]) {
				if (m and t[m] != s[i]) {
					-- tot[t[m] - 'a'];
					-- tot[s[i] - 'a'];
					int neo = f();
					if (neo == now) {
						++ tot[t[m] - 'a'];
						++ tot[s[i] - 'a'];
						goto ifelse;
					}
					now = neo;
					erase(pos[m --], i);
				}
				else {
ifelse:
					++ m;
					t[m] = s[i];
					pos[m] = i + 1;
				}
			}

		pos[m + 1] = n + 1;
		for (int i = 1; i <= m; i ++)
			erase(pos[i], pos[i + 1] - 1);
		erase(1, n);

		/* if (shit + T == 4) { */
			printf("%d\n", ap);
			for (int i = 1; i <= ap; i ++)
				printf("%d %d\n", ansx[i], ansy[i]);
		/* } else if (shit == 4206) */
		/* 	puts(s + 1); */
	}
}
