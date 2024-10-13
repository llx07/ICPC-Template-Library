#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main() {
    printf("[info] Checker preparing...\n");
    system("g++ gen.cpp -o gen");
    system("g++ tst.cpp -o tst");
    system("g++ std.cpp -o std");
    printf("[info] Checker start.\n\n---\n\n");
    int cnt = 0;
    while (1) {
        cnt++;
        printf("Test case %d : \n", cnt);
        clock_t a, b;
        double t;
        a = clock();
        system("./gen > data.txt");
        b = clock(), t = (double)(b - a) / CLOCKS_PER_SEC;
        printf("[info] Test data generated in %.3lf s.\n", t);
        a = clock();
        system("./tst < data.txt > tst.txt");
        b = clock(), t = (double)(b - a) / CLOCKS_PER_SEC;
        printf("[info] Test program exited in %.3lf s.\n", t);
        a = clock();
        system("./std < data.txt > expected.txt");
        b = clock(), t = (double)(b - a) / CLOCKS_PER_SEC;
        printf("[info] Standard program exited in %.3lf s.\n", t);
        if (system("diff expected.txt tst.txt")) break;
        printf("\n");
    }
    printf("Match faild.\n");
    system("pause");
    return 0;
}
