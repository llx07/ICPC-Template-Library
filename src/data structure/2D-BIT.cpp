struct BIT {
    int sm[N][N][4]; // sm 是 sum 的缩写。
    int lowbit(int x) { return x & -x; }
    void add(int x, int y, int k) {
	    int a = k, b = k * x, c = k * y, d = k * x * y;
	    for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
	 	 	    sm[i][j][0] += a;
	 	 	    sm[i][j][1] += b;
	 	 	    sm[i][j][2] += c;
	 	 	    sm[i][j][3] += d;
		    }
        }
    }
    int query(int x,int y) {
	    int ret = 0, a = x * y + x + y + 1, b = y + 1, c = x + 1, d = 1;
	    for (int i = x; i; i -= lowbit(i)) {
            for(int j = y; j; j -= lowbit(j)) {
	 	 	    ret += sm[i][j][0] * a;
	 	 	    ret -= sm[i][j][1] * b;
	 	 	    ret -= sm[i][j][2] * c;
	 	 	    ret += sm[i][j][3] * d;
	        }
        }
	    return ret;
    }
} bit;

// [a, c] * [b, d] + x : add(a, b, x), add(a, d + 1, -x), add(c + 1, b, -x), add(c + 1, d + 1, x);
// sum of [a, c] * [b, d] : query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1);