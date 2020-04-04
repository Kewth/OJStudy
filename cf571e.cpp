#if 0
2020.02.13

人间之屑。
做个人吧。

先不考虑无解的情况。

每个质数分开考虑，乘法看作加法。
每个数列的每个质数看作一个集合，用 a + bx 表示该数列在该质数上的可能的指数，
其中 x 对于同一数列不同质数要取同一个值。

两个数列合并，相当于对每个质数将集合取交，
而两个 a + bx 表示的集合取交后仍然可以用 a + bx 表示，
问题要求的就是合并到最后，每个质数对应的集合的 a 。

考虑处理数列合并。
对于每个质数，可以列出方程 a + bx = A + By ，
其中 x, y 分别是两个数列取的幂系数。
由此列出若干二元一次方程，求解。

如果存在唯一解，解出 x, y 后带入到每个质数的 a + bx 中即可得到新的 a ，
而新的 b 全部都是 0 ，因为此时这个数列只剩下一个常数。

如果存在无数解，也就是说所有方程组实际上是一样的，
那么对于 a + bx = A + By 用 exgcd 解不定方程，
找到 x, y 的最小非负整数解，同样带入到每个质数的 a + bx 中，
不同的是此时新的 b 为 lcm(b, B) 。

中间出现各种不顺利的情况都能判无解。
细节巨多，运算不当还可能爆 long long ，
需要精准把握，比如在 exgcd 后求 x, y, a 的时候快速乘取模。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int mod = 1000000007;

ll mul(ll x, ll y, ll z) {
	if(!z) return x * y;
	ll tmp = x * y - ll(ld(x) / z * y + 0.5) * z;
	return tmp < 0 ? tmp + z : tmp;
}

ll power(ll x, ll k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

struct Data {
	ll a, b;
	Data(ll a = 0, ll b = 0): a(a), b(b) { }
};
struct Set {
	std::map<int, Data> m;
};
struct Equation { // aX - bY = c
	ll a, b, c;
	Equation(): a(0), b(0), c(0) { }
};

Set operator & (Set s1, Set s2) {
	debug("merge set\n");

	std::map<int, Equation> m;
	for(auto p : s1.m) {
		m[p.first].a = p.second.b;
		m[p.first].c -= p.second.a;
	}
	for(auto p : s2.m) {
		m[p.first].b = p.second.b;
		m[p.first].c += p.second.a;
	}

	for(auto p : m)
		debug("%d: %lldx - %lldy = %lld\n",
				p.first, p.second.a, p.second.b, p.second.c);

	ll A = 0, B = 0, C = 0, ya = 0, xa = 0, xyb = 0;
	for(auto p : m) {
		ll a = p.second.a, b = p.second.b, c = p.second.c;
		if(!a and !b) {
			if(c)
				puts("-1"), exit(0);
			continue;
		}

		if(a * xa - b * ya != c * xyb)
			puts("-1"), exit(0);

		ya = c * A - C * a;
		xa = c * B - C * b;
		xyb = B * a - b * A;
		A = a;
		B = b;
		C = c;

		if(!xyb and (xa or ya)) // 无解
			puts("-1"), exit(0);
		if(xyb and (xa % xyb or ya % xyb)) // 无整数解
			puts("-1"), exit(0);

		debug("%lldx = %lld ; %lldy = %lld\n",
				xyb, xa, xyb, ya);
	}

	Set s;
	if(xyb) {
		ll x = xa / xyb, y = ya / xyb;
		if(x < 0 or y < 0)
			puts("-1"), exit(0);
		for(auto p : s1.m)
			s.m[p.first] = Data(p.second.a + p.second.b * x, 0);
		for(auto p : s2.m)
			s.m[p.first] = Data(p.second.a + p.second.b * y, 0);
	} else {
		ll x, y, b, fuck;
		ll g = exgcd(A, B, x, y);
		if(g) {
			if(C % g)
				puts("-1"), exit(0);
			// FIXME: overflow
			y = - y;
			fuck = C / g;
			b = A / g * B;
		} else {
			if(C)
				puts("-1"), exit(0);
			x = y = b = 0;
		}
		debug("x = %lld, y = %lld\n", x * fuck, y * fuck);

		for(auto p : s1.m) {
			ll a = p.second.a + mul(mul(p.second.b, x, b), fuck, b);
			if(b) {
				a += (p.second.a - a) / b * b;
				if(a < p.second.a) a += b;
			} else if(a < p.second.a)
				puts("-1"), exit(0);
			s.m[p.first] = Data(a, b);
		}
		for(auto p : s2.m) {
			ll a = p.second.a + mul(mul(p.second.b, y, b), fuck, b);
			if(b) {
				a += (p.second.a - a) / b * b;
				if(a < p.second.a) a += b;
			} else if(a < p.second.a)
				puts("-1"), exit(0);
			if(a >= s.m[p.first].a)
				s.m[p.first] = Data(a, b);
		}
	}

	for(auto p : s.m)
		debug("%d: %lld + %lldz\n", p.first, p.second.a, p.second.b);
	debug("\n");

	return s;
}

int minp(int x) {
	int p = 2;
	while(x % p and p * p <= x) ++ p;
	return p * p > x ? x : p;
}

int main() {
	int n = read;
	Set all;

	for(int i = 1; i <= n; i ++) {
		Set now;

		int a = read, b = read;
		while(a > 1) {
			int p = minp(a);
			++ now.m[p].a;
			a /= p;
		}
		while(b > 1) {
			int p = minp(b);
			++ now.m[p].b;
			b /= p;
		}

		all = i == 1 ? now : all & now;
	}

	ll ans = 1;
	for(auto p : all.m)
		(ans *= power(p.first, p.second.a)) %= mod;
	printf("%lld\n", ans);
}
