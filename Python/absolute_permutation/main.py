# https://www.hackerrank.com/challenges/absolute-permutation/problem

# Those two lines make the code 1:1 compatiple with hackerrank
f = open('./input/test_case_9.txt')
input=f.readline


import itertools as it
import sys
sys.setrecursionlimit(15000)


def trivial_absolutePermutation(n, k):
    orig=list(range(1, n+1))
    options=set(range(1, n+1))

    result = []

    for num in orig:
      want = num+k
      if want>n:
        want=num-k
      if want<1:
        return [-1]

      if want in options:
        result.append(want)
        options.remove(want)
      else:
        return [-1]

    return result





def inrange(opt,n):
  return opt>=1 and opt<=n


def sweep(a2opts):

  #find first occurcence of an a with only a single option
  op = -1
  for a, opts in a2opts.items():
    if len(opts)==1:
      op=opts.pop()
      combo={a:op}
      break
  if op==-1:
    return False, None, None
  ###print("  op", op)
  #remove a from dict
  a2opts.pop(a)

  # #loop over the options and remove op everywhere
  # for a, opts in a2opts.items():
  #   if op in opts:
  #     if len(opts)==1:
  #       return False, None, None
  #     a2opts[a].remove(op)
  c1 = op+k
  c2 = op-k
  if c1 in a2opts.keys():
    if op in a2opts[c1]:
      a2opts[c1].remove(op)
    if len(a2opts[c1])==0:
         return False, None, None
  if c2 in a2opts.keys():
    if op in a2opts[c2]:
      a2opts[c2].remove(op)
    if len(a2opts[c2])==0:
      return False, None, None



  return True, a2opts, combo

def absolutePermutation(n, k):

  if k == 0:
    return [i+1 for i in range(n)]

  if (n / k) % 2 !=0:
    return [-1]

  a2opts={a:set([]) for a in range(1, n+1)}

  for a in range(1, n+1):
    if a-k >= 1:
      a2opts[a].add(a-k)
    if a+k <= n:
      a2opts[a].add(a+k)

  ###print("BEFORE SWEEP", a2opts)
  result={i:-1 for i in range(1,n+1)}
  success, a2opts, combo = sweep(a2opts)
  ###print("AFTER  SWEEP", a2opts, result)
  while success:
    result.update(combo)
    success, a2opts, combo = sweep(a2opts)
    ###print("AFTER  SWEEP", a2opts, result)

  if -1 in result.values():
    return [-1]
  return [result[k] for k in sorted(result.keys())]







t = int(input())

# result = absolutePermutation(10, 1)
# print("RESULT:", result )

for t_itr in range(t):
    nk = input().split()

    n = int(nk[0])

    k = int(nk[1])

    result = trivial_absolutePermutation(n, k)
    if result==[-1]:
      print("No trivial solution")
      result = absolutePermutation(n, k)

    print("Result", result)