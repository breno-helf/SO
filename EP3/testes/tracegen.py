from random import randint
from random import shuffle
from random import choice

END_TIME = 300
START_TIME = 0

total = 60
virtual = 120
s = 4
p = 2
print(str(total) + " " + str(virtual) + " " + str(s) + " " + str(p))

process_num = 10
compact_num = randint(1, 4)

v = []

for i in range(compact_num):
    t = randint(START_TIME, END_TIME)
    v.append(str(t) + " " + "COMPACTAR")

for i in range(process_num):
    t0 = randint(START_TIME, END_TIME)
    tf = randint(t0, END_TIME)
    b  = choice([2, 4, 6, 8])
    nome = "Processo" + str(i)
    acessos = randint(1, 10)
    s = (str(t0) + " " + str(tf) + " " + str(b) + " " + nome)
    for j in range(acessos):
        p = randint(0, b - 1)
        t = randint(t0, tf)
        s += (" " + str(p) + " " + str(t))
    v.append(s)
    
shuffle(v)
for s in v:
    print(s)
