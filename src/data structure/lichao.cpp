const double eps = 1e-9;
struct line {
    double k, b;
    double operator () (const double &x) const {
        return k * x + b;
    }
};
bool cmp(double x, double y) {
    return y - x > eps;
}
struct SMT {
    #define mid ((l + r) >> 1)
    #define ls (k << 1)
    #define rs ((k << 1) | 1)
    line f[N << 2];
    void insert(int k, int l, int r, int x, int y, line g) {
        if (x <= l && r <= y) {
            if (cmp(f[k](mid), g(mid))) swap(f[k], g);
            if (cmp(f[k](l), g(l))) insert(ls, l, mid, x, y, g);
            if (cmp(f[k](r), g(r))) insert(rs, mid + 1, r, x, y, g);
            return;
        }
        if (x <= mid) insert(ls, l, mid, x, y, g);
        if (y > mid) insert(rs, mid + 1, r, x, y, g);
    } // 插入 O(log^2n) ：定位到 O(logn) 个区间，每个区间 O(logn) 递归到叶子。
    int query(int k, int l, int r, int x) {
        double res = f[k](x);
        if (l == r) return res;
        if (x <= mid) return max(res, query(ls, l, mid, x));
        else return max(res, query(rs, mid + 1, r, x));
    }
} smt;