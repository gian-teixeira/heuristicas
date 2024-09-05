from sys import argv
from os import listdir

for filename in listdir(argv[1]):
    output = open(f"{argv[1]}/parsed_{filename}.csv", 'w+')
    result_sum = 0
    time_sum = 0

    with open(f"{argv[1]}/{filename}") as file:
        if '.csv' in filename:
            continue

        output.write('It.,Resultado,Tempo\n')
        for it,line in enumerate(file):
            result,time = line.split(',')
            result = float(result)
            time = float(time)
            output.write(f"{it+1},{result:.3f},{time:.3f}\n")
            result_sum += result
            time_sum += time


    result_sum /= 10
    time_sum /= 10

    output.write(f"Média,{result_sum:.3f},{time_sum:.3f}\n")