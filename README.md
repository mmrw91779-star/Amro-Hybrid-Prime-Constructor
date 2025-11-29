# 🔥 Amro Hybrid Constructive Prime Constructor (AHPC)

A new hybrid-engine prime construction system by **Amro Abuhron (عمرو أبوهرون)**  
Designed to generate and filter prime candidates at ultra-high speed using behavioral
digit construction instead of expensive division.

---

## 🚀 Key Idea

🔸 Phase 1 — Construct odd prime candidates  
🔸 Phase 2 — Apply Multi-Constructor Filtering (O(k))  
🔸 Phase 3 — Deep validation (Miller-Rabin + internal sieve)

Any number rejected by any constructor stops immediately → composite instantly.

---

## 🔥 Current Implementation — V8 (2025)

| Feature | Status |
|---|---|
| Behavioral Constructors | ✔ 22 Rules (P=3 → 113) |
| String-based Engine | ✔ Supports contraction/expansion |
| Memory-Safe MU | ✔ Returns final reduced integer |
| Leading-zero removal | ✔ Eliminated successfully |
| Composite rejection | ✔ Instant fail trigger |

---

## 🧠 Compile & Run

```bash
gcc -O2 amro_prime_v8.c -o amro && ./amro
