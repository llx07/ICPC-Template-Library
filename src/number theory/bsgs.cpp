inline int BSGS(int a, int mod, int b) {
    int sq = ceil(sqrt(mod));
    mp.clear();
    int powa = 1;
    for (int B = 0, x = 1; B <= sq; B++)
        x = 1ll * b * powa % mod, mp[x] = B,
        powa = 1ll * powa * ((B == sq) ? 1 : a) % mod;
    for (int A = 0, B, x = 1; A <= sq; A++) {
        if (mp.find(x) != mp.end()) {
            B = mp[x];
            if (A * sq - B >= 0)
                return A * sq - B;
        }
        x = 1ll * x * powa % mod;
    }
    return -1;  // 无解
}