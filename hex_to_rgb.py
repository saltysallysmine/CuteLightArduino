from sys import stdin

for line in stdin:
    hex_ = line.rstrip("\n").lstrip("#")
    print(tuple(int(hex_[i:i+2], 16) for i in (0, 2, 4)))


