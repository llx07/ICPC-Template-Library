const int mod = 998244353, G = 3, iG = 332748118;
int tr[N], lim;
void adjust(int n) { // n: 多项式的次数。
    lim = 1;
    while (lim <= n) lim <<= 1;
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
} // 准备蝶形变换。
void ntt(int *f, int op) { // op: 1 为 dft ，-1 为 idft 。
    for (int i = 0; i < lim; i++) if (tr[i] < i) swap(f[tr[i]], f[i]);
    for (int l = 1; l < lim; l <<= 1) {
        int w1 = qpow(op == 1 ? G : iG, (mod - 1) / (l << 1)); // qpow: 快速幂。
        for (int i = 0; i < lim; i += l << 1) {
            for (int j = i, w = 1; j < i + l; j++, (w *= w1) %= mod) {
                int x = f[j], y = f[j + l] * w % mod;
                f[j] = (x + y) % mod, f[j + l] = (x - y) % mod;
            }
        }
    }
    if (op == -1) {
        int iv = qpow(lim); // 算逆元。
        for (int i = 0; i < lim; i++) (f[i] *= iv) %= mod;
    }
}