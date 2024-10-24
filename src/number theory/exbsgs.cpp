inline int inv(int a, int mod) {
    int x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
inline int exBSGS(int a, int mod, int b) {
    b %= mod;
    if (b == 1 || mod == 1)
        return 0;
    int k = 0, D = 1, U = 1, tmod = mod, tb = b;
    for (int x; (x = gcd(tmod, a)) > 1;) {
        if (tb % x)
            return -1;
        tmod /= x, tb /= x, D *= x, k++;
        U = 1ll * U * a / x % tmod;
        if (U == tb)
            return k;
    }
    tb = 1ll * tb * inv(U, tmod) % tmod;
    int ret = BSGS(a, tmod, tb);
    if (ret == -1)
        return -1;
    return ret + k;
}