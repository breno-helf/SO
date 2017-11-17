from random import randint

END_TIME = 300
START_TIME = 0

total = 40
virtual = 80
s = 8
p = 4
print(str(total) + " " + str(virtual) + " " + str(s) + " " + str(p))

process_num = 10
compact_num = randint(1, 5)

for i in range(compact_num):
    t = randint(START_TIME, END_TIME)
    print(str(t) + " " + "COMPACTAR")

for i in range(process_num):
    t0 = randint(START_TIME, END_TIME)
    tf = randint(t0, END_TIME)
    b  = randint(1, 40)
    nome = "Processo" + str(i)
    acessos = randint(1, 10)
    print(str(t0) + " " + str(tf) + " " + str(b) + " " + nome, end='')
    for j in range(acessos):
        p = randint(0, b - 1)
        t = randint(t0, tf)
        print(" " + str(p) + " " + str(t), end='')
    print("")
    
        
