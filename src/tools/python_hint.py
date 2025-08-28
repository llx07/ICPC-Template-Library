from itertools import * # itertools库
# 笛卡尔积
product('ABCD', 'xy') # Ax Ay Bx By Cx Cy Dx Dy
product(range(2), repeat=3) # 000 001 010 011 100 101 110 111
# 排列
permutations('ABCD', 2) # AB AC AD BA BC BD CA CB CD DA DB DC
# 组合
combinations('ABCD', 2) # AB AC AD BC BD CD
# 有重复的组合
combinations_with_replacement('ABC', 2) # AA AB AC BB BC CC


from random import * # random 库
randint(l, r) # 在 [l, r] 内的随机整数
choice([1, 2, 3, 5, 8]) # 随机选择序列中一个元素
sample([1, 2, 3, 4, 5], k=2) # 随机抽样两个元素
shuffle(x) # 原地打乱序列 x
l,r = sorted(choices(range(1, N+1), k=2)) # 生成随机区间 [l,r]
binomialvariate(n, p) # 返回服从 B(n,p) 的一个变量
normalvariate(mu, sigma) # 返回服从 N(mu,sigma) 的一个变量

# 列表操作
l = sample(range(100000), 10)
l.sort() # 原地排序
l.sort(key=lambda x:x%10) # 按末尾排序
from functools import cmp_to_key
l.sort(key=cmp_to_key(lambda x,y:y-x)) # 比较函数，小于返回负数
sorted(l) # 非原地排序
l.reverse() reversed(l)

# 复数
a = 1+2j
print(a.real, a.imag, abs(a), a.conjugate())

# 高精度小数
from decimal import Decimal, getcontext, FloatOperation, ROUND_HALF_EVEN
getcontext().prec = 100 # 设置有效位数
getcontext().rounding = getattr(ROUND_HALF_EVEN) # 四舍六入五成双
getcontext().traps[FloatOperation] = True # 禁止 float 混合运算
a = Decimal("114514.1919810")
print(a, f"{a:.2f}")
a.ln() a.log10() a.sqrt() a**2