# https://www.hackerrank.com/challenges/matrix-script/problem

# Those two lines make the code 1:1 compatiple with hackerrank
f = open('./input/test_case_0.txt')
input=f.readline


import re

first_multiple_input = input().rstrip().split()
n = int(first_multiple_input[0])
m = int(first_multiple_input[1])
matrix = []

for _ in range(n):
    matrix_item = input()
    matrix.append(matrix_item)

maxlen = max([ len(i) for i in matrix])
test2 = [ [ str(w+' ')[i] for w in matrix] for i in range(maxlen)]
test3 = ["".join(i) for i in test2]
test4 = "".join(test3)

result = ''.join(re.findall('^[^\w]*',test4))+' '.join(re.findall('\w+',test4))+''.join(re.findall('[^\w]*$',test4))
print(result)