mt19937 mt(chrono::system_clock::now(). time_since_epoch().count());
int rt;
struct FHQ {
    struct node {
        int val, pri, siz, ch[2], rv;
        #define val(x) nod[x].val
        #define pri(x) nod[x].pri
        #define siz(x) nod[x].siz
        #define ls(x) nod[x].ch[0]
        #define rs(x) nod[x].ch[1]
        #define rv(x) nod[x].rv
    } nod[N];
    int cnt;
    int create(int val) { return nod[++cnt] = {val, mt(), 1}, cnt; }
    void pushup(int x) { siz(x) = siz(ls(x)) + siz(rs(x)) + 1; }
    void reverse(int x) { rv(x) ^= 1, swap(ls(x), rs(x)); }
    void pushdown(int x) { if (rv(x)) reverse(ls(x)), reverse(rs(x)), rv(x) = 0; }
    void split(int x, int siz, int &x1, int &x2) {
        if (!x) return x1 = x2 = 0, void();
        pushdown(x);
        if (siz(ls(x)) + 1 <= siz) x1 = x, split(rs(x), siz - siz(ls(x)) - 1, rs(x), x2);
        else x2 = x, split(ls(x), siz, x1, ls(x));
        pushup(x);
    } // x1 中存放了前 siz 个元素，x2 中存放了其余的元素。
    int merge(int x1, int x2) {
        if (!x1 || !x2) return x1 | x2;
        pushdown(x1), pushdown(x2);
        if (pri(x1) < pri(x2)) return rs(x1) = merge(rs(x1), x2), pushup(x1), x1;
        else return ls(x2) = merge(x1, ls(x2)), pushup(x2), x2;
    }
    int kth(int k) {
        int x = rt;
        while (x) {
            pushdown(x);
            if (siz(ls(x)) + 1 == k) return val(x);
            else if (k <= siz(ls(x))) x = ls(x);
            else k -= siz(ls(x)) + 1, x = rs(x);
        }
        return -1;
    } // 寻找第 k 位的元素。
} fhq;