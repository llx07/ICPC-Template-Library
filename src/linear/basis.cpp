void Insert(ll x) // 加入一个数
{
    for (int i = 62; i >= 0; i--)
        if ((x >> i) & 1) {
            if (!p[i]) {
                p[i] = x;
                break;
            }
            x ^= p[i]; // 更新 [0,i-1] 位的更优答案
        }
}
bool exist(ll x) // 查询一个元素是否可以被异或出来
{
    for (int i = 62; i >= 0; i--)
        if ((x >> i) & 1) x ^= p[i];
    return x == 0;
}
ll query_max() // 查询异或最大值
{
    ll ret = 0;
    for (int i = 62; i >= 0; i--)
        if ((ans ^ p[i]) > ans) ans ^= p[i];
    return ans;
}
ll query_min() // 查询异或最小值
{
    for (int i = 0; i <= 62; i++)
        if (p[i]) return p[i];
    return 0;
}
ll kth(ll k) // 查询异或第 k 小
{
    // 重建 d 数组，求出哪些位可以被异或为 1
    // d[i] 中任意两个数在任意一个二进制位上不可能同时为 1
    for (int i = 62; i >= 1; i--) // 从高到低防止后效性
        for (int j = i - 1; j >= 0; j--)
            if ((p[i] >> j) & 1) p[i] ^= p[j];
    for (int i = 0; i <= 62; i++)
        if (p[i]) d[cnt++] = p[i];

    if (!k) return 0ll;                     // 特判 0
    if (k >= (1ll << (ll)cnt)) return -1ll; // k 大于可以表示出的数的个数
    ll ret = 0;
    for (int i = 62; i >= 0; i--)
        if ((k >> i) & 1) ret ^= d[i];
    return ret;
}
ll Rank(ll k) {
    ll Now = 1, ret = 0;
    for (int i = 0; i <= 62; i++)
        if (p[i]) // 记得保证 k 可以被异或出来
        {
            if ((k >> i) & 1) ret += Now;
            Now <<= 1;
        }
    return ret;
}