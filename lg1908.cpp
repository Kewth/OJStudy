// include files {{{1
#include <bits/stdc++.h>

// function to speed up input {{{1
long long input() {
	int ch = getchar();
	long long res = 0;
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res;
}

// definition {{{1
const int maxn = 500050;
int a[maxn];
int b[maxn];
int bak[maxn];
int num[maxn];

// gb sort {{{1
long long GB(int l,int r) {
	if(l == r) return 0;
	int mid = (l + r) >> 1;
	long long res = GB(l, mid) + GB(mid+1, r);
	int p = l - 1, p1, p2;
	for(p1=l,p2=mid+1;p1<=mid&&p2<=r;) {
		if(a[p1] > a[p2])
			num[++p] = a[p2++];
		else {
			num[++p] = a[p1++];
			res += p2-mid-1;
		}
	}
	while(p1 <= mid) {
		num[++p] = a[p1++];
		res += r - mid;
	}
	while(p2 <= r)
		num[++p] = a[p2++];
	if(p != r) for(;;);
	for(int i=l;i<=r;i++)
		a[i] = num[i];
	return res;
}

// Main function {{{1
int main(int, const char**) {
	int n = input();
	for(int i=1;i<=n;i++)
		a[i] = input();
	printf("%lld\n",GB(1, n));
}

// }}}1
