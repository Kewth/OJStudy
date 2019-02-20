#include <bits/stdc++.h>

struct dot {
	long long x, y;
	dot(long long x=0, long long y=0): x(x), y(y) {}
};

const int maxn = 100050;
long long f[maxn][2];
long long s[maxn];
dot Q[maxn], q[maxn];

double K(dot x, dot y) {
	return double(x.y - y.y) / double(x.x - y.x);
}

int main() {
	int n, k;
	std::cin >> n >> k;
	for(int i=1; i<=n; i++) {
		std::cin >> s[i];
		if(not s[i]) {
			i --;
			n --;
			continue;
		}
		s[i] += s[i - 1];
		q[i] = dot(s[i], - s[i] * s[i]);
	}
	k ++;
	for(int ti=2; ti<=k; ti++) {
		bool now = ti & 1;
		int l = 1, r = 0;
		for(int i=1; i<=n; i++) {
			while(r >= l + 1 and
					K(q[i], Q[r]) > K(Q[r], Q[r - 1]))
				r --;
			Q[++ r] = q[i];
			f[i][now] = INT64_MIN;
			while(l <= r) {
				long long no = Q[l].y + s[i] * Q[l].x;
				if(no > f[i][now]) {
					f[i][now] = no;
					++ l;
				} else
					break;
			}
			l --;
			q[i] = dot(s[i], f[i][now] - s[i] * s[i]);
		}
	}
	std::cout << f[n][k & 1] << std::endl;
}
