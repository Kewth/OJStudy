#if 0
2019.12.07

惟一的限制在于曲线不能穿过边界，那么只需要考虑在边界上的点对，
而边界实际是一个环，不合法当且仅当环上有点对相交，
而把环找任意一点断成链，问题可以转换为一类括号匹配。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
Par pr[maxn];

int r, c;
int getpos(int x, int y) {
	if(x == 0) return c - y;
	if(y == 0) return c + x;
	if(x == r) return r + c + y;
	if(y == c) return (r + c) * 2 - x;
	return -1;
}

bool vis[maxn];
int stack[maxn], sp;

int main() {
	read(r, c);
	int n = read;

	int p = 0;
	for(int i = 1; i <= n; i ++) {
		int x1 = read, y1 = read, x2 = read, y2 = read;
		int p1 = getpos(x1, y1), p2 = getpos(x2, y2);
		if(p1 == -1 or p2 == -1) continue;
		pr[++ p] = Par(p1, i);
		pr[++ p] = Par(p2, i);
	}

	std::sort(pr + 1, pr + p + 1);
	for(int i = 1; i <= p; i ++) {
		int id = pr[i].second;
		if(!vis[id]) {
			vis[id] = 1;
			stack[++ sp] = id;
		}
		else if(stack[sp] != id)
			return puts("NO"), 0;
		else
			-- sp;
	}

	puts("YES");
}
