import time
import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots()
ind = np.arange(1, 5)

# show the figure, but do not block
plt.show(block=False)


pm, pc, pn, pk = plt.bar(ind, (10, 10, 14, 14))
pm.set_facecolor('r')
pc.set_facecolor('g')
pn.set_facecolor('b')
pn.set_facecolor('y')
ax.set_xticks(ind)
ax.set_xticklabels(['Optimal', 'FIFO', 'LRU2', 'LRU4'])
ax.set_ylim([0, 16])
ax.set_ylabel('Tempo')
ax.set_title('Page Faults Substituicao de pagina')

start = time.time()
for i in range(200):  # run for a little while
    m, c, n, k = (10, 10, 14, 14)
    
    # update the animated artists
    pm.set_height(m)
    pc.set_height(c)
    pn.set_height(n)
    pk.set_height(k)
    
    # ask the canvas to re-draw itself the next time it
    # has a chance.
    # For most of the GUI backends this adds an event to the queue
    # of the GUI frameworks event loop.
    fig.canvas.draw_idle()
    try:
        # make sure that the GUI framework has a chance to run its event loop
        # and clear any GUI events.  This needs to be in a try/except block
        # because the default implementation of this method is to raise
        # NotImplementedError
        fig.canvas.flush_events()
    except NotImplementedError:
        pass
