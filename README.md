# Practical Assignment 01 — Brute Force & Backtracking in C++

**Course:** Analysis and Design of Algorithms
**University:** EAFIT
**Language:** C++17 | **Compiler:** `g++ -O2 -std=gnu++17`
**IDE:** Visual Studio Code

---

## Overview

This project implements and compares two fundamental algorithm design paradigms through two classic problems:

| Exercise | Problem | Paradigm |
|---|---|---|
| `EjercicioFuerzaBruta` | Permutations with restrictions | Brute Force (`next_permutation`) |
| `EjercicioBacktracking` | Graph coloring with k colors | Backtracking + Brute Force (verification) |


## How to Compile and Run

### Exercise 1 — Brute Force Permutations

```powershell
cd EjercicioFuerzaBruta
g++ -O2 -std=gnu++17 -o EjercicioFuerzaBruta main.cpp
./EjercicioFuerzaBruta
```

**Menu:**
```
1. Enter a custom set
2. Run timing experiment (n = 1..11)
```

**Sample — Option 1 (n=4, set={1,2,3,4}):**
```
=== VALID PERMUTATIONS ===
[ 1 2 3 4 ]  [ 1 2 4 3 ]  [ 1 3 2 4 ]  ...

Total permutations generated : 24
Total valid permutations     : 12
Ratio valid/total            : 50%
Execution time               : 0.013 ms
```

**Sample — Option 2 (timing experiment):**

| n | n! | Valid | Time (ms) |
|---|---|---|---|
| 8 | 40,320 | 2,880 | ~2.7 |
| 9 | 362,880 | 14,400 | ~22 |
| 10 | 3,628,800 | 86,400 | ~195 |
| 11 | 39,916,800 | 518,400 | ~2,135 practical limit |

Timing table saved to `results/tiempos_ej1.csv`.

---

### Exercise 2 — Graph Coloring (Backtracking + Brute Force)

```powershell
cd EjercicioBacktracking
g++ -O2 -std=gnu++17 -o EjercicioBacktracking main.cpp
./EjercicioBacktracking
```

**Menu:**
```
1. Enter graph manually
2. Example 1 - Cycle C4       (n=4, k=3)
3. Example 2 - Complete K4    (n=4, k=4)
4. Example 3 - Bipartite K2,3 (n=5, k=2)
```

**Sample — Example 1 (C4, k=3):**
```
First solution (Backtracking):
  color[0]=1  color[1]=2  color[2]=1  color[3]=2

Metodo                      Coloraciones  Nodos    Tiempo (ms)
------------------------------------------------------------
Backtracking (poda)         18            40       0.006
Fuerza Bruta (k^n)          18            81       0.013

[OK] Both approaches agree: 18 valid colorings.
Pruning reduction: 50.6%
```

Results saved to `results/resultado_ej2_nX_kY.txt`.

---

## Complexity Summary

| Exercise | Approach | Time | Space |
|---|---|---|---|
| 1 | Brute Force (permutations) | O(n! * n) | O(n) |
| 2 | Backtracking (graph coloring) | O(k^n * n) worst case | O(n) |
| 2 | Brute Force (graph coloring) | O(k^n * n^2) | O(n) |

---

## Key Concepts

**Why is Exercise 1 Brute Force and not Backtracking?**
The restriction `P[i] <= 2 * P[i+1]` is applied *after* generating each complete permutation.
No branch is pruned early — the full space of n! permutations is always explored.

**How does Backtracking reduce nodes explored?**
In Exercise 2, colors are assigned vertex by vertex. The moment a color conflicts with an adjacent vertex, the entire subtree under that partial assignment is skipped.
This produced a 50-75% reduction in nodes explored across the test graphs.

## About

Individual assignment — Analysis and Design of Algorithms, EAFIT 2025-1.