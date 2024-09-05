#!/bin/bash

declare -a iter=(1 3 5 7 9 10 30 50 70 90 100 500 1000)

execute_programa() {
    local begin=$(date +%s.%N)
    local result=$(./solver TSP 1 VNS < data/tsp_51 2>&1)

    awk \
        -v result=$result \
        -v t1=$(date +%s.%N) \
        -v t0=$begin \
        'BEGIN { printf "%.2f,%.3f\n", result, t1 - t0 }'
}

for i in ${iter[@]}; do
    execute_programa
done