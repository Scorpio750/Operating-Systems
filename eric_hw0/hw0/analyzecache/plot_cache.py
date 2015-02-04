import matplotlib.pyplot as plt
import sys
import math

if(len(sys.argv) != 2):
	print "python plot_cache.py <infile>"
	raise Exception("Invalid number of arguments")

infile = open(str(sys.argv[1]), "r")

x = list()
y = list()

for line in infile:
	line = line.split()
	num = int(line[0])
	num = math.log(num, 2)
	num = str(num)
	print num
	x.append(num)
	y.append(line[1])
plt.scatter(x,y)
plt.show()
