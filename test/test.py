import subprocess
import time
import sys

TARGET = '../solver'

def run(command, input_path):
    process = subprocess.Popen(command, 
        stdin = subprocess.PIPE,
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        text = True)
    with open(input_path, 'r') as input_file:
        content = input_file.read()
        process.stdin.write(content)
        #process.stdin.close()
    begin = time.time()
    output,error = process.communicate()
    return (output, time.time()-begin)

if __name__ == "__main__":
    epochs = int(sys.argv[2])
    # for a in range(10,100,10):
    #     a /= 100
    for i in [1,3,5,7,9,10,30,50,70,90,100,500,1000]:
        cmd = [TARGET, 'KNAPSACK', '1', 'GRASP', str(0.8), str(i)]
        output_name = f"output/{sys.argv[1]}[{'_'.join(cmd[1:])}]"
        
        with open(output_name, 'w+') as file:
            result = run(cmd, 'data/'+sys.argv[1])
            for i in range(epochs):
                result = [str(i).strip() for i in result]
                file.write(','.join(result)+'\n')
                time.sleep(1)