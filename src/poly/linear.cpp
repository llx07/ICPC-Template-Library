void multi(int *f, int *g, int *h) { // 对 f 和 g 做子集卷积，答案为 h 。
    static int a[n][lim], b[n][lim], c[n][lim]; // lim = 1 << n
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    memset(c, 0, sizeof c);
    for (int i = 0; i < lim; i++) a[pcnt[i]][i] = f[i]; // pcnt[i] = popcount(i)
    for (int i = 0; i < lim; i++) b[pcnt[i]][i] = g[i];
    for (int i = 0; i <= n; i++) fmt(a[i], 1), fmt(b[i], 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k < lim; k++)
                c[i][k] += a[j][k] * b[i - j][k];
    for (int i = 0; i <= n; i++) fmt(c[i], -1);
    for (int i = 0; i < lim; i++) h[i] = c[pcnt[i]][i];
}