from pulp import LpProblem, LpMaximize, LpVariable, lpSum
import sys

# Ler ficheiro de input
with open(sys.argv[1], 'r') as f:
    lines = f.read().splitlines()

capacity = int(lines[0].split()[1])
values = list(map(int, lines[1].split()[1:]))
weights = list(map(int, lines[2].split()[1:]))

n = len(values)

# Criar modelo
model = LpProblem("Knapsack", LpMaximize)

# Variáveis binárias (0 ou 1)
x = [LpVariable(f"x{i}", cat='Binary') for i in range(n)]

# Função objetivo
model += lpSum(values[i] * x[i] for i in range(n))

# Restrição de capacidade
model += lpSum(weights[i] * x[i] for i in range(n)) <= capacity

# Resolver
model.solve()

# Escrever resultado
with open(sys.argv[2], 'w') as f:
    f.write("selected_items " + ' '.join(str(int(x[i].varValue)) for i in range(n)) + "\n")
    f.write("total_value " + str(int(model.objective.value())) + "\n")