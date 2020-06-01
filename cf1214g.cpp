#if 0
2020.06.01

  用 bitset 维护每一行，修改操作是很容易做到 O(m/w) 的，考虑维护答案，对于两行 x1, x2 ，
如果这两行之间不存在答案，当且仅当 a[x1] 包含 a[x2] 或者 a[x2] 包含 a[x1] ，其中 a[x] 表
示第 x 行的 bitset ，那么如果将 a 按 1 的数量排序，只要相邻两两有包含关系，就全局无解。
  用 set 维护 a 之间的相对顺序，再用另外一个 set 维护所有可行的答案 (x1, x2) ，满足 x1,
x2 这两行之间有解，并且 x1, x2 在排序后的序列中相邻，随着修改这些都是很好维护的。
  那么回答询问只需要在第二个 set 中随便拿一组 (x1, x2) 出来即可，无解当且仅当该 set 为空。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 2005;
std::bitset<maxn> bs[maxn], pre[maxn];
std::set<par> s1; // (size, id)
std::set<par> s2; // (ans.x1, ans.x2)

int n, m;
bool check (int i, int j) {
	if (i == 0 or j == n + 1) return 0;
	return (bs[i] & bs[j]) != bs[i];
}

void insert (int x) {
	par p(int(bs[x].count()), x);
	s1.insert(p);
	int _x = (-- s1.lower_bound(p)) -> second;
	int x_ = s1.upper_bound(p) -> second;
	s2.erase(par(_x, x_));
	if (check(_x, x)) s2.insert(par(_x, x));
	if (check(x, x_)) s2.insert(par(x, x_));
}

void erase (int x) {
	par p(int(bs[x].count()), x);
	int _x = (-- s1.lower_bound(p)) -> second;
	int x_ = s1.upper_bound(p) -> second;
	s1.erase(p);
	s2.erase(par(_x, x));
	s2.erase(par(x, x_));
	if (check(_x, x_)) s2.insert(par(_x, x_));
}

void print (int x1, int x2) {
	int y1 = int((bs[x1] & ~bs[x2])._Find_first());
	int y2 = int((bs[x2] & ~bs[x1])._Find_first());
	if (x1 > x2) std::swap(x1, x2);
	if (y1 > y2) std::swap(y1, y2);
	printf("%d %d %d %d\n", x1, y1, x2, y2);
}

int main () {
	read(n, m);
	for (int i = 1; i <= m; i ++) {
		pre[i] = pre[i - 1];
		pre[i].set(si(i));
	}

	s1.insert(par(-1, 0));
	s1.insert(par(m + 1, n + 1));
	for (int i = 1; i <= n; i ++)
		insert(i);

	int q = read;
	while (q --) {
		int x = read, l = read, r = read;
		erase(x);
		bs[x] ^= pre[r];
		bs[x] ^= pre[l - 1];
		insert(x);
		if (s2.empty()) puts("-1");
		else print(s2.begin() -> first, s2.begin() -> second);
	}
}
