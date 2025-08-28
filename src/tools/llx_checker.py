import os

while True:
    os.system("python3 data.py > in")
    os.system('/usr/bin/time -f "test time = %e" ./test < in > out')
    os.system('/usr/bin/time -f "std time = %e" ./std < in > ans')
    if os.system("diff out ans"):
        print("WA")
        exit(1)
    print("AC")
        