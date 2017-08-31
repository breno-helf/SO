import sys
import os
import random
import time

n_arquivos_trace = 30
tempo_max = 2
n_processos_por_arquivo = 10
longevidade_do_proc = 5
proporcao_deadline = 2
count = 0
tempo = 0

random.seed(time.time())



if len(sys.argv) < 2:
	print "Modo de uso\n\n"
	print "geradorArquivosTrace <diretorio dos arquivos de trace>\n"
	print "-n\tnumero de arquivos trace\n"
	print "-N\tnumero de processos de cada arquivo de trace"
	print "-p\ttempo maximo de entrada de arquivos"
	print "-l\tquanto tempo um processo pode durar no maximo"
	print "-c\tcomeca a criar arquivo a partir dessa posicao. Ex: -c 2 / primeiro arquivo sera arquivoTrace2.txt"
	print "-d\tproporcao deadline em relacao ao dt do processo"
	print "\n"
	exit(0)
	
directory = sys.argv[1]

# pega os argumentos de entrada
if len(sys.argv) > 2:
	tamanho = len(sys.argv) - 1
	while(tamanho > 1):
		if sys.argv[tamanho - 1] == '-n':
			n_arquivos_trace = sys.argv[tamanho]
			tamanho = tamanho - 2
		if sys.argv[tamanho - 1] == '-p':
			tempo_max = sys.argv[tamanho]
			tamanho = tamanho - 2
		if sys.argv[tamanho - 1] == '-N':
			n_processos_por_arquivo = sys.argv[tamanho]
			tamanho = tamanho - 2
		if sys.argv[tamanho - 1] == '-l':
			longevidade_do_proc = sys.argv[tamanho]
			tamanho = tamanho - 2
		if sys.argv[tamanho - 1] == '-d':
			proporcao_deadline = sys.argv[tamanho]
			tamanho = tamanho - 2
		if sys.argv[tamanho - 1] == '-c':
			count = sys.argv[tamanho]
			tamanho = tamanho - 2

# se nao tem o diretorio, cria
if directory != '-n':
	if not os.path.exists(directory):
		os.makedirs(directory)

# gera os arquivos de trace
for arq_i in range(0, int(n_arquivos_trace)):
	tempo = 1

	if directory == '-n': file = open("arquivoTrace" + str(int(arq_i) + int(count)) + ".txt", "w")
	else: file = open(directory + "/arquivoTrace" + str(int(arq_i) + int(count)) + ".txt", "w")
	for proc_i in range(0, int(n_processos_por_arquivo)):
		tempo = random.uniform(1, float(tempo_max) + 1)
                tempo *= 10.0
                tempo = int(tempo)
                tempo /= 10.0
		# gera dt e deadline aleatorios
		dt = random.uniform(1, float(longevidade_do_proc) + 1)
                dt *= 10.0
                dt = int(dt)
                dt /= 10.0
		deadline = random.uniform(tempo + dt, tempo + dt * float(proporcao_deadline) + 1)
                deadline *= 10.0
                deadline = int(deadline)
                deadline /= 10.0
                
		file.write(str(tempo) + " " + str(dt) + " " + str(deadline) + " processo" + str(proc_i) + "\n")
		
	file.close()
        
