// include files {{{1
#include <bits/stdc++.h>
#include "template.h"

int use[maxn], know[maxn][maxn];

// Main function {{{1
int main(const int, const char **) {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	int S = 0, T = n + 1;
	long long ans = 0;
	for(int i=1;i<=n;i++)
		std::cin >> use[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			std::cin >> know[i][j];
			ans += know[i][j];
		}
	for(int i=1;i<=n;i++) {
		add(S, i, use[i]);
		/* add(i, T, use[i]); */
		int sum = 0;
		for(int j=1;j<=n;j++)
			if(i != j)
				sum += know[j][i];
		add(i, T, sum);
		/* add(S, i, sum); */
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i != j)
				add(i, j, know[i][j] << 1);
	std::cerr << "SUM !" << ans << std::endl;
	ans -= maxflow(S, T);
	std::cout << ans << std::endl;
}

// {{{1
// }}}1
