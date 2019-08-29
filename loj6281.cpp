#if 0
2019.08.28

分块 + 标记。
当一个块所有值都为 1/0 时可跳过修改操作，而每个数开方到 1 最多开 log 次。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 50200, maxb = 233;
int s[maxb][maxb];
int sum[maxb];
bool allone[maxb];

int b, ans;

void extract_one(int l, int r) {
	for(int i = l; i <= r; i ++) {
		int &now = s[i / b][i % b];
		sum[i / b] -= now;
		now = int(sqrt(now));
		sum[i / b] += now;
	}
	allone[l / b] = true;
	for(int i = 0; i < b; i ++)
		if(s[l / b][i] > 1)
			allone[l / b] = false;
}

void extract_all(int l, int r) {
	for(int i = l; i <= r; i ++)
		if(not allone[i])
			extract_one(i * b, i * b + b - 1);
}

void query_one(int l, int r) {
	for(int i = l; i <= r; i ++)
		ans += s[i / b][i % b];
}

void query_all(int l, int r) {
	for(int i = l; i <= r; i ++)
		ans += sum[i];
}

int main() {
	int n = input(), q = n;

	b = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		sum[i / b] += (s[i / b][i % b] = input());

	while(q --) {
		int typ = input(), l = input() - 1, r = input() - 1;
		input();

		if(typ == 0) {
			if(l / b == r / b)
				extract_one(l, r);
			else {
				extract_one(l, l / b * b + b - 1);
				extract_all(l / b + 1, r / b - 1);
				extract_one(r / b * b, r);
			}
		}

		else {
			ans = 0;
			if(l / b == r / b)
				query_one(l, r);
			else {
				query_one(l, l / b * b + b - 1);
				query_all(l / b + 1, r / b - 1);
				query_one(r / b * b, r);
			}
			printf("%d\n", ans);
		}
	}
}
