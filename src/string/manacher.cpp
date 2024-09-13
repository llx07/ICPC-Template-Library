char s[N], t[N];
// s[] : 原串，t[] : 加入分割字符的串，这样就只需考虑奇回文串了。
int mxp, cen, r[N], n;
// mxp : 最右回文串的右端点的右侧，cen : 最右回文串的中心，r[i] : 以位置 i 为中心的回文串半径，即回文串的长度一半向上取整。

void manacher() {
    t[0] = '~', t[1] = '#';
    // 在 t[0] 填入特殊字符，防止越界。
    int m = 1;
    for (int i = 1; i <= n; i++) {
        t[++m] = s[i], t[++m] = '#';
    }
    for (int i = 1; i <= m; i++) {
        r[i] = mxp > i ? min(r[2 * cen - i], mxp - i) : 1;
        // 若 i∈(cen, mxp), 则由对称性 r[i] 至少取 min(r[2 * cen - i], mxp - i)。否则直接暴力扩展。
        while (t[i + r[i]] == t[i - r[i]]) r[i]++;
        if (i + r[i] > mxp) mxp = i + r[i], cen = i;
    }
}