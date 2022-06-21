from sys import stdin
input = stdin.readline

if __name__ == '__main__':
    while True:
        line = input().strip().lower()
        if line == "#":
            break
        c, st = line[0], line[1:].strip()
        print(f"{c} {st.count(c)}")
