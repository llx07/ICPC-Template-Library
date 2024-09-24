struct comp {
    double x, y;
    comp(double X = 0, double Y = 0) { x = X, y = Y; }
    comp operator + (const comp &rhs) const { return comp(x + rhs.x, y + rhs.y); }
    comp operator - (const comp &rhs) const { return comp(x - rhs.x, y - rhs.y); }
    comp operator * (const comp &rhs) const { return comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    comp operator / (const comp &rhs) const {
        double t = rhs.x * rhs.x + rhs.y * rhs.y;
        return {(x * rhs.x + y * rhs.y) / t, (y * rhs.x - x * rhs.y) / t};
    }
};
const double pi = acos(-1);
int lim, tr[N];
void adjust(int n) { // n: 多项式的次数。
    lim = 1;
    while (lim <= n) lim <<= 1;
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
} // 准备蝶形变换。
void fft(comp *f, int op) { // op: 1 为 dft ，-1 为 idft 。
    for (int i = 0; i < lim; i++) if (tr[i] < i) swap(f[tr[i]], f[i]);
    for (int l = 1; l < lim; l <<= 1) {
        comp w1(cos(2 * pi / (l << 1)), sin(2 * pi / (l << 1)) * op);
        for (int i = 0; i < lim; i += l << 1) {
            comp w(1, 0);
            for (int j = i; j < i + l; j++, w = w * w1) {
                comp x = f[j], y = f[j + l] * w;
                f[j] = x + y, f[j + l] = x - y;
            }
        }
    }
    if (op == -1) {
        for (int i = 0; i < lim; i++) f[i].x /= lim;
    }
}