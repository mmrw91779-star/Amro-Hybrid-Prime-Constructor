# MU System – Modularity Unit Prime Constructor
### Version 1.5 — Core Specification  
Part of the A-HPC (Amro Hybrid Prime Constructor) Architecture

---

## 1. Introduction

The **MU System (Modularity Unit)** represents the classical layer of the  
Amro-Prime framework.  
It provides a deterministic way to reduce a large number *N* into a smaller number  
*N′* using a structural rule of the form:

```
N′ = a ± k·b
```

Where:  
- **a** = the number after removing the last digit  
- **b** = the last digit  
- **k** = the constructor coefficient  
- The sign (±) is determined by the modular relation of `10k mod P`

The MU system was the original engine for filtering candidates before the newer  
O(L) linear sieve was introduced.

---

## 2. Mathematical Foundation of MU

The core idea relies on finding a value **k** such that:

```
10k ≡ ±1 (mod P)
```

Where **P** is a prime (called “Constructor Prime”).

Two possible modes arise:

### 2.1 Add Mode
If:

```
10k ≡ -1 (mod P)
```

Rule becomes:

```
N′ = a + k·b
```

### 2.2 Subtract Mode
If:

```
10k ≡ +1 (mod P)
```

Rule becomes:

```
N′ = a − k·b
```

Repeating the transformation shrinks *N* until it reaches a small integer,  
allowing primality rejection based on divisibility by *P*.

---

## 3. Example (P = 7)

Solve:

```
10k ≡ -1 (mod 7)
```

We have:

```
20 = 21 - 1
```

Thus:

```
10 × 2 ≡ -1 (mod 7)
k = 2
Mode = Add Mode
Rule = N′ = a + 2·b
```

### Example for N = 128

```
128 → a=12 , b=8 → 12 + 2×8 = 28
 28 → a=2  , b=8 → 2 + 2×8 = 18
 18 → a=1  , b=8 → 1 + 16 = 17
 17 → a=1  , b=7 → 1 + 14 = 15
```

Since **15 is divisible by 3 and 5**,  
128 is composite under MU(7).

---

## 4. Why MU Works

MU eliminates the need for classical division by *P*.  
Instead, the number is collapsed digit by digit using small integer arithmetic.

This avoids large-number multiplication, but:

- MU is **not O(L)**
- And becomes slow for very large input

Therefore, MU was replaced by the **O(L) linear sieve** in A-HPC V3.

---

## 5. MU Algorithm (Pseudo-Code)

```
function MU_Test(number, P, k, mode):

    while length(number) > 2:
        a = number / 10
        b = last_digit(number)

        if mode == ADD:
            number = a + k*b
        else:
            number = a - k*b

        remove_leading_zeros(number)

        if number < 0:
            return NEGATIVE_RESULT

    if number % P == 0:
        return COMPOSITE

    return CANDIDATE
```

---

## 6. Problems in Classical MU (Why It Was Replaced)

The MU system has structural issues:

### 6.1 ❌ Negative results  
Subtract-mode may produce negative numbers during contraction.

### 6.2 ❌ Zero accumulation  
Removing leading zeros requires extra cleanup.

### 6.3 ❌ Non-linear cost  
String rebuilding and memory contraction → can reach **O(L²)**.

### 6.4 ❌ Limited analytical spectrum  
Some primes generate weak constructor dynamics.

Because of these issues MU was deprecated and replaced by:

### ✔ A-HPC V3  
Single-Pass Linear Modular Sieve  
**O(L)** deterministic complexity.

---

## 7. MU Inside A-HPC (Legacy Layer)

MU is not removed; it is preserved as:

```
Layer 0 — Historical Constructor Structure
```

It provides:

- Conceptual foundation of constructor rules  
- The origin of k-coefficients  
- Validation of the modern sieve's prime selection

---

## 8. Files Included

```
MU-README.md       ← (this file)
mu_core.c          ← classical MU implementation
mu_rules.json      ← k-constructors table
mu_examples.txt    ← contraction examples
```

---

## 9. License

This component is part of the A-HPC project  
and released under the **MIT License**.
