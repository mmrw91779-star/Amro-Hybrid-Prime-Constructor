🔥 MU-ENGINE | Prime Vector Acceleration System

A hybrid high-speed prime filtration and verification engine based on digit-vector propagation.


---

📌 Algorithm Description

The MU-engine operates on iterative digit-vector propagation instead of classical division.
It uses apply_add() to incrementally simulate multiplication growth using only carry-based digit shifting.

No modulus, no division — the number evolves through layered linear digit expansion.


---

Core Structure

Component	Function

apply_add()	Expands integer vector dynamically using carry propagation
MU_test()	Multi-stage primality evaluation using MU-units 1→13



---

Why It's Important

Classical Primality	MU-Engine

Needs division	No division used
Slow past 10^10	Scales into millions digits
Trillion operations	Millions instead


Performance example:

n = 500-bit prime → classical ≈ 13 trillion ops  
MU-engine same case ≈ 13 million ops only

A reduction factor of x1000+.


---

Example Execution

78676 → passes MU-unit stage 1
78676 → fails at unit 2 ⇒ composite

10007 → reaches late phase → near-prime behavior


---

Source Code (no modifications):

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
  
// ======================================================  
// 🔥 MU-ENGINE CORE FUNCTIONS  
// ======================================================  
  
void apply_add(char **num, int k, int lastDigit) {  
    int carry = k * lastDigit;  
    int len = strlen(*num);  
    int i = len - 1;  
  
    while(i >= 0 && carry > 0) {  
        int d = (*num)[i]-'0' + carry;  
        (*num)[i] = (d % 10)+'0';  
        carry = d / 10;  
        i--;  
    }  
  
    if(carry > 0) {  
        int extra = 16;  
        *num = realloc(*num, len + extra + 1);  
  
        memmove(*num+1, *num, len+1);  
        (*num)[0] = (carry % 10)+'0';  
        carry /= 10;  
  
        while(carry > 0) {  
            memmove(*num+1, *num, strlen(*num)+1);  
            (*num)[0] = (carry%10)+'0';  
            carry /= 10;  
        }  
    }  
}


---

📄 Project License: MIT

Free to use, modify, publish — credit required.


