/*
 * Author: Kewth

 * Date:
  2020.11.03

 * Solution:
  In blog.

 * Digression:
  自然溢出哈希用 998244353 作 base 就被卡，用 297 就没有问题？

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int X = 1000000007, Y = 998244353;
struct Hash2 {
	 int x, y;
	 static Hash2 base;
	 Hash2 () { }
	 Hash2 (int val): x(val), y(val) { }
	 Hash2 (int x, int y): x(x), y(y) { }
};
Hash2 Hash2::base = {300000007, 23456789};
Hash2 operator * (Hash2 a, Hash2 b) { return {int(1ll * a.x * b.x % X), int(1ll * a.y * b.y % Y)}; }
Hash2 operator - (Hash2 a, Hash2 b) { return {(a.x + X - b.x) % X, (a.y + Y - b.y) % Y}; }
Hash2 operator + (Hash2 a, Hash2 b) { return {(a.x + b.x) % X, (a.y + b.y) % Y}; }
bool operator == (Hash2 a, Hash2 b) { return a.x == b.x and a.y == b.y; }
bool operator < (Hash2 a, Hash2 b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }

#if 0
// 这个会 WA
const int base = 998244353;
typedef unsigned long long ull;
#elif 1
const int base = 297;
typedef unsigned long long ull;
#else
auto base = Hash2::base;
typedef Hash2 ull;
#endif

const int maxn = 2020;
struct Ans {
	int i, slen, tlen;
};
bool operator < (Ans a, Ans b) {
	return a.slen + a.tlen < b.slen + b.tlen;
}

int s[maxn], t[maxn];
ull spre[maxn], tpre[maxn];
ull po[maxn];
int prev[maxn], next[maxn], size[maxn];

ull get (ull *pre, int l, int r) {
	return pre[r] - pre[l - 1] * po[r - l + 1];
}

int main () {
	int n = 0, m = 0, c;
	while ((c = getchar()) != '\n') s[++ n] = c;
	while ((c = getchar()) != '\n') t[++ m] = c;

	po[0] = 1;
	for (int i = 1; i <= n or i <= m; i ++)
		po[i] = po[i - 1] * base;
	for (int i = 1; i <= n; i ++)
		spre[i] = spre[i - 1] * base + ull(s[i]);
	for (int i = 1; i <= m; i ++)
		tpre[i] = tpre[i - 1] * base + ull(t[i]);

	Ans ans = {1, n, m};
	for (int len = 1; len <= n; len ++) {
		std::fill(prev, prev + n + 1, 0);
		std::fill(next, next + n + 1, 0);
		std::fill(size, size + n + 1, 0);
		std::map<ull, int> las;
		for (int r = len; r <= n; r ++) {
			ull h = get(spre, r - len + 1, r);
			int &x = las[h];
			if (!x) size[x = r] = 1;
			else if (r >= x + len) {
				next[x] = r;
				prev[r] = x;
				size[r] = size[x] + 1;
				x = r;
			}
		}
		for (int r = len; r <= n; r ++)
			if (!prev[r]) {
				int lasR = las[get(spre, r - len + 1, r)];
				if ((m - n) % size[lasR]) continue;
				int tlen = len + (m - n) / size[lasR];
				if (tlen < 0) continue;
				ull replace = get(tpre, r - len + 1, r - len + tlen);
				ull now = 0;
				for (int R = r; R; R = next[R]) {
					now = now * po[R - prev[R] - len] + get(spre, prev[R] + 1, R - len);
					now = now * po[tlen] + replace;
				}
				now = now * po[n - lasR] + get(spre, lasR + 1, n);
				Ans check = {r - len + 1, len, tlen};
				if (now == tpre[m] and check < ans)
					ans = check;
			}
	}

	printf("s/");
	for (int i = 0; i < ans.slen; i ++)
		putchar(s[ans.i + i]);
	printf("/");
	for (int i = 0; i < ans.tlen; i ++)
		putchar(t[ans.i + i]);
	printf("/g\n");
}
