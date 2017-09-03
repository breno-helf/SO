import sys
import os

for trace in range(10, 15):    
    for escal in range(1, 4):
        for i in range(1, 3):
            print("Executando teste %d do trace %d com escalonador %d" % (i, trace, escal))
            os.system("./ep1 %d arquivoTrace%d.txt OutTrace%descal%dt%d.txt" % (escal, trace, trace, escal, i) )


os.system("mv OutTrace* PEQ/");

for trace in range(15, 21):    
    for escal in range(1, 4):
        for i in range(1, 3):
            print("Executando teste %d do trace %d com escalonador %d" % (i, trace, escal))
            os.system("./ep1 %d arquivoTrace%d.txt OutTrace%descal%dt%d.txt" % (escal, trace, trace, escal, i) )

os.system("mv OutTrace* GRA/");
