'''
2019.07.20

贪心（其实是找规律），我猜每题都是 A 0 0 0 0
'''
n = int(input())
print(3 ** (n - 1) * 4 % 998244353)
for i in range(n):
    print('A 0 0 0 0')
