#if 0
2019.11.09

一共只有三段，分类讨论并暴力扫描即可。
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

const int maxn = 1000005;
char s[maxn];
int f[maxn][2];

int main() {
	int T = read;
	while(T --) {
		int n = read;
		scanf("%s", s + 1);

		int L = 0;
		for(int i = 1; i <= n; i ++)
			if(s[i] == 'p') {
				L = i;
				break;
			}

		int R = 0;
		for(int i = n; i; i --)
			if(s[i] == 'k') {
				R = i;
				break;
			}

		if(!L or !R or L > R) {
			puts("-1");
			continue;
		}

		int a = 0;
		for(int i = L; i <= R; i ++)
			if(s[i] == 'i') {
				a = i;
				break;
			}

		int b = 0;
		for(int i = R; i >= L; i --)
			if(s[i] == 'n') {
				b = i;
				break;
			}

		if(!a or !b or a > b) {
			puts("-1");
			continue;
		}

		int ans = b - a - 1;

		for(int i = b; i >= a; i --)
			if(s[i] == 'i') {
				ans = std::max(ans, i - L - 1);
				break;
			}

		for(int i = a; i <= b; i ++)
			if(s[i] == 'n') {
				ans = std::max(ans, R - i - 1);
				break;
			}

		printf("%d\n", ans);
	}
}
