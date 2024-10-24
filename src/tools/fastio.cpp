char *p1, *p2, buf[100000];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
int read() {
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = gc(); }
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    return x * f;
}