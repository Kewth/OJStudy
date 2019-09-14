#if 0
2019.08.31

设 f[i] 表示第 i 月的兔兔，g[i] 表示 f[i] 前缀和。
直接算是 O(n) 的，可以矩阵优化，每 a 个 f, g 搁一块转移。
f[a * s ~ a * s + a - 1] -> f[a * s + a ~ a * s + 2a - 1]
特别地， a = 1 的时候矩阵会太小无法转移，需要特判另外构造矩阵。

update，并不需要记 a 个 g ，只要记一个 sum ，跑玩矩阵快速幂后加上剩下的 f 即可。
这样可以卡 8 倍常数。

另外有个神奇的矩阵构造方法可以通用于 a = 1 ，
类似于普通斐波那契的转移矩阵，
由于每 a 轮转移会有一个贡献，考虑在矩阵里开 a 个空，每次转移后移一位，
保证 a 次转移后能定期贡献到 f 和 g 。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() {
    int x;
    scanf("%d", &x);
    return x;
}
inline lolong linput() {
    lolong x;
    scanf("%lld", &x);
    return x;
}

const int mod = 19260817, maxa = 53;
lolong f[maxa];

struct Mar {
    lolong val[maxa][maxa];
    int w, h;
};
Mar ma, ans, tmp;

void mul(Mar &x, Mar &y) {
    memset(tmp.val, 0, sizeof tmp.val);
    for (int i = 0; i < x.w; i++)
        for (int j = 0; j < x.h; j++)
            for (int k = 0; k < y.h; k++) tmp.val[i][k] += x.val[i][j] * y.val[j][k] % mod;
    for (int i = 0; i < x.w; i++)
        for (int j = 0; j < y.h; j++) tmp.val[i][j] %= mod;
}

lolong power(lolong x, int k) {
    if (k < 0)
        k += mod - 1;
    lolong res = 1;
    while (k) {
        if (k & 1)
            (res *= x) %= mod;
        (x *= x) %= mod;
        k >>= 1;
    }
    return res;
}

int main() {
    lolong n = linput();
    int a = input();
    lolong b = linput(), k = linput();
    int len;

    if (a == 1) {
        ma.val[0][0] = 1;
        ma.val[0][1] = 1;
        ma.val[0][4] = 1;

        ma.val[1][0] = 1;
        ma.val[1][1] = 2;
        ma.val[1][3] = 1;
        ma.val[1][4] = 2;

        ma.val[3][3] = 1;

        ma.val[4][4] = 2;
        ma.val[4][3] = 1;

        ans.val[0][0] = 1;
        ans.val[1][0] = 1 + b;
        ans.val[3][0] = k;
        ans.val[4][0] = k + b;

        len = 5;
        a++;
    } else {
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i < a; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;

        len = a + 3;

        for (int i = 0; i < a; i++) ans.val[i][0] = f[i];
        ans.val[len - 2][0] = k;
        ans.val[len - 1][0] = b;

        ma.val[len - 2][len - 2] = 1;
        ma.val[len - 1][len - 1] = 1;
        ma.val[len - 1][len - 2] = 1;

        ma.val[0][a - 1] = 1;
        ma.val[0][a - 2] = 1;
        ma.val[1][a - 1] = 2;
        ma.val[1][a - 2] = 1;
        ma.val[0][len - 1] = 1;
        ma.val[1][len - 1] = 1;

        for (int i = 2; i < a; i++)
            for (int j = 0; j < len; j++) ma.val[i][j] = (ma.val[i - 1][j] + ma.val[i - 2][j]) % mod;
    }

    for (int i = 0; i <= a; i++) ma.val[a][i] = 1;

    lolong K = n / a;
#if 1
    while (K) {
        ma.w = ma.h = len;
        ans.w = len;
        ans.h = 1;
        if (K & 1) {
            mul(ma, ans);
            ans = tmp;
        }
        mul(ma, ma);
        ma = tmp;
        K >>= 1;
    }
#else
    for (int i = 0; i < len; i++) debug("%lld\n", ans.val[i][0]);

    while (K--) {
        ma.w = ma.h = len;
        ans.w = len;
        ans.h = 1;

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) debug(" %lld", ma.val[i][j]);
            debug(" *");
            debug(" %lld\n", ans.val[i][0]);
        }

        mul(ma, ans);
        ans = tmp;

        for (int i = 0; i < len; i++) debug("%lld\n", ans.val[i][0]);
    }
#endif

    lolong sum = ans.val[a][0];
    for (int i = 0; i <= n % a; i++) sum += ans.val[i][0];
    sum--;
    printf("%lld\n", sum % mod);
}
