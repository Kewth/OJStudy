#if 0
2020.04.09

直接考虑求出 a[S] 表示询问为集合 S 时的答案。
对于每个字符串，其贡献的是包含某元素的所有集合，做子集差分后容斥后就只有 2^len 个点有贡献。
然后通过子集和变换还原答案即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 24;
int a[maxl];
char s[10];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s);
		int b[3] = {s[0] - 'a', s[1] - 'a', s[2] - 'a'};
		std::sort(b, b + 3);
		if (b[0] == b[1] and b[1] == b[2])
			++ a[1 << b[0]];
		else if (b[0] == b[1])
			++ a[1 << b[1]],
			++ a[1 << b[2]],
			-- a[1 << b[1] | 1 << b[2]];
		else if (b[1] == b[2])
			++ a[1 << b[0]],
			++ a[1 << b[1]],
			-- a[1 << b[0] | 1 << b[1]];
		else
			++ a[1 << b[0]],
			++ a[1 << b[1]],
			++ a[1 << b[2]],
			-- a[1 << b[0] | 1 << b[1]],
			-- a[1 << b[0] | 1 << b[2]],
			-- a[1 << b[1] | 1 << b[2]],
			++ a[1 << b[0] | 1 << b[1] | 1 << b[2]];
	}

	for (int m = 1; m < maxl; m <<= 1)
		for (int i = 0; i < maxl; i += m << 1)
			for (int k = i; k < i + m; k ++)
				a[k + m] += a[k];

	int ans = 0;
	for (int i = 0; i < maxl; i ++)
		ans ^= a[i] * a[i];
	printf("%d\n", ans);
}
