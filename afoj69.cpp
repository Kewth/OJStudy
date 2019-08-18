#if 0
2019.08.09

贪心即可，每次需要左括号的时候就把最右边的左括号换过来。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100000;
char s[maxn];

int main() {
	int n = input(), tot = 0, ans = 0;
	scanf("%s", s + 1);
	for(int i = 1, j = n + 1; i <= n; i ++) {
		if(s[i] == '(')
			tot ++;
		else if(tot)
			tot --;
		else {
			j --;
			while(j > 0 and s[j] == ')')
				j --;
			if(j <= i) {
				ans = -1;
				break;
			}
			s[i] = '(';
			s[j] = ')';
			ans ++;
			tot ++;
		}
		// debug("%d - %d, %d\n", i, j, tot);
	}
	if(tot)
		ans = -1;
	printf("%d\n", ans);
	debug("%s", s + 1);
}
