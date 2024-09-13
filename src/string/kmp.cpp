char s[N], t[N];
int nex[N], n, m;

void kmp() {
    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j && s[j + 1] != s[i]) j = nex[j];
        if (s[j + 1] == s[i]) j++;
        nex[i] = j;
    }
}

void match() {
    int j = 0;
    for (int i = 1; i <= m; i++) {
        while (j && s[j + 1] != t[i]) j = nex[j];
        if (s[j + 1] == t[i]) j++;
        if (j == n) {
            //match.
            j = nex[j];
        }
    }
}