void fmt(int *f, int op) { // op: 1 为 dft ，-1 为 idft 。
    for (int l = 1; l < lim; l <<= 1) {
        for (int i = 0; i < lim; i += l << 1) {
            for (int j = i; j < i + l; j++) {
                f[j + l] += f[j] * op;
            }
        }
    }
}