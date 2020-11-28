# https://www.hackerrank.com/challenges/validating-credit-card-number/problem

# Those two lines make the code 1:1 compatiple with hackerrank
f = open('./input/test_case_5.txt')
input=f.readline


import re

def validate(cnum):
    if re.match('\d{5}-', cnum)!=None:
        return False
    if re.match('-\d{5}', cnum)!=None:
        return False
    if len(re.findall('--', cnum)) != 0:
        return False
    cnum=cnum.replace('-','')
    if cnum[0] not in ['4', '5', '6']:
        return False
    if len(cnum)!=16:
        return False
    for i in ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']:
        if i*4 in cnum:
            return False
    if re.match('^\d+$', cnum)==None:
        return False
    return True


N = int(input())

for _ in range(N):
    cnum=input().rstrip()
    if validate(cnum):
        print("Valid")
    else:
        print("Invalid")