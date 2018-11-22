import subprocess
import time
import sys
import math

rngs = ['mt', 'rnlx0', 'r250']
# samples = 10**6


def runProcess(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    while(True):
        retcode = p.poll()  # returns None while subprocess is running
        line = p.stdout.readline()
        yield line
        if(retcode is not None):
            break


csv_text = 'RNG,SamplesPower,Energy,EnergyDev,Magnetization,Heat,HeatDev,Temperature\n'
for samples in [10**j for j in range(5, 6)]:
    for i in rngs:
        for line in runProcess(['./wolf_sim', str(i), str(samples), 'point']):
            text = line.decode().split('\n')[0]
            if(len(line) > 0):
                csv_text += (i+','+str(int(math.log10(samples)))+','+text+'\n')

# print(csv_text[:-1])

with open(f'Results/{time.time()}.csv', 'w') as file:
    file.write(csv_text)
