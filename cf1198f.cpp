#if 0
2019.12.25

众所周知多个数的 gcd 下降的速度极快，一般很快就会变为 1 ，一般可以各种乱搞。
在本题中只要不断将序列 random_shuffle 然后贪心地前面一段放 A 集合后面一段放 B 集合即可。
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

const int maxn = 100005;
Par p[maxn];
int ans[maxn];

int main() {
	srand(19491001);

	int n = read;
	for(int i = 1; i <= n; i ++)
		p[i] = Par(read, i);

	for(int t = 0; t <= 11000000; t += n + 10) {
		std::random_shuffle(p + 1, p + n + 1);

		int x = 0, y = 0;
		for(int i = 1; i <= n; i ++) {
			if(x != 1) {
				int z = std::__gcd(x, p[i].first);
				if(z != x) {
					x = z;
					ans[p[i].second] = 1;
				}
				else {
					y = std::__gcd(y, p[i].first);
					ans[p[i].second] = 2;
				}
			}
			else {
				y = std::__gcd(y, p[i].first);
				ans[p[i].second] = 2;
			}
		}

		if(x == 1 and y == 1) {
			puts("YES");
			for(int j = 1; j <= n; j ++)
				printf("%d ", ans[j]);
			puts("");
			return 0;
		}
	}

	puts("NO");
}
