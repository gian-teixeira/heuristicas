from collections import defaultdict
import sys
import os

rows = []
columns = defaultdict(lambda : [])
TARGET = sys.argv[1]

for filename in os.listdir(TARGET):
    if '.csv' in filename:
        continue

    it = filename
    for c in ['_',']']: it = it.replace(c, ' ')
    it = int(it.split()[-1])

    result_mean = 0
    time_mean = 0

    with open(f'{TARGET}/{filename}', 'r') as file:
        print(f'{TARGET}/{filename}')
        line_count = 0
        for line in file:
            result, time = line.split(',')
            result_mean += float(result)
            time_mean += float(time)
            line_count += 1
            columns[it].append(result)
        result_mean /= line_count
        time_mean /= line_count
    
    rows.append((it, time_mean, result_mean))
    columns[it].append(result_mean)

rows.sort()
result_table = open(f"{TARGET}/result.csv", 'w+')
time_table = open(f"{TARGET}/time.csv", 'w+')
all = open(f"{TARGET}/all.csv", 'w+')

time_table.write(f"iter,time\n")
result_table.write(f"iter,result\n")
for row in rows:
    time_table.write(f"{row[0]},{row[1]:.3f}\n")
    result_table.write(f"{row[0]},{row[2]:.3f}\n")

repeat = len(columns[1])
print(repeat)

all.write('It.,'+','.join(map(str,range(1,repeat)))+',Média\n')
for it,results in sorted(columns.items()):
    results = map(lambda x : str(round(float(x),3)), results)
    all.write(f'{it},')
    all.write(','.join(results))
    all.write('\n')

result_table.close()
time_table.close()