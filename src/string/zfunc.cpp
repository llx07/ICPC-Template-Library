char s[N];
int z[N];

void zfunc() {
    z[1] = n;
    int j = 0;
    for (int i = 2; i <= n; i++) {
        if (j && j + z[j] - 1 >= i) z[i] = min(z[i - j + 1], j + z[j] - i);
        while (i + z[i] <= n && s[i + z[i]] == s[1 + z[i]]) z[i]++;
        if (i + z[i] > j + z[j]) j = i;
    }
}