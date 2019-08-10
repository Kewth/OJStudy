#if 0
2019.08.09

扩展 KMP 模板。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100005;
char s[maxn], t[maxn];
int a[maxn];
int b[maxn];

void exkmp(char *s, char *t, int n, int m, int *lcp, int *z) {
	int l, r = 0;
	for(int i = 1; i <= n; i ++) {
		lcp[i] = i <= r ? std::min(r - i + 1, z[i - l + 1]) : 0;
		while(i + lcp[i] <= n and s[i + lcp[i]] == t[lcp[i] + 1])
			lcp[i] ++;
		if(i > 1 and i + lcp[i] - 1 > r) {
			l = i;
			r = i + lcp[i] - 1;
		}
	}
}

int main() {
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	int n = strlen(s + 1), m = strlen(t + 1);
	exkmp(t, t, m, m, b, b);
	exkmp(s, t, n, m, a, b);
	for(int i = 1; i <= m; i ++)
		printf("%d ", b[i]);
	puts("");
	for(int i = 1; i <= n; i ++)
		printf("%d ", a[i]);
	puts("");
}

