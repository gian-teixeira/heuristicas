# Solver
 
## Methods and arguments

- **LS** : local search
    - iteration count

- **ILS** : iterated local search
    - shaking count
    - inner local search iteration count

## Build and execute

```bash
make
./tsp 'method' 'args...' < 'input'
```

*Example*: 
```
./tsp ILS 10 1000 < data/tsp_5
```

> Giancarlo Oliveira Teixeira
>
> *Heurísticas e Metaheurísticas - UFSJ 2024.1*