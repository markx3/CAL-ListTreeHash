import subprocess

for tipo in ["list", "hash", "tree"]:
    for i in range(1,6):
        e = "diff -w -u " + tipo + "_saidaentrada-" + str(i) + ".txt" + " saida/saida-" +str(i) + ".txt"
        print(e)
        p = subprocess.Popen(e, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        for line in p.stdout.readlines():
            print (line)
            retval = p.wait()
        print("Pressione enter p/ continuar.")
        raw_input()
