#if 0
2019.03.10

%%% CZZ 又做过了这题，并且以“一眼”嘲讽我

将魔法石按魔法值从大到小排序依次尝试插入线性基，
可以用反证法证明，如果当前点可以插入线性基却不选，
后面一定不会更优的方案
#endif
#include <bits/stdc++.h>

typedef unsigned long long ulolong;
typedef std::pair<int, ulolong> par;
const int maxn = 1005, maxk = 62;
ulolong xian[maxk];
par a[maxn];

bool xian_add(ulolong x) {
	for(unsigned k=maxk-1; k<maxk; k--)
		if(x >> k & 1) {
			if(xian[k])
				x ^= xian[k];
			else {
				xian[k] = x;
				/* std::clog << " inserted " << x << std::endl; */
				return true;
			}
		}
	return false;
}

bool cmp(par _a, par _b) { return _a > _b; }

int main() {
	int n;
	std::cin >> n;
	for(int i=1; i<=n; i++)
		std::cin >> a[i].second >> a[i].first;
	std::sort(a + 1, a + n + 1, cmp);
	int ans = 0;
	for(int i=1; i<=n; i++)
		if(xian_add(a[i].second))
			ans += a[i].first;
	std::cout << ans << std::endl;
}
