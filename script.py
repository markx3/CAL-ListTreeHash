import subprocess

p = subprocess.Popen('make all', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
for line in p.stdout.readlines():
    print (line)
retval = p.wait()

for tipo in ["list", "tree", "hash"]:
	for i in range (1, 6):
		e = "./" + tipo + "/exec entrada-" + str(i) + ".txt"
		p = subprocess.Popen(e, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
		for line in p.stdout.readlines():
	    		print (line)
		retval = p.wait()
