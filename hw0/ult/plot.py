import matplotlib.pyplot as plot_t
import sys
import math

interval_position = 2
time_position = 6


filename = str(sys.argv[1])
file = open(filename, "r")

x_coord = list()
y_coord = list()

for line in file:
	string_list = line.split()
	x_coord.append(string_list[interval_position])
	y_coord.append(string_list[time_position])
plot_t.scatter(x_coord, y_coord)
plot_t.show()
