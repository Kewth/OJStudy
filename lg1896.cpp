#include <cstdio>

inline int read () { int x; scanf("%d", &x); return x; }
const int N = 9;
void predo (int);

long long f[N + 1][N * N + 1][1 << N]; // 1 << N 即 2 的 N 次方
bool ill[1 << N]; // 一个状态是否有左右相邻的棋子
int main () {
	int n = read(), K = read();
	predo(n); // 预处理 ill 数组
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = 0; j <= i * n; j ++)
			for (int S = 0; S < (1 << n); S ++)
				if (!ill[S]){
					int tot = 0; // 计算二进制里有多少 1
					for (int k = 0; k < n; k ++)
						tot += S >> k & 1;
					if (tot <= j)
						for (int T = 0; T < (1 << n); T ++)
							// 需判断是否有上下相邻棋子
							if (!ill[T] and (S & T) == 0 and
									(S & (T << 1)) == 0 and ((S << 1) & T) == 0)
								f[i][j][S] += f[i - 1][j - tot][T];
				}
	long long ans = 0;
	for (int S = 0; S < (1 << n); S ++)
		ans += f[n][K][S];
	printf("%lld\n", ans);
}

void predo (int n) {
	for (int S = 0; S < (1 << n); S ++) {
		for (int i = 0; i + 1 < n; i ++)
			if ((S >> i & 1) and (S >> (i + 1) & 1))
				ill[S] = 1;
		/* if (!ill[S]) */
		/* 	printf("%d\n", S); */
	}
}

/* int count (int S) { return __builtin_popcount(unsigned(S)); } */
