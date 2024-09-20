void Max(auto &x, auto y) { x = max(x, y); }
void Min(auto &x, auto y) { x = min(x, y); }
struct SMT {
    #define ls (k << 1)
    #define rs (k << 1 | 1)
    #define mid ((l + r) >> 1)
    struct node {
        int sm, mx, mx2, c, hmx, ad, ad2, had, had2;
        // 区间和，最大值，次大值，最大值个数，历史最大值，最大值加法标记，其余值加法标记，最大值的历史最大加法标记，其余值的历史最大加法标记。
        node operator + (const node &x) const {
            node t = *this;
            t.sm += x.sm, Max(t.hmx, x.hmx);
            if (t.mx > x.mx) Max(t.mx2, x.mx);
            else if (t.mx < x.mx) t.mx2 = max(t.mx, x.mx2), t.mx = x.mx, t.c = x.c;
            else Max(t.mx2, x.mx2), t.c += x.c;
            t.ad = t.ad2 = t.had = t.had2 = 0;
            return t;
        }
    } nod[N << 2];
    #define sm(x) nod[x].sm
    #define mx(x) nod[x].mx
    #define mx2(x) nod[x].mx2
    #define c(x) nod[x].c
    #define hmx(x) nod[x].hmx
    #define ad(x) nod[x].ad
    #define ad2(x) nod[x].ad2
    #define had(x) nod[x].had
    #define had2(x) nod[x].had2
    void pushup(int k) { nod[k] = nod[ls] + nod[rs]; }
    void add(int k, int l, int r, int ad, int ad2, int had, int had2) {
        Max(had(k), ad(k) + had), Max(had2(k), ad2(k) + had2), Max(hmx(k), mx(k) + had);
        sm(k) += c(k) * ad + (r - l + 1 - c(k)) * ad2, mx(k) += ad, ad(k) += ad, ad2(k) += ad2, mx2(k) += ad2;
    }
    void pushdown(int k, int l, int r) {
        int mx = max(mx(ls), mx(rs));
        if (mx(ls) == mx) add(ls, l, mid, ad(k), ad2(k), had(k), had2(k));
        else add(ls, l, mid, ad2(k), ad2(k), had2(k), had2(k));
        if (mx(rs) == mx) add(rs, mid + 1, r, ad(k), ad2(k), had(k), had2(k));
        else add(rs, mid + 1, r, ad2(k), ad2(k), had2(k), had2(k));
        ad(k) = ad2(k) = had(k) = had2(k) = 0;
    }
    void build(int k, int l, int r) {
        if (l == r) return nod[k] = {a[l], a[l], -inf, 1, a[l]}, void();
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(k);
    }
    void add(int k, int l, int r, int x, int y, int v) {
        if (x <= l && r <= y) return add(k, l, r, v, v, v, v);
        pushdown(k, l, r);
        if (x <= mid) add(ls, l, mid, x, y, v);
        if (y > mid) add(rs, mid + 1, r, x, y, v);
        pushup(k);
    }
    void Min(int k, int l, int r, int x, int y, int v) {
        if (v >= mx(k)) return;
        if (x <= l && r <= y && v > mx2(k)) return add(k, l, r, v - mx(k), 0, v - mx(k), 0), void();
        pushdown(k, l, r);
        if (x <= mid) Min(ls, l, mid, x, y, v);
        if (y > mid) Min(rs, mid + 1, r, x, y, v);
        pushup(k);
    }
    node query(int k, int l, int r, int x, int y) {
        if (x <= l && r <= y) return nod[k];
        pushdown(k, l, r);
        if (y <= mid) return query(ls, l, mid, x, y);
        else if (x > mid) return query(rs, mid + 1, r, x, y);
        else return query(ls, l, mid, x, y) + query(rs, mid + 1, r, x, y);
    }
} smt;