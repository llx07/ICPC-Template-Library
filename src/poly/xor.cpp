void fwt(int *f, int op) { // op: 1 为 dft ，-1 为 idft 。
    for (int l = 1; l < lim; l <<= 1) {
        for (int i = 0; i < lim; i += l << 1) {
            for (int j = i; j < i + l; j++) {
                int x = f[j], y = f[j + l];
                f[j] = x + y, f[j + l] = x - y;
                if (op == -1) f[j] /= 2, f[j + l] /= 2;
                // 模意义下改成乘逆元。
            }
        }
    }
}