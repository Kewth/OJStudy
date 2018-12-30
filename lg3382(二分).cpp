// include files {{{1
#include <bits/stdc++.h>

// Nth Function {{{1
double func(double x, double *a, int n) {
	double now = 1, res = 0;
	for(int i=0;i<=n;i++) {
		res += now * a[i];
		now *= x;
	}
	return res;
}

// Main function {{{1
int main(int, const char**) {
	int n;
	double l, r;
	const double eps = 1e-12;
	std::cin >> n >> l >> r;
	double *a = new double[n+1];
	for(int i=n;i;i--)
		std::cin >> a[i];
	while(l < r - eps*3) {
		double mid = (l + r) / 2;
		/* double lmid = l + (r-l)/3; */
		/* double rmid = r - (r-l)/3; */
		double lmid = mid - eps;
		double rmid = mid + eps;
		double lans = func(lmid, a, n);
		double rans = func(rmid, a, n);
		/* std::cout << l << ' ' << r << std::endl; */
		/* std::cout << lans << ' ' << rans << std::endl; */
		if(lans < rans) l = lmid;
		else r = rmid;
	}
	printf("%.5lf\n", l);
	delete[] a;
}

// }}}1
