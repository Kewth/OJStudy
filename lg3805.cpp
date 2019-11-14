#if 0
2019.11.14

manacher 模板。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 11000010;
char s[maxn << 1];
int r[maxn << 1];

void manacher(int n) {
	int M = 0, R = 0;
	s[n + 1] = 1;
	for(int i = 1; i <= n; i ++) {
		r[i] = i <= R ? std::min(r[M - (i - M)], R - i) : 0;
		while(s[i - r[i] - 1] == s[i + r[i] + 1])
			++ r[i];
		if(i + r[i] > R) {
			M = i;
			R = i + r[i];
		}
	}
}

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	for(int i = n; i; i --) {
		s[i << 1] = s[i];
		s[i << 1 | 1] = '#';
	}
	s[1] = '#';

	manacher(n << 1 | 1);
	int ans = 0;
	for(int i = 1; i <= (n << 1 | 1); i ++)
		if(s[i] == '#')
			ans = std::max(ans, r[i]);
		else
			ans = std::max(ans, r[i]);

	printf("%d\n", ans);
}
