#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

int main() {
    int T = 10;
    while (T--) {
        int x = rnd();
        cout << x << '\n';
        // int y = x;
        // cout << y << '\n';
    }
    return 0;
}