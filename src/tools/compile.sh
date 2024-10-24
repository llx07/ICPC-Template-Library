g++ X.cpp -Wall -O2 -fsanitize=undefined -fsanitize=address X
# -fsanitize=undefined: 检测未定义行为
# -fsanitize=address: 检测内存溢出