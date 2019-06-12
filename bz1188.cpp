#if 0
2019.06.12

把每个豆子独立出来看做一个子游戏。
不同的豆之间不会相互干扰，可以用 SG 定理。
久违的一遍过。
#endif
#include <cstdio>
#include <set>

const int maxn = 21;
int a[maxn];
int sg[maxn];

inline int SG(int n) {
	int res = 0;
	for(int i = 0; i < n; i ++)
		if(a[i] & 1)
			res ^= sg[n - 1 - i];
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	sg[0] = 0;
	for(int i = 1; i < maxn; i ++) {
		std::set<int> trans;
		for(int j = 0; j < i; j ++)
			for(int k = 0; k <= j; k ++)
				trans.insert(sg[j] ^ sg[k]);
		while(trans.count(sg[i]))
			sg[i] ++;
	}
	while(T --) {
		int n, tot = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; i ++)
			scanf("%d", a + i);
		if(not SG(n)) {
			puts("-1 -1 -1");
			puts("0");
			continue;
		}
		for(int i = 0; i < n; i ++)
			if(a[i])
				for(int j = i + 1; j < n; j ++)
					for(int k = j; k < n; k ++) {
						a[i] --;
						a[j] ++;
						a[k] ++;
						if(not SG(n)) {
							if(not tot)
								printf("%d %d %d\n", i, j, k);
							tot ++;
						}
						a[i] ++;
						a[j] --;
						a[k] --;
					}
		printf("%d\n", tot);
	}
}
