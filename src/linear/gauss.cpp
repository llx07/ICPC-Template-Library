scanf("%d", &n);
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n + 1; j++)
        scanf("%lf", &a[i][j]);
for (int i = 1, Max = 1; i <= n; Max = ++i) {
    for (int s = i + 1; s <= n; s++)
        if (fabs(a[s][i]) > fabs(a[Max][i]))
            Max = s;  // 找出绝对值最大的
    for (int j = 1; j <= n + 1; j++)
        swap(a[i][j], a[Max][j]);
    if (a[i][i] < 10e-8 && a[i][i] > -10e-8) {
        p = false;
        break;
    }  // 记得 double 的精度问题
    for (int s = 1; s <= n; s++)
        if (s != i)  // 这样省去了第二步处理的麻烦
        {
            double tmp = 0 - (a[s][i] / a[i][i]);
            a[s][i] = 0;
            for (int j = i + 1; j <= n + 1; j++)
                a[s][j] += tmp * a[i][j];
        }
}
if (p)
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", a[i][n + 1] / a[i][i]);
else
    printf("No Solution\n");