#if 0
2019.10.12
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

char s[100][100];
bool vis[10000000];

int main() {
	int T = input();
	while(T --) {
		int n = input();
		bool ans = 1;
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s[i] + 1);
			int now = s[i][1] * 10000 + s[i][2] * 100 + s[i][3];
			if(vis[now])
				ans = 0;
			vis[now] = 1;
		}
		if(ans)
			puts("Yes");
		else
			puts("No");
		for(int i = 1; i <= n; i ++) {
			int now = s[i][1] * 10000 + s[i][2] * 100 + s[i][3];
			vis[now] = 0;
		}
	}
}
