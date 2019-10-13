#if 0
2019.10.12
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 1000005;
char s[maxn], t[maxn];
bool vis[maxn];

int main() {
	int T = input();
	while(T --) {
		int n = input(), m = input(), r = input(), c = input();

		for(int i = 0; i < n; i ++)
			scanf("%s", s + i * m);
		for(int i = 0; i < n; i ++)
			scanf("%s", t + i * m);

		for(int i = 0; i < n * m; i ++)
			if(t[i] == '1')
				s[i] = '1' + '0' - s[i];

		for(int i = 0; i < n * m; i ++)
			vis[i] = 0;

		for(int i = 0; i < n * m; i ++)
			if(!vis[i]) {
				int tot = 0;
				for(int x = i / m; x < n; x += r)
					for(int y = i % m; y < m; y += c) {
						vis[x * m + y] = 1;
						if(s[x * m + y] == '1')
							tot ++;
					}
				if(tot & 1) {
					puts("No");
					goto GET;
				}
			}
		puts("Yes");
GET:;
	}
}
