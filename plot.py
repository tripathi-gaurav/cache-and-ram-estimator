import matplotlib.pyplot as pyplot
import csv

x = []
y = []

with open('cache.dat','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for line in lines:
        x.append(float(line[0]))
        y.append(float(line[1]))

pyplot.plot(x,y, linestyle='-', marker='o', label='cache.dat')
pyplot.xlabel('Size in KiB')
pyplot.ylabel('Time in seconds')
pyplot.title('Time vs Cache size')
pyplot.legend()
fig = pyplot.gcf()
fig.canvas.set_window_title("HW5")
pyplot.show()
