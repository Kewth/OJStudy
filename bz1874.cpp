#if 0
2019.06.12

SG 定理裸题一遍过。
#endif
#include <cstdio>
#include <set>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 12, maxv = 1010;
int a[maxn], b[maxn];
int sg[maxv];

int game_sg(int n) {
	int res = 0;
	for(int i = 1; i <= n; i ++)
		res ^= sg[a[i]];
	return res;
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	int m = input();
	for(int i = 1; i <= m; i ++)
		b[i] = input();
	for(int i = 1; i < maxv; i ++) {
		std::set<int> trans;
		for(int j = 1; j <= m; j ++)
			if(i >= b[j])
				trans.insert(sg[i - b[j]]);
		while(trans.count(sg[i]))
			sg[i] ++;
	}
	if(not game_sg(n))
		puts("NO");
	else {
		puts("YES");
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(a[i] >= b[j]) {
					a[i] -= b[j];
					if(not game_sg(n)) {
						printf("%d %d\n", i, b[j]);
						return 0;
					}
					a[i] += b[j];
				}
	}
}
