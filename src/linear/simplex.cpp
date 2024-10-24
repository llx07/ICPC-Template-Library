typedef double db;
const db eps = 1e-8, inf = 1e9;
int n, m, ans;
db b[N], a[N][M], c[M]; // n: 约束个数。m: 变量个数。
bool dcmp(db x) { return fabs(x) > eps; }

db pivot(int out, int in) {
    b[out] /= a[out][in];
    for (int i = 1; i <= m; i++) if (i != in) a[out][i] /= a[out][in];
    a[out][in] = 1; // 理论上是 1 / a[out][in] ，但这个系数可以任取，但也不要随便取。
    for (int i = 1; i <= n; i++) {
        if (i != out && dcmp(a[i][in])) {
            b[i] -= a[i][in] * b[out];
            for (int j = 1; j <= m; j++)
                if (j != in) a[i][j] -= a[i][in] * a[out][j];
            a[i][in] *= -a[out][in];
        }
    }
    db res = c[in] * b[out];
    for (int i = 1; i <= m; i++) if (i != in) c[i] -= a[out][i] * c[in];
    c[in] *= -a[out][in];
    return res;
}
void simplex() {
    db res = 0;
    while (1) {
        int in = 0;
        for (int i = 1; i <= m; i++) {
            if (c[i] > eps) {
                in = i;
                break;
            }
        }
        if (!in) break; // simplex 完成，找到最优解。
        int out = 0;
        db mn = inf;
        for (int i = 1; i <= n; i++)
            if (a[i][in] > eps && b[i] / a[i][in] < mn) mn = b[i] / a[i][in], out = i;
        if (!out) {
            res = inf;
            break;
        } // 解为无穷大。
        res += pivot(out, in);
    }
    ans = round(res);
}