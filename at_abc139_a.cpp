#if 0
2019.09.01
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	char s[10], t[10];
	scanf("%s", s);
	scanf("%s", t);
	int ans = 0;
	for(int i = 0; i < 3; i ++)
		if(s[i] == t[i])
			ans ++;
	printf("%d\n", ans);
}
