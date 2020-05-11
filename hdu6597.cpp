#pragma GCC optimize(2)
#if 0
2020.05.11

  这是一个优秀的不公平博弈，所有状态都能用合法的超现实数表示，不存在先手必胜态。
  把超现实数用 x / y 这样的有理数表示即可，爆搜所有游戏的值，加法和偏序都很好实现，重点
是需要实现 P = {L|R} 的运算，这个根据定义按深度暴力枚举所有数即可。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef size_t si;
typedef std::string str;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator str () { char x[7]; return scanf("%s", x), x; }
} read;

ll gcd (ll a, ll b) {
	if (!b) return a;
	return gcd(b, a % b);
}

struct SN {
	int x, y;
	friend bool operator <= (SN, SN);
	friend bool operator < (SN, SN);
	int ceil () {
		ld c = std::ceil(ld(x) / y);
		return int(c);
	}
	int floor () {
		ld c = std::floor(ld(x) / y);
		return int(c);
	}
	SN (int x = 0, int y = 1): x(x), y(y) { }
	SN operator - () { return {-x, y}; }
};
bool operator <= (SN a, SN b) {
	return 1ll * a.x * b.y <= 1ll * b.x * a.y;
	/* return ld(a.x) / a.y <= ld(b.x) / b.y; */
}
bool operator < (SN a, SN b) {
	return a <= b && !(b <= a);
}
SN operator + (SN a, SN b) {
	ll X = 1ll * a.x * b.y + 1ll * b.x * a.y, Y = 1ll * a.y * b.y;
	ll G = gcd(std::abs(X), std::abs(Y));
	return {int(X / G), int(Y / G)};
}
SN operator | (SN l, SN r) {
	if (r <= l) debug("EAT SHIT\n");
	if (l < 0 && 0 < r) return 0;
	if (r <= 0) return - ((-r) | (-l));
	int x = l.ceil();
	if (x <= l && l <= x) ++ x;
	if (x < r) return x;
	int y = 1;
	while (1) {
		SN s = {1, y};
		while (s < r) {
			if (l < s) return s;
			++ s.x;
		}
		y <<= 1;
	}
}

int mystoi (str x) {
	int y = 0;
	for (si i = 0; i < 9; i ++) {
		if (x[i] == 'O') y ^= 0 << (i * 2);
		if (x[i] == 'X') y ^= 1 << (i * 2);
		if (x[i] == '.') y ^= 2 << (i * 2);
	}
	return y;
}
str myitos (int x) {
	str y;
	for (si i = 0; i < 9; i ++) {
		if ((x >> (i * 2) & 3) == 0) y += 'O';
		if ((x >> (i * 2) & 3) == 1) y += 'X';
		if ((x >> (i * 2) & 3) == 2) y += '.';
	}
	return y;
}

SN f[1 << 18];
bool vis[1 << 18];

SN F (str x) {
	int y = mystoi(x);
	if (vis[y]) return f[y];
	SN l = - 1000000000, r = 1000000000;
	for (si i = 0; i < 9; i ++) {
		if (x[i] == 'O') {
			str a = x, b = x, c = x;
			a[i] = '.';
			b[i] = '.';
			c[i] = '.';
			if (i % 3 >= 1) a[i - 1] = '.', c[i - 1] = '.';
			if (i % 3 < 2) a[i + 1] = '.', c[i + 1] = '.';
			if (i / 3 >= 1) b[i - 3] = '.', c[i - 3] = '.';
			if (i / 3 < 2) b[i + 3] = '.', c[i + 3] = '.';
			l = std::max({l, F(a), F(b), F(c)});
		}
		if (x[i] == 'X') {
			str a = x;
			a[i] = '.';
			r = std::min(r, F(a));
		}
	}
	vis[y] = 1;
	return f[y] = l | r;
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		SN ans = 0;
		while (n --) {
			str s1 = read, s2 = read, s3 = read;
			str s = str() + s1[0] + s1[2] + s1[4] +
				s2[0] + s2[2] + s2[4] +
				s3[0] + s3[2] + s3[4];
			for (si i = 0; i < 9; i ++)
				if (s[i] == '#')
					s[i] = '.';
			ans = ans + F(s);
			/* debug("%d/%d\n", F(s).x, F(s).y); */
		}
		bool x = ans <= 0, y = 0 <= ans;
		if (x && y) puts("Second");
		if (!x && !y) puts("First");
		if (x && !y) puts("Bob");
		if (!x && y) puts("Alice");
	}
}
