#include <bits/stdc++.h>

const int maxn = 101, maxm = 1001;
const int inf = 1000000000;
const double eps = 1e-9;
int head[maxn], Head[maxn], level[maxn];
int nxt[maxm<<1], to[maxm<<1], p = 1;
double cap[maxm<<1];

void add(int x, int y, int c) {
	nxt[++p] = head[x];
	head[x] = p;
	to[p] = y;
	cap[p] = c;
	nxt[++p] = head[y];
	head[y] = p;
	to[p] = x;
	cap[p] = 0;
}

bool bfs(int s, int t) {
	std::queue<int> q;
	q.push(s);
	memset(level, 0, sizeof(level));
	level[s] = 1;
	while(not q.empty()) {
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i]) {
			int v = to[i];
			if(not level[v] and cap[i]) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return level[t];
}

double dfs(int u, int t, double c) {
	if(u == t)
		return c;
	for(int &i=Head[u];i;i=nxt[i]) {
		int v = to[i];
		if(cap[i] and level[v] == level[u] + 1) {
			double cc = dfs(v, t, std::min(cap[i], c));
			if(cc) {
				cap[i] -= cc;
				cap[i^1] += cc;
				return cc;
			}
		}
	}
	return 0;
}

double max_flow(int s, int t) {
	double res = 0;
	while(bfs(s, t)) {
		memcpy(Head, head, sizeof(Head));
		double now = 0;
		do {
			now = dfs(s, t, inf);
			res += now;
		} while(std::abs(now) > eps);
	}
	return res;
}

double Cap[maxm << 1];
int main(int, char **) {
	int n, m, k;
	std::cin >> n >> m >> k;
	int s = 1, t = n;
	for(int i=1;i<=m;i++) {
		int a, b, c;
		std::cin >> a >> b >> c;
		add(a, b, c);
	}
	memcpy(Cap, cap, sizeof(Cap));
	double Max = max_flow(s, t);
	double l = 1, r = 50000;
	while(r - l > eps) {
		double mid = (l + r) / 2;
		std::cerr << l << ' ' << mid << ' ' << r << std::endl;
		memcpy(cap, Cap, sizeof(cap));
		for(int i=2;i<=m*2+1;i++)
			cap[i] = std::min((double)mid, cap[i]);
		if(std::abs(max_flow(s, t) - Max) < eps) r = mid;
		else l = mid + eps;
		/* std::cerr << mid << " " << max_flow(s, t) << std::endl; */
	}
	printf("%d\n%.4lf\n", (int)Max, l * k);
}
