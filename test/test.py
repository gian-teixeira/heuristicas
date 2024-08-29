import subprocess
import time
import sys

TARGET = '../solver'

def run(command):
    begin = time.time()
    result = subprocess.Popen(command, 
        stdin = subprocess.PIPE,
        stdout = subprocess.PIPE,
        text = True)
    return (result.stdout, time.time()-begin)

if __name__ == "__main__":
    input_name = 'data/'+sys.argv[1]
    epochs = int(sys.argv[2])
    cmd = [TARGET, 'TSP', '0', 'LS', '<', input_name]
    output_name = f"output/'{sys.argv[1]}[{'_'.join(cmd[1:-2])}]"

    with open(output_name, 'w+') as file:
        result = run(cmd)
        for i in range(epochs):
            file.write(','.join(cmd)+'\n')