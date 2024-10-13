#include <bits/stdc++.h>
using namespace std;

int main() {
    system("clear");                    // 为了整洁，先清空屏幕
    cout << "对拍检验程序启动\n\n";     // 提示语句
    cout << "开始编译数据生成器\n";     // 提示语句
    system("g++ gen.cpp -o gen");       // 重新编译 gen.cpp
    cout << "编译成功\n\n";             // 提示语句
    cout << "开始编译暴力程序\n";       // 提示语句
    system("g++ baoLi.cpp -o baoLi");   // 重新编译 baoLi.cpp
    cout << "编译成功\n\n";             // 提示语句
    cout << "开始编译优化程序\n";       // 提示语句
    system("g++ youHua.cpp -o youHua"); // 重新编译 youHua.cpp
    cout << "编译成功\n\n";             // 提示语句
    cout << "开始对拍测试\n\n";         // 提示语句
    int testCase = 0;                   // 定义测试点编号
    while (true)
    {
        testCase++;         // 每次测试点编号都加一
        system("./gen");    // 生成数据
        system("./baoLi");  // 运行暴力代码
        int TTT = clock();  // 记录要测试的代码运行前的时间
        system("./youHua"); // 运行要测试的优化后的代码
        cout << "Test case #" << testCase << " Time: " << (double)(clock() - TTT) / CLOCKS_PER_SEC << "s\n";
        // 将运行 youHua 后的时间减去运行 youHua 前的时间，得到这份代码跑了多久，并输出
        if (system("diff result1.txt result2.txt") == 0)
            // 这个 diff 是 Mac 以及 Linux 下都有的用于非常简陋地比较两个文件是否一样的指令
            // diff 指令返回 0 表示一样，返回 1 表示有差异
            cout << "Accepted on test case #" << testCase << "\n\n";
        else
        {
            cout << "Wrong answer on test case #" << testCase << "\n\n";
            break;
            // 为了保存下来这组跑出错误的数据以便后续 debug，我们迅速终止对拍并留住这组数据
        }
    }
    cout << "对拍结束！\n"; // 提示语句
    system("rm gen baoLi youHua check");
    cout << "已删除临时文件！\n\n"; // 提示语句
    // 将程序编译生成的临时可执行文件删除，如果想保留可执行文件的话可以将这两行代码注释掉
    return 0;
}
