#if 0
2019.08.17

贪心，从左到右扫一遍，
当前的字母单独拿出来和上一个不同就只拿这一个，
否则把当前字母和下一个字母拼起来。
可以发现分出的字符串长度只有 1 和 2 。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
char s[maxn];

int main() {
	scanf("%s", s);
	int n = int(strlen(s)), last = -1, ans = 0;
	for(int i = 0; i < n; i ++) {
		if(last != -1 and last == s[i]) {
			i ++;
			last = -1;
		} else
			last = s[i];
		if(i < n)
			ans ++;
		// debug("%d %d\n", i, last);
	}
	printf("%d\n", ans);
}
