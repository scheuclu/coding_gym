# https://www.hackerrank.com/challenges/matrix-script/problem

# Those two lines make the code 1:1 compatiple with hackerrank
f = open('./input/test_case_0.txt')
input=f.readline


import sys
import os
from functools import lru_cache


def get_possible_moves(config):
  inputs=[]
  for i, char in enumerate(config):
    if char=='I':
      # Throw a single pin over
      inputs.append(' '+config[:i]+'X'+config[i+1:])
      # Throw 2 pins over if possible
      if i<len(config)-1 and config[i+1]=='I':
        inputs.append(' '+config[:i]+'XX'+config[i+2:])
  return inputs


@lru_cache(maxsize=None)
def isWinning(config, mymove, doprint=False):
  #print(config, mymove)

  # base cases
  if config.count('I')==1:
    return mymove #I win if its my turn
  if config.count('I')==2:
    nexttoeachother=config.rfind('I')==config.find('I')+1
    return nexttoeachother and mymove

  # Make all possible moves
  inputs=get_possible_moves(config)
  results = [isWinning(input, not mymove) for input in inputs]

  if doprint:
    for input in inputs:
      print(input,mymove, isWinning(input, not mymove) )

  return True in results and mymove



result = isWinning('IIIII', True, True)
print("RESULT", result)

# if __name__ == '__main__':
#   fptr = open(os.environ['OUTPUT_PATH'], 'w')
#
#   t = int(input())
#
#   for t_itr in range(t):
#     n = int(input())
#
#     config = input()
#
#     result = isWinning(n, config)
#
#     print("RESULT", result)
