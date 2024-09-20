int join(int x1, int x2) {
    if (!x1 || !x2) return x1 + x2;
    if (pri(x1) > pri(x2)) swap(x1, x2);
    int ls, rs;
    split(x2, val(x1), ls, rs);
    ls(x1) = join(ls(x1), ls);
    rs(x1) = join(rs(x1), rs);
    return pushup(x1), x1;
}