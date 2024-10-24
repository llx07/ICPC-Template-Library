vp convex(vp a) {
    if (a.size() < 2) return a;
    sort(a.begin(), a.end());
    int n = a.size(), cnt = 0;
    vp con({p[0]});
    for (int i = 0; i < n; ++i) {
        while (cnt > 0 && sgn(((p[i] - con[cnt - 1]) ^ (con[cnt] - con[cnt - 1]))) > 0) //>=
            --cnt, con.pop_back();
        ++cnt, con.push_back(p[i]);
    }
    int fixed = cnt;
    for (int i = n - 2; ~i; --i) {
        while (cnt > fixed && sgn(((p[i] - con[cnt - 1]) ^ (con[cnt] - con[cnt - 1]))) > 0) //>=
            --cnt, con.pop_back();
        ++cnt, con.push_back(p[i]);
    }
    con.pop_back();
    return con;
}

vp minkowski(vp p1, vp p2) {
    if (p1.empty() || p2.empty()) return vp();
    int n1 = p1.size(), n2 = p2.size();
    vp ret;
    if (n1 == 1) {
        for (int i = 0; i < n2; ++i)
            ret.push_back(p1[0] + p2[i]);
        return ret;
    }
    if (n2 == 1) {
        for (int i = 0; i < n1; ++i)
            ret.push_back(p1[i] + p2[0]);
        return ret;
    }
    p1.push_back(p1[0]), p1.push_back(p1[1]), p2.push_back(p2[0]), p2.push_back(p2[1]);
    ret.push_back(p1[0] + p2[0]);
    int i1 = 0, i2 = 0;
    while (i1 < n1 || i2 < n2) {
        if (((p1[i1 + 1] - p1[i1]) ^ (p2[i2 + 1] - p2[i2])) > 0)
            ret.push_back(p1[++i1] + p2[i2]);
        else
            ret.push_back(p2[++i2] + p1[i1]);
    } // p1.pop_back(),p1.pop_back(),p2.pop_back(),p2.pop_back();
    ret.pop_back();
    return ret;
}

struct Con {
    int n;
    vp a, upper, lower;

    Con(cvp _a) : a(_a) {
        n = a.size();
        int k = 0;
        for (int i = 1; i < n; ++i)
            if (a[i] > a[k]) k = i;
        for (int i = 0; i <= k; ++i)
            lower.push_back(a[i]);
        for (int i = k; i < n; ++i)
            upper.push_back(a[i]);
        upper.push_back(a[0]);
    }

}

// Below is from Nemesis

// Convex
int n;
vector<point> a; // 可以封装成一个 struct
bool inside(cp u) { // 点在凸包内
    int l = 1, r = n - 2;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (turn(a[0], a[mid], u) >= 0)
            l = mid;
        else
            r = mid - 1;
    }
    return turn(a[0], a[l], u) >= 0 && turn(a[l], a[l + 1], u) >= 0 && turn(a[l + 1], a[0], u) >= 0;
}
int search(auto f) { // 凸包求极值，需要 C++17
    int l = 0, r = n - 1;
    int d = f(a[r], a[l]) ? (swap(l, r), -1) : 1;
    while (d * (r - l) > 1) {
        int mid = (l + r) / 2;
        if (f(a[mid], a[l]) && f(a[mid], a[mid - d]))
            l = mid;
        else
            r = mid;
    }
    return l;
}
pair<int, int> get_tan(cp u) { // 求切线
    return // 严格在凸包外；需要边界上时，特判 a[n-1] -> a[0]
        {search([&](cp x, cp y) { return turn(u, y, x) > 0; }),
         search([&](cp x, cp y) { return turn(u, x, y) > 0; })};
}
point at(int i) { return a[i % n]; }
int inter(cp u, cp v, int l, int r) {
    int sl = turn(u, v, at(l));
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (sl == turn(u, v, at(m)))
            l = m;
        else
            r = m;
    }
    return l % n;
}
bool get_inter(cp u, cp v, int &i, int &j) { // 求直线交点
    int p0 = search([&](cp x, cp y) { return det(v - u, x - u) < det(v - u, y - u); }),
        p1 = search([&](cp x, cp y) { return det(v - u, x - u) > det(v - u, y - u); });
    if (turn(u, v, a[p0]) * turn(u, v, a[p1]) < 0) {
        if (p0 > p1) swap(p0, p1);
        i = inter(u, v, p0, p1);
        j = inter(u, v, p1, p0 + n);
        return true;
    } else
        return false;
}
LD near(cp u, int l, int r) {
    if (l > r) r += n;
    int sl = sgn(dot(u - at(l), at(l + 1) - at(l)));
    LD ret = p2s(u, {at(l), at(l + 1)});
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (sl == sgn(dot(u - at(m), at(m + 1) - at(m))))
            l = m;
        else
            r = m;
    }
    return min(ret, p2s(u, {at(l), at(l + 1)}));
}
LD get_near(cp u) { // 求凸包外点到凸包最近点
    if (inside(u)) return 0;
    auto [x, y] = get_tan(u);
    return min(near(u, x, y), near(u, y, x));
}

// Dynamic convex hull
struct hull { // upper hull, left to right
    set<point> a;
    LL tot;
    hull() { tot = 0; }
    LL calc(auto it) {
        auto u = it == a.begin() ? a.end() : prev(it);
        auto v = next(it);
        LL ret = 0;
        if (u != a.end()) ret += det(*u, *it);
        if (v != a.end()) ret += det(*it, *v);
        if (u != a.end() && v != a.end()) ret -= det(*u, *v);
        return ret;
    }
    void insert(point p) {
        if (!a.size()) {
            a.insert(p);
            return;
        }
        auto it = a.lower_bound(p);
        bool out;
        if (it == a.begin())
            out = (p < *it); // special case
        else if (it == a.end())
            out = true;
        else
            out = turn(*prev(it), *it, p) > 0;
        if (!out) return;
        while (it != a.begin()) {
            auto o = prev(it);
            if (o == a.begin() || turn(*prev(o), *o, p) < 0)
                break;
            else
                erase(o);
        }
        while (it != a.end()) {
            auto o = next(it);
            if (o == a.end() || turn(p, *it, *o) < 0)
                break;
            else
                erase(it), it = o;
        }
        tot += calc(a.insert(p).first);
    }
    void erase(auto it) {
        tot -= calc(it);
        a.erase(it);
    }
};