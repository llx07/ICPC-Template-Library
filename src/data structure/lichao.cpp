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
    line f[N << 2];
    void insert(int k, int l, int r, int x, int y, int k) {
        if (x <= l && r <= y) {
            
        }
    }
};