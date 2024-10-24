// 解法1：类似辗转相除
n = rd(), mod = rd();
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        a[i][j] = rd() % mod;
for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
        while (a[j][i]) {
            ll tmp = a[i][i] / a[j][i];
            for (int k = i; k <= n; k++)
                a[i][k] = (a[i][k] - tmp * a[j][k] % mod + mod) % mod;
            swap(a[i], a[j]), w = -w; // ?
        }
    }
}
for (int i = 1; i <= n; i++)
    ans = ans * a[i][i] % mod;
printf("%lld\n", (mod + w * ans) % mod);