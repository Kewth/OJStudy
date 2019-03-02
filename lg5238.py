'''
2019.03.02

洛谷月赛 T1 模拟题
哈哈那些用 C++ 写的已经去世了
'''

l, r, T = input().split()
l = int(l)
r = int(r)
T = int(T)

for i in range(T):
    try:
        s = input()
        num = int(s)
        if num == 0 and len(s) > 1:
            raise KeyError
        if s[0] == '-':
            s = s[1:]
        if num != 0 and s[0] == '0':
            raise KeyError
    except:
        print(1)
        continue
    # print(num, l, r)
    if num >= l and num <= r:
        print(0)
    else:
        print(2)
