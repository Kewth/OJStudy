#!/usr/bin/python3
'''
2019.05.18

乍一看 DP, 发现稳 T 。
考虑股价的差分数组 a ，题目保证了 a 的每个位置都可以取 1 ~ m 。
容易发现 a 的出现次数，也就是对答案的贡献就是 n - sum(a) 。
那么就要求所有差分数组 a 的贡献和。

由于 a 每个位置都取遍了 1 ~ m 的所有值，
事实上每个数在所有 a 中出现次数一致。
也就是说 1 ~ m 每个数 i 对 sigma(sum(a)) 有 m ^ (k - 2) * i 的贡献。
'''

def power(x, k, p):
    res = 1
    while k:
        if k & 1:
            res *= x
            res %= p
        x *= x
        x %= p
        k >>= 1
    return res

n, k, m, p = [int(i) for i in input().split()]
k -= 1
print((n * m - k * m * (m + 1) // 2 + p) \
                * power(m, k - 1, p) % p)
