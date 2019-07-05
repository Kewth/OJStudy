#if 0
2019.07.05

设 S[i] b, c 一定时表示答案为 i 的所有 a 序列，S[0] 为不合法的所有 a 序列。
那么答案为 i 当且仅当 a 与 S[i - 1] 的某一个序列有恰好一位不同。
问题转换为修改 a 中的一些值使其不合法，答案即最小的修改次数。
最后满足 a[i] >= a[i - 1] + b[i - 1] >= a[i - 2] + b[i - 1] + b[i - 2] >= ...
即所有 i > j 有 a[i] >= a[j] + B[i - 1] - B[j - 1] ，
即 a[i] - B[i - 1] >= a[j] - B[j - 1] ，其中 B 是 b 的前缀和。
同理有所有 i > j 满足 a[i] - C[i - 1] <= a[j] - C[j - 1] 。
设点 i 为 (a[i] - B[i - 1], a[i] - C[i - 1]) ，问题转换为最长下降子序列。
#endif
#include <iostream>
#include <unordered_map>
#include <algorithm>

typedef long long lolong;
typedef std::pair<lolong, lolong> par;
const int maxn = 100050;
lolong a[maxn], b[maxn], c[maxn];
lolong B[maxn], C[maxn], tmp[maxn];
lolong to_real[maxn];
std::unordered_map<lolong, int> to_img;
par dot[maxn];
lolong bit[maxn];

int main() {
    std::ios::sync_with_stdio(false);
    int n = 0;
    std::cin >> n;
    if(not n) return 0;
    for(int i = 1; i <= n; i ++)
        std::cin >> a[i];
    for(int i = 1; i < n; i ++)
        std::cin >> b[i];
    for(int i = 1; i < n; i ++)
        std::cin >> c[i];
    for(int i = 1; i < n; i ++) {
        if(b[i] > c[i]) {
            std::cout << -1 << std::endl;
			return 0;
        }
        B[i] = B[i - 1] + b[i];
        C[i] = C[i - 1] + c[i];
    }
    for(int i = 1; i <= n; i ++) {
        dot[i].first = B[i - 1] - a[i];
        dot[i].second = C[i - 1] - a[i];
        tmp[i] = C[i - 1] - a[i];
    }
    std::sort(tmp + 1, tmp + n + 1);
    std::sort(dot + 1, dot + n + 1);
    int p = 0;
    for(int i = 1; i <= n; i ++)
        if(tmp[i] != tmp[i - 1]) {
            to_img[tmp[i]] = ++ p;
            to_real[p] = tmp[i];
        }
    for(int i = 1; i <= n; i ++) {
        lolong now = 0;
        for(int k = n - to_img[dot[i].second] + 1; k; k -= k & -k)
            now = std::max(bit[k], now);
        now ++;
        for(int k = n - to_img[dot[i].second] + 1; k <= n; k += k & -k)
            bit[k] = std::max(bit[k], now);
    }
    lolong ans = 0;
    for(int k = n; k; k -= k & -k)
        ans = std::max(bit[k], ans);
    std::cout << n - ans << std::endl;
}
