out = open("resultados", 'w')
for trace in range (4, 9):
    out.write("trace %d\n" %trace)
    for escalonador in range (1, 4):
        s1 = ""
        s2 = ""
        out.write("escalonador %d\n" %escalonador)
        for teste in range (1, 31):
            with open("OutTrace%descal%dt%d.txt" %(trace, escalonador, teste), 'r') as f:
                data = f.readlines()
                s1 = s1 + (str(data[len(data) - 2]).rstrip("\n")) + ", "
                s2 = s2 + (str(data[len(data) - 1]).rstrip("\n")) + ", "
        out.write(s1 + "\n")
        out.write(s2 + "\n")
out.close()