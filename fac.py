import sys
#calculate (n -1) !

result = 1
for i in xrange(1, int(sys.argv[1], 10)):
  result *= i
print result
