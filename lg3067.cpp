#if 0
2018.02.27

一般的折半是两边 2^n 爆搞，这题 n=20 ，给我可以一次 2^n 过的错觉。
事实上折半后需要 2^n * 2^n 统计答案，枚举方案再枚举划分。
不能直接 map 统计答案，这样会有情况算重复，
正确的做法是把折半搜到的方案全记下来再分别排序，一起统计答案。
统计答案为了不算重复可以开 2^n 数组记录状态是否被用到。

#endif
#include <bits/stdc++.h>

int input() { int res; scanf("%d", &res); return res; }

typedef unsigned long ulong;
typedef std::pair<int, int> par;
const int maxn = 20;
int num[maxn];
bool used[1 << maxn];
std::vector<par> left, right;

int main() {
	int n = input();
	int m = n >> 1;
	for(int i=0; i<n; i++)
		num[i] = input();
	for(int S=0; S<(1<<m); S++)
		for(int T=0; T<(1<<m); T++)
			if((T | S) == S) {
				int sum = 0;
				for(int i=0; i<m; i++)
					if(T >> i & 1) sum += num[i];
					else if(S >> i & 1) sum -= num[i];
				left.push_back(par(sum, S));
			}
	int k = n - m;
	for(int S=0; S<(1<<k); S++)
		for(int T=0; T<(1<<k); T++)
			if((T | S) == S) {
				int sum = 0;
				for(int i=0; i<k; i++)
					if(T >> i & 1) sum += num[m + i];
					else if(S >> i & 1) sum -= num[m + i];
				right.push_back(par(sum, S << m));
			}
	right.push_back(par(INT_MAX >> 1, 0));
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	for(ulong l=0, r=0; l<left.size(); l++) {
		/* fprintf(stderr, "%d : %d (%d)\n", */
		/* 		left[l].first, right[r].first, */
		/* 		left[l].second | right[r].second); */
		while(right[r].first < left[l].first)
			r ++;
		ulong pre = r;
		while(right[r].first == left[l].first)
			used[left[l].second | right[r ++].second] = true;
		r = pre;
	}
	int ans = 0;
	for(int S=0; S<(1<<n); S++)
		ans += used[S];
	printf("%d\n", ans - 1);
	/* for(int S=0; S<(1<<n); S++) */
	/* 	if(used[S]) */
	/* 		fprintf(stderr, "use %d\n", S); */
}
