"""
Graph generator
"""
import numpy as np
import matplotlib.pyplot as plt
import sys
import pylab

Y = (.5, .5, .5)
N = 3
A = [0, 0, 0]
B = [0, 0, 0]

for E in range(1, 4):    
    for i in range(4, 9):
        for t in range(1, 3):
            F = open("TESTES_LUCAS/OutTrace%descal%dt%d.txt" % (i, E, t))
            V = []
            for line in F:
                V.append(line)
            A[E - 1] += float(V[-2])
            F = open("TESTES_LUCAS/OutTrace%descal%dt%d.txt" % (i, E, t))
            V = []
            for line in F:
                V.append(line)
            B[E - 1] += float(V[-2])

M = 0
for E in range(1, 4):
    A[E - 1] /= (2 * 5)
    B[E - 1] /= (2 * 5)
    M = max(A[E - 1], B[E - 1])
A = tuple(A)
B = tuple(B)

ind = np.arange(N)  # the x locations for the groups
width = 0.30       # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(ind, A, width, color='r', yerr = Y)

rects2 = ax.bar(ind + width, B, width, color='y', yerr = Y)

# add some text for labels, title and axes ticks
ax.set_ylabel('Trocas de contexto')
#ax.set_ylabel('Deadlines perdidos')
ax.set_title('Quantidade de trocas de contexto - Traces Medios')
#ax.set_title('Quantidade de deadlines perdidos - Traces Medios')
ax.set_xticks(ind + width / 2)
ax.set_xticklabels(('Shortest', 'Robin', 'Priority'))
pylab.ylim([0, 530])
plt.legend((rects1[0], rects2[0]), ('A', 'B'))


def autolabel(rects):
    """
    Attach a text label above each bar displaying its height
    """
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., 1.05*height,
                '%.1lf' % float(height),
                ha='center', va='bottom')
    
autolabel(rects1)
autolabel(rects2)

plt.show()
