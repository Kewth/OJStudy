#if 0
2019.10.25
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 404, maxq = 100005;
char s[maxn][maxn];
char t[maxq];
int x[maxn * maxn], y[maxn * maxn];

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);
	scanf("%s", t + 1);

	int l = 0, r = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(s[i][j] == '@') {
				l = r = 1;
				x[1] = i;
				y[1] = j;
				s[i][j] = '.';
			}

	for(int i = 1; t[i]; i ++) {
		int tx = x[r], ty = y[r];
		if(t[i] == 'W')
			tx --;
		else if(t[i] == 'S')
			tx ++;
		else if(t[i] == 'A')
			ty --;
		else if(t[i] == 'D')
			ty ++;

		/* debug("%d %d\n", tx, ty); */

		if(!tx or !ty or tx > n or ty > m) {
			puts("GG");
			return 0;
		}

		r ++;
		x[r] = tx;
		y[r] = ty;

		if(s[tx][ty] == 'o')
			s[tx][ty] = '.';
		else
			l ++;
	}

	for(int i = l; i < r; i ++)
		s[x[i]][y[i]] = 'X';
	s[x[r]][y[r]] = '@';

	for(int i = 1; i <= n; i ++)
		puts(s[i] + 1);
}
