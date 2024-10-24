ll C(ll x, ll y) {
    if (x < y)
        return 0;
    if (x < mod && y < mod)
        return mi[x] * invmi[y] % mod * invmi[x - y] % mod;
    return C(x / mod, y / mod) * C(x % mod, y % mod) % mod;
}  // mod 为一素数。