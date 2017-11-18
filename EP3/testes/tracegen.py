from random import randint
from random import shuffle

END_TIME = 300
START_TIME = 0

total = 40
virtual = 80
s = 8
p = 4
print(str(total) + " " + str(virtual) + " " + str(s) + " " + str(p))

process_num = 10
compact_num = randint(1, 5)

v = []

for i in range(compact_num):
    t = randint(START_TIME, END_TIME)
    v.append(str(t) + " " + "COMPACTAR")

for i in range(process_num):
    t0 = randint(START_TIME, END_TIME)
    tf = randint(t0, END_TIME)
    b  = randint(1, 40)
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
