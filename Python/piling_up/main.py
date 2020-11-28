# https://www.hackerrank.com/challenges/piling-up/problem

# Those two lines make the code 1:1 compatiple with hackerrank
f = open('./input/test_case_1.txt')
input=f.readline


def check_sequence(l):
    L = len(l)
    pl = 0
    pr = L - 1
    top = float('Inf')

    while pl < pr:
        if l[pl] > top or l[pr] > top:
            return False
        # pick the bigger one
        if l[pl] > l[pr]:
            top = l[pl]
            pl += 1
        else:
            top = l[pr]
            pr -= 1

    if pl == pr:
        return l[pl] <= top
    return True


T = int(input())
for _ in range(T):
    n = input()
    l = [int(i) for i in input().rstrip().split(' ')]

    result = check_sequence(l)
    if result:
        print("Yes")
    else:
        print("No")



'#', ' ', 'i', '#'
' ', '@', '#', 'U'